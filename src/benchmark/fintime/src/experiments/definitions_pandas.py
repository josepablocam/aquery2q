from datetime import datetime, timedelta
import pandas as pd
import numpy as np


# load all necessary benchmarking data
from load_data import *

# set up a moving average function that behaves like q
# meaning, for a moving window of size x, while we have |n| < x
# we cumulatively and divide by n
# we don't use this since performance is much slower than pd.rolling_mean
# the q semantics are by no means the 'true' ones
def qma(v, w):
    mavg = pd.rolling_mean(v, w)
    # assume n > 0, since that is the case unless w = 1
    mavg[0:w] = np.cumsum(v[0:w]) / np.arange(1.0, w + 1)
    return mavg


# ********* QUERY 0 ****************
# Get the closing price of a set of 10 stocks for a 10-year period and group into weekly,
# monthly and yearly aggregates.  For each aggregate period determine the low, high
# and average closing price value. The output should be sorted by id and trade date.
def q0():
    start = startYear10
    end = start + timedelta(days = 365 * 10)
    
    # select relevant data set and add time columns for grouping
    pxdata = price[price['Id'].isin(stock10)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] <= end)]
    pxdata['week'] = pxdata['TradeDate'].map(lambda x: x.week)
    pxdata['month'] = pxdata['TradeDate'].map(lambda x: x.month)
    pxdata['year'] = pxdata['TradeDate'].map(lambda x: x.year)
    ops = { 'low' :  np.min, 'high' : np.max, 'mean' : np.mean }
   
    # aggregate along various time dimensions
    weekly = pxdata.groupby(['Id','week'])['ClosePrice'].agg(ops)   
    monthly = pxdata.groupby(['Id','month'])['ClosePrice'].agg(ops) 
    yearly = pxdata.groupby(['Id','year'])['ClosePrice'].agg(ops) 
    weekly['name'] = 'weekly'
    monthly['name'] = 'monthly'
    yearly['name'] = 'yearly'
    frames = [weekly, monthly, yearly]

    # rename indices and concatenate
    for frame in frames:
        frame.index.names = ['Id', 'bucket']

    return pd.concat(frames).reset_index().sort_values(by = ['Id', 'name', 'bucket'])


# ********* QUERY 1 ****************
# Adjust all prices and volumes (prices are multiplied by the split factor and volumes are divided
# by the split factor) for a set of 1000 stocks to reflect the split events during a specified 300
# day period, assuming that events occur before the first trade of the split date. These are called
# split-adjusted prices and volumes.
def q1():
    start = start300Days
    end = start300Days + timedelta(days = 300)
    pxdata = price[price['Id'].isin(stock1000)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] <= end)]
    splitdata = split[split['Id'].isin(stock1000)]
    splitdata = splitdata[splitdata['SplitDate'] >= start]
    joindata = pxdata.merge(splitdata, on = 'Id', how = "inner")
    # prices get adjusted by splits that happen later
    joindata = joindata[joindata['TradeDate'] < joindata['SplitDate']]
    # adjustment factor for each stock's trade date
    adjFactors = joindata.groupby(['Id', 'TradeDate'], as_index = False)['SplitFactor'].agg(np.prod)
    adjFactors.columns = ['Id', 'TradeDate', 'SF']
    # only care about adjusting those that have splits, so inner join
    allData = pxdata.merge(adjFactors, on = ['Id', 'TradeDate'], how = 'left')
    allData['SF'] = allData['SF'].fillna(1.0)
    allData['HighPrice'] = allData['HighPrice'] * allData['SF']
    allData['LowPrice'] = allData['LowPrice'] * allData['SF']
    allData['ClosePrice'] = allData['ClosePrice'] * allData['SF']
    allData['OpenPrice'] = allData['OpenPrice'] * allData['SF']
    allData['Volume'] = allData['Volume'] / allData['SF']
    allData.drop(['SF'], axis = 1, inplace = True)
    return allData

# ********* QUERY 2 ****************
# For each stock in a specified list of 1000 stocks, find the differences between the daily high and
# daily low on the day of each split event during a specified period.
def q2():
    pxdata = price[price['Id'].isin(stock1000)]
    # we perform inclusive range, as that is what we do with q/aquery
    pxdata = pxdata[(pxdata['TradeDate'] >= startPeriod) & (pxdata['TradeDate'] <= endPeriod)]   
    splitdata = split[split['Id'].isin(stock1000)]
    splitdata = splitdata[(splitdata['SplitDate'] >= startPeriod) & (splitdata['SplitDate'] <= endPeriod)]
    splitdata.rename(columns = {'SplitDate' : 'TradeDate'}, inplace = True)
    joindata = pxdata.merge(splitdata, on = ['Id', 'TradeDate'], how = "inner")
    joindata['MaxDiff'] = joindata['HighPrice'] - joindata['LowPrice']
    results = joindata[['Id', 'TradeDate', 'MaxDiff']]
    return results
 

