\l parallel.q
PWD:first system "readlink -f ."

// helper to spin up processes
initproc:{[xtra;p] system ssr/["q parallel.q %xtra -p %p";("%xtra";"%p");(xtra;p)]}
mkhandle:{hsym `$"localhost:",x}

// 2 masters
mports:string 7087 7088
// 6 workers (3 per master)
wports:string 7089+til 6
if[count mports inter wports; '"error workers and masters must be disjoint"];

// start master processes
initproc["-s -2";] each mports
// start worker processes
initproc["";] each wports

// sleep two seconds to make sure processes are forked by OS before connecting
system "sleep 2s";

masters:mkhandle each mports;
workers:3 cut mkhandle each wports;

// initialize
.aq.par.supermaster.init[masters;workers];
// create partitioned data
.aq.par.createSamplePartitioned[1;`:toydb];
// load data on all masters and workers
.aq.par.supermaster.onAll[(system;"l ",PWD,"/toydb")];

// queries (query/callback pairs) to be processed by super-master
query1:{
  // helper function to assign chunks of values to workers
  workers:.aq.par.workerNames[];
  split:{[x;y] x!(ceiling count[y]%count x) cut y}[workers;];
  // groups split by workers
  pgs:split (select distinct c1 from t)`c1;
  // date partitions by workers
  pds:split (select distinct date from t)`date;
  // create some in-memory data for each worker process
  {[d;p] `local set select from t where date in d p}[pds;] peach workers;
  // now we want to query each in-memory table for the data we want
  fs:{[x;y] select from local where c1 in x}@/:value pgs;
  // shuffle and write to local data as "shuffled"
  .aq.par.master.map[fs;key pgs;{`shuffled upsert x}];
 };
// writers simply share name of data written as callback (used to distribute across)
// other processes
callback1:`shuffled;

query2:{raze {select from shuffled} peach .z.pd[]};
callback2:{`shuffled set x};

