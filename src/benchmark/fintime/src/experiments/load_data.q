//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  load data to run benchmarks         //
//                                      //
//////////////////////////////////////////

path:hsym `$"/Users/josecambronero/MS/S15/aquery/src/benchmark/fintime/src/experiments"
base:get ` sv path,`tables`base
price:get ` sv path,`tables`price
split:get ` sv path,`tables`split

// Retrieve randomly created lists
stock10:get ` sv path,`parameters`stock10
startYear10:get ` sv path,`parameters`startYear10
stock1000:get ` sv path,`parameters`stock1000
start300Days:get ` sv path,`parameters`start300Days
startPeriod:get ` sv path,`parameters`startPeriod
endPeriod:get ` sv path,`parameters`endPeriod
SP500:get ` sv path,`parameters`SP500
start6Mo:get ` sv path,`parameters`start6Mo
Russell2000:get ` sv path,`parameters`Russell2000
