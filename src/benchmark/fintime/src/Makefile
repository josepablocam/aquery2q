.PHONY: clean

# set up parameter
ifndef BENCHMARKSIZE
BENCHMARKSIZE=2000
endif

EXPPATH=./experiments
DATAGENPATH=./findata

all: a2q fintime data

clean:
	cd ${EXPATH}; rm -rf compiled.q *.pyc parameters/ tables/
	
# make compiler for aquery and set alias
a2q:
	cd ../../../; make; alias a2q="./a2q"

# make benchmark generation code
fintime:
	cd ${DATAGENPATH}; make

# # create data neede for benchmark
data: fintime
	cd ${DATAGENPATH}; ./histgen ${BENCHMARKSIZE}; mv ./hist-* ../../data/

        
