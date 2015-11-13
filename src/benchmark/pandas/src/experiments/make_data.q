readpath:hsym `$"./tables"
getcsvpath:{` sv readpath,` sv x,`csv}
df_frame:{(`$"c",/:string cols x) xcol x}(10#"F"; enlist ",") 0:getcsvpath `df_frame
bool_arr:1="F"$read0 getcsvpath`bool_arr
df_groupby:("SSFFF"; enlist ",") 0:getcsvpath`df_groupby
s_value_counts:([]val:"I"$read0 getcsvpath`s_value_counts)
df_groupby_multi_python:("FFII";enlist ",") 0:getcsvpath`df_groupby_multi_python
mdf1:("FFFFSSI"; enlist ",") 0:getcsvpath`mdf1
mdf2:("FFFFSSI"; enlist ",") 0:getcsvpath`mdf2
df_multi_join:("SSFFFF";enlist ",") 0:getcsvpath`df_multi_join
df_join:("FFSS";enlist ",") 0:getcsvpath`df_join
s_std:([]val:"F"$read0 getcsvpath`s_std)

// save out in binary format for ease reading in aquery
getbinpath:{` sv readpath,`q,x}


save getbinpath`df_frame
save getbinpath`bool_arr
save getbinpath`df_groupby
save getbinpath`s_value_counts
save getbinpath`df_groupby_multi_python
save getbinpath`mdf1
save getbinpath`mdf2
save getbinpath`df_multi_join
save getbinpath`df_join
save getbinpath`s_std
exit 0



