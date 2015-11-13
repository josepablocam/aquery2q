# load in data
import numpy as np
import pandas as pd

df_frame = pd.read_pickle("./tables/df_frame")
bool_arr = np.load("./tables/bool_arr")
df_groupby = pd.read_pickle("./tables/df_groupby")
s_value_counts = pd.read_pickle("./tables/s_value_counts")
df_groupby_multi_python = pd.read_pickle("./tables/df_groupby_multi_python")
mdf1 = pd.read_pickle("./tables/mdf1")
mdf2 = pd.read_pickle("./tables/mdf2")
df_multi_join = pd.read_pickle("./tables/df_multi_join")
df_join = pd.read_pickle("./tables/df_join")
s_std = pd.read_pickle("./tables/s_std")
