FINTIME_OPS="uid=DBA;pwd=sql;dbn=fintime"
TMP_IQ_FILE=iq_params_sql.tmp

function date_to_sybase {
	sed 's/\./-/g' | awk '{printf "'\''%s'\''", $1}'
}

function csv_ids_to_sybase {
	sed "s/,/\',\'/g" | awk '{printf "'\''%s'\''", $1}'
}

# declaring variables used in queries...
PARAMPATH=./parameters

stock10=$(cat ${PARAMPATH}/stock10.csv | csv_ids_to_sybase)
startYear10=$(cat ${PARAMPATH}/startYear10.csv | date_to_sybase) 
endYear10=$(cat ${PARAMPATH}/endYear10.csv | date_to_sybase) 
startYear10Plus2=$(cat ${PARAMPATH}/startYear10Plus2.csv | date_to_sybase) 
stock1000=$(cat ${PARAMPATH}/stock1000.csv | csv_ids_to_sybase)
start300Days=$(cat ${PARAMPATH}/start300Days.csv | date_to_sybase) 
end300Days=$(cat ${PARAMPATH}/end300Days.csv | date_to_sybase) 
startPeriod=$(cat ${PARAMPATH}/startPeriod.csv | date_to_sybase) 
endPeriod=$(cat ${PARAMPATH}/endPeriod.csv | date_to_sybase) 
sp500=$(cat ${PARAMPATH}/SP500.csv | csv_ids_to_sybase) 
start6Mo=$(cat ${PARAMPATH}/start6Mo.csv | date_to_sybase) 
end6Mo=$(cat ${PARAMPATH}/end6Mo.csv | date_to_sybase) 
russell2000=$(cat ${PARAMPATH}/Russell2000.csv | csv_ids_to_sybase) 
maxTradeDate=$(cat ${PARAMPATH}/maxTradeDate.csv | date_to_sybase) 
maxTradeDateMinusYear=$(cat ${PARAMPATH}/maxTradeDateMinusYear.csv | date_to_sybase) 
maxTradeDateMinus3Years=$(cat ${PARAMPATH}/maxTradeDateMinus3Years.csv | date_to_sybase) 
alloc=10000

## TURN OFF glob, avoid replacement of * in queries with directory contents
set -f

# create tables for stock data that is randomly generated
if [ $# -eq 1 ]
  then 
  if [ $1  == "-create" ]
    then
    rm -rf ${TMP_IQ_FILE}; touch ${TMP_IQ_FILE};
    OLDIFS=${IFS}
    IFS=","
    for tb in "stock10" "stock1000";
    do
       echo "DROP TABLE ${tb}; CREATE TABLE \"${tb}\"(\"INSTRUMENT_ID\" char(30));" >> ${TMP_IQ_FILE}
      poss=${!tb}
      for id in $poss; do
        echo "INSERT into ${tb} VALUES($id);" >> ${TMP_IQ_FILE}
      done
    done
   
    # handle sp500 and russell2000 separately
    echo 'DROP TABLE MARKET_INDEX; DROP TABLE INDEX_CMPSTN;' >> ${TMP_IQ_FILE}
    echo 'CREATE TABLE INDEX_CMPSTN("INDEX_NAME" char(30), "INSTRUMENT_ID" char(30));' >> ${TMP_IQ_FILE}
    echo 'CREATE TABLE MARKET_INDEX("INDEX_NAME" char(30));' >> ${TMP_IQ_FILE}
    echo "INSERT INTO MARKET_INDEX VALUES('SP 500');" >> ${TMP_IQ_FILE}
    echo "INSERT INTO MARKET_INDEX VALUES('Russell 2000');" >> ${TMP_IQ_FILE}
      
    for tb in "sp500" "russell2000"; do
      if [ ${tb} == "sp500" ]
        then
          indexName="'SP 500'"
        else
          indexName="'Russell 2000'"
      fi      
      poss=${!tb}
      for id in $poss; do
          echo "INSERT INTO INDEX_CMPSTN VALUES(${indexName}, ${id});" >> ${TMP_IQ_FILE}
      done
    done
    
    # Create the temporary history tables used in queries
    echo 'CREATE TABLE hist_temp(
    "row_nbr" int, 
    "INSTRUMENT_ID" char(30),
    "TRADE_DATE"        date,
    "CLOSE_PRICE"       double,
    "SPLIT_FACTOR"      double);' >> ${TMP_IQ_FILE}
    
    echo 'CREATE TABLE hist6_temp(
    "row_nbr" int,
    "INSTRUMENT_ID"     char(30),
    "TRADE_DATE"        date,
    "avg_5day"       double,
    "avg_21day"      double);' >> ${TMP_IQ_FILE}
    
    echo 'CREATE TABLE hist7_temp(
        "row_nbr" int,
        "INSTRUMENT_ID"     char(30),
        "TRADE_DATE"        date,
        "avg_5mth"       double,
        "avg_21day"       double);' >> ${TMP_IQ_FILE}
    
    #write them out
    dbisql -nogui -c=${FINTIME_OPS} -onerror continue ${TMP_IQ_FILE}
    IFS=$OLDIFS
  fi