# ********* QUERY 3 + 4 ****************
# Calculate the value of the S&P500 and Russell 2000 index for a specified day using unadjusted
# prices and the index composition of the 2 indexes (see appendix for spec) on the specified day
def q3():
    pxdata = price[price['Id'].isin(SP500) & (price['TradeDate'] == startPeriod)]
    indexValue = pxdata['ClosePrice'].mean()
    return pd.DataFrame({'avg_close_px' : [ indexValue ] })
    
def q4():
    pxdata = price[price['Id'].isin(Russell2000) & (price['TradeDate'] == startPeriod)]
    indexValue = pxdata['ClosePrice'].mean()
    return pd.DataFrame({'avg_close_px' : [ indexValue ] })
        

# ********* QUERY 5 ****************
# Find the 21-day and 5-day moving average price for a specified list of 1000 stocks during a
# 6-month period. (Use split adjusted prices)
def q5():
    start = start6Mo
    end = start6Mo + timedelta(days = 31 * 6)
    # relevant prices
    pxdata = price[price['Id'].isin(stock1000)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] < end)]
    # relevant split information
    splitdata = split[split['Id'].isin(stock1000)]
    splitdata = splitdata[splitdata['SplitDate'] >= start]
    # join to adjust prices by split factors
    joindata = pxdata.merge(splitdata, on = 'Id', how = "inner")
    # prices get adjusted by splits that happen later
    joindata = joindata[joindata['TradeDate'] < joindata['SplitDate']]
    # adjustment factor for each stock's trade date
    adjFactors = joindata.groupby(['Id', 'TradeDate'], as_index = False)['SplitFactor'].agg(np.prod)
    adjFactors.columns = ['Id', 'TradeDate', 'SF']
    allData = pxdata.merge(adjFactors, on = ['Id', 'TradeDate'], how = 'left', suffixes = ['_pxdata', '_adjdata'])
    allData['SF'] = allData['SF'].fillna(1.0)
    allData['ClosePrice'] = allData['ClosePrice'] * allData['SF']
    relevantCols = ['Id', 'TradeDate', 'ClosePrice']
    allData = allData[relevantCols]
    sortedData = allData.sort_values(by = ['Id','TradeDate'], ascending = True)
    # groupby preserves order 
    grouped = sortedData[['Id', 'ClosePrice']].groupby('Id')
    # note that we use a rolling mean function that emulates q's treatment of edge cases
    sortedData['p21'] = grouped['ClosePrice'].transform(lambda x: pd.rolling_mean(x, 21))
    sortedData['p5'] = grouped['ClosePrice'].transform(lambda x: pd.rolling_mean(x, 5))
    # set a copy of results to a global variable, so can use in q6
    # as per query description
    return sortedData         

# ********* QUERY 6 ****************
# (Based on the previous query) 
# Find the points (specific days) when the 5-day moving average intersects the 21-day 
# moving average for these stocks. The output is to be sorted by id and date.
def q6():
    start = start6Mo
    end = start6Mo + timedelta(days = 31 * 6)
    # relevant prices
    pxdata = price[price['Id'].isin(stock1000)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] < end)]
    # relevant split information
    splitdata = split[split['Id'].isin(stock1000)]
    splitdata = splitdata[splitdata['SplitDate'] >= start]
    # join to adjust prices by split factors
    joindata = pxdata.merge(splitdata, on = 'Id', how = "inner")
    # prices get adjusted by splits that happen later
    joindata = joindata[joindata['TradeDate'] < joindata['SplitDate']]
    # adjustment factor for each stock's trade date
    adjFactors = joindata.groupby(['Id', 'TradeDate'], as_index = False)['SplitFactor'].agg(np.prod)
    adjFactors.columns = ['Id', 'TradeDate', 'SF']
    allData = pxdata.merge(adjFactors, on = ['Id', 'TradeDate'], how = 'left', suffixes = ['_pxdata', '_adjdata'])
    allData['SF'] = allData['SF'].fillna(1.0)
    allData['ClosePrice'] = allData['ClosePrice'] * allData['SF']
    relevantCols = ['Id', 'TradeDate', 'ClosePrice']
    allData = allData[relevantCols]
    sortedData = allData.sort_values(by = ['Id','TradeDate'], ascending = True)
    # groupby preserves order 
    grouped = sortedData[['Id', 'ClosePrice']].groupby('Id')
    # note that we use a rolling mean function that emulates q's treatment of edge cases
    sortedData['p21'] = grouped['ClosePrice'].transform(lambda x: pd.rolling_mean(x, 21))
    sortedData['p5'] = grouped['ClosePrice'].transform(lambda x: pd.rolling_mean(x, 5))
    crossAbove = (sortedData['p5'].shift(1) <= sortedData['p21'].shift(1)) & (sortedData['p5'] > sortedData['p21'])
    crossBelow = (sortedData['p5'].shift(1) >= sortedData['p21'].shift(1)) & (sortedData['p5'] < sortedData['p21'])
    sameId = sortedData['Id'].shift(1) == sortedData['Id']
    crosses = sortedData[sameId & (crossAbove | crossBelow)]
    return crosses[['Id', 'TradeDate', 'ClosePrice']]
 
