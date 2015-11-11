# ********* QUERY 0 ****************
# 	Get the closing price of a set of 10 stocks for a 10-year period and
# 	group into weekly, monthly and yearly aggregates. For each aggregate
# 	period determine the low, high and average closing price value.
# 	The output should be sorted by id and trade date.
export q0="
CREATE TEMPORARY TABLE pricedata AS
	  select * from
		(select id, trade_date, close_price,
    week(trade_date) as week_bucket,
    \"year\"(trade_date) as year_bucket,
    \"month\"(trade_date) as month_bucket
		from price 
		where 
		trade_date >= ${startYear10} and 
		trade_date < ${endYear10}
		) p INNER JOIN stock10 s
		USING (id)
  WITH DATA
  ON COMMIT PRESERVE ROWS;  


CREATE TEMPORARY TABLE collect_aggs(
	id     char(30),
	name	 char(10),
	bucket integer,
	low    double,
	high   double,
  avg	   double
) ON COMMIT PRESERVE ROWS;

INSERT INTO collect_aggs 
	select id, 'weekly' as name, week_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, week_bucket
;

INSERT INTO collect_aggs 
	select id, 'monthly' as name, month_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, month_bucket
;

INSERT INTO collect_aggs 
	select id, 'yearly' as name, year_bucket as bucket, 
	min(close_price) as low, max(close_price) as high, avg(close_price) as mean
	from pricedata group by id, year_bucket
;

CREATE TEMPORARY TABLE query_result AS
	SELECT * from collect_aggs order by id, name, bucket
	WITH DATA
 ON COMMIT PRESERVE ROWS
;
"

# ********* QUERY 1 ****************
# Adjust all prices and volumes (prices are multiplied by the split factor and
# volumes are divided by the split factor) for a set of 1000 stocks to reflect the
# split events during a specified 300 day period, assuming that events occur before
# the first trade of the split date. These are called split-adjusted prices and volumes.
export q1="
 CREATE TEMPORARY TABLE pricedata AS
 	 SELECT *
	 FROM price INNER JOIN stock1000 USING (id)
	 WHERE trade_date >= ${start300Days} AND trade_date < ${end300Days}
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 
 CREATE TEMPORARY TABLE splitdata AS
 	 SELECT *
	 FROM split INNER JOIN stock1000 USING (id)
	 WHERE split_date >= ${start300Days}
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 
 CREATE TEMPORARY TABLE adjdata AS 
   SELECT id, trade_date, prod(split_factor) as adj
   FROM pricedata INNER JOIN splitdata USING (id)
	 WHERE trade_date <= split_date
	 GROUP BY id, trade_date
	 WITH DATA
 ON COMMIT PRESERVE ROWS;	
 
 CREATE TEMPORARY TABLE query_result AS
 	SELECT
  id, trade_Date,
 	high_price * adj as high_price,
 	low_price * adj as low_price,
 	close_price * adj as close_price,
 	open_price * adj as open_price,
 	volume / adj as volume
 	FROM
  (select id, trade_date, high_price, low_price,
  close_price, open_price, volume,
  CASE WHEN adj is NULL then 1 ELSE adj END as adj 
   FROM
 	pricedata LEFT JOIN adjdata USING (id, trade_date)) filled
  ORDER BY Id asc, trade_date asc
 	WITH DATA
 ON COMMIT PRESERVE ROWS;
"



#********* QUERY 2 ****************
# For each stock in a specified list of 1000 stocks, find the differences between the daily 
# high and  daily low on the day of each split event during a specified period.
export q2="
  CREATE TEMPORARY TABLE query_result AS
		select p.id, trade_date, max(high_price - low_price)  FROM
		((SELECT * FROM price where 
		trade_date >= ${startPeriod} and trade_date <= ${endPeriod}) as p
	 		INNER JOIN
	  (SELECT * FROM split where 
		split_date >= ${startPeriod} and split_date <= ${endPeriod}) as s
			ON p.id = s.id AND p.trade_date = s.split_date)
			INNER JOIN stock1000 ON p.id = stock1000.id
			GROUP BY p.id, trade_date
	WITH DATA
	ON COMMIT PRESERVE ROWS		
;
"

# ********* QUERY 3 + 4 ****************
# Calculate the value of the S&P500 and Russell 2000 index for a specified day using
# unadjusted prices and the index composition of the 2 indexes (see appendix for spec) on
# the specified day
export q3="
select avg(close_price) as avg_close_px from
(select * from price where trade_date=${startPeriod}) p
 INNER JOIN sp500 ix ON p.id = ix.id;
"
export q4="
select avg(close_price) as avg_close_px from
(select * from price where trade_date=${startPeriod}) p
 INNER JOIN russell2000 ix ON p.id = ix.id;
"

