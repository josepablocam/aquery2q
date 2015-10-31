# arguments and validation
if [ $# -ne 3 ]
  then
    echo "usage: <csv-output-path> <per_query_iters> <benchmark_iters>"
    exit 1
fi    

CSVOUT="$1"
PER_QUERY_ITERS="$2"
BENCHMARK_ITERS="$3"

# messages for user
GOOD_PROMPT="\033[32m Benchmark:"
BAD_PROMPT="\033[31m Benchmark:"
NC="\033[0m"

function announce {
  echo -e "${GOOD_PROMPT} ${1}${NC}"
}

function warn {
  echo -e "${BAD_PROMPT} ${1}${NC}"
}

# build data
announce "Building tables"
q make_tables.q > /dev/null
announce "Compiling aquery"
a2q -c -s -a 1 -o compiled.q definitions_aquery.a > /dev/null

# No point in running benchmark if we are getting different results
# using q as a gold-standard for aquery
announce "Verifying q-Aquery equivalence"
q verify_equivalence.q > /dev/null
if [ $? -ne 0 ]
  then
    warn "Aquery and Q results are not strictly equivalent. Fix and rerun"
    exit 1
fi    

# run benchmark
for ((iter=1;iter <= BENCHMARK_ITERS;iter++)); do
  announce "Iteration ${iter} of benchmark"
  announce "Creating random benchmark parameters"
  q make_parameters.q > /dev/null
  announce "running aquery"
  q run_aquery.q -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  announce "running q"
  q run_q.q -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  announce "running pandas"
  python run_pandas.py -out $CSVOUT -iters $PER_QUERY_ITERS > /dev/null
  # TODO: monetdb
done

