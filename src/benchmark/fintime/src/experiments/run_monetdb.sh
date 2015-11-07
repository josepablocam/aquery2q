
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

## TURN OFF glob
set -f


# create tables for stock data
# #if [ $1  == "-create" ]; then
# 	create_insert_params="";
# 	OLDIFS=${IFS}
# 	IFS=","
# 	for tb in "stock10" "stock1000" "sp500" "russell2000";
# 	do
# 		create_insert_params="${create_insert_params}
# 			DROP TABLE ${tb}; CREATE TABLE \"${tb}\"(\"id\" char(30));"
# 		poss=${!tb}
# 		for id in $poss; do
# 			create_insert_params="${create_insert_params} INSERT into ${tb} VALUES($id);"
# 		done
# 	done
# 	IFS=$OLDIFS
# #fi

# ********* QUERY 0 ****************
# 	Get the closing price of a set of 10 stocks for a 10-year period and
# 	group into weekly, monthly and yearly aggregates. For each aggregate
# 	period determine the low, high and average closing price value.
# 	The output should be sorted by id and trade date.

q0="CREATE TEMPORARY TABLE \"pricedata\" (
		\"id\"     				char(30),
		\"trade_date\"	  date,
		\"close_price\"   double,
		\"week_bucket\"   integer,
		\"month_bucket\"  integer,
		\"year_bucket\"   integer)
		ON COMMIT PRESERVE ROWS;

INSERT INTO pricedata
	select id, trade_date, close_price,
	datediff/7 as week_bucket,
	datediff/31 as month_bucket,
	datediff/365 as year_bucket from 
		(select id, trade_date, close_price,
		trade_date - ${startYear10} as datediff
		from price where 
		id in (${stock10}) and
		trade_date >= ${startYear10} and 
		trade_date < ${endYear10}) prep
;

CREATE TEMPORARY TABLE \"results\"(
	\"id\"     char(30),
	\"name\"	 char(10),
	\"bucket\" integer,
	\"low\"    double,
	\"high\"   double,
  \"avg\"	   double
) ON COMMIT PRESERVE ROWS;

INSERT INTO results 
	select id, 'weekly' as name, week_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, week_bucket
;

INSERT INTO results 
	select id, 'monthly' as name, month_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, month_bucket
;

INSERT INTO results 
	select id, 'yearly' as name, year_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, year_bucket
;
SELECT * from results order by id, name, bucket
;
"

# using a join
q0_v2="CREATE TEMPORARY TABLE \"pricedata\" (
		\"id\"     				char(30),
		\"trade_date\"	  date,
		\"close_price\"   double,
		\"week_bucket\"   integer,
		\"month_bucket\"  integer,
		\"year_bucket\"   integer)
		ON COMMIT PRESERVE ROWS;

INSERT INTO pricedata
	select p.id, p.trade_date, p.close_price,
	p.datediff/7 as week_bucket,
	p.datediff/31 as month_bucket,
	p.datediff/365 as year_bucket from 
		(select id, trade_date, close_price,
		trade_date - ${startYear10} as datediff
		from price 
		where 
		trade_date >= ${startYear10} and 
		trade_date < ${endYear10}
		) p INNER JOIN stock10 s
		ON p.id = s.id
;

CREATE TEMPORARY TABLE \"results\"(
	\"id\"     char(30),
	\"name\"	 char(10),
	\"bucket\" integer,
	\"low\"    double,
	\"high\"   double,
  \"avg\"	   double
) ON COMMIT PRESERVE ROWS;

INSERT INTO results 
	select id, 'weekly' as name, week_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, week_bucket
;

INSERT INTO results 
	select id, 'monthly' as name, month_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, month_bucket
;

INSERT INTO results 
	select id, 'yearly' as name, year_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, year_bucket
;
SELECT * from results order by id, name, bucket
;
"

# TODO: query 1
# consider if it is better to do this with a join instead
q1="
	CREATE AGGREGATE first_double(i double) RETURNS double LANGUAGE PYTHON {
  		return i[0];
	};
	
	CREATE AGGREGATE first_bigint(i bigint) RETURNS bigint LANGUAGE PYTHON {
  		return i[0];
	};
	
 CREATE TEMPORARY TABLE pricedata AS
 	 SELECT *
	 FROM price INNER JOIN stock1000 USING (id)
	 WHERE trade_date >= ${start300Days} AND trade_date < ${end300Days}
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 
 CREATE TEMPORARY TABLE splitdata AS
 	 SELECT *
	 FROM split INNER JOIN stock1000 USING (id)
	 WHERE split_date >= ${start300Days} AND split_date < ${end300Days}
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 

  SELECT 
		first(high_price) * 1.0 / prod(split_factor) as high_price,
		first(low_price) * 1.0 / prod(split_factor) as low_price,
		first(close_price) * 1.0 / prod(split_factor) as close_price,
		first(open_price) * 1.0 / prod(split_factor) as open_price,
		first(volume) * prod(split_factor) as volume
  FROM pricedata INNER JOIN splitdata USING (id)
	WHERE trade_date <= split_date
	GROUP BY Id, trade_date		
;
"

#********* QUERY 2 ****************
# For each stock in a specified list of 1000 stocks, find the differences between the daily 
# high and  daily low on the day of each split event during a specified period.
q2="
	select p.id, trade_date, max(high_price - low_price)  FROM
	((SELECT * FROM price where 
	trade_date >= ${startPeriod} and trade_date <= ${endPeriod}) as p
 		INNER JOIN
  (SELECT * FROM split where 
	split_date >= ${startPeriod} and split_date <= ${endPeriod}) as s
		ON p.id = s.id AND p.trade_date = s.split_date)
		INNER JOIN stock1000 ON p.id = stock1000.id
		GROUP BY p.id, trade_date
;
"

# ********* QUERY 3 + 4 ****************
# Calculate the value of the S&P500 and Russell 2000 index for a specified day using
# unadjusted prices and the index composition of the 2 indexes (see appendix for spec) on
# the specified day
q3="
select sum(close_price * Volume)/ 8.9e9 as index_val from
(select * from price where trade_date=${startPeriod}) p
 INNER JOIN sp500 ix ON p.id = ix.id;
"
q4="
select sum(close_price * Volume)/ 8.9e9 as index_val from
(select * from price where trade_date=${startPeriod}) p
 INNER JOIN russell2000 ix ON p.id = ix.id;
"






