// Code generated by a2q version 1.0 please report any bugs to jpc485@nyu.edu
// ***** Aquery utilities ***** ///
//table related
.aq.gencd:{[t;sn;m] ((`$(sn,"."),/:sc),c)!(2*count c)#`$($[m;sn,"__";""]),/:sc:string c:cols t}
.aq.rcols:{[t;p] (`$(p,"__"),/:string cols t) xcol t};
.aq.ju:{[cs;j] $[2<>count m:cs where cs like "*__",s:string j;'"ambig-join:",s;`rename`remap!(m!2#n;((.aq.cd?m),j)!(1+count m)#n:`$"_"sv string m)]}
.aq.scbix:{[m] iasc `s`p`g`u?exec c!a from m}; //sort column names by attribute
// local reordering
.aq.swix0:{[c;w] 
 // singleton or empty, no point in reordering anything
 $[1>=count w;
  w;
  w iasc min each c?fw@'where each type[`]=(type each) each fw:(raze/) each w
  ]
 };
.aq.swix:{[v;ix;w]
 m:meta v;
 // no point in reording if we don't have attributes or only have 1 clause
 $[(1=count w)|exec all null a from m;
   w;
   // check if we need to worry about aggregates
   0=count ix;
   .aq.swix0[.aq.scbix m;w];
   // otherwise reorder locally between aggregates according to safe principle
   raze .aq.swix0[.aq.scbix m; ] each $[0<>first lix:distinct raze 0 1+/:(),ix;0,lix;lix] cut w
  ]
 };
.aq.negsublist:{[x;y] neg[x] sublist y};
.aq.chkattr:{[x;t] any (.aq.cd where any each flip .aq.cd like/: "*",/:string (),x) in exec c from meta t where not null a};
.aq.acctgrps:{[p;g] @[p;key[p] ix;:;key[g] raze where each c ix:where any each c:value[p]~/:\:value g]};
 //full outer join using (definition compliant with traditional sql semantics
k).aq.ejix:{(=x#z:0!z)x#y:0!y}; // from ej
.aq.foju:{
  nix:.aq.ejix[x:(),x;y:0!y;z:0!z];
  iz:raze nix; //indices in z for equijoin
  iy:where count each nix; // indices in y for equijoin
  ejr:y[iy],'(x _ z) iz; // perform equi join
  my:select from y where not i in iy; // records in y not in equi join
  mz:select from z where not i in iz; // records z not in equi join
  ejr upsert/(my;mz) // add missing records
  };
.aq.nj:{[t1;t2;p] raze {?[x,'count[x]#enlist y;z;0b;()]}[t1; ;p] each t2};
.aq.hj:{[t1;t2;a1;a2;p]
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
  $[hasneq;raze .aq.nj'[inner;outer;(count matches)#enlist p];raze {x cross y}'[inner;outer]]
 };
// check if tables are keyed on join keys
// if so use ij instead of ej, much more peformant, same semantics in such a case
.aq.iskey:{(count[k]>0)&min (k:keys x) in y};
.aq.ej:{[k;t1;t2] $[(kt2:.aq.iskey[t1;k])|kt1:.aq.iskey[t2;k]; $[kt1;t1 ij t2;t2 ij t1]; ej[k;t1;t2]]};


// Start of code
// create table statement
 `prices set ([]Open:"f"$(); High:"f"$(); Low:"f"$(); Close:"f"$(); Volume:"f"$(); EndOfDayPrice:"f"$(); ID:"s"$(); Date:"d"$())
// load data statement
{
 `prices set prices upsert (upper exec t from meta prices; enlist ",") 0:hsym `$"./data/sp500_eod_complete_data.csv"
 }[]
// verbatim q code
vars:{mavg[x;y*y]-m*m:mavg[x;y:"f"$y]}
// verbatim q code
system "cd ./R/"