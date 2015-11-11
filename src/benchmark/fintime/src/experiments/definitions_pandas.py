from datetime import datetime, timedelta
import pandas as pd
import numpy as np


# load all necessary benchmarking data
from load_data import *

# set up a moving average function that behaves like q
# meaning, for a moving window of size x, while we have |n| < x
# we cumulatively and divide by n
def qma(v, w):
    mavg = pd.rolling_mean(v, w)
    isnull = pd.isnull(mavg)
    # assume n > 0, since that is the case unless w = 1
    n = np.sum(isnull)
    replace = np.cumsum(v[isnull]) / np.arange(1.0, n + 1)
    mavg[isnull] = replace
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
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] < end)]
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

    return pd.concat(frames)


# ********* QUERY 1 ****************
# Adjust all prices and volumes (prices are multiplied by the split factor and volumes are divided
# by the split factor) for a set of 1000 stocks to reflect the split events during a specified 300
# day period, assuming that events occur before the first trade of the split date. These are called
# split-adjusted prices and volumes.
def q1():
    start = start300Days
    end = start300Days + timedelta(days = 300)
    pxdata = price[price['Id'].isin(stock1000)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] < end)]
    splitdata = split[split['Id'].isin(stock1000)]
    splitdata = splitdata[(splitdata['SplitDate'] >= start) & (splitdata['SplitDate'] < end)]
    joindata = pxdata.merge(splitdata, on = 'Id', how = "inner")
    # prices get adjusted by splits that happen later
    joindata = joindata[joindata['TradeDate'] <= joindata['SplitDate']]
    # adjustment factor for each stock's trade date
    adjFactors = joindata.groupby(['Id', 'TradeDate'], as_index = False)['SplitFactor'].agg(np.prod)
    adjFactors.columns = ['Id', 'TradeDate', 'SF']
    # only care about adjusting those that have splits, so inner join
    allData = adjFactors.merge(pxdata, on = ['Id', 'TradeDate'], how = 'inner')
    allData['HighPrice'] = allData['HighPrice'] / allData['SF']
    allData['LowPrice'] = allData['LowPrice'] / allData['SF']
    allData['ClosePrice'] = allData['ClosePrice'] / allData['SF']
    allData['OpenPrice'] = allData['OpenPrice'] / allData['SF']
    allData['Volume'] = allData['Volume'] * allData['SF']
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
    return results.sort(columns = ['Id', 'TradeDate'], ascending = True)
 

# ********* QUERY 3 + 4 ****************
# Calculate the value of the S&P500 and Russell 2000 index for a specified day using unadjusted
# prices and the index composition of the 2 indexes (see appendix for spec) on the specified day
# Divisor of 8.9bn taken from https://en.wikipedia.org/wiki/S%26P_500
def q3():
    pxdata = price[price['Id'].isin(SP500) & (price['TradeDate'] == startPeriod)]
    indexValue = (pxdata['ClosePrice'] * pxdata['Volume']).sum() / 8.9e9
    return pd.DataFrame({'index' : [ indexValue ] })
    
def q4():
    pxdata = price[price['Id'].isin(Russell2000) & (price['TradeDate'] == startPeriod)]
    indexValue = (pxdata['ClosePrice'] * pxdata['Volume']).sum() / 8.9e9
    return pd.DataFrame({'index' : [ indexValue ] })
        

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
    splitdata = splitdata[(splitdata['SplitDate'] >= start) & (splitdata['SplitDate'] < end)]
    # join to adjust prices by split factors
    joindata = pxdata.merge(splitdata, on = 'Id', how = "inner")
    # prices get adjusted by splits that happen later
    joindata = joindata[joindata['TradeDate'] <= joindata['SplitDate']]
    # adjustment factor for each stock's trade date
    adjFactors = joindata.groupby(['Id', 'TradeDate'], as_index = False)['SplitFactor'].agg(np.prod)
    adjFactors.columns = ['Id', 'TradeDate', 'SF']
    adjData = adjFactors.merge(pxdata, on = ['Id', 'TradeDate'], how = 'inner')
    adjData['ClosePrice'] = adjData['ClosePrice'] / adjData['SF']
    allData = pxdata.merge(adjData, on = ['Id', 'TradeDate'], how = 'left', suffixes = ['_pxdata', '_adjdata'])
    allData['ClosePrice'] = allData['ClosePrice_adjdata'].fillna(allData['ClosePrice_pxdata'])
    relevantCols = ['Id', 'TradeDate', 'ClosePrice']
    allData = allData[relevantCols]
    sortedData = allData.sort(columns = ['Id','TradeDate'], ascending = True)
    # groupby preserves order 
    grouped = sortedData[['Id', 'ClosePrice']].groupby('Id')
    # note that we use a rolling mean function that emulates q's treatment of edge cases
    sortedData['p21'] = grouped['ClosePrice'].transform(lambda x: qma(x, 21))
    sortedData['p5'] = grouped['ClosePrice'].transform(lambda x: qma(x, 5))
    # set a copy of results to a global variable, so can use in q6
    # as per query description
    global query5Table
    query5Table = sortedData
    return sortedData    

