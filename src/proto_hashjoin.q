// Author: Jose Cambronero (jpc485@nyu.edu)
// A prototype of hash join implementation for Aquery to q compiler

// nested loop join
// args: table 1, table 2, join predicate
// algo:
//    for each tuple i in t2:
//          horizontally concatenate i to each tuple in t1 (akin to second loop but much faster)
//          and execute selection with join predicate
nj:{[t1;t2;p] raze {?[x,'count[x]#enlist y;z;0b;()]}[t1; ;p] each t2}

// simple hash join
// args: table 1, table 2, equality attributes table 1, equality attributes table 2, all join
// predicates
// we don't explicitly hash keys but rather use q's lookup tables, which are efficiently hashed
// behind the covers on their keys
// algo: 
//   create build table with smaller table, where keys are equality attributes, 
//   values are indices for tuples
//      create similar table for larger table, where keys are equality attributes
//      intersect keys between the 2 tables to find matches
//      if there are any non-equality predicates, perform nested loop joins with each potential
//      match bucket, otherwise simply crosses within each bucket (since all tuples in bucket are 
//      guaranteed to satisfy the join predicate)
hj:{[t1;t2;a1;a2;p]
  // argument preparation
  a1,:();a2,:();p:$[0<>type first p;enlist p;p];hasneq:any not (=)~/:first each p;
  targs:$[count[t2]>count t1;(t1;t2;a1;a2);(t2;t1;a2;a1)];
  s:targs 0;b:targs 1;sa:targs 2;ba:targs 3;
  // here the "hash function" is identity of join attributes, extract index
  bti:?[s;();sa!sa;`i];
  // hash larger and drop no matches
  bw:?[b;();ba!ba;`i];
  matches:((sa xcol key bw) inter key bti)#bti;
  // perform nj for all matches using complete join predicate
  // if has any predicate that is not equality based otherwise just cross (guaranteed matches)
  inner:b bw ba xcol key matches;
  outer:s value matches;
  $[hasneq;raze nj'[inner;outer;(count matches)#enlist p];raze {x cross y}'[inner;outer]]
 }    
  
/
Simple example usage
q)\l proto_hashjoin.q
q)\S 10
q)n:`int$1e6
q)t:([]c1:n?100;c2:n?100;c3:n?1000)
q)ts:(`$"ts_",/:string cols t) xcol 1000#t
q)\ts r1:nj[t;ts;enlist (=;`c1;`ts_c1)]
111 33425936
q)\ts r2:hj[t;ts;`c1;`ts_c1;(=;`c1;`ts_c1)]
31 31203712
q)({cols[x] xasc x}r1)~{cols[x] xasc x}r2
1b

// Comparing performance of ej with hj, with and without indexing on join keys
q)//renamed columns
q)tsr:`c1 xcol ts
q)tix:@[`c1 xasc t;`c1;`p#]
q)\ts:100 ej[`c1;tix;tsr]
36608 809514144
q)\ts:100 hj[tix;ts;`c1;`ts_c1;(=;`c1;`ts_c1)]
30926 1568766912

// Now assume we need to add in inequality constraints
q)\ts:10 select from ej[`c1;tix;tsr] where c2 < ts_c2
5745 1073742480
q)\ts:10 hj[tix;ts;`c1;`ts_c1;((=;`c1;`ts_c1);(<;`c2;`ts_c2))]
4951 803568368

gold:select from ej[`c1;tix;tsr] where c2 < ts_c2
test:hj[tix;ts;`c1;`ts_c1;((=;`c1;`ts_c1);(<;`c2;`ts_c2))]
test:`c1`c2`c3`ts_c2`ts_c3 xasc delete ts_c1 from test
gold:`c1`c2`c3`ts_c2`ts_c3 xasc gold
gold~test







 work flow for select ... t1, t2 where ...
1 - if join predicate and tables reveal this is foreign key join, then simply
  add columns to column dictionary so that we can access using q's pointers. No
  physical join takes place.
2 - if join predicate only shows equality conditions, then rename columns to match
    and perform a equijoin with "USING" (which takes advantage of q's fast joins). This
    is much more efficient than my hash join.
3 - use hash join implementation

My implementation of hj is a "worst-case scenario" kind of tool.

Note that check for equality conditions in (2 and inside hash join) is done "superficially", 
i.e. if f:{x=y} and join predicate is (f;`c1;`c2), then it will not satisfy this condition

For now, we will not allow UDFs in a join predicate

(
consider how would we handle something like 
select ... from t1, t2 where sums(t1.c1) = t2.c1
)
    
However note that in most cases the user can achieve the same effect by using an
UPDATE and a JOIN in sequence.

(
for the prior example:
  UPDATE t1 SET joincol = sums(c1)
  SELECT * FROM t1, t2 WHERE t1.joincol = t2.c1
)
 
 
    


    