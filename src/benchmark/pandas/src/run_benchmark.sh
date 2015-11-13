# arguments and validation
if [ $# -ne 4 ]
  then
    echo "usage: <abs-path-csv-output> <per_query_iters> <benchmark_iters> <benchmark-size>"
    exit 1
fi    

CSVOUT="$1"
PER_QUERY_ITERS="$2"
BENCHMARK_ITERS="$3"
BENCHMARK_SIZE="$4"

# messages for user
GOOD_PROMPT="\033[32m Benchmark:"
BAD_PROMPT="\033[31m Benchmark:"
NC="\033[0m"

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
		warn "${CSVOUT} already exists, appending to file, careful!"
fi		

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

announce "Compiling aquery"
${A2Q} -c -s -a 1 -o compiled.q definitions_aquery.a > /dev/null

for ((iter=1;iter <= BENCHMARK_ITERS;iter++)); do
  announce "Iteration ${iter} of benchmark"
  announce "Creating random python data for benchmark"
  python make_data.py $BENCHMARK_SIZE > /dev/null
  announce "Copying random python data to aquery/q format"
  q make_data.q > /dev/null
  announce "running aquery"
  q run_aquery.q -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  announce "running pandas"
  python run_pandas.py -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
done
