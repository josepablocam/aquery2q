\l parallel.q
PWD:first system "readlink -f ."

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
.aq.par.createSamplePartitioned 1;
// load data on all masters and workers
.aq.par.supermaster.onAll[(system;"l ",PWD,"/sampledb")];

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
  .aq.par.master.shuffle[fs;key pgs;{`shuffled upsert x}];
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


/
.aq.par.supermaster.execute[1b;(query1;::);callback1];
.aq.par.supermaster.execute[0b;(query2;::);callback2];
.aq.par.supermaster.execute[0b;(query3;::);callback3];
.aq.par.supermaster.execute[1b;(query4;::);callback4];
.aq.par.supermaster.execute[0b;(query5;::);callback5];
.aq.par.supermaster.execute[0b;(query6;::);callback6];

/ Simple check of moving average calculation
ref:raze .aq.par.runSynch[first .aq.par.masterNames[];({select c1, c2, id, ms:4 msum c4, ma:4 mavg c4 from `c1`c2`id xasc select from t};::)]
ref~localMovResult





/
Author note: "f peach args" doesn't actually distribute the function to the workers
as it might immediately look. It allocates a call of f[arg] (one elem of the list)
to each slave process (as indicated by .z.pd). I believe (and am trying to confirm)
that if count[args] = count[n], and slave processes start out with 0 workload, then
this uniquely allocates one task to each process in the order of process handles in .z.pd

I have a slightly uglier call that guarantees this and behaves similar to peach otherwise
.aq.par.runAsynchAndBlock

