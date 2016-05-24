// Fintime Queries in a distributed setting
// jose.cambronero@cs.nyu.edu
// Queries in .qpar are executed using our parallel q library
// Queries in .qser are executed centrally from a master process
// (note that the latter still use worker processes, but only implicitly)

\l parallel.q
// Initialization
masters:hsym `$"localhost:",/:string 7080+til 3;
workers:hsym `$"localhost:",/:string 7090+til 30;
workers:(count[workers] div count masters) cut workers;
.aq.par.supermaster.init[masters;workers];

// load db everywhere
.aq.par.supermaster.onAll[(system;"l sampledb")];
// some global definitions
globs:{
  .aq.par.master.define[`getMonth;{1 + (`month$x) mod 12}];
  .aq.par.master.define[`getYear;{`long$`year$x}];
  .aq.par.master.define[`firstDateOfYear;{`date$`month$d-30*-1+getMonth d:`date$`month$x}];
  .aq.par.master.define[`getWeek;{1 + floor (x - firstDateOfYear x)%7}];
  // Map partitions to workers
  .aq.par.master.define[`.aq.part.map;.aq.par.master.mapPartitions[]];
  };  
{x[]} peach (count .z.pd[])#globs;
 


/
********* QUERY 0 ****************
	Get the closing price of a set of 10 stocks for a 10-year period and group into 
  weekly, monthly and yearly aggregates. For each aggregate period determine the low, 
  high and average closing price value. The output should be sorted by id and trade date.
\
.qpar.q0.query:{
  // perform preliminary selections and store locally in each worker
  { `t1 set select Id, TradeDate, ClosePrice from price 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]],Id in stock10, 
    TradeDate >= startYear10,TradeDate <= startYear10 + 365 * 10
   } peach .z.pd[];
   
   // map reduce to calculate aggregates 
   map:{
       raze {[x;y;z] 
       select low:min ClosePrice, high:max ClosePrice, 
       sCp:sum ClosePrice, cCp:sum not null ClosePrice 
       by Id, bucket:y TradeDate, name:z from x
       }[`t1;;]'[(getWeek;getMonth;getYear);`weekly`monthly`yearly]
    };
   reduce:{[x;y] 
     kx:key x; gety:y[kx]; 
     adjusted:update low:low^low&gety[`low], high:high^high|gety[`high], 
              sCp:sCp^sCp+gety[`sCp], cCp:cCp^cCp+gety[`cCp] from x;
     y upsert adjusted
     };
    result:update mean:sCp%cCp from .aq.par.master.mapreduce[map;reduce;3];

    // remove temporary columns and sort
   `Id`name`bucket xasc delete sCp,cCp from result
  };
.qpar.q0.callback:{`q0result set x};

.qser.q0.query:{
	data:select Id, TradeDate, ClosePrice from price where Id in stock10, 
      TradeDate >= startYear10, TradeDate <= startYear10 + 365 * 10;
	`Id`name`bucket xasc (upsert/)
	 {[x;y;z] 
		0!select low:min ClosePrice, high:max ClosePrice, mean:avg ClosePrice 
		by Id, bucket:y TradeDate, name:z from x
		}[data;;]'[(getWeek;getMonth;getYear);`weekly`monthly`yearly]
	};
