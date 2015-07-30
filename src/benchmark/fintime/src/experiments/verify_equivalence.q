

// Load q
\l test_q.q

// Compile aquery, with silenced warnings (since we're performing a cross in benchmark)
a2qPath:"/Users/josecambronero/MS/S15/aquery/src/a2q"
system a2qPath," -c -s -a 1 -o compiled.q definitions_aquery.a"

// Load compiled aquery (will run one query once, by default)
\l compiled.q

queries:`$"q",/:string til 8

nruns:10;

//verify correctness
queries!{
  ar:eval(`$".aq.",x;::);
  .Q.gc[];
  qr:eval(`$".aq.",x;::);
  ar~qr
  } each string queries
exit



 
