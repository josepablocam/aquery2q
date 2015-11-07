//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  create testing benchmark constants  //
//  that involve randomness             //
//                                      //
//////////////////////////////////////////

path:hsym`$"./"
base:get ` sv path,`tables`base
price:get ` sv path,`tables`price
split:get ` sv path,`tables`split

// create random sets required for tests and save out
stock10:neg[10 & count base]?(base`Id);
startYear10:first 1?exec distinct TradeDate from price where TradeDate.year <= -10+max TradeDate.year;
// adding to date here to deal easily with monetdb
endYear10:startYear10 + 365 * 10;
startYear10Plus2:startYear10 + 365 * 2;

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

// saving in q format for aquery and q, and as a text file for others
saveparams:{
  // saving as q binaries for aquery and q
  show save p:` sv path,`parameters,x;
  // saving as csvfile for non-q
  show (` sv path,`parameters,` sv x,`csv) 1:"," sv string (),get x;
  }

params:`stock10`startYear10`stock1000`start300Days`startPeriod`endPeriod`SP500`start6Mo`Russell2000;
// extra for ease of use with monetdb
params,:`endYear10`startYear10Plus2`end300Days`end6Mo`maxTradeDate`maxTradeDateMinusYear;
saveparams each params

exit 0