# ********* QUERY 7 ****************
# Determine the value of $100,000 now if 1 year ago it was invested equally in 10 specified
# stocks (i.e. allocation for each stock is $10,000). The trading strategy is: When the 20-day
# moving average crosses over the 5-month moving average the complete allocation for that stock
# is invested and when the 20-day moving average crosses below the 5-month moving average the entire
# position is sold. The trades happen on the closing price of the trading day.
# Modifications based on sybase benchmark: use adjusted prices, 21-day moving avg, instead
# of 20 days
def q7():
    # create adjusted prices
    maxTradeDate = price['TradeDate'].max()
    start = maxTradeDate - timedelta(days = 365)
    pxdata = price[price['Id'].isin(stock10)]
    pxdata = pxdata[pxdata['TradeDate'] >= start]
    # relevant split information
    splitdata = split[split['Id'].isin(stock10)]
    splitdata = splitdata[splitdata['SplitDate'] >= start]
    # join to adjust prices by split factors
    joindata = pxdata.merge(splitdata, on = 'Id', how = "inner")
    # prices get adjusted by splits that happen later
    joindata = joindata[joindata['TradeDate'] < joindata['SplitDate']]
    # adjustment factor for each stock's trade date
    adjFactors = joindata.groupby(['Id', 'TradeDate'], as_index = False)['SplitFactor'].agg(np.prod)
    adjFactors.columns = ['Id', 'TradeDate', 'SF']
    allData = pxdata.merge(adjFactors, on = ['Id', 'TradeDate'], how = 'left')
    allData['SF'] = allData['SF'].fillna(1.0)
    allData['ClosePrice'] = allData['ClosePrice'] * allData['SF']

    # creating moving price information for signals
    allData = allData.sort_values(by = ['Id', 'TradeDate'], ascending = True)
    grouped = allData.groupby('Id')
    allData['m5month'] = grouped['ClosePrice'].transform(lambda x: pd.rolling_mean(x, 160))
    allData['m21day'] = grouped['ClosePrice'].transform(lambda x: pd.rolling_mean(x, 21))
    allData['isSignal'] = (allData['Id'].shift(1) == allData['Id']) & (
       ( # cross under -> sell signal
           (allData['m5month'].shift(1) <= allData['m21day'].shift(1)) &
           (allData['m5month'] > allData['m21day'])
        )
     | # alternatively
        ( # cross over -> buy signal
            (allData['m5month'].shift(1) >= allData['m21day'].shift(1)) &
            (allData['m5month'] < allData['m21day'])
        )
     )
    allData['buySignal'] = allData['m5month'] < allData['m21day'] # buy signal, if coincides with isSignal
    signals = allData[allData['isSignal']]
    grouped = signals.groupby('Id')
    # a vectorized approach to the strategy is
    # - can't sell before we buy, so need to wait for first buy signal to do anything w/ 10k
    # after that, replace each buy signal with 1 / ClosePrice (how many shares can you buy)
    # and every sell signal with ClosePrice (how much can you sell it for)
    # result of strategy then is 10,000 * product of "actions"
    # if last action is buy, then multiply by latest price.
    # result: total valuation per stock simulating strategy (ignoring fees etc)
    seedMoneyPerStock = 10000
    def strategy(x):
        hasSeenBuy = np.cumsum(x['buySignal']) > 0.0
        if (not hasSeenBuy.any()):
            return seedMoneyPerStock # we never got to trade
        # the action is how much money do we sell for
        # we copy to avoid issues with assigning
        sell = x['ClosePrice'].copy()
        sell[x['buySignal']] = 0.0
        # when we buy action is how many stocks can we get for the price
        buy = (1.0 / x['ClosePrice'])
        buy[~x['buySignal']] = 0.0
        multiplier = np.maximum(buy, sell) # 0s will be replaced with appropriate action
        multiplier[~hasSeenBuy] = 1.0 # if we haven't seen a buy, we stay put
        return seedMoneyPerStock * np.prod(multiplier)

    valuations = grouped.apply(strategy)
    # latest set of prices incase needed
    # making copy to avoid setting a slice error
    results = allData[allData['TradeDate'] == maxTradeDate].copy()
    results['valuation'] = valuations[results['Id']].values
    # value stock holdings at current market prices
    stillInvested = results['buySignal']
    results.loc[stillInvested, 'valuation'] = results.loc[stillInvested, 'ClosePrice'] * results.loc[stillInvested, 'valuation']
    # if you never invested the allocation for a given stock, you still have the initial allocation
    results['valuation'] = results['valuation'].fillna(seedMoneyPerStock)
    return results['valuation'].sum()




