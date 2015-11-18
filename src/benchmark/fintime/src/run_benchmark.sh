# arguments and validation
if [ $# -ne 3 ]
  then
    echo "usage: <abs-path-csv-output> <per_query_iters> <benchmark_iters>"
    exit 1
fi    

CSVOUT="$1"
PER_QUERY_ITERS="$2"
BENCHMARK_ITERS="$3"

# messages for user
GOOD_PROMPT="\033[32m Benchmark:"
BAD_PROMPT="\033[31m Benchmark:"
NC="\033[0m"

# fintime benchmark configuration file
FINTIME_BENCH_CONFIG=./fintime_benchmark.config

# path to run experiments
RUNPATH=./experiments/

function announce {
  echo -e "${GOOD_PROMPT} ${1}${NC}"
}

function warn {
  echo -e "${BAD_PROMPT} ${1}${NC}"
}

# if output file already exists, create fresh name and warn
if [ -f $CSVOUT ]
	then
		warn "${CSVOUT} already exists, appending to file (careful!)"
fi		

# if benchmark configuration file doesn't exist complain
if [ ! -f $FINTIME_BENCH_CONFIG ]
  then
    warn "Please `make` along with appropriate systems, see README"
    exit 1
fi


# Check which systems running for this benchmark
RUNNING_AQUERY=$(grep -Fxq "aquery" ${FINTIME_BENCH_CONFIG})$?
RUNNING_Q=$(grep -Fxq "q" ${FINTIME_BENCH_CONFIG})$?
RUNNING_PANDAS=$(grep -Fxq "pandas" ${FINTIME_BENCH_CONFIG})$?
RUNNING_MONETDB=$(grep -Fxq "monetdb" ${FINTIME_BENCH_CONFIG})$?
RUNNING_SYBASE=$(grep -Fxq "sybase" ${FINTIME_BENCH_CONFIG})$?

# Running experiments from RUNPATH
announce "Running experiments from ${RUNPATH}, output path should be absolute"
cd ${RUNPATH}
:

# check that aquery compiler is available
export A2Q=../../../../a2q
if [ ! -f $A2Q ]
	then 
		warn "No aquery compiler available, please call `make` before running"
		exit 1
fi

# monetdb set up
if [ ${RUNNING_MONETDB} == 0 ]
  then
    announce "Starting up monetdb"
    ./monetdb_server.sh -start
fi    

# sybase set up
if [ ${RUNNING_SYBASE} == 0 ]
  then
    announce "Starting up sybase"
    ./iq_server.sh -start
fi    

announce "Compiling aquery"
${A2Q} -c -s -a 1 -o compiled.q definitions_aquery.a > /dev/null

# No point in running benchmark if we are getting different results
# using q as a gold-standard for aquery
announce "Verifying q-Aquery equivalence"
q verify_equivalence.q > /dev/null

if [ $? -ne 0 ]
  then
    warn "Aquery and Q results are not strictly equivalent. Fix and rerun"
    exit 1
fi    



for ((iter=1;iter <= BENCHMARK_ITERS;iter++)); do
  announce "Iteration ${iter} of benchmark"
  announce "Creating random benchmark parameters"
  q make_parameters.q > /dev/null
  
  # Both aquery and q run by default.
  announce "running aquery"
  q run_aquery.q -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  
  if [ ${RUNNING_Q} == 0 ]
    then 
    announce "running q"
    q run_q.q -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  fi  
  
  if [ ${RUNNING_PANDAS} == 0 ]
    then
    announce "running pandas"
    python run_pandas.py -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  fi   
   
  if [ ${RUNNING_MONETDB} == 0 ]
    then
    announce "running monetdb + embedded python"
    # call with create to recreate the tables for random stock indices
    announce "\trebuilding monetdb random parameter tables"
    ./load_data_define_queries_monetdb.sh -create > /dev/null
    q run_monetdb.q -out $CSVOUT -iters $PER_QUERY_ITERS
  fi  
 
  if [ ${RUNNING_SYBASE} == 0 ]
    then
    announce "running sybase iq"
    announce "\trebuilding sybase random parameter tables"
    ./load_data_define_queries_iq.sh -create > /dev/null
    q run_iq.q -out $CSVOUT -iters $PER_QUERY_ITERS
  fi  

done

#stop monetdb server
if [ ${RUNNING_MONETDB} == 0 ]
  then
  ./monetdb_server.sh -stop
fi  

# stop sybase server
if [ ${RUNNING_SYBASE} == 0 ]
  then
   ./iq_server.sh -stop
fi    