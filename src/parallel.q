/////////// Process Communication //////////////
// list of worker handles
.aq.par.workerNames:`u#`:localhost:7089`:localhost:7090;
.aq.par.workerHandles:`u#`int$();
.aq.par.workerToHandle:(`$())!`int$();

// connect to workers and create dictionary mapping process name
// to process handle
.aq.par.connect:{`.aq.par.workerToHandle upsert x!get `.aq.par.workerHandles upsert hopen each x}

// running commands
.aq.par.runSynch:{[wnames;r] (.aq.par.workerToHandle wnames)@\:r};
.aq.par.runAsynch:{[wnames;r] (neg .aq.par.workerToHandle wnames)@\:r};
.aq.par.runAsynchAndBlock:{[wnames;a;s] .aq.par.runAsynch[wnames;a]; .aq.par.runSynch[wnames;s]};

//////// Worker Data ////////////
.aq.par.worker.store:([id:`$()] val:());


////// Worker Request Data /////////
// Process handles are ordered (as data is ordered)
// Find process name for next/previous process in ordered list (needed for edge extension)
.aq.par.worker.getXPrevProcessName:{k (neg x)+(k:key d)?(d:.aq.par.workerToHandle)?.z.w}
.aq.par.worker.getPrevProcessName:{.aq.par.worker.getXPrevProcessName 1}
.aq.par.worker.getNextProcessName:{.aq.par.worker.getXPrevProcessName -1}



////// Primitives /////////
// Reorder (centrally coordinated)
// TODO


// Edge extension
// TODO

// Carry lookahead aggregations
// TODO


// Normal map reduce
// TODO


// Create very simple sample data for experimenting
.aq.par.master.createSamplePartitioned:{
 system "S ",string x;
 n:100000; // # of obs per partition
 pars:.z.D + til 10; // partitions
 parpaths:` sv/: `:sampledb,/:(`$string pars),\:`t`;
 // we avoid symbols for simplicity
 {y set ([]c1:x?10;c2:x?10;c3:x?100.;c4:x?100)}[n;] each parpaths
 }


////// Master functions /////////
.aq.par.master.init:{
  // open conn to each worker
  .aq.par.connect .aq.par.workerNames;
  // set workers to use peach
 `.z.d set .aq.par.workerHandles;
  // connect workers to each other, synch to avoid deadlock
  .aq.par.runSynch[.aq.par.workerNames;(`.aq.par.connect;.aq.par.workerNames)]
  }

// Rough draft for edge extension
.aq.par.worker.selectEdge:{[t;w] ({select from x where i in y sublist i}; t; w)}

.aq.par.worker.edgeExtend:{[t;w]
  pp:.aq.par.worker.getPrevProcessName[];
  np:.aq.par.worker.getNextProcessName[];
  // actual data
  pt:$[null pp;0#t;.aq.par.runSynch[pp;.aq.par.worker.selectEdge[t;neg w]]]; // end of data
  nt:$[null np;0#t;.aq.par.runSynch[np;.aq.par.worker.selectEdge[t;w]]]; // beginning of data
  pt,t,nt
  }

.aq.par.worker.edgeQuery:{[q;t;w]
  ft:q .aq.par.worker.edgeExtend[t;w];
  select from ft where i > w, i < (neg[w]+max i)
  }

/
// Simple example (assume run in directory where parallel.q is available)
// start worker processes in background
system "q parallel.q -p 7089 &"
system "q parallel.q -p 7090 &"
\l parallel.q
.aq.par.master.init[]
.aq.par.runAsynchAndBlock[.aq.par.workerNames;({`temp set til x};`int$1e7);({get `temp};::)]