# ********* QUERY 8 ****************
# Find the pair-wise coefficients of correlation in a set of 10 securities for a 2 year period.
# Sort the securities by the coefficient of correlation, indicating the pair of securities 
# corresponding to that row. [Note: coefficient of correlation defined in appendix]
def q8():
    start = startYear10
    end = startYear10 + timedelta(days = 365 * 2)
    pxdata = price[price['Id'].isin(stock10)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] <= end)]
    pxdata = pxdata.sort_values(by = ['TradeDate'], ascending = True)
    #pxdata.set_index('TradeDate', inplace = True)
    corrdata = pxdata.pivot(index = 'TradeDate', columns = 'Id', values = 'ClosePrice')
    #column wise correlation
    corrs = corrdata.corr()
    corrs = corrs.reset_index()
    corrs.columns.name = None
    # "unpivot"
    flatCorrs = pd.melt(corrs, id_vars = "Id", value_name = "corrCoeff", var_name = "Id2")
    # remove self-correlation
    flatCorrs = flatCorrs[flatCorrs['Id'] != flatCorrs["Id2"]]
    # sort by correlation coefficient
    return flatCorrs.sort_values(by = ['corrCoeff'], ascending = True)
  
    
# ********* QUERY 9 ****************
# Determine the yearly dividends and annual yield (dividends/average closing price) for the past 3
# years for all the stocks in the Russell 2000 index that did not split during that period.
# Use unadjusted prices since there were no splits to adjust for. 
# Note that we follow the implementation provided by sybase, which excludes tickers
# with a split anytime in the past three calendar years (not necessarily in the
# 3 years since today). Furthermore, note that their solution uses only inner joins
# thus it doesn't include stocks that did not have dividends (which would have a yield
# of 0 by default). It also includes dividends that might have happened been announced prior to the
# first trade date in the relevant 3 year period (the inner join is done on the year part) 
def q9():
    start = price['TradeDate'].max() - timedelta(days = 365 * 3)
    splitdata = split[split['Id'].isin(Russell2000)]
    splitdata['year'] = splitdata['SplitDate'].map(lambda x: x.year)
    splitdata = splitdata[splitdata['year'] >= start.year]
    hadSplits = pd.unique(splitdata['Id'])
    pxdata = price[(price['Id'].isin(Russell2000)) & (~price['Id'].isin(hadSplits))].copy()
    pxdata['year'] = pxdata['TradeDate'].map(lambda x: x.year)
    pxdata = pxdata[pxdata['year'] >= start.year]
    nosplit_avgpx = pxdata.groupby(['Id', 'year'], as_index = False)['ClosePrice'].mean()
    divdata = dividend[(dividend['Id'].isin(Russell2000)) & (~dividend['Id'].isin(hadSplits))].copy()
    divdata['year'] = divdata['AnnounceDate'].map(lambda x: x.year)
    divdata = divdata[divdata['year'] >= start.year]
    divs = divdata.groupby(['Id', 'year'], as_index = False)['DivAmt'].sum()
    combined = nosplit_avgpx.merge(divs, on = ['Id', 'year'], how = 'inner')
    combined['yield'] = combined['DivAmt'] / combined['ClosePrice']
    return combined    

    