-- PATHS RELATIVE TO tables/sybase/fintime
DROP TABLE base;
DROP TABLE SPLIT_EVENT;
DROP TABLE STOCK_HISTORY;
DROP TABLE DIVIDEND_EVENT;

-- These correspond to:
-- _, split, price, and dividend in all other queries

CREATE TABLE "base" (
  "id"            char(30),
  "ex"            char(3),
  "descr"         varchar(256),
  "sic"           char(30),
  "spr"           char(4),
  "cu"            char(5),
  "create_date"   date
);

CREATE TABLE "SPLIT_EVENT" (
  "INSTRUMENT_ID"  char(30),
  "EFFECTIVE_DATE"  date,
  "ENTRY_DATE"      date,
  "SPLIT_FACTOR"    double
);


CREATE TABLE "STOCK_HISTORY" (
  "INSTRUMENT_ID"            char(30),
  "TRADE_DATE"     date,
  "HIGH_PRICE"     double,
  "LOW_PRICE"      double,
  "CLOSE_PRICE"    double,
  "OPEN_PRICE"     double,
  "Volume"        bigint
)

CREATE TABLE "DIVIDEND_EVENT" (
  "INSTRUMENT_ID"      char(30),
  "xdivdate"            date,
  "dividend_value"      double,
  "ANNOUNCED_DATE"      date
);


--Load data using LOAD statement to avoid delay due to logging
LOAD TABLE base(id, ex, descr, sic, spr, cu, create_date) 
FROM '../../../../../data/hist-base-file' 
FORMAT BCP 
DELIMITED BY '|' 
ROW DELIMITED BY '\n' 
SKIP 1 
ESCAPES OFF;

LOAD TABLE SPLIT_EVENT(INSTRUMENT_ID, EFFECTIVE_DATE, ENTRY_DATE, SPLIT_FACTOR) 
FROM '../../../../../data/hist-split-file' 
FORMAT BCP 
DELIMITED BY '|' 
ROW DELIMITED BY '\n' 
SKIP 1 
ESCAPES OFF;

LOAD TABLE STOCK_HISTORY(INSTRUMENT_ID, TRADE_DATE, HIGH_PRICE, 
  LOW_PRICE, CLOSE_PRICE, OPEN_PRICE, Volume) 
FROM '../../../../../data/hist-price-file' 
FORMAT BCP 
DELIMITED BY '|' 
ROW DELIMITED BY '\n' 
SKIP 1 
ESCAPES OFF;

LOAD TABLE DIVIDEND_EVENT(INSTRUMENT_ID, xdivdate, dividend_value, 
  ANNOUNCED_DATE) 
FROM '../../../../../data/hist-dividend-file' 
FORMAT BCP 
DELIMITED BY '|' 
ROW DELIMITED BY '\n' 
SKIP 1 
ESCAPES OFF;
