// Compile aquery, with silenced warnings (since we're performing a cross in benchmark)
a2qPath:"/Users/josecambronero/MS/S15/aquery/src/a2q"
system a2qPath," -c -s -a 1 -o compiled.q definitions_aquery.a"

\l compiled.q
queries:`$"q",/:string til 8

time:{
  .Q.gc[];
  start:.z.P;
  do[x;eval(`$".aq.",y;::)];
  (.z.P - start)%1e6*x
  }
  
time[10;] each string queries
exit 0  
