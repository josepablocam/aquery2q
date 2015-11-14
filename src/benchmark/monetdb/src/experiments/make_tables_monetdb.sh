DATAPATH=$(pwd)/tables/

if [ $1 == "-create" ]; then
 echo "DROP TABLE nums;" | mclient -d quantile
 echo 'CREATE TABLE "nums"(val integer);' | mclient -d quantile
 echo "COPY INTO nums FROM '${DATAPATH}/random_numbers.txt' USING DELIMITERS '\n';" | mclient -d quantile
 echo "DROP FUNCTION quantile;" | mclient -d quantile
 mclient -d quantile < load_functions_monetdb.sql
fi
