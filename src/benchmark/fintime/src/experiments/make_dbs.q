/
	Author: Jose Cambronero
	jose.cambronero@cs.nyu.edu
	A quick script to create the influxdb data needed for benchmaring
\

// Data paths
DATAPATH:`:/Users/josecambronero/MS/S15/aquery/src/benchmark/fintime/data;
UNIXEPOCH:1970.01.01;
files:`$("hist-base-file";"hist-price-file";"hist-split-file");

// Hist base file
base:("SSSSSSD";enlist "|") 0:` sv DATAPATH,files 0;
// Hist price file
price:("SDFFFFJ";enlist "|") 0:` sv DATAPATH,files 1;
// Hist split file
split:("SDDI";enlist "|") 0:` sv DATAPATH,files 2;

// Influxdb doesn't play nice with future values so create fixed
// Offset to use with it, and anything that is a date/timestamp
// will get offset by that amount
DATEOFFSET:{
 maxprice:exec max TradeDate from price;
 maxsplit:exec max SplitDate from split;
 .z.D - maxprice|maxsplit
 }[];
 
adjDateCols:{![x;();0b;dts!(+; ;y) each dts:exec c from meta x where t="d"]}

// adjusting date columns
base:adjDateCols[base;DATEOFFSET];
price:adjDateCols[price;DATEOFFSET];
split:adjDateCols[split;DATEOFFSET];

// Influxdb doesn't like it if we give it a number with no decimals
// if it has already decided it is a float (no type promotion as far as i can
// tell, when writing ... super annoying), so we smudge by adding 0.01
// where necessary
adjFloatCols:{![x;();0b;c!{x+0.01*x=floor x},/:c:exec c from meta x where t="f"]};
base:adjFloatCols[base];
price:adjFloatCols[price];
split:adjFloatCols[split];


/////////////////////////////////
//                             //
//                             //
// Creating InfluxDB database  //
//                             //	
//                             //
/////////////////////////////////
// influx related functions
.influx.PORT:"8086";
.influx.HOST:"localhost";
.influx.address:"http://",.influx.HOST,":",.influx.PORT;
.influx.createdb:{ system "curl -G ",.influx.address,"/query --data-urlencode \"q=CREATE DATABASE ",string[x],"\""};
.influx.write:{[db;msg] strmsg:"\n" sv string (),msg; system "curl -i -XPOST '",.influx.address,"/write?db=",string[db],"' --data-binary '",strmsg,"'"};
COUNTER:0
SLEEP:15 // seconds
.influx.writeAndSleep{[ct;db;msg]
  // when we hit limit, sleep, and then reset
  if[COUNTER=ct;system "sleep ",string SLEEP;`COUNTER set 0];
  .influx.write[db;msg];
  `COUNTER set COUNTER+1
 }
.influx.mkpairs:{[t;c] ","sv/:flip ("=" sv/:) each string c,/:'t c,:()};

// default precision in influxdb is nanoseconds
.influx.nanosecs:{`long$neg["p"$UNIXEPOCH] + "p"$x};

// Creating and writing out data
.influx.createdb[`benchmarking];
// base
// we remove quotes and colon in the description and spaces become underscores
base:update Descr:`$ssr/[ ;("'";":";" ");("";"";"_")] each string Descr from base;
// we ignore CreateDate as tag, as unnecessary
basetags:.influx.mkpairs[base;(cols base) except `CreateDate];
basetimestamps:string exec .influx.nanosecs CreateDate from base;
// influxdb requires at least one "field-value" pair, so insert a dummy one
basefields:count[base]#enlist "DummyValue=1"
basemsg:`$'"base,",/:" "sv/:flip (basetags;basefields;basetimestamps);
//.influx.write[`benchmarking; ] each 1000 cut basemsg;
.influx.writeAndSleep[100;`benchmarking;] each 1000 cut basemsg;

// price
// we'll pretend the date is the time at the start of the day
pricetags:.influx.mkpairs[price;`Id];
pricefields:.influx.mkpairs[price;(cols price) except `Id`TradeDate];
// we'll create a timestamp based off of the Tradedate
pricetimestamps:string exec .influx.nanosecs TradeDate from price;
pricemsg:`$'"price,",/:" "sv/:flip (pricetags;pricefields;pricetimestamps);
//.influx.write[`benchmarking; ] each 1000 cut pricemsg;
.influx.writeAndSleep[100;`benchmarking;] each 1000 cut pricemsg;


// split
// we're going to ignore SplitDate/SplitFactor and avoid including as tag, as slows down
splittags:.influx.mkpairs[split;`Id];
splitfields:.influx.mkpairs[split;`SplitFactor];
// we;ll use the entry date as a timestamp
splittimestamp:string exec .influx.nanosecs SplitDate from split
splitmsg:`$'"split,",/:" "sv/:flip (splittags;splitfields;splittimestamp)
//.influx.write[`benchmarking; ] each 1000 cut splitmsg;
.influx.writeAndSleep[100;`benchmarking;] each 1000 cut splitmsg;

/////////////////////////////////
//                             //
//                             //
// Creating kdb+ database      //
//                             //	
//                             //
/////////////////////////////////
// write out tables
save `:price
save `:base
save `:split



//////////////////////////////////////
//                                  //
//                                  //
// Saving testing related constants //
//                                  //	
//                                  //
/////////////////////////////////////
// create random sets required for tests and save out
\S 100
stock10:neg[10 & count base]?(base`Id);
startYear10:first 1?exec distinct TradeDate from price where TradeDate.year <= -10+max TradeDate.year;
stock1000:neg[1000 & count base]?base`Id;
start300Days:first 1?-300_exec asc distinct TradeDate from price;
startPeriod:first 1?exec asc distinct TradeDate from price;
endPeriod:first 1?exec distinct TradeDate from price where TradeDate > startPeriod;
SP500:neg[500 & count base]?base`Id;
start6Mo:first 1?exec distinct TradeDate from price where TradeDate.month <= -6 + max TradeDate.month;
Russell2000:neg[2000 & count base]?base`Id;

save `:stock10
save `:startYear10
save `:stock1000
save `:start300Days
save `:startPeriod
save `:endPeriod
save `:SP500
save `:start6Mo
save `:Russell2000