# keep running into 
# Error calling shmget(key:800000147,size:56,flags:512): No space left on device
# when calling with 2 embedded python functions in the same select
# ********* QUERY 5 ****************
# Find the 21-day and 5-day moving average price for a specified list of
# 1000 stocks during a 6-month period. (Use split adjusted prices)
export q5="
 CREATE TEMPORARY TABLE pricedata AS
 	 SELECT *
	 FROM price INNER JOIN stock1000 USING (id)
	 WHERE trade_date >= ${start6Mo} AND trade_date < ${end6Mo}
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 
 CREATE TEMPORARY TABLE splitdata AS
 	 SELECT *
	 FROM split INNER JOIN stock1000 USING (id)
	 WHERE split_date >= ${start6Mo} AND split_date < ${end6Mo}
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 
 CREATE TEMPORARY TABLE adjdata AS 
   SELECT id, trade_date, prod(split_factor) as adj
   FROM pricedata INNER JOIN splitdata USING (id)
	 WHERE trade_date <= split_date
	 GROUP BY id, trade_date
	 WITH DATA
 ON COMMIT PRESERVE ROWS;
 
 CREATE TEMPORARY TABLE combined AS
	 SELECT id, trade_date, close_price, close_price * 1.0 / adj as adj_price
	 FROM pricedata LEFT JOIN adjdata USING (id, trade_date)
	 ORDER BY id ASC, trade_date asc
	 WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	UPDATE combined SET adj_price=close_price WHERE adj_price IS NULL;
	
	CREATE TEMPORARY TABLE mavg_21 AS
		SELECT id, trade_date, mavg(adj_price, 21, id) as m21 FROM combined
		WITH DATA
	ON COMMIT PRESERVE ROWS;	
	
	CREATE TEMPORARY TABLE mavg_5 AS
	 select id, trade_date, mavg(adj_price, 5, id) as m5, close_price FROM combined
	 WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	DROP TABLE q5_result;
	
	CREATE TABLE q5_result AS
		SELECT * FROM mavg_21 INNER JOIN mavg_5 USING (id, trade_date)
		WITH DATA;
"


# ********* QUERY 6 ****************
# (Based on the previous query) 
# Find the points (specific days) when the 5-month moving average intersects 
# the 21-day moving average for these stocks. The output is to be sorted by id and date.
export q6="
CREATE TEMPORARY TABLE m21_data AS
	SELECT id, trade_date, m21, prev_double(m21) as prev_m21 
	FROM q5_result
	WITH DATA
ON COMMIT PRESERVE ROWS;

CREATE TEMPORARY TABLE m5_data AS
	SELECT id, trade_date, m5, prev_double(m5) as prev_m5
	FROM q5_result
	WITH DATA
ON COMMIT PRESERVE ROWS;

CREATE TEMPORARY TABLE moving_avg_data AS
	SELECT * from
	(SELECT id, trade_date, prev_char(id) as prev_id, close_price
	FROM q5_result) ids INNER JOIN 
	(SELECT * from m21_data INNER JOIN m5_data USING (id, trade_date)) pxs
	USING (id, trade_date)
	WITH DATA
ON COMMIT PRESERVE ROWS;

CREATE TEMPORARY TABLE sorted_data AS
  SELECT * FROM moving_avg_data ORDER BY id ASC, trade_date ASC
  WITH DATA
ON COMMIT PRESERVE ROWS;  


CREATE TEMPORARY TABLE query_result AS
	SELECT id, trade_date as cross_date, close_price from sorted_data
	WHERE id = prev_id AND
	((prev_m5 <= prev_m21 AND m5 > m21) OR (prev_m5 >= prev_m21 AND m5 < m21))
	WITH DATA
ON COMMIT PRESERVE ROWS	
;
"