.qser.q0.callback:{`q0ref set x};  


/
********* QUERY 1 ****************
Adjust all prices and volumes (prices are multiplied by the split factor and volumes 
are divided by the split factor) for a set of 1000 stocks to reflect the split events 
during a specified 300 day period, assuming that events occur before the first trade of 
the split date. These are called split-adjusted prices and volumes.
\
.qpar.q1.query:{
   // select appropriate price data and store
   {
     `pxdata set select from price 
     where month in .aq.part.map[.aq.par.worker.getSelfName[]], 
     Id in stock1000, TradeDate >= start300Days, 
     TradeDate <= start300Days + 300
   } peach .z.pd[];
  
   // select appropriate split data and store
   {
     `splitdata set select from split 
     where month in .aq.part.map[.aq.par.worker.getSelfName[]], 
     Id in stock1000, SplitDate >= start300Days
   } peach .z.pd[];
  
   // join price and split data in distributed fashion
   .aq.par.master.join[ej;`Id;`pxdata;`splitdata;`adjdata];
   // our join guarantees that we are effectively partitioned by the first
   // column in our join
   {
     `adjdata set select adjFactor:prd SplitFactor by Id, TradeDate from adjdata 
     where TradeDate < SplitDate
   } peach .z.pd[];
   
   // join price and adjustment data and calculate final result
   .aq.par.master.join[lj;`Id`TradeDate;`pxdata;`adjdata;`adjdata];
    0!`Id`TradeDate xasc raze {
      select Id, TradeDate, HighPrice:HighPrice*1^adjFactor, 
      LowPrice:LowPrice*1^adjFactor, ClosePrice:ClosePrice*1^adjFactor,
      OpenPrice:OpenPrice*1^adjFactor,Volume:Volume%1^adjFactor 
      from adjdata 
      } peach .z.pd[]
  };
.qpar.q1.callback:{`q1result set x}; 
 
.qser.q1.query:{
 	pxdata:select from price where Id in stock1000, 
        TradeDate >= start300Days, TradeDate <= start300Days + 300;
 	splitdata:select from split where Id in stock1000, SplitDate >= start300Days;
   adjdata:select adjFactor:prd SplitFactor by Id, TradeDate 
           from ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
     0!`Id`TradeDate xasc select Id, TradeDate, HighPrice:HighPrice*1^adjFactor, 
       LowPrice:LowPrice*1^adjFactor, ClosePrice:ClosePrice*1^adjFactor, 
       OpenPrice:OpenPrice*1^adjFactor, Volume:Volume%1^adjFactor 
       from pxdata lj `Id`TradeDate xkey adjdata
 	};
.qser.q1.callback:{`q1ref set x}; 


/
********* QUERY 2 ****************
For each stock in a specified list of 1000 stocks, 
find the differences between the daily high and daily low on the day 
of each split event during a specified period.
\
.qpar.q2.query:{
  // select relevant price data and store in processes
	{
    `pxdata set select Id, TradeDate, HighPrice, LowPrice from price 
      where month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in stock1000, 
      TradeDate within (startPeriod;endPeriod)
  } peach .z.pd[];

  // select relevant split data and store in processes 
	{
    `splitdata set select Id, TradeDate:SplitDate, SplitFactor from split 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in stock1000, 
    SplitDate within (startPeriod;endPeriod)
  } peach .z.pd[];
  
  // reference join price and split data
  .aq.par.master.referenceJoin[ej;`Id`TradeDate;`pxdata;`splitdata;`joined];
  
  `Id`TradeDate xasc raze { select Id, TradeDate, MaxDiff:HighPrice - LowPrice from joined } peach .z.pd[]
 };
.qpar.q2.callback:{`q2result set x};


.qser.q2.query:{
	pxdata:select Id, TradeDate, HighPrice, LowPrice from price where Id in stock1000, 
		TradeDate within (startPeriod;endPeriod);
	splitdata:select Id, TradeDate:SplitDate, SplitFactor from split where Id in stock1000, 
		SplitDate within (startPeriod;endPeriod);
	select Id, TradeDate, MaxDiff:HighPrice - LowPrice from 
    `Id`TradeDate xasc ej[`Id`TradeDate;pxdata;splitdata]
	};
.qser.q2.callback:{`q2ref set x}; 


/
********* QUERY 3 + 4 ****************
Calculate the value of the S&P500 and Russell 2000 index for a specified day 
using unadjusted prices and the index composition of the 2 indexes (see appendix 
for spec) on the specified day
\

