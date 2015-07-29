\l base
\l price
\l split

// Retrieve randomly created lists
stock10:get `:stock10
startYear10:get `:startYear10
stock1000:get `:stock1000
start300Days:get `:start300Days
startPeriod:get `:startPeriod
endPeriod:get `:endPeriod
SP500:get `:SP500
start6Mo:get `:start6Mo


/
	Get the closing price of a set of 10 stocks for a 10-year period and group into weekly, monthly and yearly aggregates. For each aggregate period determine the low, high and average closing price value. The output should be sorted by id and trade date.
\

data:select from price where Id in stock10, TradeDate >= startYear10, TradeDate < startYear10 + 365 * 10
result:(upsert/){[x;y] 0!select minPx:min ClosePrice, maxPx:max ClosePrice, avgPx:avg ClosePrice by Id, bucket:floor (TradeDate - startYear10)%x, bucketName:y from data}'[7 31 365;`weekly`monthly`yearly]

/
Adjust all prices and volumes (prices are multiplied by the split factor and volumes are divided by the split factor) for a set of 1000 stocks to reflect the split events during a specified 300 day period, assuming that events occur before the first trade of the split date. These are called split-adjusted prices and volumes.
\
pxdata:select from price where Id in stock1000, TradeDate >= start300Days, TradeDate < start300Days + 300
splitdata:select from split where Id in stock1000, SplitDate >= start300Days, SplitDate < start300Days + 300
result:select HighPrice:first HighPrice*prd 1%SplitFactor,LowPrice:first LowPrice*prd 1%SplitFactor,ClosePrice:first ClosePrice*prd 1%SplitFactor,OpenPrice:first OpenPrice*prd 1%SplitFactor,Volume:first Volume*prd SplitFactor by Id, TradeDate from ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;

/
For each stock in a specified list of 1000 stocks, find the differences between the daily high and daily low on the day of each split event during a specified period.
\
pxdata:select from price where Id in stock1000, TradeDate within (startPeriod;endPeriod)
splitdata:update TradeDate:SplitDate from select from split where Id in stock1000, SplitDate within (startPeriod;endPeriod)
result:select Id, SplitDate, diff:HighPrice - LowPrice from pxdata ij `Id`TradeDate xkey splitdata 

/
Calculate the value of the S&P500 and Russell 2000 index for a specified day using unadjusted prices and the index composition of the 2 indexes (see appendix for spec) on the specified day
Divisor of 8.9bn taken from https://en.wikipedia.org/wiki/S%26P_500
\
SP500Index:select index:sum[ClosePrice*Volume]%8.9e9 from price where Id in SP500, TradeDate = startPeriod
// we have only 2000 stocks here, so take all 
Russell200Index:select index:sum[ClosePrice*Volume]%8.9e9 from price where TradeDate = startPeriod


/
Find the 21-day and 5-day moving average price for a specified list of 1000 stocks during a 6-month period. (Use split adjusted prices)
\
pxdata:select from price where Id in stock1000, TradeDate >= start6Mo, TradeDate < start6Mo + 31 * 6;
splitdata:select from split where Id in stock1000, SplitDate >= start6Mo, SplitDate < start6Mo + 31 * 6;
data:select  ClosePrice:first ClosePrice*prd 1%SplitFactor by Id, TradeDate from ej[`Id;pxdata;splitdata] where TradeDate < SplitDate;
results:update m21:21 mavg ClosePrice, m5:5 mavg ClosePrice by Id from `Id`TradeDate xasc data;

/
(Based on the previous query) Find the points (specific days) when the 5-month moving average intersects the 21-day moving average for these stocks. The output is to be sorted by id and date.
\
select from `Id`TradeDate xasc results where Id=prev Id,((m21 > m5) & prev[m21] <= prev m5) | ((m21 < m5) & prev[m21] >= prev m5)


/
Determine the value of $100,000 now if 1 year ago it was invested equally in 10 specified stocks (i.e. allocation for each stock is $10,000). The trading strategy is: When the 20-day moving average crosses over the 5-month moving average the complete allocation for that stock is invested and when the 20-day moving average crosses below the 5-month moving average the entire position is sold. The trades happen on the closing price of the trading day.
\
pricedata:select from price where Id in stock10, TradeDate >= -365 + max TradeDate
pricedata:update m20:20 mavg price, m5:5 mavg price from `Id`TradeDate xasc pricedata
pricedata:update sell:(m21 < m5) & prev[m21] >= prev m5, 
	 							 buy: (m21 > m5) & prev[m21] <= prev m5 from pricedata where Id=prev Id;

// TODO




/
Find the pair-wise coefficients of correlation in a set of 10 securities for a 2 year period. Sort the securities by the coefficient of correlation, indicating the pair of securities corresponding to that row. [Note: coefficient of correlation defined in appendix]
\
pricedata:select from price where Id in stock10, TradeDate >= startYear10, TradeDate < startYear10 + 365 * 2;
corrdata:(select Id1:Id, ClosePrice1:ClosePrice from pricedata) cross select Id2:Id, ClosePrice2:ClosePrice from pricedata
corrdata:select from corrdata where Id1<>Id2
// full matrix, not just lower/upper triangular
results:select cor[ClosePrice1;ClosePrice2] by Id1,Id2 from corrdata


/
Determine the yearly dividends and annual yield (dividends/average closing price) for the past 3 years for all the stocks in the Russell 2000 index that did not split during that period. Use unadjusted prices since there were no splits to adjust for.

No dividend file provided, so skipping for now.
\







