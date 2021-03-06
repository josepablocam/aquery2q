\l definitions_q.q
timeit:{[x;y]
  `funtotime set get y;
  .Q.gc[];
  time:system ssr["ts:%d funtotime[]";"%d";string x];
  @[`float$time;enlist 0;%[;x]]
  }
  
opts:.Q.opt .z.x;
N:10;
outpath:hsym `$first opts`out;
iters:10^first "I"$opts`iters;
// execute them in a random order
randomize:{neg[count x]?x};
queries:randomize til N;
results:timeit[iters;] each `$".qtest.",/:"q",/:string queries;
msg:","sv/:("fintime";enlist "q";string iters),/:string queries,'results;
// if we have a path append to that file
$[0=count outpath;1 ("\n"sv msg),"\n"; 
 [(neg h:hopen outpath) msg; hclose h]
 ];
exit 0  