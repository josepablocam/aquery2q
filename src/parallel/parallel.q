// Jose Cambronero (jose.cambronero@cs.nyu.edu)
// Aquery parallel: a library for distributed computation in q

// Some quick terminology for documentation
// Super-master: user interacts with this process, delegates queries to master
// Master: executes queries on worker processes
// Worker: processes associated with a given master, execute functions
// Master + workers = cohort

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
// checks to be made relating to connections etc
.aq.par.checks:{if[0<=system "s"; '"-s must be negative to use framework"];};

// General running commands
// In general, we try to use peach when possible (with each process executing once)
// (i.e. .z.pd = workers, and peach with # of args = # of workers)
// Otherwise, can use the below to handle communication

// Run a request synchronously/asychronously on each process
// args:
//  names: process names to execute on
//  r: request to execute (e.g. ({get x};`mytable))
.aq.par.runSynch:{[names;r] (.aq.par.nameToHandle (),names)@\:r};
.aq.par.runAsynch:{[names;r] (neg .aq.par.nameToHandle (),names)@\:r};

// Run a request asynchronously, and then execute a synchronous request on each process
// Useful to block until synchronous requests have been handled (provides more control vs. peach)
// args:
//  names: process names to execute on
//  a: asynchronous request (e.g ({y set get x};`mytable;`othertable))
//  s: syncronous request (e.g. ({x set othertable};`result))
.aq.par.runAsynchAndBlock:{[names;a;s] .aq.par.runAsynch[names;a]; .aq.par.runSynch[names;s]};



/////////// Super Master functions ///////////
// Initialize super master
// args:
//  ms: master processes names
//  ws: matrix of worker processes name, each row is associated with respective master
.aq.par.supermaster.init:{[ms;ws]
  .aq.par.checks[];
  // connect to each master
  .aq.par.connect[ms;`master];
  // set peach to use masters
  .z.pd:{`u#exec handle from .aq.par.connections where conntype=`master};
  // instruct each master to initialize
  .aq.par.runSynch'[ms;(`.aq.par.master.init; ;flip ws) each ws];
  // initialize availability list to all masters
  .aq.par.supermaster.availMasters:`$();
  .aq.par.supermaster.registerAvail each .aq.par.masterNames[];
  // initialize job queue to empty
  .aq.par.supermaster.jobQueue:();
 };

// Job assignment
// Assigns job to a master if any jobs still remain and masters are available for execution
.aq.par.supermaster.assignJob:{
  if[(0 < count .aq.par.supermaster.availMasters) & 0 < count .aq.par.supermaster.jobQueue; 
  .aq.par.supermaster.runJob[]
  ];
  }

// Run a job
// Run the first job in the queue, with the first master in the list of available masters
// remove both from their respective lists  
.aq.par.supermaster.runJob:{
  // take first master and adjust availability list
  assigned:first .aq.par.supermaster.availMasters;
  .aq.par.supermaster.availMasters:1_ .aq.par.supermaster.availMasters;
  // take first job and adjust remaining job queue
  job:first .aq.par.supermaster.jobQueue;
  .aq.par.supermaster.jobQueue:1_ .aq.par.supermaster.jobQueue;
  // execute job on assigned master
  (job 0) . (assigned,1_job)
  };  

// Register a master as available for execution
// args:
//  master: available master
.aq.par.supermaster.registerAvail:{[master]
  `.aq.par.supermaster.availMasters upsert master;
  };

// Actions upon job completion
// This is added to all callbacks, re-registers master as available and checks
// if any jobs remain to be assigned 
// args:
//  master: newly available master
.aq.par.supermaster.completedJob:{[master]
  .aq.par.supermaster.registerAvail master;
  .aq.par.supermaster.assignJob[];
  }  
  
// Execute a query on a master process
// adds to the query as a job to be executed as soon as a master is available
// args:
//  w: boolean, true if is writer query
//  r: request (i.e. query) to execute
//  cb: callback (a symbol if writer query, used to read that name and broadcast)
//      or a function to execute with result, if reader query
.aq.par.supermaster.execute:{[w;r;cb]
  // job to add to job queue
  job:($[w;.aq.par.supermaster.executeWriter;.aq.par.supermaster.executeReader];r;cb);
  `.aq.par.supermaster.jobQueue upsert enlist job;
  .aq.par.supermaster.assignJob[];
  };

// Execute a writer query
// Not intended for use directly, use .aq.par.supermaster.execute
// args:
//  master: master to execute query
//  r: request to execute (must write data with name n)
//  n: name of data written (must be able to read from this in worker processes), used
//    to write with same name to peer processes
.aq.par.supermaster.executeWriter:{[master;r;n]
  show "executing writer query on ",string master;
  // execute writer query
  .aq.par.runSynch[master;r];
  // now make that master broadcast the result to other masters
  .aq.par.runSynch[master;(`.aq.par.master.broadcast;n)];
  // and register job completion
  .aq.par.supermaster.completedJob[master];
  };

// Execute a reader query
// Not intended for use directly, use .aq.par.supermaster.execute
// args: request, callback to register data in super-master process
//  master: master to execute query
//  r: request to execute (must return data)
//  cb: call back to be execute on result of r
.aq.par.supermaster.executeReader:{[master;r;cb]
  show "executing reader query on ",string master;
  // execute query asynchronously along with callback
  run:{(neg .z.w) (y; eval x); (neg .z.w) (`.aq.par.supermaster.completedJob; z)};
  .aq.par.runAsynch[master;(run;r;cb;master)];
  };

// Execute a request on all masters and all workers
// args:
//  r: request (purely for sideffects) (e.g. (system; "l mydatabase"))
.aq.par.supermaster.onAll:{[r]
  run:{eval x; {eval x} peach (count .z.pd[])#enlist x};
  $[1=cm:count .z.pd[];
    .aq.par.runSynch[.aq.par.masterNames[];(run;r)];
    run peach cm#enlist r
    ]
  };



/////////// Master functions ///////////
// Initialize a master
// args:
//  ws: worker names for master
//  ctp: matrix of counterpart process names
//    (row i represents counterparts in other process to worker process i in this cohort)
.aq.par.master.init:{[ws;ctp]
  .aq.par.checks[];
  // open conn to each worker
  .aq.par.connect[ws;`worker];
  // set peach to use workers
  .z.pd:{`u#exec handle from .aq.par.connections where conntype=`worker};
 // initialize workers, synch to avoid deadlock, as there are many-to-many connections
 .aq.par.runSynch[ws;(`.aq.par.worker.init;ws;ctp)];
 };

 // Copy a data structure with the same name to all counterpart processes in other cohorts
 // args:
 //   nm: name of data structure
 //     (used to read from this cohort and write to counterparts with same name)
.aq.par.master.broadcast:{[nm]
  readAndWrite:{.aq.par.runSynch[.aq.par.counterPartNames[];({x set y};x;get x)]};
  readAndWrite peach (count .z.pd[])#nm
  };

// Define a value on all workers and self
// args:
//  nm: name of definition
//  def: definition
.aq.par.master.define:{[nm;def]
  nm set def;
  {x set y}[;def] peach (count .z.pd[])#nm
  };

// Map partition values to workers
// so that each partition is mapped to a single worker
.aq.par.master.mapPartitions:{ pv (group (count pv:.Q.pv)#.aq.par.workerNames[]) }

/////////// Worker functions ///////////
// Connect to counterparts processes in other cohort
// args:
//  ctp: matrix of counterpart process names
//    (row i represents counterparts in other process to worker process i in this cohort)
.aq.par.worker.connectCounterParts:{[ctp]
   self:.aq.par.worker.getSelfName[];
   counterparts:(ctp first where any each self=ctp) except self;
   .aq.par.connect[counterparts;`counterpart]
 };

// Initialize a worker
// args:
//  ws: worker names for given cohort
//  ctp: matrix of counterpart process names
//    (row i represents counterparts in other process to worker process i in this cohort)
.aq.par.worker.init:{[ws;ctp]
  // connect to other workers in same cohort
  .aq.par.connect[ws;`worker];
  // connect to counteparts in other cohorts if appropriate
  if[0=type ctp;.aq.par.worker.connectCounterParts ctp];
 };

// Find useful process names (self-explanatory): self, previous, next
// Process handles are considered ordered (as data is ordered)
.aq.par.worker.getSelfName:{first exec name from .aq.par.connections where handle=0};
.aq.par.worker.getXPrevProcessName:{first exec name from .aq.par.connections where conntype=`worker, neg[x] xprev handle=0};
.aq.par.worker.getPrevProcessName:{.aq.par.worker.getXPrevProcessName 1};
.aq.par.worker.getNextProcessName:{.aq.par.worker.getXPrevProcessName -1};

// Delete temporary data created by distributed operations (stored to .aq.par.temp)
.aq.par.worker.cleanUp:{![`.aq.par;();0b;(),x]}



/////////// Primitives ///////////
// Distributed computation is handled through use of 4 "primitives"
// Map (as in map-reduce), Edge Extension, Carry, (Staged) Reduce (as in map-reduce)
// Each primitive encapsulates all parallelism in a given cohort

////// Order-Preserving Map //////
// (aka. order-preserving re-partioning of data across worker processes)
// Guarantees that writes take place in order of worker list and so maintain
// any other underlying sort of data. (e.g. sort by date, and partition by id, would result in
// common id entries sorted by date)
// This precludes parallelization, so if speed is a concern, use .aq.par.master.map instead
// Strategy:
// For each function read in reads:
//  - synchronously execute across workers
//  - instruct processes to write results of read to respective process in dests
// args:
//    reads: list of functions to read data needed for a given process destination
//    dests: list of destination processes (same length as read list)
//    write: function to write data to process data structure (most likely of the form {x upsert y})
.aq.par.master.opMap:{[reads;dests;write]
  workers:.aq.par.workerNames[];
  // for each function and destination process
  // instruct each process to read and write to destination process 
  // self will correspond to handle 0 (and thus not actually send), but just copy over
  // as desired
  .aq.par.master.opMap0[ ;workers;write; ] ./: flip (reads;dests);
  // clean up potential temporary data created
  .aq.par.worker.cleanUp peach (count workers)#`temp;
  };
 
.aq.par.master.opMap0:{[read;workers;write;dest]
  //
  if[(0=count .z.pd[])|not all .z.pd[] in .aq.par.nameToHandle workers;
      '"error: set .z.pd, workers must be all processes"];
  // read data, and then write to destination process, writing done synch
  request:{[dest;read;write] .aq.par.runSynch[dest;(write;read[])]}[;read;write];
  // we want to make sure we are done writing all data destined for dest before
  // moving to next destination process
  // requests are issued synchronously, as we want writes to take place in order
  // of worker list
  .aq.par.runSynch[workers;(request;dest)];
  };

////// Non-Order-Preserving map (in-memory re-partition) //////
// Makes no guarantees for order of writes, as workers write data in parallel
// If order is not a concern, use this rather than the order-preserving variant, for speed.
// Strategy:
// For each worker (in parallel):
//  - select data for a destination, and send asynchronously
//  master blocks until all writes are done
// args:
//    reads: list of functions to read data needed for a given process destination
//    dests: list of destination processes (same length as read list)
//    write: function to write data to process data structure (most likely of the form {x upsert y})
.aq.par.master.map:{[reads;dests;write]
  workers:.aq.par.workerNames[];
  // workers perform writes in parallel
  .aq.par.worker.map0[dests;reads; ] peach (count workers)#write;
  // block until all workers done with their shuffle writes
  .aq.par.master.waitWhile[.aq.par.master.workNotDone];
  .aq.par.worker.cleanUp peach (count workers)#`temp;
  };

// master is not done until all workers are done
.aq.par.master.workNotDone:{not all .aq.par.worker.workDone peach .z.pd[]};
// waiting loop. master sleeps for a small amount of time before checking
// for completion again
.aq.par.master.waitWhile:{[continue] .aq.par.master.sleep/[continue;::];};

// put master process to sleep while workers continue to write
.aq.par.master.SLEEP_INTERVAL:"0.05";
.aq.par.master.sleep:{ system "sleep ",.aq.par.master.SLEEP_INTERVAL; };

// Worker keeps track of destinations that need to be written to
// callbacks update this list to allow determining if a worker is done with work
// all writes are done asynchronously
.aq.par.worker.map0:{[dests;reads;write]
  // list of destinations acts as work list, 1 entry removed when write done
  .aq.par.worker.workList:dests;
  job:{[d;r;w]
     // write data and call back
    .aq.par.runAsynch[d;({y x; (neg .z.w) (`.aq.par.worker.updateWorkList;::)};r[];w)]
    }[;;write];
  job'[dests;reads]
  };

// worker is done with their job when their worklist is empty
.aq.par.worker.workDone:{0=count .aq.par.worker.workList};
// updates work list by removing the first entry (don't care which entry removed for now)
.aq.par.worker.updateWorkList:{.aq.par.worker.workList:1_.aq.par.worker.workList};

////// Edge extension //////
// (aka. add necessary data from previous process for window-ed ops)
// Strategy:
//  - Each process is instructed to read their data, and ask the process
//    prior to it for the appropriate edge of missing data
//  - Once the data has been extended as necessary, each process can execute
//    an operation (f) and has a "callback" function cb, which either returns
//    the data or stores it locally
// args:
//    w: maximum window size required for edge e.g. 24
//    read: function to read data necessary e.g. {select from t}; {t}
//    f: actual operation that required the extended data e.g. {select 24 msum c1 from t}
//    write: a storing function, which either returns (::) or writes data locally to process
//      e.g. {`winopresult set x}
//    write: function to write data to process data structure
.aq.par.master.edgeOp:{[w;read;f;write]
  workers:.aq.par.workerNames[];
  .aq.par.worker.edgeOp[ ;read;f;write] peach (count workers)#w
  };

// Select edge of relevant data in a given process
//  n: number of records to take from bottom of data read with read[]
//  read: function to read data
.aq.par.worker.selectEdge:{[n;read] select from read[] where i>neg[n]+last i};

// Extend data and perform operation
// args: window size to extend, function to read data, operation requiring extended data,
//  w: window size to extend
//  read: function to read data
//  f: operation that required the extended data
//  write: a storing function, which either returns (::) or writes data locally to process
// function to store data
.aq.par.worker.edgeOp:{[w;read;f;write]
  prevProc:.aq.par.worker.getPrevProcessName[];
  result:$[null prevProc;
    f read[];
    w _ f (raze .aq.par.runSynch[prevProc;(`.aq.par.worker.selectEdge;w;read)]),read[]];
    write result
  };


////// Carry //////
// (aka. calculate running values and adjust, akin to map-reduce with an
//  order-dependent scan as reduce function)
// Strategy:
//  - Each process is instructed to compute their intermediate results and store to
//    a temporary table
//  - In a second pass, each process requests the last w results from the process prior to it
//    and combines their intermediate results with this "carry".
// Note that this is different from edge-extend, where the edge-operation
// can be carried out in parallel. In this case, we need to sequential scan
// args:
//  w: window of edge to read (e.g. 1)
//  f: intermediate result calculation (e.g. select sums c1 from t)
//  adjust: function to adjust intermediate results with carry, takes edge values from prior
//   process as first argument, and intermediate results of current process as second argument
//   (e.g. {[p;c]  update c1+ad[0;`c1] from t})
//  write: function to return results or write locally
.aq.par.master.carryOp:{[w;f;adjust;write]
  workers:.aq.par.workerNames[];
  // each process executes f in parallel
  {`.aq.par.temp set x[]} peach (count .z.pd[])#f;
  // passes (sequentially) over each worker and adjusts with adjust function
  results:raze raze .aq.par.runSynch[ ;(`.aq.par.worker.carryOp;w;adjust;write)] each workers;
  .aq.par.worker.cleanUp peach (count workers)#`temp;
  results
 };

// Adjust data as necessary in worker process
// args:
//  w: window of edge to read
//  adjust: function to adjust intermediate results with carry, takes edge values from prior
//   process as first argument, and intermediate results of current process as second argument
//  write: function to return results or write locally
.aq.par.worker.carryOp:{[w;adjust;write]
  prevProc:.aq.par.worker.getPrevProcessName[];
  requestEdge:(`.aq.par.worker.selectEdge;w;{`.aq.par.temp});
  // if appropriate, request carry, adjust, store in .aq.par.temp (for following process)
  // to access and then store with user provided write function
  write $[null prevProc;.aq.par.temp;.aq.par.temp:adjust[raze .aq.par.runSynch[prevProc;requestEdge];.aq.par.temp]]
 };


////// Staged-reduce //////
// (Optionally staged) reduce (a la map-reduce), nothing particular here
// Strategy:
//  - Each worker executes an initial function (can be as simple as a selection)
//  - Each reduction phase creates groups of worker processes of at most size k, and reduces
//    their data in a single process (the last one in that group).
//    This set of reducers constitute the set of eligible workers for the next reduction phase
//  - Operations must be associative and commutative, as no order of reduction is guaranteed
// args:
//  init: initial function function (e.g. {select sum c1 by c2 from t})
//  reducer: reducing function (e.g.{ y,x pj y})
//  k: max size of each reducer group (e.g 2)
.aq.par.master.reduce:{[init;reduce;k]
  // if executes with k=1 will loop forever, since never reducing
  if[k=1;'"must have at least 2 reducers per reduction group"];
  workers:.aq.par.workerNames[];
  ctWorkers:count workers;
  // clean up data structures
  .aq.par.worker.cleanUp peach ctWorkers#`temp;
  // each worker executes the init function and stores data to temp
  {.aq.par.temp:x[]} peach (count workers)#init;
  // reduce until all results are in a single process
  stopWhenOne:{1<>count raze x};
  // at each phase create reducer groups of at most size k
  partitionReducers:cut[k;];
  // create verb to be executed in each reduce phase
  reduceLoop:.aq.par.master.reduce0[reduce; ] partitionReducers@;
  holdsResult:reduceLoop/[stopWhenOne;workers];
  // get result from final reducer
  result:first .aq.par.runSynch[holdsResult;({.aq.par.temp};::)];
  .aq.par.worker.cleanUp peach ctWorkers#`temp;
  result
  };

// Instruct reducers to request data from their reducer group, combine
// and return new set of workers to partition as reducers for next step
// args:
//  reduce: reduce function to combine results (commutative and associative), takes 2 args
//  reducerGroups: groups of at most size k, each group reduces in parallel
.aq.par.master.reduce0:{[reduce;reducerGroups]
  // will hold results and actually reduce
  reducers:last each reducerGroups;
  // mapping from reducer to processes that they should query for intermediate results
  reducerGroupMap:reducers!reducerGroups;
  request:(`.aq.par.worker.reduce;reduce;reducerGroupMap);
  callback:(`.aq.par.worker.getSelfName;::);
  // reduce in parallel and return names
  // of new set of workers to use as reducers for next phase
  .aq.par.runAsynchAndBlock[reducers;request;callback]
  };

// Reduce data by requesting from appropriate processes
// args:
//  reduce: reduce function to combine results (commutative and associative), takes 2 args
//  reducerGroupMap: dictionary from reducer name to name of processes that should be
//    queried for intermediate results to reduce.
.aq.par.worker.reduce:{[reduce;reducerGroupMap]
  // find processes that you should query for data to combine
  reducerGroup:reducerGroupMap .aq.par.worker.getSelfName[];
  //reduce if appropriate, otherwise already done
  if[1<count reducerGroup;
    .aq.par.temp:(reduce/).aq.par.runSynch[reducerGroup;({.aq.par.temp};::)]
  ];
  };



/////////// Common query operations ///////////
// These common query operations are written as composites of primitives
// We implement: distributed sorting, distributed group-by, distributed-join

////// Distributed sorting //////
// Sort data across worker processes
// args:
//  read: function to read data to be sorted from worker processes
//  sort: function to sort data
//  nm: name with which to write sorted data
.aq.par.master.sort:{[read;sort;nm]
   workers:.aq.par.workerNames[];
   ctWorkers:count workers;
   // sort local data in each process
   .aq.par.util.sortLocalData[sort;] peach ctWorkers#read;
   // select representatives from each process to use as potential pivots for sort
   sampled:raze .aq.par.util.pickSortPivots peach ctWorkers#{.aq.par.temp};
   // sort the sample and pick representatives as reference points (i.e. pivots)
   refs:ctWorkers sublist .aq.par.util.takeEveryN[sort sampled;ctWorkers];
   // create table labeling each obs with process based on reference observations
   .aq.par.worker.assignProcessSort[ ;refs;workers] peach ctWorkers#sort;
   // create functions to shuffle based on sorting order
   shuffles:{[x;y] .aq.par.worker.getDataToSend x}@/:workers;
   // make sure the temporary name we are using is empty before inserting anything
   temp:`.aq.par.sort;
   {x set ()} peach ctWorkers#temp;
   // shuffle based on sorting (upserting new entries)
   .aq.par.master.map[shuffles;workers;{[o;a] o upsert a}[temp;]];
   // sort data in each process (as entries have been upserted incrementally)
   {z set x get y}[sort;temp; ] peach ctWorkers#nm;
  };

// take every nth observation in a list
// args:
//  x: list of observations
//  y: n
.aq.par.util.takeEveryN:{x where (count x)#1b,(-1+y)#0b};

// Swap observations in a list (element-wise)
//  args:
//    v: list of values
//    a: values to swap with b
//    b: values to swap with a
.aq.par.util.swap:{[v;a;b] @[v;a,b;:;b,a]};

// Sort data local to a process
// args:
//  read: function to read data
//  sort: function to sort data
.aq.par.util.sortLocalData:{[sort;read]
  `.aq.par.temp set sort read[]
  };

// Pick observations from a given process to be proposed as pivots for sorting
// args:
//  read: function to read data
//  Data should have been sorted by now (and thus read should read from .aq.par.temp)
.aq.par.util.pickSortPivots:{[read]
  data:read[];
  sampleN:ceiling (count data)%count .aq.par.workerNames[];
  .aq.par.util.takeEveryN[data;sampleN]
  };

// Assign what process each observation should be assigned to, based on
// position in sorting
// args:
//  sort: function to sort data
//  refs: reference points (pivot observations)
//  dests: processes associated with each pivot observation
.aq.par.worker.assignProcessSort:{[sort;refs;dests]
  // label reference observations as such and associate their destination process
  refs:update proc:dests, isref:1b from refs;
  // .aq.par.temp holds sorted observations from .aq.par.util.sortLocalData
  combined:(update proc:0#dests, isref:0b from .aq.par.temp),refs;
  // swap records so that refs are spread out throughout t (avoids all records)
  // being assigned to just one process etc
  ctComb:count combined; ctRefs:count refs; nCt:ceiling ctComb%ctRefs;
  ix:til ctComb;
  ix:.aq.par.util.swap[ix;.aq.par.util.takeEveryN[ix;nCt];neg[ctRefs] sublist ix];
  sorted:sort combined ix;
  // assign each observation to one of the processes
  assigned:update proc:reverse fills reverse fills proc from sorted;
  `.aq.par.temp set assigned
   };

// Query a process with data sorted and labeled with destination process
// for observations destined to a given process
// args:
//  want: process for which we want to get data
.aq.par.worker.getDataToSend:{[want]
  delete proc, isref from select from .aq.par.temp where proc=want, not isref
 };


////// Distributed group-by //////
// Perform group-by such that each group is wholly contained within a single process
// args:
//  read: function to read data to be grouped
//  grp: function to group data read with read[]
//  nm: name with which to write grouped data
.aq.par.master.groupby:{[read;grp;nm]
  workers:.aq.par.workerNames[];
  ctWorkers:count workers;
  // clean up data structures
  .aq.par.worker.cleanUp peach ctWorkers#`temp;
  // add up counts per group across processes
  groupCts:{y upsert x pj y}/[.aq.par.worker.groupby[read;] peach ctWorkers#grp];
  // sort groups so that consecutive groups are in the same process
  // as would happen with select ... by ...
  groupCts:(keys groupCts) xasc groupCts;
  // allocate groups in a way to reasonably balance number of obs per process
  groupCts:delete aq__ct from update aq__proc:.aq.par.master.allocGroup[aq__ct;workers] from groupCts;
  // now join this group allocation info to each processes local grouped data
  {[x;y] .aq.par.worker.addGroupAlloc[x]}[groupCts;] peach .z.pd[];
  // create shuffling functions
  shuffles:{[x;y] delete aq__proc from select from .aq.par.temp where aq__proc=x}@/:workers;
  // create special group-based append function
  groupAppend:{[o;a] odat:@[get;o;0#a]; o set $[0=count a;odat;odat,''a]};
  // group-by
  .aq.par.master.map[shuffles;workers;groupAppend[`.aq.par.group;]];
  {x set .aq.par.group} peach ctWorkers#nm;
  .aq.par.worker.cleanUp peach ctWorkers#`group;
  };

// Allocate groups to different worker processes (each group is entirely within a given
// process)
// args:
//  groupCounts: vector of counts for each group
//  workers: list of worker processes
.aq.par.master.allocGroup:{[groupCounts;workers]
  workers -1+sums differ s div 1+ceiling (last s:sums groupCounts)%count workers
  };

// Create temporary table with grouped data (assigned to .aq.par.temp)
// and returns a count of observations in each group (used to allocate groups to processes)
// Creates a column aq__ct to be used to hold count of observations
// we assume this is an unlikely column conflict (given double underscore)
// but we fail if it is a conflict
// args:
//  read: function to read data to be grouped
.aq.par.worker.groupby:{[read;grp]
  data:read[];
  if[`aq__ct in cols data; '"distributed group-by needs aq__col col, current conflict"];
  // store a copy, avoid grouping again later
  .aq.par.temp:grp data;
  groupcols:keys .aq.par.temp;
  valcols:cols[.aq.par.temp] except groupcols;
  groupCts:?[.aq.par.temp;();0b;(groupcols,`aq__ct)!groupcols,enlist (count each;first valcols)];
  groupcols xkey groupCts
  };

// Add group-process allocation information to grouped data (stored in .aq.par.temp)
// args:
//  alloc: table indicating allocation information for each group
.aq.par.worker.addGroupAlloc:{[alloc]
  .aq.par.temp:.aq.par.temp lj alloc;
  };


////// Distributed join //////
// Perform join such that we effectively repartition data along first join column
// so that all instances of a given value are held within the same process for both tables.
// We attempt to reduce the number of groups by first combining the possible join key values
// according to the type of join (if not one of the predefined joins, we are conservative and
// move all data).
// args:
//  join: operator to use for join (ej/lj/ij) or function that takes 3-args (cols, lhs table, rhs table)
//  jcols: columns along which we join
//  readl: function to read table on left of join
//  readr: function to read table on right of join
//  nm: to write the joined table as
.aq.par.master.join:{[join;jcols;readl;readr;nm]
  workers:.aq.par.workerNames[];
  ctWorkers:count workers;
  // make sure our temporary data structures are empty
  .aq.par.worker.cleanUp peach ctWorkers#enlist`temp`join;
  // various key operations depend on our join
  joinOps:.aq.par.master.getJoinOps[join];
  // join wrapper
  jc:joinOps[`jc][jcols;;];
  // key combinators
  lhscomb:joinOps[`lhs];
  rhscomb:joinOps[`rhs];

  // get preliminary values for join keys in each table
  klPrelim:raze .aq.par.worker.getJoinKeys[ ;readl] peach ctWorkers#enlist jcols;
  krPrelim:raze .aq.par.worker.getJoinKeys[ ;readr] peach ctWorkers#enlist jcols;

  // the end result of what keys we care about depends on the join type
  // at this point, we re-partition solely by the first column in the join columns
  partitionOn:enlist first jcols;
  kl:distinct partitionOn#lhscomb[klPrelim;krPrelim];
  kr:distinct partitionOn#rhscomb[klPrelim;krPrelim];

  // allocate groups to workers, allocation is based on kl (note that in cases of unknown)
  // join, this will correctly be the union of keys in both tables
  allocKs:partitionOn xkey update aq__proc:(count kl)#workers from kl;

  // associate names with temporary shuffle data and shuffle results
  templ:`.aq.par.join.temp.tl; tempr:`.aq.par.join.temp.tr;
  l:`.aq.par.join.tl; r:`.aq.par.join.tr;
  joined:`.aq.par.join.joined;

  // prepare tables for joins (make sure to only shuffle necessary data by using our
  // table-specific keys to select)
  .aq.par.master.prepareJoin[readl;templ;kl#allocKs;workers;l];
  .aq.par.master.prepareJoin[readr;tempr;kr#allocKs;workers;r];

  // actually perform the join now
  // make sure join table is empty
  {x set ()} peach ctWorkers#joined;
  .aq.par.worker.join[jc;l;r; ] peach ctWorkers#(joined upsert);
  // move results to final name
  {y set get x}[joined;] peach ctWorkers#nm;
  // clean up temporary join data
  .aq.par.worker.cleanUp peach ctWorkers#enlist`temp`join;
  };

// Prepare tables for join by shuffling data to appropriate process
// args:
//  read: function to read original data meant for join
//  temp: temporary name for intermediate shuffling
//  dests: destination processes for shuffle
//  final: final name for shuffle results
.aq.par.master.prepareJoin:{[read;temp;alloc;dests;final]
  // add allocation info to temporary table
  .aq.par.worker.allocKeys[;alloc;temp] peach (count dests)#read;
  // shuffle data to right process
  shuffle:{[x;y;z] delete aq__proc from select from x where aq__proc=y}[temp;;]@/:dests;
  .aq.par.master.map[shuffle;dests;final upsert]
 };

// Add process allocation information for join
// args:
//  read: function to read data meant for join
//  allocs: table with process allocation for each key in join
//  nm: assign results to table with this name
.aq.par.worker.allocKeys:{[read;allocs;nm]
  nm set read[] lj allocs
  };

// Collect possible values along join columns in a table
// args:
//  jcols: columns for join
//  read: function to read data needed
.aq.par.worker.getJoinKeys:{[jcols;read]
  // much faster than distinct jcols#read[]
  key ?[read[];();jc!(jc:(),jcols);(last;`i)]
  };


// Perform join between two tables and store result
// args:
//  joinop: function to join, takes as arguments two tables
//  readl: function to read left-hand-side table of join
//  readr: function to read right-hand-side table of join
//  write: function to write results of join
.aq.par.worker.join:{[joinop;readl;readr;write]
  write joinop[readl[];readr[]]
  };

// Look up wrappers for various join-dependent operations such as actually joining,
// combining keys for lhs and rhs tables
// Allow generally wrapping operations as needed
// args
//  join: function for join (ej/lj/ij/3-arg function (jcols, lhs table, rhs table))
.aq.par.master.getJoinOps:{[join]
  joinDepOps:(
    [j:(ej;lj;ij)] // pre-defined joins
    jc:({ej[(),x;y;z]};{y lj x xkey z};{(x xkey y) ij x xkey z}); // wrapper to handle uniformly
    lhs:(inter;{first (x;y)};inter);
    rhs:(inter;inter;inter)
  );
  // join is one of our predefined options
  predefJoin:(join) in key joinDepOps;
  // if not predefined, be conservative and use union for key combinations
  $[predefJoin;joinDepOps[join];`jc`lhs`rhs!(join;union;union)]
  }


////// Distributed reference-table join //////
// It is often the case that one of the tables being used for a join is significantly smaller.
// This can be the case with "reference" tables, which hold some basic information.
// Rather than perform a distributed join, which shuffles information from both tables (at large cost)
// it can be preferable to replicate the reference table in each process and then join locally in
// each process.
// args:
//  join: operator to use for join (ej/lj/ij) or function that takes 3-args (cols, lhs table, rhs table)
//  jcols: columns along which we join
//  readl: function to read table on left of join
//  readr: function to read table on right of join (will be replicated in each process)
//  nm: to write the joined table as
.aq.par.master.referenceJoin:{[join;jcols;readl;readr;nm]
  workers:.aq.par.workerNames[];
  ctWorkers:count workers;
  joinOps:.aq.par.master.getJoinOps[join];
  jc:joinOps[`jc][jcols;;];
  localRef:raze {x[]} peach ctWorkers#readr;
  {[j;l;r;nm] nm set j[l[];r]}[jc;readl;localRef;] peach ctWorkers#nm;
 };


////// Distributed cross //////
// Perform cross of two tables stored across processes
// For each process, we query all other processes for the table in the right hand
// side of the join. We then read the left hand side table locally, cross and store.
// args:
//  readl: function to read table on left of cross
//  readr: function to read table on right of cross
//  nm: to write the crossed table as
.aq.par.master.cross:{[readl;readr;nm]
  workers:.aq.par.workerNames[];
  ctWorkers:count workers;
  // avoid dead locks by running synchronous
  .aq.par.runSynch[workers;(`.aq.par.worker.cross;readl;readr;`.aq.par.cross)];
  {x set .aq.par.cross} peach ctWorkers#nm;
  .aq.par.worker.cleanUp peach ctWorkers#`cross;
  };

.aq.par.worker.cross:{[readl;readr;nm]
  workers:.aq.par.workerNames[];
  // get all portions of data relevant from other processes
  temp:raze .aq.par.runSynch[workers;(readr;::)];
  // cross with lhs (local) and store
  nm set readl[] cross temp
  };



/////////// Utilities ///////////
// Create very simple sample data for experimenting
// args:
//  x: seed for random number generator
.aq.par.createSamplePartitioned:{[seed;path]
 system "S ",string seed;
 n:100000; // # of obs per partition
 pars:.z.D + til 10; // partitions
 parpaths:` sv/: path,/:(`$string pars),\:`t`;
 // we avoid symbols for simplicity
 mk:{[ct;off;path] path set ([]id:off+til ct;c1:ct?10;c2:ct?10;c3:ct?100.;c4:ct?100)};
 mk[n;;] ./: flip (n*til count parpaths;parpaths)
 };


