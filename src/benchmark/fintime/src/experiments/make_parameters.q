//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  create testing benchmark constants  //
//  that involve randomness             //
//                                      //
//////////////////////////////////////////

path:hsym`$"/Users/josecambronero/MS/S15/aquery/src/benchmark/fintime/src/experiments"
base:get ` sv path,`tables`base
price:get ` sv path,`tables`price
split:get ` sv path,`tables`split

// create random sets required for tests and save out
stock10:neg[10 & count base]?(base`Id);
startYear10:first 1?exec distinct TradeDate from price where TradeDate.year <= -10+max TradeDate.year;
stock1000:neg[1000 & count base]?base`Id;
start300Days:first 1?-300_exec asc distinct TradeDate from price;
startPeriod:first 1?exec asc distinct TradeDate from price;
endPeriod:first 1?exec distinct TradeDate from price where TradeDate > startPeriod;
SP500:neg[500 & count base]?base`Id;
start6Mo:first 1?exec distinct TradeDate from price where TradeDate.month <= -6 + max TradeDate.month;
Russell2000:neg[2000 & count base]?base`Id;

save ` sv path,`parameters`stock10
save ` sv path,`parameters`startYear10
save ` sv path,`parameters`stock1000
save ` sv path,`parameters`start300Days
save ` sv path,`parameters`startPeriod
save ` sv path,`parameters`endPeriod
save ` sv path,`parameters`SP500
save ` sv path,`parameters`start6Mo
save ` sv path,`parameters`Russell2000
exit 0

