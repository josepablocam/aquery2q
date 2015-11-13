from pandas import *
import numpy as np
from load_data import *

#######################################################################
# http://pandas.pydata.org/pandas-docs/vbench/vb_frame_methods.html   #
#######################################################################

#######################################################################
# frame_boolean_row_select                                            #
#######################################################################
def b0():
    return df_frame[bool_arr]

#######################################################################
# http://pandas.pydata.org/pandas-docs/vbench/vb_groupby.html         #
#######################################################################

#######################################################################
# groupby_multi_different_functions                                   #
####################################################################### 
def b1():
    return df_groupby.groupby(['key1', 'key2']).agg(
        {'value1' : 'mean','value2' : 'var','value3' : 'sum'}
        )
        
#######################################################################
# series_value_counts_int64                                           #
#######################################################################        
def b2():
    return s_value_counts.value_counts()

#######################################################################
# group by multi python                                               #
#######################################################################
def b3():
    return df_groupby_multi_python.groupby(['key1', 'key2'])['data1'].agg(
        lambda x: x.values.sum()
    )
    

#######################################################################
# http://pandas.pydata.org/pandas-docs/vbench/vb_join_merge.html      #
#######################################################################

#######################################################################
# append_frame_single_mixed                                           #
#######################################################################
def b4():
    return mdf1.append(mdf2)

#######################################################################
# join_dataframe_index_multi                                          #
#######################################################################
def b5():
    return merge(df_join, df_multi_join, left_on=['key1', 'key2'], 
        right_index = True, how = 'inner')
    

#######################################################################
#  http://pandas.pydata.org/pandas-docs/vbench/vb_stat_ops.html       # 
#######################################################################

#######################################################################
#  stat_ops_series_std                                                # 
#######################################################################
def b6():
    return s_std.std()
    
    
    