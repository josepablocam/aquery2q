.PHONY: clean

# set up parameter
ifndef BENCHMARKSIZE
BENCHMARKSIZE=2000
endif

EXPPATH=./experiments
DATAGENPATH=./findata

all: a2q fintime data tables

clean:
	cd ${EXPPATH}; rm -rf compiled.q *.pyc parameters/ tables/
	
# make compiler for aquery and set alias
a2q:
	cd ../../../; make

# make benchmark generation code
fintime:
	cd ${DATAGENPATH}; make

# create raw data needed for benchmark
data: fintime
	cd ${DATAGENPATH}; ./histgen ${BENCHMARKSIZE}; mkdir -p ../../data/; mv ./hist-* ../../data/

# create tables for each system
tables: data
	cd ${EXPPATH};\
	q make_tables.q > /dev/null;\
	q make_parameters.q > /dev/null;\
	python make_tables.py > /dev/null;\
	./monetdb_server.sh -init;\
	sleep 7s;\
	./monetdb_server.sh -start;\
	sleep 5s; \
	./make_tables_monetdb.sh -create;\
	./load_data_define_queries_monetdb.sh -create;\
	./monetdb_server.sh -stop