// in reality it would suffice to run these 2 queries as the serial versions
// and simply add the call to be done with peach, realizing that
// given that data is partitioned by month, only 1 process can contain a specific
// trade date. However, this of course implies that we have to reason about the 
// relationship between TradeDate and the partitioning (which might not be possible
// in the general case, where we just know the type of the column and nothing about
// semantics). So this represents the most general case, where we blindly apply map-reduce

.qpar.q3.query:{
 map:{
   select s:sum ClosePrice, c:count i from price 
   where month in .aq.part.map[.aq.par.worker.getSelfName[]], 
   Id in SP500, TradeDate = startPeriod
   };
 reduce:{[x;y] update s:s+0^y[0;`s], c:c+0^y[0;`c] from x};
 select avg_close_price:s%c from .aq.par.master.mapreduce[map;reduce;2]
 };
.qpar.q3.callback:{`q3result set x};

.qser.q3.query:{
  select avg_close_price:avg ClosePrice from price 
  where Id in SP500, TradeDate = startPeriod
  };
.qser.q3.callback:{`q3ref set x}; 


.qpar.q4.query:{
 map:{
   select s:sum ClosePrice, c:count i from price 
   where month in .aq.part.map[.aq.par.worker.getSelfName[]], 
   Id in Russell2000, TradeDate = startPeriod
   };
 reduce:{[x;y] update s:s+0^y[0;`s], c:c+0^y[0;`c] from x};
 select avg_close_price:s%c from .aq.par.master.mapreduce[map;reduce;2]
 };
.qpar.q4.callback:{`q4result set x};


.qser.q4.query:{
	select avg_close_price:avg ClosePrice from price 
  where Id in Russell2000, TradeDate = startPeriod
 };
.qser.q4.callback:{`q4ref set x}; 


/
********* QUERY 5 ****************
Find the 21-day and 5-day moving average price for a specified list of 1000 stocks 
during a 6-month period. (Use split adjusted prices)
\

.qpar.q5.query:{
  // perform necessary price data selections
	{
    `pxdata set select Id, TradeDate, ClosePrice from price 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]],
    Id in stock1000, TradeDate >= start6Mo,TradeDate < start6Mo + 31 * 6
  } peach .z.pd[];
  
  // perform necessary split data selections
  {
    `splitdata set select Id, SplitDate, SplitFactor from split 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]],
    Id in stock1000, SplitDate >= start6Mo 
  } peach .z.pd[];
    
  // join price data and split data to have adjustment dta  
  .aq.par.master.join[ej;`Id;`pxdata;`splitdata;`splitadj];
  
  // joining by Id means all instances of Id=x are in a given process
  // (effectively partitioning by Id), so we can just run the group-by query
  // in each process
  {
    `splitadj set 0!select first ClosePrice*prd SplitFactor by Id, TradeDate from splitadj 
    where TradeDate < SplitDate
  } peach .z.pd[];
  
  // pxdata is not grouped the same way, so we need to execute distributed join
  .aq.par.master.join[lj;`Id`TradeDate;`pxdata;`splitadj;`joined];
  
  // data is already partitioned by id (due to prior join), now just group within each process
  {`joined set select TradeDate, ClosePrice by Id from joined } peach .z.pd[];
  
  // sort columns in grouped table 
  {
    `joined set update TradeDate:TradeDate@'ix, ClosePrice:ClosePrice@'ix from 
      update ix:iasc each TradeDate from joined 
  } peach .z.pd[];
  
  // calculate moving averages in each processes' grouped table
  ungroup `Id xasc raze {
    select Id, TradeDate, ClosePrice, m21:21 mavg/: ClosePrice, m5:5 mavg/: ClosePrice from joined
  } peach .z.pd[]
 };
.qpar.q5.callback:{`q5result set x};

