# Drop the tables in case they exists
echo "DROP TABLE price; DROP TABLE base; DROP TABLE split;" | mclient -d fintime

# Create tables, note columns here must be lower case
echo 'CREATE TABLE "base" (
  "id"            char(30),
  "ex"            char(3),
  "descr"         varchar(256),
  "sic"           char(30),
  "spr"           char(4),
  "cu"            char(5),
  "create_date"    date
);' | mclient -d fintime

echo 'CREATE TABLE "split" (
  "id"            char(30),
  "split_date"     date,
  "entry_date"     date,
  "split_factor"   double
);' | mclient -d fintime

echo 'CREATE TABLE "price" (
  "id"            char(30),
  "trade_date"     date,
  "high_price"     double,
  "low_price"      double,
  "close_price"    double,
  "open_price"     double,
  "volume"        bigint
);' | mclient -d fintime

DATAPATH=$(pwd)/../../data/

function nrows {
	wc -l $1 | awk '{print $1-1}'
}


# populate tables with pipe delimited data
# skip header, so count rows first
PRICEN=$(nrows ${DATAPATH}/hist-price-file)
BASEN=$(nrows ${DATAPATH}/hist-base-file)
SPLITN=$(nrows ${DATAPATH}/hist-split-file)

echo "COPY ${PRICEN} OFFSET 2 RECORDS INTO price FROM '${DATAPATH}/hist-price-file'  
 USING DELIMITERS '|', '\n';" | mclient -d fintime
 
echo "COPY ${BASEN} OFFSET 2 RECORDS INTO base FROM '${DATAPATH}/hist-base-file' 
 USING DELIMITERS '|', '\n';" | mclient -d fintime
 
echo "COPY ${SPLITN} OFFSET 2 RECORDS INTO split FROM '${DATAPATH}/hist-split-file' 
 USING DELIMITERS '|', '\n';" | mclient -d fintime
 
 
 










