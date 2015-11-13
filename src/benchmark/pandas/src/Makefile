.PHONY: clean

EXPPATH=./experiments

all: data a2q

clean:
	cd ${EXPPATH}; rm -rf compiled.q *.pyc tables/
	
# make compiler for aquery and set alias
a2q:
	cd ../../../; make
	
# create folder for tables for benchmarks
data:
	cd ${EXPPATH}; mkdir -p tables
	
