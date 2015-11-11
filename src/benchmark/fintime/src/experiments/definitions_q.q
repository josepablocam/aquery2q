
\l load_data.q
getMonth:{1 + (`month$x) mod 12}
getYear:{`year$x}
firstDateOfYear:{`date$`month$d-30*-1+getMonth d:`date$`month$x}
getWeek:{1 + floor (x - firstDateOfYear x)%7}

/
********* QUERY 0 ****************
	Get the closing price of a set of 10 stocks for a 10-year period and group into 
  weekly, monthly and yearly aggregates. For each aggregate period determine the low, 
  high and average closing price value. The output should be sorted by id and trade date.
\
.qtest.q0:{
	data:select Id, TradeDate, ClosePrice from price where Id in stock10, TradeDate >= startYear10,
	TradeDate < startYear10 + 365 * 10;
	
	`Id`name`bucket xasc (upsert/)
	 {[x;y;z] 
		0!select low:min ClosePrice, high:max ClosePrice, mean:avg ClosePrice 
		by Id, bucket:y TradeDate, name:z from x
		}[data;;]'[(getWeek;getMonth;getYear);`weekly`monthly`yearly]
	}

/
********* QUERY 1 ****************
Adjust all prices and volumes (prices are multiplied by the split factor and volumes 
are divided by the split factor) for a set of 1000 stocks to reflect the split events 
during a specified 300 day period, assuming that events occur before the first trade of 
the split date. These are called split-adjusted prices and volumes.
\
.qtest.q1:{
	pxdata:select from price where Id in stock1000, TradeDate >= start300Days, 
    TradeDate < start300Days + 300;
	splitdata:select from split where Id in stock1000, SplitDate >= start300Days;
  adjdata:select adjFactor:prd SplitFactor by Id, TradeDate
    from ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
  
    0!`Id`TradeDate xasc
    select Id, TradeDate, HighPrice:HighPrice*1^adjFactor, 
    LowPrice:LowPrice*1^adjFactor, 
    ClosePrice:ClosePrice*1^adjFactor,
    OpenPrice:OpenPrice*1^adjFactor,
    Volume:Volume%1^adjFactor
    from pxdata lj `Id`TradeDate xkey adjdata
	}  

/
********* QUERY 2 ****************
For each stock in a specified list of 1000 stocks, 
find the differences between the daily high and daily low on the day 
of each split event during a specified period.
\
.qtest.q2:{
	pxdata:select Id, TradeDate, HighPrice, LowPrice from price where Id in stock1000, 
		TradeDate within (startPeriod;endPeriod);
	splitdata:select Id, TradeDate:SplitDate, SplitFactor from split where Id in stock1000, 
		SplitDate within (startPeriod;endPeriod);
	select Id, TradeDate, MaxDiff:HighPrice - LowPrice from 
    `Id`TradeDate xasc ej[`Id`TradeDate;pxdata;splitdata]
	}


/
********* QUERY 3 + 4 ****************
Calculate the value of the S&P500 and Russell 2000 index for a specified day 
using unadjusted prices and the index composition of the 2 indexes (see appendix 
for spec) on the specified day
\
.qtest.q3:{
	select avg_close_price:avg ClosePrice from price where Id in SP500, TradeDate = startPeriod
 }

.qtest.q4:{
	select avg_close_price:avg ClosePrice from price where Id in Russell2000, TradeDate = startPeriod
 }

/
********* QUERY 5 ****************
Find the 21-day and 5-day moving average price for a specified list of 1000 stocks 
during a 6-month period. (Use split adjusted prices)
\