# ********* QUERY 6 ****************
# (Based on the previous query) 
# Find the points (specific days) when the 5-month moving average intersects the 21-day 
# moving average for these stocks. The output is to be sorted by id and date.
# Note that given differences in moving average calculation, this won't tie out 100%
# to results in aquery/q, but we focus on performance vs exact results
def q6():
    crossAbove = (query5Table['p5'].shift(1) <= query5Table['p21'].shift(1)) & (query5Table['p5'] > query5Table['p21'])
    crossBelow = (query5Table['p5'].shift(1) >= query5Table['p21'].shift(1)) & (query5Table['p5'] < query5Table['p21'])
    sameId = query5Table['Id'].shift(1) == query5Table['Id']
    crosses = query5Table[sameId & (crossAbove | crossBelow)]
    return crosses[['Id', 'TradeDate', 'ClosePrice']]
    

# ********* QUERY 7 ****************
# Determine the value of $100,000 now if 1 year ago it was invested equally in 10 specified
# stocks (i.e. allocation for each stock is $10,000). The trading strategy is: When the 20-day
# moving average crosses over the 5-month moving average the complete allocation for that stock
# is invested and when the 20-day moving average crosses below the 5-month moving average the entire
# position is sold. The trades happen on the closing price of the trading day.
def q7():
    # creating moving price information for signals
    n = np.size(stock10)
    seedMoneyPerStock = 10000
    start = price['TradeDate'].max() - timedelta(days = 365)
    pxdata = price[price['Id'].isin(stock10)]
    pxdata = pxdata[pxdata['TradeDate'] >= start]
    pxdata = pxdata.sort(['Id', 'TradeDate'], ascending = True)
    grouped = pxdata.groupby('Id')
    pxdata['m5month'] = grouped['ClosePrice'].transform(lambda x: qma(x, 31 * 5))
    pxdata['m20day'] = grouped['ClosePrice'].transform(lambda x: qma(x, 20))
    pxdata['isSignal'] = (pxdata['Id'].shift(1) == pxdata['Id']) & (
       ( # cross under -> sell signal
           (pxdata['m5month'].shift(1) <= pxdata['m20day'].shift(1)) &
           (pxdata['m5month'] > pxdata['m20day'])
        )
     | # alternatively
        ( # cross over -> buy signal
            (pxdata['m5month'].shift(1) >= pxdata['m20day'].shift(1)) &
            (pxdata['m5month'] < pxdata['m20day'])
        )
     )
    pxdata['buySignal'] = pxdata['m5month'] < pxdata['m20day'] # buy signal, if coincides with isSignal
    signals = pxdata[pxdata['isSignal']]
    grouped = signals.groupby('Id')
    # a vectorized approach to the strategy is
    # - can't sell before we buy, so need to wait for first buy signal to do anything w/ 10k
    # after that, replace each buy signal with 1 / ClosePrice (how many shares can you buy)
    # and every sell signal with ClosePrice (how much can you sell it for)
    # result of strategy then is 10,000 * product of "actions"
    # if last action is buy, then multiply by latest price.
    # result: total valuation per stock simulating strategy (ignoring fees etc)
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
    results = pxdata.groupby('Id', as_index = False).last()
    results['valuation'] = valuations[results['Id']].values
    # size of stock10...incase we change that later on
    results['value'] = np.maximum(np.ones(np.size(stock10)), results['ClosePrice'] * results['buySignal']) * results['valuation']
    results['value'] = results['value'].fillna(seedMoneyPerStock)
    return results[['Id', 'value']]




# ********* QUERY 8 ****************
# Find the pair-wise coefficients of correlation in a set of 10 securities for a 2 year period.
# Sort the securities by the coefficient of correlation, indicating the pair of securities 
# corresponding to that row. [Note: coefficient of correlation defined in appendix]
def q8():
    start = startYear10
    end = startYear10 + timedelta(days = 365 * 2)
    pxdata = price[price['Id'].isin(stock10)]
    pxdata = pxdata[(pxdata['TradeDate'] >= start) & (pxdata['TradeDate'] < end)]
    pxdata = pxdata.sort(['TradeDate'], ascending = True)
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
    return flatCorrs.sort(['corrCoeff'], ascending = False)
  
    
# ********* QUERY 9 ****************
# Determine the yearly dividends and annual yield (dividends/average closing price) for the past 3
# years for all the stocks in the Russell 2000 index that did not split during that period.
# Use unadjusted prices since there were no splits to adjust for.  
def q9():
    start = price['TradeDate'].max() - timedelta(days = 365 * 3)
    splitdata = split[split['Id'].isin(Russell2000)]
    splitdata = splitdata[splitdata['SplitDate'] >= start]
    hadSplits = pd.unique(splitdata['Id'])
    pxdata = price[(price['Id'].isin(Russell2000)) & (~price['Id'].isin(hadSplits))]
    pxdata = pxdata[pxdata['TradeDate'] >= start]
    pxdata['year'] = pxdata['TradeDate'].map(lambda x: x.year)
    nosplit_avgpx = pxdata.groupby(['Id', 'year'], as_index = False)['ClosePrice'].mean()
    divdata = dividend[(dividend['Id'].isin(Russell2000)) & (~dividend['Id'].isin(hadSplits))]
    divdata = divdata[divdata['XdivDate'] >= start]
    divdata['year'] = divdata['XdivDate'].map(lambda x: x.year)
    divs = divdata.groupby(['Id', 'year'], as_index = False)['DivAmt'].sum()
    combined = nosplit_avgpx.merge(divs, on = ['Id', 'year'], how = 'left')
    combined['DivAmt'] = combined['DivAmt'].fillna(0)
    combined['yield'] = combined['DivAmt'] / combined['ClosePrice']
    return combined    
    
    
    