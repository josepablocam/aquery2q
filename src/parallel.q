/////////// Process Communication //////////////
// Connections and communication handles
.aq.par.connectionTypes:`worker`master`supermaster`counterpart`self;
// order of worker connection is relevant!
.aq.par.connections:([] name:`u#`$(); handle:`u#`int$(); conntype:`.aq.par.connectionTypes$())
.aq.par.nameToHandle:{(exec name!handle from .aq.par.connections) x}
.aq.par.workerHandles:{exec handle from .aq.par.connections where handle<>0}
.aq.par.workerNames:{exec name from .aq.par.connections where conntype=`worker}
.aq.par.masterNames:{exec name from .aq.par.connections where conntype=`master}
.aq.par.counterPartNames:{exec name from .aq.par.connections where conntype=`counterpart}

.aq.par.connect:{[nms;conntype]`.aq.par.connections upsert flip (nms,:(); h:hopen each nms;conntype)}

// General running commands
.aq.par.runSynch:{[wnames;r] (.aq.par.nameToHandle (),wnames)@\:r};
.aq.par.runAsynch:{[wnames;r] (neg .aq.par.nameToHandle (),wnames)@\:r};
.aq.par.runAsynchAndBlock:{[wnames;a;s] .aq.par.runAsynch[wnames;a]; .aq.par.runSynch[wnames;s]};

////// Worker Request Data /////////
// Process handles are ordered (as data is ordered)
// Find process name for next/previous process in ordered list (needed for edge extension)
.aq.par.worker.getSelfName:{first exec name from .aq.par.connections where handle=0};
.aq.par.worker.getXPrevProcessName:{first exec name from .aq.par.connections where conntype=`worker, neg[x] xprev handle=0};
.aq.par.worker.getPrevProcessName:{.aq.par.worker.getXPrevProcessName 1};
.aq.par.worker.getNextProcessName:{.aq.par.worker.getXPrevProcessName -1};

////// Primitives /////////  
// Reorder (centrally coordinated)
// Strategy:
// For each function:
//  - asynchronously execute across workers, block on result
//  - Take result and write to particular process' data structure
// args:
//    fs: list of functions to execute
//    ps: list of destination processes (same length as sel list)
//    write: function to write data to process data structure
.aq.par.master.shuffle:{[fs;ps;write]
  // all workers execute each instruction (naive: results in some unnecessary data)
  // transfer, but keeps things simple
  workers:.aq.par.workerNames[];
  // shuffle data
  .aq.par.master.shuffle0[ ;workers; ;write] ./: flip (fs;ps);
  // clean up
  .aq.par.runAsynch[ps;{delete .aq.par.temp from `.}];
  };
 