fi


# Source: http://infocenter.sybase.com/help/index.jsp?topic=/com.sybase.infocenter.dc01849.0500/doc/html/asc1229989301618.html
# Query definitions
# ********* QUERY 0 ****************
# 	Get the closing price of a set of 10 stocks for a 10-year period and
# 	group into weekly, monthly and yearly aggregates. For each aggregate
# 	period determine the low, high and average closing price value.
# 	The output should be sorted by id and trade date.
q0="
commit;

SELECT sh.INSTRUMENT_ID,
DATEPART(yy,sh.TRADE_DATE) AS YEAR,
DATEPART(mm,sh.TRADE_DATE) AS MON,
DATEPART(wk,sh.TRADE_DATE) AS WEEK, 
MAX(sh.CLOSE_PRICE) AS MAX_PRICE,
MIN(sh.CLOSE_PRICE) AS MIN_PRICE,
AVG(sh.CLOSE_PRICE) AS AVG_PRICE
FROM STOCK_HISTORY sh 
WHERE
sh.TRADE_DATE BETWEEN ${startYear10}
	and ${endYear10}
and sh.INSTRUMENT_ID in (${stock10})
GROUP BY ROLLUP ( sh.INSTRUMENT_ID,
DATEPART(yy,sh.TRADE_DATE),
	 DATEPART(mm,sh.TRADE_DATE),
DATEPART(wk,sh.TRADE_DATE))
;
"

# ********* QUERY 1 ****************
# Adjust all prices and volumes (prices are multiplied by the split factor and
# volumes are divided by the split factor) for a set of 1000 stocks to reflect the
# split events during a specified 300 day period, assuming that events occur before
# the first trade of the split date. These are called split-adjusted prices and volumes.
# Modifications: take random list of 1000 stocks, use provided dates
q1="
commit; 

SELECT B.INSTRUMENT_ID, TRADE_DATE,
B.HIGH_PRICE * IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) H_PRC,
B.LOW_PRICE * IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) L_PRC,
B.CLOSE_PRICE * IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) C_PRC,
B.OPEN_PRICE *IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) O_PRC,
B.Volume/IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) VOL
FROM STOCK_HISTORY AS B 
	left outer join SPLIT_EVENT A
	on B.INSTRUMENT_ID = A.INSTRUMENT_ID 
	AND B.TRADE_DATE < A.EFFECTIVE_DATE
WHERE 
A.INSTRUMENT_ID in (${stock1000}) AND
B.TRADE_DATE BETWEEN ${start300Days}
	and ${end300Days} 
GROUP BY B.INSTRUMENT_ID, 
TRADE_DATE ,
B.HIGH_PRICE,
B.LOW_PRICE,
B.CLOSE_PRICE, 
B.OPEN_PRICE,
B.Volume
; 
"