.qser.q5.query:{
	pxdata:select Id, TradeDate, ClosePrice from price where Id in stock1000, 
    TradeDate >= start6Mo, TradeDate < start6Mo + 31 * 6;
	splitdata:select Id, SplitDate, SplitFactor from split where Id in stock1000, 
    SplitDate >= start6Mo;
	splitadj:0!select ClosePrice:first ClosePrice*prd SplitFactor by Id, TradeDate from 
    ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
  
  update m21:21 mavg ClosePrice, m5:5 mavg ClosePrice by Id from 
    `Id`TradeDate xasc pxdata lj `Id`TradeDate xkey splitadj  
 };
.qser.q5.callback:{`q5ref set x}; 


/
********* QUERY 6 ****************
(Based on the previous query) 
Find the points (specific days) when the 5-day moving average intersects the 
21-day moving average for these stocks. The output is to be sorted by id and date.
\

.qpar.q6.query:{
  // perform necessary price data selections
	{
    `pxdata set select Id, TradeDate, ClosePrice from price 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]],
    Id in stock1000, TradeDate >= start6Mo,TradeDate < start6Mo + 31 * 6
  } peach .z.pd[];
  
  // perform necessary split data selections
  {
    `splitdata set select Id, SplitDate, SplitFactor from split 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]], 
    Id in stock1000, SplitDate >= start6Mo
  } peach .z.pd[];
    
  // join price and split data for adjustments  
  .aq.par.master.join[ej;`Id;`pxdata;`splitdata;`splitadj];

  // as explained before, all Id=x are in same process due to join
  {
    `splitadj set 0!select first ClosePrice* prd SplitFactor by Id, TradeDate from splitadj 
    where TradeDate < SplitDate
  } peach .z.pd[];
  
  .aq.par.master.join[lj;`Id`TradeDate;`pxdata;`splitadj;`joined];
  
  // we group again only within each process, as join partitioned by Id
  {`joined set select TradeDate, ClosePrice by Id from joined} peach .z.pd[];
  
  {
    `joined set update TradeDate:TradeDate@'ix, ClosePrice:ClosePrice@'ix from 
      update ix:iasc each TradeDate from `Id xasc joined 
  } peach .z.pd[];
  
  {`joined set update m21:21 mavg/: ClosePrice, m5:5 mavg/: ClosePrice from joined} peach .z.pd[];
  
  // calculate cross-points on grouped data
  {
    `joined set 
    update CrossPoints:((prev'[m5] <= prev'[m21]) & m5 > m21)|((prev'[m5] >= prev'[m21]) & m5 < m21) 
    from joined
  } peach .z.pd[];
  
  // ungroup and take results
  `Id`CrossDate xasc raze { select Id, CrossDate:TradeDate, ClosePrice from ungroup joined where CrossPoints } peach .z.pd[]
  };
.qpar.q6.callback:{`q6result set x};

.qser.q6.query:{
	pxdata:select Id, TradeDate, ClosePrice from price where Id in stock1000, TradeDate >= start6Mo,
	 TradeDate < start6Mo + 31 * 6;
	splitdata:select Id, SplitDate, SplitFactor from split where Id in stock1000, 
    SplitDate >= start6Mo;
	splitadj:0!select ClosePrice:first ClosePrice*prd SplitFactor by Id, TradeDate from 
    ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
  movingAvgs:update m21:21 mavg ClosePrice, m5:5 mavg ClosePrice by Id from 
      `Id`TradeDate xasc pxdata lj `Id`TradeDate xkey splitadj;
    
	select Id, CrossDate:TradeDate, ClosePrice from movingAvgs where Id=prev Id, 
	((prev[m5] <= prev m21) & m5 > m21)|((prev[m5] >= prev m21) & m5 < m21)
  };
.qser.q6.callback:{`q6ref set x}; 


/
********* QUERY 7 ****************
Determine the value of $100,000 now if 1 year ago it was invested equally in 10 
specified stocks (i.e. allocation for each stock is $10,000). The trading strategy 
is: When the 20-day moving average crosses over the 5-month moving average the complete 
allocation for that stock is invested and when the 20-day moving average crosses below 
the 5-month moving average the entire position is sold. The trades happen on the closing
price of the trading day.

