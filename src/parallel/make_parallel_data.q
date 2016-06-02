opts:.Q.opt .z.x;

// setup workers for parallel processing if
if[`workers in key opts;
  workers:hsym `$"," vs first opts`workers;
  if[(abs[s]<>count workers)|0<s:system "s"; 
      show "setup -s and workers appropriately";
      exit 1
    ];
  .z.pd:`u#hopen each workers
 ];


DATAPATH:`:data;
DBPATH:`:sampledb;

paths:` sv/:DATAPATH,/:`$("hist-base-file";"hist-price-file";"hist-split-file";"hist-dividend-file");
files:`base`price`split`dividend!paths;

// in chunks
write:{[read;db;nm;partfn;str]
  t:.Q.en[db] read str;
  parts:group partfn t;
 {[t;db;part;nm;mapix]  
    path:` sv .Q.par[db;part;nm],`;
    dat:t mapix part;
    op:$[count key path;,;:];
    .[path;();op;dat]
  }[t;db; ;nm;parts] each key parts
 };

// initialize sym file
initSymFile:{(` sv x,`sym) set `$()}

// some file specific operations
readOps:()!()
readOps[`price]:flip `Id`TradeDate`HighPrice`LowPrice`ClosePrice`OpenPrice`Volume!("SDFFFFJ";"|") 0:;
readOps[`split]:flip `Id`SplitDate`EntryDate`SplitFactor!("SDDI";"|") 0:;
readOps[`dividend]:flip `Id`XdivDate`DivAmt`AnnounceDate!("SDFD";"|") 0:;

partOps:()!()
partOps[`price]:{`month$x`TradeDate}
partOps[`split]:{`month$x`SplitDate}
partOps[`dividend]:{`month$x`AnnounceDate}


// build db with parallel writes for tables
writeOps:`price`split`dividend!{write[readOps y;x;y;partOps y; ]}[DBPATH; ] each `price`split`dividend;

initSymFile[DBPATH];

{[files;writes;nm]
  show "building ",string nm;
  .Q.fs[writes nm] files nm
  }[files;writeOps;] peach `split`price`dividend
  

// create any missing tables in the partitions
.Q.chk[DBPATH];

// part by Id
applyParted:{[db;nm;s;p]
  show "apply attributes to ",string[nm];
  partitions:(key db) except `sym;
  paths:` sv/:flip (db;partitions;nm;`);
  {[s;p;d] @[s d;p;`p#]}[s;p;] each paths
  };


args:((`price;`Id`TradeDate xasc); (`dividend;`Id`AnnounceDate xasc); (`split;`Id`SplitDate xasc));
(applyParted[DBPATH; ; ;`Id] .) peach args;

// select parameters here

// load db
system "l ",1_string DBPATH;
// load in workers if necessary
if [`workers in key opts;{system "l ",1_string x} peach (count .z.pd[])#DBPATH];
ids:sym;
months:select distinct month from price;
dates:raze{select distinct TradeDate from price where month=x} peach months`month;

// set seed for reproducibility
\S 100

stock10:neg[10 & count ids]?ids;
stock1000:neg[1000 & count ids]?ids;
// for large queries
stockLarge:neg[10000 & count ids]?ids;
SP500:neg[500 & count ids]?ids;
Russell2000:neg[2000 & count ids]?ids;

startYear10:first 1?exec TradeDate from dates where TradeDate.year <= -10+max TradeDate.year;
start300Days:first 1?-300_asc dates`TradeDate;
startPeriod:first 1?asc dates`TradeDate;
endPeriod:first 1?exec TradeDate from dates where TradeDate > startPeriod;
start6Mo:first 1?exec TradeDate from dates where TradeDate.month <= -6 + max TradeDate.month;
maxTradeDate:exec max TradeDate from dates;


params:`stock10`stock1000`stockLarge`SP500`Russell2000`startYear10`start300Days`startPeriod`endPeriod`start6Mo`maxTradeDate;
(` sv/: `:.,/:params) set'get each params
exit 0
