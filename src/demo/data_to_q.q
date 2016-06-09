//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  create tables for demo              //
//                                      //
//////////////////////////////////////////

// Options
opts:.Q.opt .z.x;
if[any not `csv`save in key opts; show "Usage: -csv <path-to-csv-folder> -save <path-to-save-q-tables>"; exit 1];

// saving as q binaries for aquery and q
saveToDB:{[path;name;data] show (` sv path,name) set data}

// CSV data paths
CSVPATH:hsym `$first opts`csv;

// paths to write out q serialized objects
SAVEPATH:hsym `$first opts`save;

// subfolders for tables and parameters
tablePath:` sv SAVEPATH,`tables;
paramPath:` sv SAVEPATH,`parameters;


makeFintime:{
  paths:` sv/:CSVPATH,/:`$("hist-base-file";"hist-price-file";"hist-split-file";"hist-dividend-file");
  files:`base`price`split`dividend!paths;
  
  // Hist base file
  base:("SSSSSSD";enlist "|") 0:files`base;
  // Hist price file
  price:("SDFFFFJ";enlist "|") 0:files`price;
  // Hist split file
  split:("SDDI";enlist "|") 0:files`split;
  // Hist dividends file
  dividend:("SDFD"; enlist "|") 0:files`dividend;

  // save tables
  saveToDB[tablePath;`price;price];
  saveToDB[tablePath;`base;base];
  saveToDB[tablePath;`split;split];
  saveToDB[tablePath;`dividend;dividend];

  // save out parameters for query examples that require them
  stock10:neg[10 & count base]?(base`Id);
  startYear10:first 1?exec distinct TradeDate from price where TradeDate.year <= -10+max TradeDate.year;

  stock1000:neg[1000 & count base]?base`Id;
  start300Days:first 1?-300_exec asc distinct TradeDate from price;
  end300Days:start300Days + 300;

  startPeriod:first 1?exec asc distinct TradeDate from price;
  endPeriod:first 1?exec distinct TradeDate from price where TradeDate > startPeriod;

  SP500:neg[500 & count base]?base`Id;
  start6Mo:first 1?exec distinct TradeDate from price where TradeDate.month <= -6 + max TradeDate.month;
  end6Mo:start6Mo + 6 * 31;

  Russell2000:neg[2000 & count base]?base`Id;

  maxTradeDate:exec max TradeDate from price;
  maxTradeDateMinusYear:maxTradeDate-365;
  maxTradeDateMinus3Years:maxTradeDate-3*365;

  // save parameters
  saveToDB[paramPath;`stock10;stock10];
  saveToDB[paramPath;`startYear10;startYear10];
  saveToDB[paramPath;`stock1000;stock1000];
  saveToDB[paramPath;`start300Days;start300Days];
  saveToDB[paramPath;`startPeriod;startPeriod];
  saveToDB[paramPath;`endPeriod;endPeriod];
  saveToDB[paramPath;`SP500;SP500];
  saveToDB[paramPath;`start6Mo;start6Mo];
  saveToDB[paramPath;`Russell2000;Russell2000];
  };

makeEOD:{
  eodprices:("FFFFJFSD";enlist ",") 0:` sv CSVPATH,`$"sp500_eod_complete_data.csv";
  saveToDB[tablePath;`eodprices;eodprices];
  };

/////////////////////////////////
//                             //
//                             //
// Creating kdb+ databases      //
//                             //	
//                             //
/////////////////////////////////

if[count key ` sv CSVPATH,`$"hist-base-file"; show "Creating fintime db"; makeFintime[]];
if[count key ` sv CSVPATH,`$"sp500_eod_complete_data.csv"; show "Creating EOD db"; makeEOD[]];
exit 0