# original q1="
# SELECT B.TRADING_SYMBOL, TRADE_DATE,
# B.HIGH_PRICE * IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) H_PRC,
# B.LOW_PRICE * IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) L_PRC,
# B.CLOSE_PRICE * IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) C_PRC,
# B.OPEN_PRICE *IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) O_PRC,
# B.Volume/IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) VOL
# FROM STOCK_HISTORY AS B
#   left outer join SPLIT_EVENT A
#   on B.INSTRUMENT_ID = A.INSTRUMENT_ID
#   AND B.TRADE_DATE < A.EFFECTIVE_DATE
# WHERE  B.TRADING_SYMBOL BETWEEN 'AAA' AND 'BML'
#   AND LENGTH(B.TRADING_SYMBOL) = 3
#   and B.TRADE_DATE BETWEEN '2005-03-03'
#   and '2005-12-03'
# GROUP BY B.TRADING_SYMBOL,
# TRADE_DATE ,
# B.HIGH_PRICE,
# B.LOW_PRICE,
# B.CLOSE_PRICE,
# B.OPEN_PRICE,
# B.Volume
# ;
# "


#********* QUERY 2 ****************
# For each stock in a specified list of 1000 stocks, find the differences between the daily 
# high and  daily low on the day of each split event during a specified period.
# Modifications: take random list of 1000 stocks, use provided dates
q2="
commit;

SELECT sh.INSTRUMENT_ID, sh.HIGH_PRICE - sh.LOW_PRICE AS D_PRICE, sh.TRADE_DATE
FROM   STOCK_HISTORY AS sh 
inner join SPLIT_EVENT A
on sh.INSTRUMENT_ID = A.INSTRUMENT_ID 
AND sh.TRADE_DATE = A.EFFECTIVE_DATE
WHERE  sh.INSTRUMENT_ID in (${stock1000})
and sh.TRADE_DATE BETWEEN ${startPeriod}
and ${endPeriod}
ORDER  BY sh.INSTRUMENT_ID 
;
"

# q2="
# SELECT sh.TRADING_SYMBOL, sh.HIGH_PRICE - sh.LOW_PRICE AS D_PRICE, sh.TRADE_DATE
# FROM   STOCK_HISTORY AS sh
# inner join SPLIT_EVENT A
# on sh.INSTRUMENT_ID = A.INSTRUMENT_ID
# AND sh.TRADE_DATE = A.EFFECTIVE_DATE
# WHERE  sh.TRADING_SYMBOL BETWEEN 'AAA' AND 'BML'
# AND LENGTH(sh.TRADING_SYMBOL) = 3
# and sh.TRADE_DATE BETWEEN '2005-08-04'
# and '2005-10-04'
# ORDER  BY sh.TRADING_SYMBOL
# ;
# "

# ********* QUERY 3 + 4 ****************
# Calculate the value of the S&P500 and Russell 2000 index for a specified day using
# unadjusted prices and the index composition of the 2 indexes (see appendix for spec) on
# the specified day
# Modifications: break up into 2 queries, and take random day
q3="
commit;

Select ii.INDEX_NAME, AVG(sh.CLOSE_PRICE) as AVERAGE_CLOSE_PRICE
FROM MARKET_INDEX AS ii 
inner join INDEX_CMPSTN AS ic
	on ii.INDEX_NAME = ic.INDEX_NAME 
inner join STOCK_HISTORY AS sh
on ic.INSTRUMENT_ID = sh.INSTRUMENT_ID
and sh.TRADE_DATE = ${startPeriod}
WHERE ii.INDEX_NAME in ('SP 500') 
GROUP BY
ii.INDEX_NAME
;
"

# q3="
# Select ii.INDEX_NAME, AVG(sh.CLOSE_PRICE) as AVERAGE_CLOSE_PRICE
# FROM MARKET_INDEX AS ii
# inner join INDEX_CMPSTN AS ic
#   on ii.MARKET_INDEX_ID = ic.MARKET_INDEX_ID
# inner join STOCK_HISTORY AS sh
# on ic.INSTRUMENT_ID = sh.INSTRUMENT_ID
# and sh.TRADE_DATE = '2005-03-03'
# WHERE ii.INDEX_NAME in ('S&P 500')
# GROUP BY
# ii.INDEX_NAME
# ;
# "

