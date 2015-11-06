//////////////////////////////////////////
//  Author: Jose Cambronero             //
//	jose.cambronero@cs.nyu.edu          //
//	A quick script to                   //
//  create tables for benchmark         //
//                                      //
//////////////////////////////////////////

// Data paths
DATAPATH:hsym `$"../../data/";
files:`base`price`split!` sv/:DATAPATH,/:`$("hist-base-file";"hist-price-file";"hist-split-file");

// Hist base file
base:("SSSSSSD";enlist "|") 0:files`base;
// Hist price file
price:("SDFFFFJ";enlist "|") 0:files`price;
// Hist split file
split:("SDDI";enlist "|") 0:files`split;


// Rewrite the files as friendly for monetdb and pandas
{x 0:"|" 0:get y}'[value files;key files];


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