// we only want this from one process (otherwise will get duplicates)
query3:{raze {select from t} peach 1#.z.pd[]}
callback3:{`orig set x}

// each process creates some local data based on dates
query4:{
  // helper function to assign chunks of values to workers
  workers:.aq.par.workerNames[];
  split:{[x;y] x!(ceiling count[y]%count x) cut y}[workers;];
  // date partitions by workers
  pds:split (select distinct date from t)`date;
  // create some in-memory data for each worker process
  {[d;p] `local set select from t where date in d p}[pds;] peach workers
 };
callback4:`local; 

// sort based on 3 columns and then calculate window-based moving aggregates
query5:{
  // sorting
  read:{get `local}; sort:{`c1`c2`id xasc x}; nm:`localSorted;
  .aq.par.master.sort[read;sort;nm];
  // window operation
  readSorted:{get `localSorted}; mOp:{select c1, c2, id, ms:4 msum c4, ma:4 mavg c4 from x}; st:(::);
  raze .aq.par.master.edgeOp[4;readSorted;mOp;st]
  };
callback5:{`localMovResult set x};  


// sort based on column in other table
// ==> t[<t1.c1]
query6:{
    workers:.aq.par.workerNames[];
    // create a random table o with a single column c1
    // same length as local
    makeO:{
        system "S ",string 1+sum string .aq.par.worker.getSelfName[];
        `o set ([]c1:(count local)?10000)
        };
    {x[]} peach (count .z.pd[])#makeO;
    read:{update oc1:o.c1 from local};
    sort:{`oc1 xasc x};
    nm:`localOSorted;
    .aq.par.master.sort[read;sort;nm];
    raze{select from localOSorted} peach .z.pd[]
 };
callback6:{`q6result set x};


// Calculate sums and prods
query7:{
  workers:.aq.par.workerNames[];
  // sort data first
  read:{get `local}; sort:{`c1`c2`id xasc x};nm:`localSorted;
  .aq.par.master.sort[read;sort;nm];
  // perform carry calc
  // we fill in with zero to avoid wrapping into null
  w:1; f:{select sums c2, mins c3, maxs c4 from localSorted};
  adj:{[x;y] update c2:c2+x[0;`c2], c3:c3&x[0;`c3], c4:c4|x[0;`c4] from y};
  .aq.par.master.carryOp[w;f;adj;(::)]
  };
callback7:{`q7result set x};

// Avg and sum by c1, c2
query8:{
  workers:.aq.par.workerNames[];
  // group data first
  read:{get `local}; grp:{select c3, c4 by c1, c2 from x};nm:`localGrouped;
  .aq.par.master.groupby[read;grp;nm];
  // perform the actual calc
  raze {select c1, c2, avg each c3, sum each c4 from localGrouped} peach .z.pd[]
  };
callback8:{`q8result set x};


query9:{
  workers:.aq.par.workerNames[];
  // group
  read:`local;
  grp:{select date, id, c3, c4 by c1 from x};
  nmGrouped:`localGrouped;
  .aq.par.master.groupby[read;grp;nmGrouped];
  // now sort within each group
  {`localGrouped set update ix:{i iasc x i:iasc y}'[date;id] from localGrouped} peach .z.pd[];
  {`localGrouped set update c3:c3@'ix, c4:c4@'ix from localGrouped} peach .z.pd[];
  // now the actual query, write table
  {`q9result set select c1, last each c3, last each c4 from localGrouped} peach .z.pd[]
  };
callback9:`q9result;


query10:{
  raze {select from q9result} peach .z.pd[]
 };
callback10:{`q10result set x};

// Avg and sum by c1, c2 (map-reduce)
// This is a much more likely strategy than query8
query11:{
  init:{select s3:sum c3, ct3:count c3, s4:sum c4 by c1, c2 from local};
  reduce:{y upsert x pj y};
  k:2;
  data:.aq.par.master.reduce[init;reduce;k];
  select c1, c2, c3:s3%ct3, c4:s4 from data
  };
callback11:{`q11result set x};


// Group, then join (with ij)
// And perform sum
query12:{
  .aq.par.master.groupby[`local;{select id, c3 by c1, c2 from x};`t1grouped];
  .aq.par.master.groupby[`local;{select id, c4 by c1, c2 from x};`t2grouped];
  // sorted by id
  {`t1grouped set update ix:iasc each id from t1grouped} peach .z.pd[];
  {`t2grouped set update ix:iasc each id from t2grouped} peach .z.pd[];
  {`t1grouped set update id:id@'ix, c3:c3@'ix from t1grouped} peach .z.pd[];
  {`t2grouped set update id:id@'ix, c4:c4@'ix from t2grouped} peach .z.pd[];
  .aq.par.master.join[ej;`c1`c2;`t1grouped;`t2grouped;`tjoined];
  // now we want to ungroup them add columns and return result
  `id xasc raze {select id, c1, c2, added:c3+c4 from ungroup tjoined} peach .z.pd[]
  };
callback12:{`q12result set x};



/
.aq.par.supermaster.execute[1b;(query1;::);callback1];
.aq.par.supermaster.execute[0b;(query2;::);callback2];
.aq.par.supermaster.execute[0b;(query3;::);callback3];
.aq.par.supermaster.execute[1b;(query4;::);callback4];
.aq.par.supermaster.execute[0b;(query5;::);callback5];
.aq.par.supermaster.execute[0b;(query6;::);callback6];
.aq.par.supermaster.execute[0b;(query7;::);callback7];
.aq.par.supermaster.execute[0b;(query8;::);callback8];
.aq.par.supermaster.execute[1b;(query9;::);callback9];
.aq.par.supermaster.execute[0b;(query10;::);callback10];
.aq.par.supermaster.execute[0b;(query11;::);callback11];
.aq.par.supermaster.execute[0b;(query12;::);callback12];


/ Simple check of moving average
\l toydb
ref:select `#c1, c2, id, ms:4 msum c4, ma:4 mavg c4 from `c1`c2`id xasc select from t
ref~localMovResult

/ Simple carry calculation
ref:select sums c2, mins c3, maxs c4 from `c1`c2`id xasc select from t
ref~q7result

/ Simple group by (can be done with shuffled group-by, or map-reduce)
ref:update `#c1 from 0!select avg c3, sum c4 by c1, c2 from t
ref~q8result
ref~q11result

/ Simple sort, then group by
ref:update `#c1 from 0!select last c3, last c4 by c1 from `date`id xasc select from t
ref~q10result

/ Group, join, and add
ref:`id xasc select id, c1, c2, added:c3+c4 from ungroup {ej[`c1`c2;x;`c1`c2`id2 xcol x]} select id, c3, c4 by c1, c2 from select from t
ref~q12result
