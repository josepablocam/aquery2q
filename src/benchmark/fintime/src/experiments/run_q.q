\l definitions_q.q
queries:`$"q",/:string til 8

time:{
  .Q.gc[];
  start:.z.P;
  do[x;eval(`$".qtest.",y;::)];
  (.z.P - start)%1e6*x
  }
  
time[10;] each string queries
exit 0  
