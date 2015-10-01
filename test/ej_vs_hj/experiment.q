\l /Users/josecambronero/MS/S15/aquery/src/proto_hashjoin.q

// cast x to the appropriate type t, along with any operations necessary
totype:{[x;t];
  tm:"ijfsdp"!(::;::;::;string;::;::);
  tc:"ijfsdp"!("i";"j";"f";`;"d";"p");
  tc[t]$tm[t] x
 }


// add attributes to an existing table
// table, number of cols with attributes, any preset attributes
// (empty -> random, single -> extend, or defined)
addAttr:{[t;j;as]
  a:"psug "!(asc;asc;{totype[til count x;lower .Q.ty x]};asc;::);
  as:$[1=c:count as;j#as;$[0=c;j?key[a] except " ";as]];
  // extend with no attributes for remaining columns to the right
  as:count[cols t]#as,count[cols t]#" ";
  // matrix form with satisfying conditions for attributes
  // apply attributes and return as table
  flip (cols t)!(`$'as)#'a[as]@'value flip t
 }


// number of rows, number of cols
// types of col (empty -> randomize, single -> extend, or defined)
// types of attributes (empty -> random, single -> extend, or defined)
// column name prefix
// range of random number draw
createSample:{[i;j;ts;as;cnp;r]
  // types
  t:"ijfsdp"!(::;::;::;string;::;::);
  tc:"ijfsdp"!("i";"j";"f";`;"d";"p");
  ts:$[1=c:count ts;j#ts;$[0=c;j?key t;ts]];
  // matrix of values
  m:i cut (j*i)?r;
  // cast to appropriate types
  mt:totype'[m;ts];
  // create column names
  cn:`$cnp,/:string til j;
  // add appropriate attributes;
  t:flip cn!mt;
  $[all " "=as;t;addAttr[t;j;as]]
 }
 
// values from t1 to t2 (sampled) 
// columns c to add
// table1, table2, percentage of matches (based on column c)
// renaming prefix for columns
addCommon:{[t1;t2;c;p;r]
  // sampled from t1
  s:(ct2:count t2)?(c sublist cols t1)#t1;
  // append to t2 horizontally, and then null out 1 - p pct rows
  ext2:@[s,'t2;neg[`int$ct2*(1-p)]?til ct2;first each 0#'];
  (`$r,/:string cols s) xcol ext2
  } 

// create closures to use for timing
makehj:{[t1;t2;cn]
  c1:cn#cols t1;
  c2:cn#cols t2;
  pred:(=),/:c1,'c2;
  {[t1;t2;c1;c2;pred;dummy] hj[t1;t2;c1;c2;pred]}[t1;t2;c1;c2;pred]
  }
  
makeej:{[t1;t2;cn]
  c:cn#cols t1;
  // execute same way as hj, ie smaller goes on left
  t2:c xcol t2;
  ts:$[count[t2]>count t1;(t1;t2);(t2;t1)];
  {[c;t1;t2;dummy] ej[c;t1;t2]}[c;first ts;last ts]
  }  
  
makeclosure:{[jt;t1;t2;cn] $[jt=`ej;makeej;makehj][t1;t2;cn]}    
  
experiments:([]
  id:`long$();
  exp_type:`$();
  nrows_large:`long$(); 
  nrows_small:`long$();
  data_range:`long$();
  pct_match:`float$();
  ncol_join:`long$();
  attr_join:`$();
  types:`$();
  join_type:`$();
  time:`float$();
  memory:`float$()
 );
 
EXPERIMENTID:0;
 
timeit:{[reps] (system ssr["ts:%n .timer.totime[]"; "%n"; string reps])%reps};

// runs with both hj and ej, for comparison purposes, and records in experiments
// table
runexp:{[expdesc;reps;t1;t2;cn;datarange;pctmatch] 
  // info shared by both joins
  nrows_large:count t1;
  nrows_small:count t2;
  ncols_join:cn;
  jc:cn#cols t1;
  attr_join:first `$raze string (`$"*")^exec a from meta t1 where c in jc;
  types:`$exec t from meta t1 where c in jc;
  commoninfo:(EXPERIMENTID; expdesc; nrows_large; nrows_small; datarange; pctmatch; ncols_join; attr_join; types);
  
  // create closures specific to each join type, execute and store results
  show "running hj";
  .timer.totime:makeclosure[`hj;t1;t2;cn];
  hjinfo:timeit[reps];
  show "running ej";
  .timer.totime:makeclosure[`ej;t1;t2;cn];
  ejinfo:timeit[reps];
  0N!`hj,hjinfo;
  0N!`ej,ejinfo;
  show `experiments upsert commoninfo, `hj, hjinfo;
  show `experiments upsert commoninfo, `ej, ejinfo;
  `EXPERIMENTID set EXPERIMENTID + 1;
  } 

// parameters for experiments
// very important to set seed for reproducibility (since types/attributes are assigned)
// randomly
NROWS1:500000;
NCOLS:10;
JOINCOLS:1+til 3;
REPS:10;
// scenarios
// different sizes for second table
nrows2:1000 2000 3000;
// different ranges for data in join columns
ranges:100 1000 10000;
// different pcts of data matched
matchpcts:0.25 0.5 0.75 1.0;

runScenario:{[rows2;range;pct]
  show ssr/[
      "---> Scenario: Rows-Table-2:%n, Data-Range:%r, Match-Pct:%p";
      ("%n";"%r";"%p");
      string(rows2;range;pct)];
  system "S 10";
  // with random types, no attributes
  noattr:NCOLS#" ";
  r1:createSample[NROWS1;NCOLS;();noattr;"large";range];
  r2:createSample[rows2;NCOLS;();noattr;"small";range];
  // add columns that match, creates various tables for experiments
  r2j:addCommon[r1;r2; ;pct;"j"] each JOINCOLS;

  // without attributes
  show "running experiments: random types and no attributes";
  runexp[`$"random_type_no_attr";REPS;r1; ; ;range;pct]'[r2j;JOINCOLS];
  .Q.gc[];
  
  // with attributes (randomly assigned)
  show "running experiments: random types and random attributes";
  r1a:addAttr[r1;max JOINCOLS;()];
  r2ja:addCommon[r1a;r2; ;pct;"j"] each JOINCOLS;
  runexp[`$"random_type_random_attr";REPS;r1a; ; ;range;pct]'[r2ja;JOINCOLS];
  .Q.gc[];
  
  // with more likely types (say... date, symbol, integer)
  show "running experiments: specified types and no attributes";
  spectypes:NCOLS#"dsi",NCOLS#"f";
  t1:createSample[NROWS1;NCOLS;spectypes;noattr;"large";range];
  t2:createSample[rows2;NCOLS;();noattr;"small";range];
  t2j:addCommon[t1;t2; ;pct;"j"] each JOINCOLS;
  
  // without attributes
  runexp[`$"chosen_types_no_attr";REPS;t1; ; ;range;pct]'[t2j;JOINCOLS];
  .Q.gc[];
  
  show "running experiments: specified types and random attributes";
  t1a:addAttr[t1;max JOINCOLS;()];
  t2ja:addCommon[t1a;t2; ;pct;"j"] each JOINCOLS;
  // with attributes
  runexp[`$"chose_types_random_attr";REPS;t1a; ; ;range;pct]'[t2ja;JOINCOLS];
  .Q.gc[];
  
  show "running experiments: specified types and reasonable attributes";
  specattr:NCOLS#"sp",NCOLS#" ";
  t1s:createSample[NROWS1;NCOLS;spectypes;specattr;"large";range];
  t2s:createSample[rows2;NCOLS;();noattr;"small";range];
  t2sj:addCommon[t1s;t2s; ;pct;"j"] each 2#JOINCOLS;
  // with attributes
  runexp[`$"chosen_types_chosen_attr";REPS;t1s; ; ;range;pct]'[t2sj;2#JOINCOLS];
  .Q.gc[];
  
  show "running experiments: original (i.e. integer join column with parted attribute)";
  origtypes:NCOLS#"i",NCOLS#"f";
  origattr:NCOLS#"p",NCOLS#" ";
  t1o:createSample[NROWS1;NCOLS;origtypes;origattr;"large";range];
  t2o:createSample[rows2;NCOLS;origtypes;noattr;"small";range];
  t2oj:addCommon[t1o;t2o;1;pct;"j"];
  // original example, from email conversations with dr shasha, with attributes
  runexp[`$"original";REPS;t1o;t2oj;1;range;pct];
  // write out results in case crashes
  save `:experiments;
  .Q.gc[];
  }


scenarios:nrows2 cross ranges cross matchpcts;
// keep running out of memory, so match pct = 1 can only happen with high data range
// or small table numbers
//scenarios:{x where (p<=0.25)|(2000>first each x)&(1000<=x@\:1)&1=p:last each x} scenarios
scenarios:{x where (1000<=x@\:1)|1<>p:last each x}scenarios;
runScenario ./:scenarios

/
\S 10
n:`int$1e6
t:([]c1:n?100;c2:n?100;c3:n?100)
ts:(`$"ts_",/:string cols t) xcol 1000#t
tsr:`c1 xcol ts
\ts:10 ej[`c1;t;tsr]
\ts:10 hj[t;ts;`c1;`ts_c1;(=;`c1;`ts_c1)]

tix:@[`c1 xasc t; `c1; `p#]
\ts:10 ej[`c1;tix;tsr]
\ts:10 hj[tix;ts;`c1;`ts_c1;(=;`c1;`ts_c1)]






