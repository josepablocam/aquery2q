// Make (month) partitioned versions of data
DATAPATH:`:data;
paths:` sv/:DATAPATH,/:`$("hist-base-file";"hist-price-file";"hist-split-file";"hist-dividend-file");
files:`base`price`split`dividend!paths;
// Hist base file
base:("SSSSSSD";enlist "|") 0:files`base;
// Hist price file
price:("SDFFFFJ";enlist "|") 0:files`price;
// Hist split file
split:("SDDI";enlist "|") 0:files`split;
// Hist dividends file
dividend:("SDFD"; enlist "|") 0:files`dividend;

d:`price`split`dividend!`TradeDate`SplitDate`AnnounceDate;
months:distinct `month$raze(key d)@'value d;
makePartition:{[path;tbl;pc;pv]
  sym:` sv path,`sym;
  part:` sv path,(`$string pv),tbl,`;
  s:exec c!flip[((sym?;) each c; c)]@'t<>"s" from meta tbl; 
  part set ?[tbl;enlist(=;(`month$;pc);pv);0b;s]
  };

makePartition'[`:sampledb; ; ;months] ./: flip (key d;value d)

// set seed for reproducibility
\S 10

// save out parameters for queries
// create random sets required for tests and save out
stock10:neg[10 & count base]?(base`Id);
startYear10:first 1?exec distinct TradeDate from price where TradeDate.year <= -10+max TradeDate.year;
// adding to date here to deal easily with monetdb
endYear10:startYear10 + 365 * 10;
startYear10Plus2:startYear10 + 365 * 2;

stock1000:neg[1000 & count base]?base`Id;
stockLarge:neg[10000 & count base]?base`Id;
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

params:`stock10`startYear10`stock1000`start300Days`startPeriod`endPeriod`SP500`start6Mo`Russell2000`stockLarge`maxTradeDate;

(` sv/: `:sampledb,/:params) set'get each params

exit 0
 

