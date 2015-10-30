# Author: Jose Cambronero
# jose.cambronero@cs.nyu.edu
# A quick script to pickle pandas data frames
# to avoid reloading slowly during benchmark

import pandas as pd
import numpy as np
from datetime import datetime

# sourced from http://stackoverflow.com/questions/14446744/speed-improvement-on-large-pandas-read-csv-with-datetime-index
def parse_datetime(dt_array, cache=None):
    if cache is None:
        cache = {}
    parsed_dates = np.empty(dt_array.shape[0], dtype=object)
    for i, d_str in enumerate(dt_array):
        try:
            date = cache[d_str]
        except KeyError:
            date = pd.to_datetime(d_str)
            cache[d_str] = date
        parsed_dates[i] = date        
    return parsed_dates
    
    
def clean(df, date_cols = []):
    # remove extra space in all string columns
    is_string_col = df.dtypes == object
    for col in df.columns[is_string_col]:
        df[col] = df[col].map(lambda x: x.strip())
    # remove extra space from column headers    
    df.rename(columns = lambda x: x.strip(), inplace = True)
    # parse dates to column
    for col in date_cols:
        df[col] = parse_datetime(df[col], {})
    # return copy for convenience    
    return df
        
# read in data and clean up       
path = "/Users/josecambronero/MS/S15/aquery/src/benchmark/fintime/data/"
files = ["hist-base-file", "hist-price-file", "hist-split-file"]
base = pd.read_csv(path + "/" + files[0], sep = "|")
price = pd.read_csv(path + "/" + files[1], sep = "|")
split = pd.read_csv(path + "/" + files[2], sep = "|")

base = clean(base, ['CreateDate'])
price = clean(price, ['TradeDate'])
split = clean(split, ['SplitDate', 'EntryDate'])


# write out to pickle format
price.to_pickle("./tables/price_pandas")
base.to_pickle("./tables/base_pandas")
split.to_pickle("./tables/split_pandas")