.PHONY: clean

# set up parameter
ifndef BENCHMARKSIZE
BENCHMARKSIZE=2000
endif

EXPPATH=./experiments
DATAGENPATH=./findata

all: a2q fintime data aquery pandas monetdb sybase

clean:
	rm -rf fintime_benchmark.config; \
	cd ${EXPPATH}; rm -rf compiled.q *.pyc parameters/ tables/
	
# make compiler for aquery and set alias
a2q:
	cd ../../../; make

# make benchmark generation code
fintime: ${DATAGENPATH}/histgen.C
	cd ${DATAGENPATH}; make

# create raw data needed for benchmark
data: fintime
	cd ${DATAGENPATH}; ./histgen ${BENCHMARKSIZE}; mkdir -p ../../data/; mv ./hist-* ../../data/

# set up a simple config file with the benchmark names we're running
benchconfig:
	touch fintime_benchmark.config

# start up requirements for each of the benchmarked systems	
aquery: data benchconfig
	echo "Building aquery benchmark data"; \
	cd ${EXPPATH};\
	q make_tables.q > /dev/null;\
	q make_parameters.q > /dev/null
	echo "aquery" >> fintime_benchmark.config
	
pandas: aquery
	echo "Building pandas benchmark data"; \
	cd ${EXPPATH};\
	python make_tables.py > /dev/null
	echo "pandas" >> fintime_benchmark.config
	
monetdb: aquery
	echo "Building monetdb server and benchmark data";
	cd ${EXPPATH};\
	./monetdb_server.sh -init;\
	sleep 7s;\
	./monetdb_server.sh -start;\
	sleep 5s; \
	./make_tables_monetdb.sh -create;\
	./monetdb_server.sh -stop
	echo "monetdb" >> fintime_benchmark.config
	
sybase: aquery
	echo "Building sybase server and benchmark data"; \
	cd ${EXPPATH};\
	./iq_server.sh -create # creates server and tables!
	echo "sybase" >> fintime_benchmark.config
		
		
		
	