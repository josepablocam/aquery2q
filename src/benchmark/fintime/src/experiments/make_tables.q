//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  create tables for benchmark         //
//                                      //
//////////////////////////////////////////

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

/////////////////////////////////
//                             //
//                             //
// Creating kdb+ database      //
//                             //	
//                             //
/////////////////////////////////
// write out tables
save `:tables/price
save `:tables/base
save `:tables/split
exit 0