# ********* QUERY 7 ****************
# Determine the value of $100,000 now if 1 year ago it was invested equally
# in 10 specified stocks (i.e. allocation for each stock is $10,000).
# The trading strategy is: When the 20-day moving average crosses over the 5-month
# moving average the complete allocation for that stock is invested and when the
# 20-day moving average crosses below the 5-month moving average the entire position
# is sold. The trades happen on the closing price of the trading day.
export q7="
	CREATE TEMPORARY TABLE pricedata AS
		SELECT * FROM
		(SELECT id, trade_date, close_price FROM price 
		WHERE trade_date >= ${maxTradeDateMinusYear}) p INNER JOIN
		stock10 USING (id) ORDER BY id ASC, trade_date ASC
		WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	CREATE TEMPORARY TABLE mavg_20_day AS
	  SELECT id, trade_date, m20day, prev_double(m20day) as prev_m20day FROM
		(SELECT id, trade_date, mavg(close_price, 20, id) as m20day FROM pricedata) p
	WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	CREATE TEMPORARY TABLE mavg_5_month AS
	 SELECT id, trade_date, m5month, prev_double(m5month) as prev_m5month,
	 close_price FROM
	 (select id, trade_date, mavg(close_price, 5 * 31, id) as m5month, 
	 close_price FROM pricedata) p
	 WITH DATA
	ON COMMIT PRESERVE ROWS;
	
  CREATE TEMPORARY TABLE sorted_data AS
    		select id,  prev_char(id) as prev_id, trade_date, 
    			m20day, prev_m20day, m5month, prev_m5month, close_price FROM 
    			mavg_5_month INNER JOIN mavg_20_day USING (id, trade_date)
    	ORDER BY id ASC, trade_date ASC
    WITH DATA
  ON COMMIT PRESERVE ROWS;  
  
	CREATE TEMPORARY TABLE relevant AS
	SELECT id, prev_id, trade_date, m20day, prev_m20day, m5month, prev_m5month,
		m20day > m5month as buy_signal, close_price
	 from sorted_data
	WHERE id = prev_id AND 
	(
		(prev_m5month <= prev_m20day AND m5month > m20day)
		OR
		(prev_m5month >= prev_m20day AND m5month < m20day) 
	)	
	WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	CREATE TEMPORARY TABLE simulated AS
		select id, result, still_invested FROM
			(select id, execute_strategy(buy_signal, close_price) * ${alloc} as result
			from relevant group by id) a INNER JOIN 
			(select id, last_boolean(buy_signal) as still_invested
				from relevant group by id) s USING (id)
			WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	CREATE TEMPORARY TABLE query_result AS
	select 
		id, result * close_price as dollars, result
    from 
	simulated LEFT JOIN (
		select id, close_price, true as still_invested 
		FROM pricedata
		where trade_date=${maxTradeDate}
	) latest_pxs USING (id, still_invested)
	WITH DATA
	ON COMMIT PRESERVE ROWS;
	
  UPDATE query_result SET dollars=result WHERE dollars IS NULL;  
"


# ********* QUERY 8 ****************
# Find the pair-wise coefficients of correlation in a set of 10 securities
# for a 2 year period. Sort the securities by the coefficient of correlation,
# indicating the pair of securities corresponding to that row. [Note: coefficient
# of correlation defined in appendix]
export q8="
	CREATE TEMPORARY TABLE pricedata AS
		SELECT * FROM
		(SELECT id, trade_date, close_price FROM price WHERE
		trade_date >= ${startYear10} and trade_date < ${startYear10Plus2}) AS p
		INNER JOIN stock10 USING (id)
		ORDER BY id, trade_date
		WITH DATA
	ON COMMIT PRESERVE ROWS;
	
	CREATE TEMPORARY TABLE query_result AS
		SELECT p1.id as id1, p2.id as id2, pairs_corr(p1.close_price, p2.close_price) as corr_val
		FROM pricedata p1, pricedata p2 WHERE p1.id <> p2.id AND p1.trade_date = p2.trade_date
		GROUP BY p1.id, p2.id
		WITH DATA
	ON COMMIT PRESERVE ROWS;   
"


# ********* QUERY 9 ****************
# Determine the yearly dividends and annual yield (dividends/average closing price) for the past 3
# years for all the stocks in the Russell 2000 index that did not split during that period.
# Use unadjusted prices since there were no splits to adjust for.
export q9="
  CREATE TEMPORARY TABLE splitdata AS
    SELECT distinct(id) from split INNER JOIN russell2000 USING (id)
    WHERE split_date >= ${maxTradeDateMinus3Years}
    WITH DATA
  ON COMMIT PRESERVE ROWS;
  
  CREATE TEMPORARY TABLE pricedata AS
  select * from 
  (select * from price where trade_date >= ${maxTradeDateMinus3Years}) p
  INNER JOIN russell2000 USING (id)
  WITH DATA
  ON COMMIT PRESERVE ROWS;
  
  CREATE TEMPORARY TABLE nosplit_avgpx AS
    select id, year_val, avg(close_price) as avg_px from
    (select id, close_price, \"year\"(trade_date) as year_val from pricedata
    WHERE NOT EXISTS (SELECT * from splitdata WHERE pricedata.id=splitdata.id)
    ) pxs group by id, year_val
    WITH DATA
  ON COMMIT PRESERVE ROWS;
  
  CREATE TEMPORARY TABLE dividenddata AS
  select * from 
  (select * from dividend where xdivdate >= ${maxTradeDateMinus3Years}) d
  INNER JOIN russell2000 USING (id)
  WITH DATA
  ON COMMIT PRESERVE ROWS;
  
  CREATE TEMPORARY TABLE nosplit_div AS
    select id, year_val, sum(divamt) as total_divs from
    (select id, divamt, \"year\"(xdivdate) as year_val from dividenddata
    WHERE NOT EXISTS (SELECT * from splitdata WHERE dividenddata.id=splitdata.id)
    ) divs group by id, year_val
    WITH DATA
  ON COMMIT PRESERVE ROWS;

  CREATE TEMPORARY TABLE query_result AS
    select id, year_val, avg_px, total_divs, total_divs / avg_px as yield
     from nosplit_avgpx LEFT JOIN nosplit_div USING (id, year_val)
    WITH DATA
  ON COMMIT PRESERVE ROWS;
  
  UPDATE query_result SET total_divs=0.0, yield=0.0 WHERE total_divs IS NULL; 
"  


    
    
    