// using peach(requires that the data exist in ALL processes beforehand)
// but that is not unreasonable
.aq.par.master.shuffle0:{[f;ps;dest;write]
  //
  if[(0=count .z.pd[])|not all .z.pd[] in .aq.par.nameToHandle ps; 
      '"error: set .z.pd, ps must be all processes"];
  // actually run the computation
  data:raze {x[]} peach (count ps)#f;
  .aq.par.runSynch[enlist dest;(write;data)];
  }  
  
  
// Edge extension
.aq.par.worker.prevProcRequest:{[f;ps;def]
  self:.aq.par.worker.getSelfName[];
  prevProc:.aq.par.worker.getPrevName[];
  // if not the first process in our list, request data from 
  // if is, return empty table
  $[self<>first ps;
    .aq.par.runSynch[fprevProc;fs];
    def]
 }
 
.aq.par.worker.edgeExtend:{[w;p;t]
  f:{[x;y] select from x where i >= count[i] - w};
  .aq.par.worker.prevProcRequest[f;w;0#t]
 }
 

// Carry lookahead aggregations
// TODO


// Normal map reduce
// TODO


// Create very simple sample data for experimenting
.aq.par.createSamplePartitioned:{
 system "S ",string x;
 n:100000; // # of obs per partition
 pars:.z.D + til 10; // partitions
 parpaths:` sv/: `:sampledb,/:(`$string pars),\:`t`;
 // we avoid symbols for simplicity
 {y set ([]c1:x?10;c2:x?10;c3:x?100.;c4:x?100)}[n;] each parpaths
 };


////// Master functions /////////
// Connect to counterparts in other processes
// args: list of lists of connections, with current processes' counterparts
// in same sublist
.aq.par.worker.connectCounterParts:{[cns]
   self:.aq.par.worker.getSelfName[];
   counterparts:(cns first where any each self=cns) except self;
   .aq.par.connect[counterparts;`counterpart]
 };

// Initialize a worker
// args: worker names for master, list of lists of counterpart process names
// with each row representing a set of counterparts
.aq.par.worker.init:{[workers;ctm]
  // connect to other workers in same cohort
  .aq.par.connect[workers;`worker];
  // connect to counteparts in other cohorts if appropriate
  if[0=type ctm;.aq.par.worker.connectCounterParts ctm];
 };

// Initialize a master
// args: worker names for master, list of lists of counterpart process names
// with each row representing a set of counterparts
.aq.par.master.init:{[workers;ctm]
  // open conn to each worker
  .aq.par.connect[workers;`worker];
  // set workers to use peach
  .z.pd:{`u#exec handle from .aq.par.connections where conntype=`worker};
 // initialize workers, synch to avoid deadlock, as there are many-to-many connections
 .aq.par.runSynch[workers;(`.aq.par.worker.init;workers;ctm)];
 };
 
 // Copy a data structure to all counterpart processes with the same name
 // args: name of data
.aq.par.master.broadcast:{[nm]{.aq.par.runSynch[.aq.par.counterPartNames[];({x set y};x;get x)]} peach (count .z.pd[])#nm}
 
 
//// Super master functions //////
// Initialize super master
// args: master processes names, list of lists of worker processes
// each sublist is associated with respective master
.aq.par.supermaster.init:{[ms;ws]
  // connect to each master
  .aq.par.connect[ms;`master];
  // set masters to use peach
  .z.pd:{`u#exec handle from .aq.par.connections where conntype=`master};
  // instruct each master to initialize
  .aq.par.runSynch'[ms;(`.aq.par.master.init; ;flip ws) each ws];
 };

// Pick master for delegation
// round-robin for now
.aq.par.supermaster.COUNTER:0;
.aq.par.supermaster.pickMaster:{.aq.par.supermaster.COUNTER+:1; first .aq.par.supermaster.COUNTER rotate .aq.par.masterNames[]};

// Execute a query on a master
// args: is writer, request, callback
// callback for a writer is just the name of the data structure it writes
// callback for a reader is a function to register data on super-master (e.g. {`results set x})
.aq.par.supermaster.execute:{[writer;r;cb]  
  $[writer; .aq.par.supermaster.executeWriter[r;cb]; .aq.par.supermaster.executeReader[r;cb]]
  };

// Execute a writer query
// args: request, name of data written
.aq.par.supermaster.executeWriter:{[r;cb]
  show "executing writer query";
  master:.aq.par.supermaster.pickMaster[];
  // execute writer query
  .aq.par.runSynch[master;r];
  // now make that master broadcast the result to other masters
  .aq.par.runSynch[master;(`.aq.par.master.broadcast;cb)];
  };

// Execute a reader query
// args: request, callback to register data in super-master process
.aq.par.supermaster.executeReader:{[r;cb]
  show "executing reader query";
  master:.aq.par.supermaster.pickMaster[];
  // execute query asynchronously along with callback;
  run:{(neg .z.w) (y; eval x)};
  .aq.par.runAsynch[master;(run;r;cb)];
  };

// execute a request on all masters and all workers
// args: request (purely for sideffects) (e.g. (system; "l mydatabase"))
.aq.par.supermaster.onAll:{[r] {eval x; .aq.par.runAsynch[.aq.par.workerNames[];x]} peach (count .z.pd[])#enlist r}
  




/
// Scratch pad
// not using peach
//.aq.par.master.shuffle0:{[f;ps;dest;write]
//   // extend function to write to temporary data
//   runfun:({`.aq.par.temp set x[]};f);
//   // helper to request data from processes
//   getdata:(get;`.aq.par.temp);
//   // run function on each process in ps, and then request data from each
//   data:raze .aq.par.runAsynchAndBlock[ps;runfun;getdata];
//   // send data to destination and store using write function
//   .aq.par.runAsynch[enlist dest;(write;data)]
//  };



// Rough draft for edge extension
//.aq.par.worker.selectEdge:{[t;w] ({select from x where i in y sublist i}; t; w)};

//.aq.par.worker.edgeExtend:{[t;w]
//  pp:.aq.par.worker.getPrevProcessName[];
//  np:.aq.par.worker.getNextProcessName[];
//  // actual data
//  pt:$[null pp;0#t;.aq.par.runSynch[pp;.aq.par.worker.selectEdge[t;neg w]]]; // end of data
//  nt:$[null np;0#t;.aq.par.runSynch[np;.aq.par.worker.selectEdge[t;w]]]; // beginning of data
//  pt,t,nt
//  };

//.aq.par.worker.edgeQuery:{[q;t;w]
//  ft:q .aq.par.worker.edgeExtend[t;w];
//  select from ft where i > w, i < (neg[w]+max i)
//  };




