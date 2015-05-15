//Testing sorting as a table vs sorting inside group
nrows:`int$1e6;
ncols:3 5 10 20; //our tables will have various sizes
gs:`int$1 10 100 1e3 1e4 1e5 1e6; //divide table into x groups
mktbl:{[nr;nc]flip (`$"c",/:string til nc)!nr cut (nr*nc)?10}; //create a table with nr rows and nc cols
aspec:{ix iasc x[`id] ix:iasc x`c0}; //sorting spec when sorting full table
gspec:{iasc x`c0};  //given that we are grouping by id, and then sorting by c1, means our order spec is asc id, asc c0
sort:{y x y}; //sort
sorte:{y@\:x y}; //sort each 
grpids:{cty#raze (ceiling (cty:count y)%x)#'til x}; //generate group ids
agrp:{update id:{neg[count x]?x}grpids[x;y] from y}; //assign group ids
grp:{?[x;();sy!sy;cx!cx:cols[x] except sy:(),y]}; //perform a group (note that xgroups doesn't result in sorted groups)
strat1:{[t] sorte[gspec;] each grp[;`id] t}; //group then sort
strat2:{[t] grp[;`id] sort[aspec;] t}; //sort then group
timer:{1"timing\n"; ct:.z.P; x[]; %[;1e6] .z.P-ct}; //timer

run:{[nr;nc] //for each strategy, for each # of groups, apply and time
 t:mktbl[nr;nc];
 times:raze {[t;n]timer each {z;y x}[gt:agrp[n;t];]@/:(strat1;strat2)}[t;]each gs;
 flip `nr`nc`ngrps`strat`time!flip ((nr;nc),/:gs cross (`sortEach;`sortAll)),'times
 }

res:raze run ./: nrows cross ncols //run on each size of table
`:group_sorting.csv 0:csv 0:res
