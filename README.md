AQuery to Q (A2Q)
----------------

A2Q is a project that explores order-based optimizations for a simple query
language. Optimizations are mainly targeted as AST rewrites and, though simple,
yield empirical advantages at runtime.

It compiles [AQuery](http://dl.acm.org/citation.cfm?id=1315482) into [q](https://kx.com/),
providing users with two advantages:

* Allows users to query kdb+ databases with a syntax similar to SQL
* Heuristic, order-based optimizations, which provide performance advantages, while maintaining
readability in the source code
* Transparent compilation into q code (allowing experienced users to inspect the code executed)

The transformations on queries provide the same semantics at a fraction of the cost. These involve:
pushing selections below sorting, removing unnecessary sorts, maintaining order across local tables,
amongst others.


## Installation/Building
If you are interested in using AQuery, the steps below should provide you
with all the information needed to build on your system. Note that A2Q is meant
for \*nix. There are no plans on making this available for windows.

As AQuery currently compiles into q code, it is essential to have the kdb+
executable installed. You can visit [kx systems](https://kx.com/software-download.php)
to download the appropriate version for your machine. For licensing reasons, we
cannot include this for you. However, the process is simple.

Once you install q, make sure you add its installation location to your path.

```
export PATH=$PATH:/my/q/installation/location/
```

Calling `which q` should echo back the appropriate location, if
added succesfully.

Most uses of q in examples/demos will assume you have this appropriately setup.

Compilation of the AQuery translator is straightforward and
relies on just a few standard tools. Namely, compilation works
seamlessly using

* GCC 4.8.4
* Flex 2.5.35
* Bison 2.3

Other versions may work equally well, but they have not been
tested.

The first step is to clone this git repository

```
git clone git@github.com:josepablocam/aquery2q.git
```

Assuming you have the mentioned requirements, you can build by

```
cd aquery2q/src
make
```
Similarly to the q installation, many demos/examples assume
the AQuery executable is in your path, so make sure to add it

```
export PATH=$PATH:path/to/aquery2q/src/
```

## Basic Usage
```
josecambronero src$ a2q -help
Usage: ./a2q [-p|-c][-o output_q_file][-a <#>] aquery_file
-p  print dot file AST to stdout
-a  optimization level [0-1]
-s  silence warnings
-c  generate code
-o  code output file
-c/-p are mutually exclusive
```

`-p` prints a simple visualization of the AST and is occasionally helpful, but
is mainly used for development purposes. The most common command will likely be
translating AQuery to q code, with optimizations. This can be achieved with

```
a2q -a 1 -s -c -o my_output_file.q my_input_file.a
# or equally
a2q -a 1 -s -c my_input_file.a > my_output_file.q
```

(Note that the file endings are not significant).

Currently optimizations can only be turned on/off (1/0), work is currently going
into modularity here.

## Demo
The project comes with a simple demo, found in `src/demo`.
The demo includes various examples in `src/demo/examples` and
also provides a simple "interpreter" to run AQuery queries
interactively.

In order to build the demo:
```
cd src/demo
make
```
This will:
* build the AQuery translator, if not done already
* create sample data (randomly generated)
* compile various sample queries in the examples folder

Building requires that you have the `q` executable in your path,
and actually running additionally requires the same for the
`a2q` executable.

Running the examples `src/demo/examples/fintime_aquery.a` (and their
  respective translation), requires one additional step:

```
make fintime
```
which generates extra data.

The "interpreter" is a simple way for users to interact with AQuery. Behind the
scenes, it is simply accumulating user input into a file, translating as usual,
feeding the translation to a background q process for execution, and returning
results to the user.

In addition to having the AQuery translator, and the q executable, using the
interpreter requires Python 2.7.\*.

Using the interpreter is as simple as launching the bash script
`a2qinterpret.sh` found
in the demo folder with a free port number as an argument. The port number is
used to open the background q process.

Given that filesystem paths used in the example queries in `src/demo/examples`
are relative, if you would like to run these in the interpreter, it is important
to `cd` into the appropriate folder.

```
cd examples; ../a2qinterpret.sh 7089
```

Entering an empty line executes the command written.

## Basic Grammar
The grammar for AQuery is simple and should be familiar to
most people familiar with SQL. A good way to get a thorough overview
of the grammar is to explore the parser rules in `src/parser/aquery.y`.
These are written for Bison, and should be fairly readable. We provide a simple
summary here of the most frequently used constructs: queries, data
creation, loading/saving data, and user-defined functions.
We use `ID` to stand for identifier, and `epsilon` to stand
for the standard notation.

```
program : [full-query | create | insert | load | dump | udf | verbatim-q]*

// aquery files allow standard q code within special markers
verbatim-q: <q> q code </q>

// Queries
full-query : [local_queries] query

local_queries: WITH local_query+

local_query: ID ['('columns')'] AS '(' query ')'

query : SELECT projections FROM source order-clause where-clause groupby-clause

projections: [val as ID | val] (, [val as ID | val])*

source : ID [ID | AS ID] |
  ID INNER JOIN source USING (columns) |
  ID FULL OUTER JOIN source USING (columns) |
  FLATTEN '(' ID ')'

order-clause: ASSUMING ([ASC|DESC] ID)+

where-clause: WHERE search-conditions;

groupby-clause: GROUP BY val [as ID] (, val [as ID])* [HAVING search-conditions]

// where search condition is a boolean-yielding expression
search-conditions: search-condition (AND search-condition)*;

// Creating data
create: CREATE TABLE ID [AS query | '(' schema ')']
schema: ID type (, ID type)*

insert: INSERT INTO ID [query | VALUES '(' vals ')']
vals: val (, val)*;

// Loading/Saving data
load: LOAD DATA INFILE str INTO TABLE ID FIELDS TERMINATED BY str

save: query INTO OUTFILE str FIELDS TERMINATED BY str

// User defined functions
udf: FUNCTION ID '(' arg-list ')' '{' fun-body '}'
arg_list: ID (, ID)*
fun_body: val | ID := val;

val: val binop val | fun'('val (,val)*')' | -val | ID | int |
  float | datetime | str | date | hex
fun: ID | abs| avg[s] | count | deltas | distinct | drop
  | fill | first | last | max[s] | min[s] | mod | next
  | prev | sum[s] | stddev | ratios | vars | moving

binop: +|-|=|*|!=|<|>|>=|<=|&&|||
```


### Basic Examples
Following the commonly user grammar above, we provide some basic examples.
More examples can be found in `src/demo/examples`
#### Queries
```
WITH t1(c1, c2, c3) AS (
  SELECT c10, c20, c30 FROM t ASSUMING ASC c4
  WHERE f(c3) > 10 AND c5 != c6
  )
SELECT c1, sum(c2) FROM t1 GROUP BY c1
```
```
WITH nested_t1(c1, c2, c3) AS (
  SELECT c10, c20, c30 FROM t ASSUMING ASC c4
  WHERE f(c3) > 10 AND c5 != c6
  GROUP BY c10
  )
// must flatten out nested arrable using built-in FLATTEN
SELECT c1, sum(c2) FROM FLATTEN(nested_t1) GROUP BY c1
```

#### Creating Data
You can create data directly in AQuery as done below, but often
the use of verbatim q `<q> q commands here </q>` allows for simple
data creation for experiments.

```
CREATE TABLE my_table (c1 INT, c2 INT, c3 STRING)
INSERT INTO my_table VALUES(10, 20, "example")
INSERT INTO my_table SELECT * FROM my_table
```

#### Loading and Saving data
```
SELECT * FROM my_table
INTO OUTFILE "my_table.csv"
FIELDS TERMINATED BY ","

// note that we have my_table schema already defined
// required to parse fields as appropriate type
LOAD DATA INFILE "my_table.csv"
INTO TABLE my_table
FIELDS TERMINATED BY ","
```

### User-Defined Functions
Users can define their own aggregates using a simple syntax. In the example
below, we define our own covariance aggregate. You are free to use other
aggregates in the definition.

```
FUNCTION myCov(x, y) {
  center_x := x - avg(x);
  center_y := y - avg(y);
  num := sum(center_x * center_y);
  denom := sqrt(sum(center_x * center_x)) * sqrt(sum(center_y * center_y));
  num / denom
  }
```

If you have any doubts/issues/feedback, please do not hesitate to contact
[José Cambronero](mailto:jpc485@nyu.edu)