.qtest.q5:{
	pxdata:select Id, TradeDate, ClosePrice from price where Id in stock1000, TradeDate >= start6Mo,
	 TradeDate < start6Mo + 31 * 6;
	splitdata:select Id, SplitDate, SplitFactor from split where Id in stock1000, 
    SplitDate >= start6Mo, SplitDate < start6Mo + 31 * 6;
	splitadj:0!select ClosePrice:first ClosePrice*prd 1%SplitFactor by Id, TradeDate from ej[`Id;pxdata;splitdata] where TradeDate <= SplitDate;
  
  update m21:21 mavg ClosePrice, m5:5 mavg ClosePrice by Id from `Id`TradeDate xasc pxdata lj `Id`TradeDate xkey splitadj  
 };

show `query5TableQ set .qtest.q5[]; 

/
********* QUERY 6 ****************
(Based on the previous query) 
Find the points (specific days) when the 5-month moving average intersects the 
21-day moving average for these stocks. The output is to be sorted by id and date.
\
.qtest.q6:{
	select Id, CrossDate:TradeDate, ClosePrice from query5TableQ where Id=prev Id, 
	((prev[m5] <= prev m21) & m5 > m21)|((prev[m5] >= prev m21) & m5 < m21)
  }


/
********* QUERY 7 ****************
Determine the value of $100,000 now if 1 year ago it was invested equally in 10 
specified stocks (i.e. allocation for each stock is $10,000). The trading strategy 
is: When the 20-day moving average crosses over the 5-month moving average the complete 
allocation for that stock is invested and when the 20-day moving average crosses below 
the 5-month moving average the entire position is sold. The trades happen on the closing
price of the trading day.
\

.qtest.q7:{
 relevant:select from price where Id in stock10, TradeDate >= -365 + max TradeDate;
 movingAvgs:update m20day:20 mavg ClosePrice, m5month:(31 * 5) mavg ClosePrice by Id
 from `Id`TradeDate xasc relevant;
 
 simulated:select ClosePrice, result:10000*prd ?[maxs m20day > m5month;?[m20day > m5month;1%ClosePrice;ClosePrice];1],
 stillInvested:last[m20day] > last m5month by Id
 from movingAvgs where (Id=prev[Id]) & 
   (
     ((prev[m5month] <= prev m20day)& m5month > m20day) |
     ((prev[m5month] >= prev m20day)& m5month < m20day)
   );
   
 latestPxs:select Id, ClosePrice from relevant where TradeDate=max TradeDate;
 select Id, dollars:result * ?[stillInvested;ClosePrice;1] from simulated ij `Id xkey latestPxs
 }

/
********* QUERY 8 ****************
Find the pair-wise coefficients of correlation in a set of 10 securities for a 
2 year period. Sort the securities by the coefficient of correlation, indicating 
the pair of securities corresponding to that row. [Note: coefficient of correlation
defined in appendix]
\
.qtest.q8:{
	pricedata:select Id, ClosePrice from `Id`TradeDate xasc price where Id in stock10, TradeDate >= startYear10,
    TradeDate < startYear10 + 365 * 2;
	pair1:select ClosePrice1:ClosePrice by Id1:Id from pricedata;
	pair2:`Id2`ClosePrice2 xcol pair1;
	// full matrix, not just lower/upper triangular
	corrdata:pair1 cross pair2;
	corrResults:select Id1, Id2, corrCoeff:cor'[ClosePrice1;ClosePrice2] from corrdata where Id1<>Id2;
  `corrCoeff xdesc corrResults
 }


/
********* QUERY 9 ****************
Determine the yearly dividends and annual yield (dividends/average closing price)
for the past 3 years for all the stocks in the Russell 2000 index that did not split
during that period. Use unadjusted prices since there were no splits to adjust for.
\
.qtest.q9:{
  hadSplits:exec distinct Id from split where Id in Russell2000, 
    SplitDate>=(-365*3)+max SplitDate;
  nosplit:select avg_px:avg ClosePrice by Id, year:`year$TradeDate from price 
    where Id in Russell2000, TradeDate>=(-365*3)+max TradeDate, not Id in hadSplits;
  divdata:select total_divs:sum DivAmt by Id, year:`year$XdivDate from dividend 
    where Id in Russell2000, XdivDate>=(-365*3)+max XdivDate, not Id in hadSplits;
  
  0!update yield:(0^total_divs)%avg_px from select from nosplit lj `Id`year xkey divdata
 }





