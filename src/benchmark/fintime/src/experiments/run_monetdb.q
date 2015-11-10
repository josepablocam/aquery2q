// must have sourced definitions before, as they are set to be
// system variables
timeit0:{[x]
  cmd:"set -f;echo $q",string[x]," | (TIMEFORMAT=\"%R\";time (mclient -d fintime) 2>&1)";
  results:system cmd;
  show -1_results;
  1000 * "F"$last results // convert to milliseconds
  };
  
timeit:{[iters;query]  
  t:{y; timeit0 x}[query;] each til iters;
  (sum t)%iters
  }; 

opts:.Q.opt .z.x;

N:9;
outpath:hsym `$first opts`out;
iters:10^first "I"$opts`iters;
// execute them in a random order
// since q6 depends on q5, just run q5 at the start always
// for some reason running this first query can cause trouble, so will
// catch and retry until success
retryq5:{@[timeit0;5;{[x] show "rerunning q5"; system "sleep 5";.z.s[]}];}
retryq5[];

randomize:{neg[count x]?x};
queries:randomize til N;
results:timeit[iters;] each queries;
msg:","sv/:("monetdb";string iters),/:string queries,'results;
// if we have a path append to that file
$[0=count outpath;1 ("\n"sv msg),"\n"; 
 [(neg h:hopen outpath) msg; hclose h]
 ];
exit 0  