# ********* QUERY 0 ****************
# 95 quantile
q0="SELECT quantile(val, 0.95) from nums;"

# ********* QUERY 1 ****************
# 5 quantile
q1="SELECT quantile(val, 0.05) from nums;"

mkdir -p monetdb_queries/
echo $q0 > monetdb_queries/q0.sql
echo $q1 > monetdb_queries/q1.sql