q4="
commit;

Select ii.INDEX_NAME, AVG(sh.CLOSE_PRICE) as AVERAGE_CLOSE_PRICE
FROM MARKET_INDEX AS ii 
inner join INDEX_CMPSTN AS ic
	on ii.INDEX_NAME = ic.INDEX_NAME 
inner join STOCK_HISTORY AS sh
on ic.INSTRUMENT_ID = sh.INSTRUMENT_ID
and sh.TRADE_DATE = ${startPeriod}
WHERE ii.INDEX_NAME in ('Russell 2000') 
GROUP BY
ii.INDEX_NAME
;
"

# q4="
# Select ii.INDEX_NAME, AVG(sh.CLOSE_PRICE) as AVERAGE_CLOSE_PRICE
# FROM MARKET_INDEX AS ii
# inner join INDEX_CMPSTN AS ic
#   on ii.MARKET_INDEX_ID = ic.MARKET_INDEX_ID
# inner join STOCK_HISTORY AS sh
# on ic.INSTRUMENT_ID = sh.INSTRUMENT_ID
# and sh.TRADE_DATE = '2005-03-03'
# WHERE ii.INDEX_NAME in ('Russell 2000')
# GROUP BY
# ii.INDEX_NAME
# ;
# "


# ********* QUERY 5 ****************
# Find the 21-day and 5-day moving average price for a specified list of
# 1000 stocks during a 6-month period. (Use split adjusted prices)
# Modifications: take random dates, make last date not-inclusive
q5="
truncate table hist_temp;
commit;

insert hist_temp
SELECT number(),B.INSTRUMENT_ID, B.TRADE_DATE, B.CLOSE_PRICE,
IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) 
FROM STOCK_HISTORY AS B
left outer join SPLIT_EVENT as A
on B.INSTRUMENT_ID = A.INSTRUMENT_ID
AND B.TRADE_DATE < A.EFFECTIVE_DATE 
WHERE B.INSTRUMENT_ID in (${stock1000})
and B.TRADE_DATE >= ${start6Mo}
and B.TRADE_DATE < ${end6Mo}
GROUP BY B.INSTRUMENT_ID,
B.TRADE_DATE, B.CLOSE_PRICE
ORDER BY B.INSTRUMENT_ID,
B.TRADE_DATE;

SELECT x.INSTRUMENT_ID, x.TRADE_DATE, AVG_5DAY , AVG_21DAY
FROM (SELECT B.INSTRUMENT_ID, B.TRADE_DATE,
AVG(C.CLOSE_PRICE * B.SPLIT_FACTOR ) avg_5day
FROM hist_temp as B 
left outer join hist_temp as C
on B.INSTRUMENT_ID = C.INSTRUMENT_ID
and c.row_nbr BETWEEN b.row_nbr - 5 and b.row_nbr 
Where B.TRADE_DATE >= ${start6Mo}
GROUP BY B.INSTRUMENT_ID,B.TRADE_DATE) x,
(SELECT B.INSTRUMENT_ID, B.TRADE_DATE,
AVG(C.CLOSE_PRICE * B.SPLIT_FACTOR ) avg_21day
FROM hist_temp as B 
left outer join hist_temp as C
on B.INSTRUMENT_ID = C.INSTRUMENT_ID
and c.row_nbr BETWEEN b.row_nbr - 21 and b.row_nbr 

Where B.TRADE_DATE >= ${start6Mo}
GROUP BY B.INSTRUMENT_ID, B.TRADE_DATE) y 
where x.INSTRUMENT_ID = y.INSTRUMENT_ID
and x.TRADE_DATE = y.TRADE_DATE
;
"

# ********* QUERY 6 ****************
# (Based on the previous query) 
# Find the points (specific days) when the 5-month moving average intersects 
# the 21-day moving average for these stocks. The output is to be sorted by id and date.
q6="
truncate table hist_temp;
truncate table hist6_temp;
commit;

