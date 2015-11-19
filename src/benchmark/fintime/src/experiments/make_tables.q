//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  create tables for benchmark         //
//                                      //
//////////////////////////////////////////

// Data paths
DATAPATH:hsym `$"../../data/";
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
save `:tables/dividend
exit 0