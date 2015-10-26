// Load q query definitions (as functions)
\l definitions_q.q

// Compile aquery, with silenced warnings (since we're performing a cross in benchmark)
// Make sure you have a2q in your path or aliased
system "a2q -c -s -a 1 -o compiled.q definitions_aquery.a"

// Load compiled aquery (will run one query once, by default)
\l compiled.q
N:9;
queries:`$"q",/:string til N;

//verify correctness
show "---> Queries match"
show results:queries!{
  ar:eval(`$".aq.",x;::);
  .Q.gc[];
  qr:eval(`$".qtest.",x;::);
  ar~qr
  } each string queries;
  

$[all results; exit 0; exit 1];


 