insert hist_temp
SELECT number(),B.INSTRUMENT_ID, B.TRADE_DATE, B.CLOSE_PRICE,
IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) 
FROM STOCK_HISTORY AS B
left outer join SPLIT_EVENT as A
on B.INSTRUMENT_ID = A.INSTRUMENT_ID
AND B.TRADE_DATE < A.EFFECTIVE_DATE 
WHERE B.INSTRUMENT_ID in (${stock1000})
and B.TRADE_DATE >= ${start6Mo}
and B.TRADE_DATE <= ${end6Mo}
GROUP BY B.INSTRUMENT_ID,
B.TRADE_DATE, B.CLOSE_PRICE
ORDER BY B.INSTRUMENT_ID,
B.TRADE_DATE;

Insert hist6_temp
SELECT number(),x.INSTRUMENT_ID, x.TRADE_DATE, avg_5day,
avg_21day
FROM (SELECT B.INSTRUMENT_ID, B.TRADE_DATE,
AVG(C.CLOSE_PRICE * B.SPLIT_FACTOR)  avg_5day
FROM hist_temp as B
left outer join hist_temp as C
on B.INSTRUMENT_ID = C.INSTRUMENT_ID
and c.row_nbr BETWEEN b.row_nbr - 5 and b.row_nbr 
Where B.TRADE_DATE >= ${start6Mo}
GROUP BY B.INSTRUMENT_ID, B.TRADE_DATE) x,
(SELECT B.INSTRUMENT_ID, B.TRADE_DATE,
AVG(C.CLOSE_PRICE * B.SPLIT_FACTOR) avg_21day
FROM hist_temp as B
left outer join hist_temp as C
on B.INSTRUMENT_ID = C.INSTRUMENT_ID
and c.row_nbr BETWEEN b.row_nbr - 21 and b.row_nbr 
Where B.TRADE_DATE >= ${start6Mo}
GROUP BY B.INSTRUMENT_ID, B.TRADE_DATE) y
where x.INSTRUMENT_ID = y.INSTRUMENT_ID
and x.TRADE_DATE = y.TRADE_DATE
order by x.INSTRUMENT_ID, x.TRADE_DATE;


select z.INSTRUMENT_ID, z.TRADE_DATE, DAY_5, DAY_21, PREV_DAY5, PREV_DAY21
from (SELECT a.INSTRUMENT_ID, a.TRADE_DATE,  avg(b.avg_21day) as prev_day21
from hist6_temp a, hist6_temp b
where a.INSTRUMENT_ID = b.INSTRUMENT_ID
and b.row_nbr between a.row_nbr - 2 and a.row_nbr - 1
group by a.INSTRUMENT_ID, a.TRADE_DATE) x,
(SELECT a.INSTRUMENT_ID, a.TRADE_DATE,  avg(b.avg_5day) as prev_day5
from hist6_temp a, hist6_temp b
where a.INSTRUMENT_ID = b.INSTRUMENT_ID
and b.row_nbr between a.row_nbr - 2 and a.row_nbr - 1
group by a.INSTRUMENT_ID, a.TRADE_DATE) y,
(SELECT INSTRUMENT_ID, TRADE_DATE, avg_5day as day_5, avg_21day as day_21
from hist6_temp) z
where z.INSTRUMENT_ID = x.INSTRUMENT_ID
and z.TRADE_DATE = x.TRADE_DATE
and z.INSTRUMENT_ID = y.INSTRUMENT_ID
and z.TRADE_DATE = y.TRADE_DATE
and sign(day_21-day_5) * sign(prev_day21-prev_day5) < 0;
"

