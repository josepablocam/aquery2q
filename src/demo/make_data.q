// Simple script to create
// some random data for demo examples
// in case that the user doesn't have the
// predownloaded sp500 data (too large to clutter repo with it)

genData:{[tickers;ndays]
  ntickers:count tickers;
  n:ndays*ntickers;

  hp:n?100.0;
  lp:hp&n?100.0;
  op:lp|hp&n?100.0;
  cp:lp|hp&n?100.0;
  v:n?20000j;
  adjp:cp*1+(n?0.2)*n?1 -1;
  id:raze ndays#'tickers;
  d:raze ntickers#'.z.D+til ndays;
  flip `High`Low`Open`Close`Volume`Adjusted`ID`Date!(hp;lp;op;cp;v;adjp;id;d)
 };

NTICKERS:500;
NDAYS:4000;
DATA_FOLDER:`:data/
TABLE_PATH:` sv DATA_FOLDER,`$"sp500_eod_complete_data.csv";
TICKERS_PATH:` sv DATA_FOLDER,`tickers.txt;
if[0=count key TABLE_PATH;
  1 "Generating random data for demo\n";
  TABLE_PATH 0:csv 0:genData[`$read0 TICKERS_PATH;NDAYS]
 ]
exit 0
