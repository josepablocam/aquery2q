import pandas as pd
import numpy as np
import string
import sys
from numpy.random import rand as randn

# We scale our experiments to N , so all data frames are created
# relative to this size, when appropriate. 
# Meaning, if the original created a data frame of size
# 10,000, and used 100 different random numbers to populate a column, then
# our experiments will use floor(N * 100/10,000) random numbers and so on
N = int(sys.argv[1])
if (N < 100000):
    print "Benchmark size must be at least 100,000"
    sys.exit(1)


#######################################################################
# http://pandas.pydata.org/pandas-docs/vbench/vb_frame_methods.html   #
#######################################################################

#######################################################################
# frame_boolean_row_select                                            #
#######################################################################
# Reduced to 10 rows, as we're just testing selection
df_frame = pd.DataFrame(randn(N, 10))
bool_arr = np.zeros(N, dtype=bool)
# we're doing this as a fraction since our size is larger
select_size = int(N * 1000 / 10000.0)
bool_arr[:select_size] = True

# benchmark
# df_frame[bool_arr]

#######################################################################
# http://pandas.pydata.org/pandas-docs/vbench/vb_groupby.html         #
#######################################################################


#######################################################################
# groupby_multi_different_functions                                   #
#######################################################################
fac1 = np.array(['A', 'B', 'C'], dtype='O')
fac2 = np.array(['one', 'two'], dtype='O')

df_groupby = pd.DataFrame({'key1': fac1.take(np.random.randint(0, 3, size=N)),
                'key2': fac2.take(np.random.randint(0, 2, size=N)),
                'value1' : np.random.randn(N),
                'value2' : np.random.randn(N),
                'value3' : np.random.randn(N)})
                
# benchmark
# df_groupby.groupby(['key1', 'key2']).agg({'value1' : 'mean', 'value2' : 'var', 'value3' : 'sum'})           
                                                   
#######################################################################
# series_value_counts_int64                                           #
#######################################################################
n_diff_values = int(N * 1000 / 100000.0)
s_value_counts = pd.Series(np.random.randint(0, n_diff_values, size=N))

# benchmark
# s_value_counts.value_counts()



#######################################################################
# group by multi python                                               #
#######################################################################
# similarly, we use percentage based here to adjust for size
ngroups = int(N * 100/100000.0)

def get_test_data(ngroups=100, n=N):
    unique_groups = range(ngroups)
    arr = np.asarray(np.tile(unique_groups, n / ngroups), dtype=object)
    if len(arr) < n:
        arr = np.asarray(list(arr) + unique_groups[:n - len(arr)], dtype=object)
    np.random.shuffle(arr)
    return arr

# aggregate multiple columns
df_groupby_multi_python = pd.DataFrame({'key1' : get_test_data(ngroups=ngroups),
                'key2' : get_test_data(ngroups=ngroups),
                'data1' : np.random.randn(N),
                'data2' : np.random.randn(N)})

# benchmark
# df_groupby_multi_python.groupby(['key1', 'key2'])['data1'].agg(lambda x: x.values.sum())


#######################################################################
# http://pandas.pydata.org/pandas-docs/vbench/vb_join_merge.html      #
#######################################################################

#######################################################################
# append_frame_single_mixed                                           #
#######################################################################
df1_append = pd.DataFrame(np.random.randn(N, 4), columns=['A', 'B', 'C', 'D'])
df2_append = df1_append.copy()
df2_append.index = np.arange(N, 2 * N)
mdf1 = df1_append.copy()
mdf1['obj1'] = 'bar'
mdf1['obj2'] = 'bar'
mdf1['int1'] = 5
mdf1.consolidate(inplace=True)
mdf2 = mdf1.copy()
mdf2.index = df2_append.index

# benchmark
# mdf1.append(mdf2)


#######################################################################
# join_dataframe_index_multi                                          #
#######################################################################
def choice(x, size=10):
    try:
        return np.random.choice(x, size=size)
    except AttributeError:
        return np.random.randint(len(x), size=size).choose(x)
        

RANDS_CHARS = np.array(list(string.ascii_letters + string.digits),dtype=(np.str_, 1))

                      
def rands(nchars):
    return ''.join(choice(RANDS_CHARS, nchars))
            

times10 = int(N * (10 / 100000.0))
times1000 = int(N * (1000 / 100000.0))
level1 = np.array([rands(10) for _ in xrange(times10)], dtype='O')
level2 = np.array([rands(10) for _ in xrange(times1000)], dtype='O')
label1 = np.arange(times10).repeat(1000)
label2 = np.tile(np.arange(times1000), 10)

key1 = np.tile(level1.take(label1), 10)
key2 = np.tile(level2.take(label2), 10)