# ********* QUERY 7 ****************
# Determine the value of $100,000 now if 1 year ago it was invested equally
# in 10 specified stocks (i.e. allocation for each stock is $10,000).
# The trading strategy is: When the 20-day moving average crosses over the 5-month
# moving average the complete allocation for that stock is invested and when the
# 20-day moving average crosses below the 5-month moving average the entire position
# is sold. The trades happen on the closing price of the trading day.
q7="
 BEGIN

 truncate table hist_temp;
 truncate table hist7_temp;
 commit;

 insert hist_temp
 SELECT number(),B.INSTRUMENT_ID, B.TRADE_DATE,b.CLOSE_PRICE,
 IFNULL(sum(A.SPLIT_FACTOR),1,sum(A.SPLIT_FACTOR)) 
 FROM STOCK_HISTORY AS B
 left outer join SPLIT_EVENT as A
 on B.INSTRUMENT_ID = A.INSTRUMENT_ID
 AND B.TRADE_DATE < A.EFFECTIVE_DATE 
 WHERE B.INSTRUMENT_ID in (${stock10})
 and B.TRADE_DATE >= ${maxTradeDateMinusYear}
 GROUP BY B.INSTRUMENT_ID,
 B.TRADE_DATE, B.CLOSE_PRICE
 ORDER BY B.INSTRUMENT_ID,
 B.TRADE_DATE;


 Insert hist7_temp
 SELECT number(),x.INSTRUMENT_ID, x.TRADE_DATE, avg_5mth , avg_21day
 FROM (SELECT B.INSTRUMENT_ID, B.TRADE_DATE,
 AVG(C.CLOSE_PRICE * B.SPLIT_FACTOR) avg_5mth
 FROM hist_temp as B
 left outer join hist_temp as C
 on B.INSTRUMENT_ID = C.INSTRUMENT_ID
 and c.row_nbr BETWEEN b.row_nbr - 160 and b.row_nbr 
 GROUP BY B.INSTRUMENT_ID,
 B.TRADE_DATE) x,
 (SELECT B.INSTRUMENT_ID, B.TRADE_DATE,
 AVG(C.CLOSE_PRICE * B.SPLIT_FACTOR) avg_21day
 FROM hist_temp as B
 left outer join hist_temp as C
 on B.INSTRUMENT_ID = C.INSTRUMENT_ID
 and c.row_nbr BETWEEN b.row_nbr - 21 and b.row_nbr 
 GROUP BY B.INSTRUMENT_ID,
 B.TRADE_DATE) y
 where x.INSTRUMENT_ID = y.INSTRUMENT_ID
 and x.TRADE_DATE = y.TRADE_DATE
 order by x.INSTRUMENT_ID, x.TRADE_DATE;


 select z.INSTRUMENT_ID, z.TRADE_DATE, diff, td2, diff2, pre_diff into #hist7_temp
 from (SELECT a.INSTRUMENT_ID, a.TRADE_DATE,  b.avg_21day - b.avg_5mth as pre_diff
 from hist7_temp a, hist7_temp b
 where a.INSTRUMENT_ID = b.INSTRUMENT_ID
 and b.row_nbr = a.row_nbr - 1 
 ) x,
  (SELECT a.INSTRUMENT_ID, a.TRADE_DATE, b.TRADE_DATE as td2, 
 b.avg_21day - b.avg_5mth as diff2
 from hist7_temp a, hist7_temp b
 where a.INSTRUMENT_ID = b.INSTRUMENT_ID
 and b.row_nbr = a.row_nbr + 1 
 ) y,
 (SELECT INSTRUMENT_ID, TRADE_DATE, avg_21day - avg_5mth as diff
 from hist7_temp) z
 where z.INSTRUMENT_ID = x.INSTRUMENT_ID
 and z.TRADE_DATE = x.TRADE_DATE
 and z.INSTRUMENT_ID = y.INSTRUMENT_ID
 and z.TRADE_DATE = y.TRADE_DATE
 and pre_diff*diff <=0
 and NOT (pre_diff=0 and diff=0);

 select sum(mp2.CLOSE_PRICE * (10000/mp1.CLOSE_PRICE)) as STOCK_VALUE
 from #hist7_temp t7, STOCK_HISTORY mp1, STOCK_HISTORY mp2
 where t7.INSTRUMENT_ID = mp1.INSTRUMENT_ID 
 and t7.INSTRUMENT_ID = mp2.INSTRUMENT_ID 
 and t7.TRADE_DATE = mp1.TRADE_DATE
 and t7.td2 = mp2.TRADE_DATE;
 END
