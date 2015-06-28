


//	Section 5: Tests from Alberto Lerner's thesis and presentation on aquery. 
//	Please see the .pdf file accompanying this implementation for references to both
//	We assume the existence of tables: Ticks, Portfolio, Packets, Sales, TradedStocks, HistoricQuotes as per references in both documents

\S 10
//Creating necessary tables
n:`int$1e6;
Ticks:([]ID:n?`S`ACME`OTHER`CORP; date:n?.z.D; timestamp:n?.z.P; price:n?100.; ixCol:til n);
TicksWithAttr:update ID:`g#asc ID from Ticks;
Portfolio:([]ID:`S`ACME`OTHER`CORP; position:1e4+4?1e6)
Packets:select from ([]src:n?100; dest:n?100; length:n?256; timestamp:.z.P+10*n?`int$1e9) where src<>dest
Sales:update sales:count[i]?1e6 from ([]month:`month${neg[x]?x}1+`long$`month$.z.D)
TradedStocks:([]ID:n?`S`ACME`OTHER`CORP; date:n?.z.D);
HistoricQuotes:update ClosePrice:count[i]?100. from `ID`date xcol distinct TradedStocks;
base:([] ID:(count .Q.a)?`S`ACME`OTHER`CORP; name:`$'.Q.a)
/
//Test 5.1: pg 24
q0:{select price from `timestamp xasc Ticks where ID=`ACME}


//Test 5.2: pg 25, example 3.1
//naively writtenm
q1:{select max price-mins price from `timestamp xasc Ticks where ID=`ACME, date=2003.05.11}

//Test 5.3: pg 29, example 3.3
q2:{select avg length, ct:count timestamp by src, dest, sums (120*1e9)<deltas timestamp from `src xasc `dest xdesc `timestamp xasc Packets}


//Test 5.4: pg 30, example 3.4
q3:{
    as:select date, timestamp, a21:21 mavg price, a5:5 mavg price by ID from `ID`timestamp xasc Ticks;
    select ID, date from `ID`timestamp xasc ungroup as where (a21>a5)&(prev[a21]<=prev a5)&(prev ID)=ID
    }


//Test 5.5: pg 32, example 3.5
//recreating innerjoin semantics from traditional sql
q4:{select neg[10] sublist price by ID from `timestamp xasc ej[`ID;Ticks;Portfolio]}


//Test 5.6: pg 33, example 3.6
q5:{
     OneDay:select ID, price, timestamp from `timestamp xasc Ticks where date=2003.05.11;
     select count i by ID from `timestamp xasc OneDay where i < 1000
 }

//Test 5.7: moving average over arrables
q6:{select month, 3 mavg sales from `month xasc Sales}


//Test 5.8:
//recreating innerjoin semantics from traditional sql
q7:{select 10 mavg ClosePrice by ID from `date xasc ej[`ID`date;`ID`date xcol TradedStocks;`ID xcol HistoricQuotes]}

q8:{select last price from `name`timestamp xasc ej[`ID;base;Ticks] where name=`x}

// testing push filters
q9:{select from ej[`ID;TicksWithAttr;Portfolio] where ixCol < 1000}

//Performance comparison
nruns:10;
time:{.Q.gc[]; (system ssr/["ts do[%n;%f[]]";("%n";"%f");(string x;y)])%x}

runtest:{
 1 "------------------------------------\n";
 show ssr/["--> q results for (%n avg):%t";("%n";"%t");(string nruns; x)];
 show qr:time[nruns;x];
 show ssr/["--> aquery results for (%n avg):%t";("%n";"%t");(string nruns; x)];
 show ar:time[nruns;".aq.",x];
 show "--> % Difference AQ wrt to Q:";
 show -1+ar%qr;
 }

tests:`q0`q1`q2`q3`q4`q5`q6`q7`q8`q9

verify:{
	show "--->correctness results for ",x;
	qr:0!eval(`$x;::);
	//ad-hoc changes to handle remaining issues in aquery (like not automatically adding
	//group cols)
	qr:$[x like "q2"; delete timestamp from qr; qr];
	aq:eval (`$".aq.",x;::);
	show qr~cols[qr] xcol aq;
 }

\l generated.q
show "****Running unoptimized aquery compilation"
verify each string tests
runtest each string tests

\l generated_optimized.q
show "****Running optimized aquery compilation"
verify each string tests
runtest each string tests
exit 0