index2 = pd.MultiIndex(levels=[level1, level2], labels=[label1, label2])
df_multi_join = pd.DataFrame(np.random.randn(len(index2), 4), index=index2, 
    columns=['A', 'B', 'C', 'D'])


df_join = pd.DataFrame({'data1' : np.random.randn(N),
                'data2' : np.random.randn(N),
                'key1' : key1,
                'key2' : key2})


# benchmark
# merge(df_join, df_multi_join, on=['key1', 'key2'], how = 'inner')
# note that the above produced the following error
# Traceback (most recent call last):
#   File "<stdin>", line 1, in <module>
#   File "/Library/Python/2.7/site-packages/pandas/tools/merge.py", line 34, in merge
#     copy=copy, indicator=indicator)
#   File "/Library/Python/2.7/site-packages/pandas/tools/merge.py", line 190, in __init__
#     self.join_names) = self._get_merge_keys()
#   File "/Library/Python/2.7/site-packages/pandas/tools/merge.py", line 403, in _get_merge_keys
#     right_keys.append(right[rk]._values)
#   File "/Library/Python/2.7/site-packages/pandas/core/frame.py", line 1914, in __getitem__
#     return self._getitem_column(key)
#   File "/Library/Python/2.7/site-packages/pandas/core/frame.py", line 1921, in _getitem_column
#     return self._get_item_cache(key)
#   File "/Library/Python/2.7/site-packages/pandas/core/generic.py", line 1090, in _get_item_cache
#     values = self._data.get(item)
#   File "/Library/Python/2.7/site-packages/pandas/core/internals.py", line 3102, in get
#     loc = self.items.get_loc(item)
#   File "/Library/Python/2.7/site-packages/pandas/core/index.py", line 1692, in get_loc
#     return self._engine.get_loc(_values_from_object(key))
#   File "pandas/index.pyx", line 137, in pandas.index.IndexEngine.get_loc (pandas/index.c:3979)
#   File "pandas/index.pyx", line 157, in pandas.index.IndexEngine.get_loc (pandas/index.c:3843)
#   File "pandas/hashtable.pyx", line 668, in pandas.hashtable.PyObjectHashTable.get_item (pandas/hashtable.c:12265)
#   File "pandas/hashtable.pyx", line 676, in pandas.hashtable.PyObjectHashTable.get_item (pandas/hashtable.c:12216)
# KeyError: 'key1'
#
# So we replace with
# merge(df_join, df_multi_join, left_on=['key1', 'key2'], right_index = True, how = 'inner')
# which works and should have the same semantics


#######################################################################
#  http://pandas.pydata.org/pandas-docs/vbench/vb_stat_ops.html       # 
#######################################################################

#######################################################################
#  stat_ops_series_std                                                # 
#######################################################################

s_std = pd.Series(np.random.randn(N), index=np.arange(N))
s_std[::2] = np.nan

# benchmark
# s_std.std()


# Write out everything as pickled data and csv (for aquery purposes)
def main():
    # pickled
    df_frame.to_pickle("./tables/df_frame")
    bool_arr.dump("./tables/bool_arr")
    df_groupby.to_pickle("./tables/df_groupby")
    s_value_counts.to_pickle("./tables/s_value_counts")
    df_groupby_multi_python.to_pickle("./tables/df_groupby_multi_python")
    mdf1.to_pickle("./tables/mdf1")
    mdf2.to_pickle("./tables/mdf2")
    df_multi_join.to_pickle("./tables/df_multi_join")
    df_join.to_pickle("./tables/df_join")
    s_std.to_pickle("./tables/s_std")
    # in csv format for aquery
    df_frame.to_csv("./tables/df_frame.csv", index = False, header = True)
    np.savetxt(fname = "./tables/bool_arr.csv", X = bool_arr, delimiter = ",")
    df_groupby.to_csv("./tables/df_groupby.csv", index = False, header = True)
    s_value_counts.to_csv("./tables/s_value_counts.csv", index = False, header = False)
    df_groupby_multi_python.to_csv("./tables/df_groupby_multi_python.csv",index = False, header = True)
    mdf1.to_csv("./tables/mdf1.csv", index = False, header = True)
    mdf2.to_csv("./tables/mdf2.csv", index = False, header = True)
    
    # we name index columns before writing them out
    df_multi_join.index.names = [ 'key1', 'key2' ]
    df_multi_join.to_csv("./tables/df_multi_join.csv", index = True, header = True)
    df_join.to_csv("./tables/df_join.csv", index = False, header = True)
    s_std.to_csv("./tables/s_std.csv", index = False, header = False)
    


if __name__ == '__main__':
    main()