"


# ********* QUERY 8 ****************
# Find the pair-wise coefficients of correlation in a set of 10 securities
# for a 2 year period. Sort the securities by the coefficient of correlation,
# indicating the pair of securities corresponding to that row. [Note: coefficient
# of correlation defined in appendix]
q8="
SELECT a.TRADING_SYMBOL,b.TRADING_SYMBOL, 
(Count(*) * sum(a.CLOSE_PRICE * b.CLOSE_PRICE) - sum(a.CLOSE_PRICE)
* sum(b.CLOSE_PRICE)/sqrt(count(*) * sum(a.CLOSE_PRICE * a.CLOSE_PRICE )
- (sum(a.CLOSE_PRICE) * sum(a.CLOSE_PRICE)))
* sqrt(count(*) * sum(b.CLOSE_PRICE * b.CLOSE_PRICE )
- (sum(b.CLOSE_PRICE) * sum(b.CLOSE_PRICE)))) as CORRELATION
from (Select TRADING_SYMBOL, TRADE_DATE,CLOSE_PRICE 
from 
STOCK_HISTORY AS B 
WHERE B.TRADING_SYMBOL BETWEEN 'AAA' AND 'AAJ'
AND LENGTH(B.TRADING_SYMBOL) = 3
and B.TRADE_DATE BETWEEN '2005-02-08'
and '2007-02-07' 
) a,
(Select TRADING_SYMBOL, TRADE_DATE,CLOSE_PRICE 
from 
STOCK_HISTORY AS B 
WHERE B.TRADING_SYMBOL BETWEEN 'AAA' AND 'AAJ'
AND LENGTH(B.TRADING_SYMBOL) = 3
and B.TRADE_DATE BETWEEN '2005-02-08'
and '2007-02-07'   ) b
where a.TRADE_DATE = b.TRADE_DATE
group by a.TRADING_SYMBOL, b.TRADING_SYMBOL
order by correlation
;  
"


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
q9="
SELECT sh.TRADING_SYMBOL, DATEPART(yy,TRADE_DATE) AS YEAR, 
SUM(dividend_value)/AVG(CLOSE_PRICE) as DIVIDEND
FROM  MARKET_INDEX mi
inner join INDEX_CMPSTN AS ic
on mi.MARKET_INDEX_ID = ic.MARKET_INDEX_ID 
inner join STOCK_HISTORY AS sh
on ic.INSTRUMENT_ID = sh.INSTRUMENT_ID
AND sh.TRADE_DATE BETWEEN '2005-04-04' and '2008-04-03'
inner join DIVIDEND_EVENT de
on de.INSTRUMENT_ID= sh.INSTRUMENT_ID 
AND DATEPART(yy,TRADE_DATE)=DATEPART(yy,ANNOUNCED_DATE) 
AND de.INSTRUMENT_ID NOT IN (SELECT se.INSTRUMENT_ID
FROM   SPLIT_EVENT se
WHERE  sh.INSTRUMENT_ID=se.INSTRUMENT_ID 
AND   DATEPART(yy,TRADE_DATE)=
DATEPART(yy,EFFECTIVE_DATE)) 
WHERE mi.INDEX_NAME ='Russell 2000' 
GROUP  BY sh.TRADING_SYMBOL,
	DATEPART(yy,TRADE_DATE)
order by sh.TRADING_SYMBOL,
	DATEPART(yy,TRADE_DATE)
;
" 
#Create a sql file per query
if [ $# -eq 1 ]
  then 
  if [ $1  == "-create" ]
    mkdir -p sybase_queries/
   then
    for query_num in {0..9}
      do
      query_name="q${query_num}"
      query_content="${!query_name}"
      echo ${query_content} > iq_queries/${query_name}.sql
      done;
  fi
fi




