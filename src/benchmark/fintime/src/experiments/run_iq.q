mkIQcmd:{[x]
 query:"dbisql -nogui -c=\"uid=DBA;pwd=sql;dbn=fintime\" sybase_queries/q",string[x],".sql";
 timing:" | tail -n 1 | awk '{ print $3 }'";
 query,timing
 }

timeit0:{[x]
  cmd:mkIQcmd x;
  show results:system cmd;
  1000 * "F"$last results // convert to milliseconds
  };
  
timeit:{[iters;query]  
  t:{y; timeit0 x}[query;] each til iters;
  (sum t)%iters
  }; 

opts:.Q.opt .z.x;
N:10;
outpath:hsym `$first opts`out;
iters:10^first "I"$opts`iters;
// execute them in a random order
randomize:{neg[count x]?x};
queries:randomize til N;
results:timeit[iters;] each queries;

msg:","sv/:("fintime";"sybase";string iters),/:string queries,'results;
// if we have a path append to that file
$[0=count outpath;1 ("\n"sv msg),"\n"; 
 [(neg h:hopen outpath) msg; hclose h]
 ];
exit 0  