Modifications based on sybase benchmark: use adjusted prices, 21-day moving avg, instead
of 20 days
\

.qpar.q7.query:{
  // define allocation
  .aq.par.master.define[`alloc;10000.0];
  
  // select relevant price data
  {
    `pxdata set select Id, TradeDate, ClosePrice from price 
      where month in .aq.part.map[.aq.par.worker.getSelfName[]], 
      Id in stock10, TradeDate >= -365 + max TradeDate
  } peach .z.pd[];
  
  // select relevant split data
  {
    `splitdata set select Id, SplitDate, SplitFactor from split 
      where month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in stock10, 
      SplitDate >= -365 + max SplitDate
  } peach .z.pd[];

  .aq.par.master.join[ej;`Id;`pxdata;`splitdata;`splitadj];
  
  // we've joined by Id, so all observations for a given Id are in the same process
  {
    `splitadj set 0!select first ClosePrice* prd SplitFactor by Id, TradeDate from splitadj 
      where TradeDate < SplitDate
  } peach .z.pd[];
  
  .aq.par.master.join[lj;`Id`TradeDate;`pxdata;`splitadj;`adjpxdata];
  
  // we can group within each process, as partitioned by Id given join above
  {`adjpxdata set select TradeDate, ClosePrice by Id from adjpxdata} peach .z.pd[];

  { 
    `adjpxdata set update TradeDate:TradeDate@'ix, ClosePrice:ClosePrice@'ix from 
      update ix:iasc each TradeDate from adjpxdata 
  } peach .z.pd[];
  // calculate moving averages
  {
    `movingAvgs set update m21day:21 mavg/: ClosePrice, 
      m5month:160 mavg/: ClosePrice from adjpxdata
  } peach .z.pd[];
  // simulate trades
  {
    `simulated set select result:alloc*prd ?[maxs m21day > m5month;?[m21day > m5month;1%ClosePrice;ClosePrice];1], 
      stillInvested:last[m21day] > last m5month by Id from ungroup movingAvgs 
        where (Id=prev[Id]) & (
          ((prev[m5month] <= prev m21day)& m5month > m21day)|
          ((prev[m5month] >= prev m21day)& m5month < m21day)
          )
  } peach .z.pd[];
  // adjpxdata is also grouped by Id (as is simulated, which stems from adjpxdata)
  // so we can just execute selections for latestPxs and joins locally
  // and then reduce by adding up results
  {
    `latestPxs set select Id, ClosePrice from ungroup adjpxdata 
    where TradeDate=max TradeDate
  } peach .z.pd[];
  map:{
    select stock_value:sum alloc^result * ?[stillInvested;ClosePrice;1] from 
    latestPxs lj `Id xkey simulated
  };
  reduce:{x+y};
  .aq.par.master.mapreduce[map;reduce;2]
  };
.qpar.q7.callback:{`q7result set x};
  

.qser.q7.query:{
 alloc:10000.0;
 pxdata:select Id, TradeDate, ClosePrice from price where Id in stock10, 
  TradeDate >= -365 + max TradeDate;
 
 splitdata:select Id, SplitDate, SplitFactor from split where Id in stock10, 
   SplitDate >= -365 + max SplitDate;
 
 splitadj:0!select ClosePrice:first ClosePrice*prd SplitFactor by Id, TradeDate from 
   ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
 
 adjpxdata:`Id`TradeDate xasc pxdata lj `Id`TradeDate xkey splitadj;
 
 movingAvgs:update m21day:21 mavg ClosePrice, m5month:160 mavg ClosePrice by Id from adjpxdata;
 
 simulated:select result:alloc*prd ?[maxs m21day > m5month;?[m21day > m5month;1%ClosePrice;ClosePrice];1],
   stillInvested:last[m21day] > last m5month by Id
   from movingAvgs where (Id=prev[Id]) & 
    (
      ((prev[m5month] <= prev m21day)& m5month > m21day) |
      ((prev[m5month] >= prev m21day)& m5month < m21day)
    );
   
 latestPxs:select Id, ClosePrice from adjpxdata where TradeDate=max TradeDate;
 select stock_value:sum alloc^result * ?[stillInvested;ClosePrice;1] from latestPxs lj `Id xkey simulated
 };
.qser.q7.callback:{`q7ref set x}; 
 

/
********* QUERY 8 ****************
Find the pair-wise coefficients of correlation in a set of 10 securities for a 
2 year period. Sort the securities by the coefficient of correlation, indicating 
the pair of securities corresponding to that row. [Note: coefficient of correlation
defined in appendix]
\

.qpar.q8.query:{
  // select relevant price data
  {
    `pricedata set select Id, TradeDate, ClosePrice from price 
      where month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in stock10, 
      TradeDate >= startYear10, TradeDate <= startYear10 + 365 * 2
  } peach .z.pd[];
  // group data by Id
  .aq.par.master.groupby[`pricedata;{`Id xgroup x};`grouped];
  // sort data by trade date in each Id group
  {`grouped set update ix:iasc each TradeDate from grouped} peach .z.pd[];
  {`grouped set update ClosePrice:ClosePrice@'ix from grouped} peach .z.pd[];
  // update column names before crossing
  pair1:{update Id1:Id, ClosePrice1:ClosePrice from grouped};
  pair2:{update Id2:Id, ClosePrice2:ClosePrice from grouped};
  // distributed crossing
  .aq.par.master.cross[pair1;pair2;`cordata];
  // calculate correlations and sort by correlation coefficient
  {
    `corrResults set select Id1, Id2, corrCoeff:cor'[ClosePrice1;ClosePrice2] from cordata 
    where Id1<>Id2
  } peach .z.pd[];
  `corrCoeff xasc raze {select from corrResults} peach .z.pd[]
  };
.qpar.q8.callback:{`q8result set x};  

.qser.q8.query:{
	pricedata:`Id`TradeDate xasc select Id, TradeDate, ClosePrice from price 
    where Id in stock10, TradeDate >= startYear10, TradeDate <= startYear10 + 365 * 2;
	pair1:select ClosePrice1:ClosePrice by Id1:Id from pricedata;
	// full matrix, not just lower/upper triangular
	corrdata:pair1 cross `Id2`ClosePrice2 xcol pair1;
	corrResults:select Id1, Id2, corrCoeff:cor'[ClosePrice1;ClosePrice2] from corrdata where Id1<>Id2;
  `corrCoeff xasc corrResults
 };
.qser.q8.callback:{`q8ref set x}; 


/
********* QUERY 9 ****************
Determine the yearly dividends and annual yield (dividends/average closing price)
for the past 3 years for all the stocks in the Russell 2000 index that did not split
during that period. Use unadjusted prices since there were no splits to adjust for.

Note that we follow the implementation provided by sybase, which excludes tickers
with a split anytime in the past three calendar years (not necessarily in the 
3 years since today). Furthermore, note that their solution uses only inner joins
thus it doesn't include stocks that did not have dividends (which would have a yield
of 0 by default). It also includes dividends that might have happened been announced prior to the
first trade date in the relevant 3 year period (the inner join is done on the year part)
\

.qpar.q9.query:{
  // map reduce to calculate largest trade date
  map:{
    select TradeDate:(-365*3)+max TradeDate from price where month in .aq.part.map[.aq.par.worker.getSelfName[]]
  };
  reduce:|;
  startDate:first exec TradeDate from .aq.par.master.mapreduce[map;reduce;2];
  .aq.par.master.define[`startDate;startDate];
  .aq.par.master.define[`startYear;getYear startDate];
  
  // map reduce to calculate Id that have experienced split
  map:{
    exec Id from select distinct Id from split where 
    month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in Russell2000, 
    (getYear SplitDate) >= startYear
  };
  reduce:{distinct x,y};
  hadSplits:.aq.par.master.mapreduce[map;reduce;2];
  .aq.par.master.define[`hadSplits;hadSplits];
  
  // map reduce to calculate average price for non-split Ids
  map:{
    select s:sum ClosePrice, c:count i by Id, year:getYear TradeDate from price 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in Russell2000, 
    TradeDate >= startDate, not Id in hadSplits
  };
  reduce:{y upsert x pj y};
  nosplit:select Id, year, avg_px:s% c from .aq.par.master.mapreduce[map;reduce;2];
  
  // map reduce to calcualte dividend amount for non-split Ids
  map:{
    select total_divs:sum DivAmt by Id, year:getYear AnnounceDate from dividend 
    where month in .aq.part.map[.aq.par.worker.getSelfName[]], Id in Russell2000, 
    (getYear AnnounceDate)>= startYear, not Id in hadSplits
  };
  reduce:{y upsert x pj y};
  divdata:.aq.par.master.mapreduce[map;reduce;2];
  
  // join locally in master and return results
  0!update yield:total_divs%avg_px from select from nosplit ij `Id`year xkey divdata
 };
.qpar.q9.callback:{`q9result set x}; 

.qser.q9.query:{
  startDate:first exec (-365*3)+TradeDate from select max TradeDate from price;
  startYear:getYear startDate;
  .aq.par.master.define[`startDate;startDate];
  .aq.par.master.define[`startYear;startYear];
  hadSplits:exec Id from select distinct Id from split where Id in Russell2000, (getYear SplitDate)>=startYear;
  .aq.par.master.define[`hadSplits;hadSplits];
  nosplit:select avg_px:avg ClosePrice by Id, year:getYear TradeDate from price where Id in Russell2000, TradeDate>=startDate, not Id in hadSplits;
  divdata:select total_divs:sum DivAmt by Id, year:`year$AnnounceDate from dividend where Id in Russell2000, (getYear AnnounceDate)>= startYear, not Id in hadSplits;
  0!update yield:total_divs%avg_px from select from nosplit ij `Id`year xkey divdata
 };
.qser.q9.callback:{`q9ref set x}; 

//////// Running queries ////////
// simple wrapper to run queries
//queryCompleted:{`completionOrder upsert x; if[20=count completionOrder;show "doneso";exit 0]};
queryCompleted:{`completionOrder upsert x}
completionOrder:`$();
execute:{[prefix;query]
  ns:`$prefix,".",query;
  q:ns`query;
  cb:queryCompleted ns[`callback]@;
  .aq.par.supermaster.execute[0b;(q;::);cb]
  };

queries:"q",/:string til 10;

// execute our queries
execute[".qpar"; ]  each queries;
execute[".qser"; ] each queries;

timer:{[iters;q]
  show "timing query ",string[q];
  master:first .aq.par.masterNames[];
  cmd:"ts:",string[iters]," .aq.par.runSynch[`",string[master],";(",string[q],";::)]";
  (system cmd)%iters
  };

getQueryNames:{` sv/:x,/:(k where not null k:key x),\:`query};
timings:([] query:`$(); time:`float$(); mem:`float$());
runBenchmark:{
   show "running benchmark, iteration:",string[x];
  `timings upsert qpar,'timer[10; ] each qpar:getQueryNames[`.qpar];
  `timings upsert qser,'timer[10; ] each qser:getQueryNames[`.qser];
  };

/
runBenchmark each til 10
update num:`$("."vs/:string query)@\:2 from `timings
update sys:`$("."vs/:string query)@\:1 from `timings

summary:select avg time, sdtime:dev time, avg mem by num, sys from timings;
update ratio:qpar%qser from exec `qpar`qser#sys!time by q:num from summary

/
q0ref~update `#Id from 0!q0result
q1ref~q1result
q2ref~q2result
q3ref~q3result
q4ref~q4result
q5ref~q5result
q6ref~q6result
q7ref~q7result
(~) . (`Id1`Id2)xasc/:(q8ref; q8result)
q9ref~q9result
