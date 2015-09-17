// Author: Jose Cambronero (jpc485@nyu.edu)
// A prototype of hash join implementation for Aquery to q compiler

// nested loop join
// args: table 1, table 2, join predicate
// algo:
//    for each tuple i in t2:
//          horizontally concatenate i to t1 (akin to second loop but much faster)
//          and execute selection with join predicate
nj:{[t1;t2;p] raze {?[x,'count[x]#enlist y;z;0b;()]}[t1;;p] each t2}

// simple hash join
// args: table 1, table 2, equality attributes table 1, equality attributes table 2, all join
// predicates
// we don't explicitly hash keys but rather use q's lookup tables, which are efficiently hashed
// behind the covers on their keys
// algo: 
//   create build table with smaller table, where keys are equality attributes
//      create similar table for larger table, where keys are equality attributes
//      intersect keys between the 2 tables to find matches
//      if there are any non-equality predicates, perform nested loop joins with each potential
//      match bucket, otherwise simply crosses within each bucket (since all tuples in bucket are 
//      guaranteed to satisfy the join predicate)
hj:{[t1;t2;a1;a2;p]
  // argument preparation
  a1,:();
  a2,:();
  p:$[0<>type first p;enlist p;p];
  hasneq:any not(=)~/:first each p;
  targs:$[count[t2]>count t1;(t1;t2;a1;a2);(t2;t1;a2;a1)];
  s:targs 0;
  b:targs 1;
  sa:targs 2;
  ba:targs 3;
  // here the "hash function" is identity of join attributes, extract index
  bti:?[s;();sa!sa;`i];
  // hash larger and drop no matches
  bw:?[b;();ba!ba;`i];
  matches:((sa xcol key bw) inter key bti)#bti;
  // perform nj for all matches using complete join predicate
  // if has any predicate that is not equality based otherwise just cross
  inner:b bw ba xcol key matches;
  outer:s value matches;
  $[hasneq;
    raze nj'[inner;outer;(count matches)#enlist p];
    raze {x cross y}'[inner;outer]
    ]
 }    
  
/
Simple example usage

q)n:`int$1e6
q)t:([]c1:n?100;c2:n?100;c3:n?1000)
q)ts:(`$"ts_",/:string cols t) xcol 10#t
q)\l proto_hashjoin.q
q)\ts r1:nj[t;ts;enlist (=;`c1;`ts_c1)]
111 33425936
q)\ts r2:hj[t;ts;`c1;`ts_c1;(=;`c1;`ts_c1)]
31 31203712
q)(`c1 xasc r1)~`c1 xasc r2
1b


 work flow for select ... t1, t2 where ...
1 - if join predicate and tables reveal this is foreign key join, then simply
  add columns to column dictionary so that we can access using q's pointers. No
  physical join takes place.
2 - if join predicate only shows equality conditions, then rename columns to match
    and perform a equijoin with "USING" (which takes advantage of q's fast joins). This
    is much more efficient than my hash join.
3 - use hash join implementation

My implementation of hj is a "worst-case scenario" kind of tool.

Note that check for equality conditions in (2) is done "superficially", i.e. if 
f:{x=y}
and join predicate is (f;`c1;`c2), then it will not satisfy this condition
In general we will not currently allow functions as a join predicate in this case
(consider how would we handle something like 
select ... from t1, t2 where sums(t1.c1) = t2.c1
)
    
However note that in most cases the user can achieve the same effect by using an
UPDATE and a JOIN in sequence.

(for the prior example:
  UPDATE t1 SET joincol = sums(c1)
  SELECT * FROM t1, t2 WHERE t1.joincol = t2.c1
 )
 
 
    


    