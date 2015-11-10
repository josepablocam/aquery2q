function date_to_monetdb {
	sed 's/\./-/g' | awk '{printf "'\''%s'\''", $1}'
}

function csv_ids_to_monetdb {
	sed "s/,/\',\'/g" | awk '{printf "'\''%s'\''", $1}'
}

# declaring variables used in queries...
PARAMPATH=./parameters

stock10=$(cat ${PARAMPATH}/stock10.csv | csv_ids_to_monetdb)
startYear10=$(cat ${PARAMPATH}/startYear10.csv | date_to_monetdb) 
endYear10=$(cat ${PARAMPATH}/endYear10.csv | date_to_monetdb) 
startYear10Plus2=$(cat ${PARAMPATH}/startYear10Plus2.csv | date_to_monetdb) 
stock1000=$(cat ${PARAMPATH}/stock1000.csv | csv_ids_to_monetdb)
start300Days=$(cat ${PARAMPATH}/start300Days.csv | date_to_monetdb) 
end300Days=$(cat ${PARAMPATH}/end300Days.csv | date_to_monetdb) 
startPeriod=$(cat ${PARAMPATH}/startPeriod.csv | date_to_monetdb) 
endPeriod=$(cat ${PARAMPATH}/endPeriod.csv | date_to_monetdb) 
sp500=$(cat ${PARAMPATH}/SP500.csv | csv_ids_to_monetdb) 
start6Mo=$(cat ${PARAMPATH}/start6Mo.csv | date_to_monetdb) 
end6Mo=$(cat ${PARAMPATH}/end6Mo.csv | date_to_monetdb) 
russell2000=$(cat ${PARAMPATH}/Russell2000.csv | csv_ids_to_monetdb) 
maxTradeDate=$(cat ${PARAMPATH}/maxTradeDate.csv | date_to_monetdb) 
maxTradeDateMinusYear=$(cat ${PARAMPATH}/maxTradeDateMinusYear.csv | date_to_monetdb) 
alloc=10000

## TURN OFF glob, avoid replacement of * in queries with directory contents
set -f

# create tables for stock data
if [ $# -eq 1 ]; then 
  if [ $1  == "-create" ]; then
    create_insert_params="";
    OLDIFS=${IFS}
    IFS=","
    for tb in "stock10" "stock1000" "sp500" "russell2000";
    do
      create_insert_params="${create_insert_params}
        DROP TABLE ${tb}; CREATE TABLE \"${tb}\"(\"id\" char(30));"
      poss=${!tb}
      for id in $poss; do
        create_insert_params="${create_insert_params} INSERT into ${tb} VALUES($id);"
      done
    done
    echo $create_insert_params | mclient -d fintime
    IFS=$OLDIFS
    # add in functions
    mclient -d fintime < load_functions_monetdb.sql
  fi
fi





