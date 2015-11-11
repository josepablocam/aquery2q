// Compile aquery, with silenced warnings (since we're performing a cross in benchmark)
// make sure you have a2q in your path before running
a2qcompiler:getenv `A2Q;
system a2qcompiler," -c -s -a 1 -o compiled.q definitions_aquery.a"

\l compiled.q
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
// execute them in a random order, but note that q5/q6 must be together
// since q6 depends on q5, just run q5 at the start alwayws
.aq.q5[];
randomize:{neg[count x]?x};
queries:randomize til N;
results:timeit[iters;] each `$".aq.",/:"q",/:string queries;
msg:","sv/:("aquery";string iters),/:string queries,'results;
// if we have a path append to that file
$[0=count outpath;1 ("\n"sv msg),"\n"; 
 [(neg h:hopen outpath) msg; hclose h]
 ];
exit 0  
