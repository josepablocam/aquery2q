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
split:("SDDI";enlist "|") 0:` sv DATAPATH,files 2


/////////////////////////////////
//                             //
//                             //
// Creating InfluxDB database  //
//                             //	
//                             //
/////////////////////////////////

/
// influx related functions
.influx.PORT:"8086";
.influx.HOST:"localhost";
.influx.address:"http://",.influx.HOST,":",.influx.PORT;
.influx.createdb:{ system "curl -G ",.influx.address,"/query --data-urlencode \"q=CREATE DATABASE ",string[x],"\""};
.influx.write:{[db;msg] strmsg:"\n" sv string (),msg; system "curl -i -XPOST '",.influx.address,"/write?db=",string[db],"' --data-binary '",strmsg,"'"};
.influx.mkpairs:{[t;c] ","sv/:flip ("=" sv/:) each string c,/:'t c,:()};

// default precision in influxdb is nanoseconds
.influx.nanosecs:{`long$neg["p"$UNIXEPOCH] + "p"$x};

// Influxdb doesn't like it if we give it a number with no decimals
// if it has already decided it is a float (no type promotion as far as i can
// tell, when writing), so make strings with nicely formatted floats
.influx.fmtFloats:{![x;();0b;c!({`$x,("";".0") not "." in x} each string@),/:c:exec c from meta x where t="f"]};

// Creating and writing out data

.influx.createdb[`benchmarking];
// base
// we remove quotes and colon in the description and spaces become underscores
base:update Descr:`$ssr/[ ;("'";":";" ");("";"";"_")] each string Descr from base;
basemsg:"base,",/:.influx.mkpairs[base;cols base];
// influxdb requires at least one "field-value" pair, so insert a dummy one
basemsg:`$'basemsg,\:" DummyValue=1";
.influx.write[`benchmarking; basemsg];

// prices
priceFormatted:.influx.fmtFloats price;
// we'll pretend the date is the time at the start of the day
pricetags:.influx.mkpairs[priceFormatted;`Id];
pricefields:.influx.mkpairs[priceFormatted;(cols price) except `Id`TradeDate];
// we'll create a timestamp based off of the Tradedate
pricetimestamps:string exec .influx.nanosecs TradeDate from priceFormatted;
pricemsg:`$'"price,",/:" "sv/:flip (pricetags;pricefields;pricetimestamps);
.influx.write[`benchmarking; ] each 1000 cut pricemsg;

// splits
splittags:.influx.mkpairs[splits;(cols splits) except `SplitFactor];
splitfields:.influx.mkpairs[split;`SplitFactor];
// we;ll use the entry date as a timestamp
splittimestamp:string exec .influx.nanosecs TradeDate from splits
splitmsg:`$'"splits,",/:" "sv/:flip (splittags;splitfields)
.influx.write[`benchmarking; splitmsg];
\

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
stock10:neg[10]?(base`Id);
startYear10:first 1?exec distinct TradeDate from price where TradeDate.year <= -10+max TradeDate.year;
stock1000:neg[1000]?base`Id;
start300Days:first 1?-300_exec asc distinct TradeDate from price;
startPeriod:first 1?exec asc distinct TradeDate from price;
endPeriod:first 1?exec distinct TradeDate from price where TradeDate > startPeriod;
SP500:neg[500]?base`Id;
start6Mo:first 1?exec distinct TradeDate from price where TradeDate.month <= -6 + max TradeDate.month;
Russell2000:neg[2000]?base`Id;

save `:stock10
save `:startYear10
save `:stock1000
save `:start300Days
save `:startPeriod
save `:endPeriod
save `:SP500
save `:start6Mo
save `:Russell2000





