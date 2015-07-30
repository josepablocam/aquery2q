path:hsym`$"/Users/josecambronero/MS/S15/aquery/src/benchmark/fintime/src/experiments"
base:get ` sv path,`base
price:get ` sv path,`price
split:get ` sv path,`split

// Retrieve randomly created lists
stock10:get ` sv path,`stock10
startYear10:get ` sv path,`startYear10
stock1000:get ` sv path,`stock1000
start300Days:get ` sv path,`start300Days
startPeriod:get ` sv path,`startPeriod
endPeriod:get ` sv path,`endPeriod
SP500:get ` sv path,`SP500
start6Mo:get ` sv path,`start6Mo
Russell2000:get ` sv path,`Russell2000

/
	Get the closing price of a set of 10 stocks for a 10-year period and group into weekly, monthly and yearly aggregates. For each aggregate period determine the low, high and average closing price value. The output should be sorted by id and trade date.
\
.qtest.q0:{
	data:select Id, TradeDate, ClosePrice from price where Id in stock10, TradeDate >= startYear10,
	TradeDate < startYear10 + 365 * 10;
	
	`Id`name`bucket xasc (upsert/)
	 {[x;y;z] 
		0!select low:min ClosePrice, high:max ClosePrice, mean:avg ClosePrice 
		by Id, bucket:floor (TradeDate - startYear10)%y, name:z from x
		}[data;;]'[7 31 365;`weekly`monthly`yearly]
	}

/
Adjust all prices and volumes (prices are multiplied by the split factor and volumes are divided by the split factor) for a set of 1000 stocks to reflect the split events during a specified 300 day period, assuming that events occur before the first trade of the split date. These are called split-adjusted prices and volumes.
\
.qtest.q1:{
	pxdata:select from price where Id in stock1000, TradeDate >= start300Days, 
		TradeDate < start300Days + 300;
	splitdata:select from split where Id in stock1000, SplitDate >= start300Days, 
		SplitDate < start300Days + 300;
	
	0!select HighPrice:first HighPrice*prd 1%SplitFactor,
		LowPrice:first LowPrice*prd 1%SplitFactor,
		ClosePrice:first ClosePrice*prd 1%SplitFactor,
		OpenPrice:first OpenPrice*prd 1%SplitFactor,
		Volume:first Volume*prd SplitFactor 
		by Id, TradeDate from ej[`Id;pxdata;splitdata] where TradeDate < SplitDate
	}

/
For each stock in a specified list of 1000 stocks, find the differences between the daily high and daily low on the day of each split event during a specified period.
\
.qtest.q2:{
	pxdata:select Id, TradeDate, HighPrice, LowPrice from price where Id in stock1000, 
		TradeDate within (startPeriod;endPeriod);
	splitdata:select Id, TradeDate:SplitDate, SplitFactor from split where Id in stock1000, 
		SplitDate within (startPeriod;endPeriod);
	select Id, TradeDate, MaxDiff:HighPrice - LowPrice from 
		`Id`TradeDate xasc pxdata ij `Id`TradeDate xkey splitdata
	}


/
Calculate the value of the S&P500 and Russell 2000 index for a specified day using unadjusted prices and the index composition of the 2 indexes (see appendix for spec) on the specified day
Divisor of 8.9bn taken from https://en.wikipedia.org/wiki/S%26P_500
\
.qtest.q3:{
	select index:sum[ClosePrice*Volume]%8.9e9 from price where Id in SP500, TradeDate = startPeriod
 }

.qtest.q4:{
	select index:sum[ClosePrice*Volume]%8.9e9 from price where Id in Russell2000, TradeDate = startPeriod
 }

/
Find the 21-day and 5-day moving average price for a specified list of 1000 stocks during a 6-month period. (Use split adjusted prices)
\
.qtest.q5:{
	pxdata:select Id, TradeDate, ClosePrice from price where Id in stock1000, TradeDate >= start6Mo,
	 TradeDate < start6Mo + 31 * 6;
	splitdata:select Id, SplitDate, SplitFactor from split where Id in stock1000, 
    SplitDate >= start6Mo, SplitDate < start6Mo + 31 * 6;
	data:select ClosePrice:first ClosePrice*prd 1%SplitFactor by Id, TradeDate 
		from ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
  avgdata:update m21:21 mavg ClosePrice, m5:5 mavg ClosePrice by Id from `Id`TradeDate xasc data;
  select Id, TradeDate, m21, m5 from avgdata
 }
 
/
(Based on the previous query) 
Modified: For now, just doing moving average not with respect to last query,
as A2Q has not yet implemented creating a table from a query, which is needed to store
the prior queries result (without repeating the query again). Performing on all stock instead

Find the points (specific days) when the 5-month moving average intersects the 21-day moving average for these stocks. The output is to be sorted by id and date.
\
.qtest.q6:{
	pricedata:update m21:21 mavg ClosePrice, m5:5 mavg ClosePrice by Id from `Id`TradeDate xasc price;
	select Id, CrossDate:TradeDate, ClosePrice from pricedata where Id=prev Id, 
	((prev[m5] < prev m21) & m5 >= m21)|((prev[m5] > prev m21) & m5 <= m21)
  }



/
Determine the value of $100,000 now if 1 year ago it was invested equally in 10 specified stocks (i.e. allocation for each stock is $10,000). The trading strategy is: When the 20-day moving average crosses over the 5-month moving average the complete allocation for that stock is invested and when the 20-day moving average crosses below the 5-month moving average the entire position is sold. The trades happen on the closing price of the trading day.
\

// TODO


/
Find the pair-wise coefficients of correlation in a set of 10 securities for a 2 year period. Sort the securities by the coefficient of correlation, indicating the pair of securities corresponding to that row. [Note: coefficient of correlation defined in appendix]
\
.qtest.q7:{
	pricedata:select from `Id`TradeDate xasc price where Id in stock10, TradeDate >= startYear10, 		TradeDate < startYear10 + 365 * 2;
	pair1:select ClosePrice1:ClosePrice by Id1:Id from pricedata;
	pair2:`Id2`ClosePrice2 xcol pair1;
	// full matrix, not just lower/upper triangular
	corrdata:pair1 cross pair2;
	select Id1, Id2, corrCoeff:cor'[ClosePrice1;ClosePrice2] from corrdata where Id1<>Id2
 }

/
Determine the yearly dividends and annual yield (dividends/average closing price) for the past 3 years for all the stocks in the Russell 2000 index that did not split during that period. Use unadjusted prices since there were no splits to adjust for.

No dividend file produced by software (I will have to follow up on this one), so skipping for now.
\


// TODO






