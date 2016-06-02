.PHONY: clean

# set up parameter for size of data (# of tickers, for 4000 days of EOD data)
ifndef BENCHMARKSIZE
BENCHMARKSIZE=5000
endif

FINTIME_CODE_PATH=$(shell echo "`pwd`/fintime")
DATA_PATH=$(shell echo "`pwd`/data")

# the whole shebang
all: fintime qdata

clean:
	rm -rf sampledb;\
	cd ${DATA_PATH}; rm -rf hist-*;\
	cd ${FINTIME_CODE_PATH}; make clean
	
# make fintime code generation
# and fintime data
fintime: ${FINTIME_CODE_PATH}/histgen.C ${FINTIME_CODE_PATH}/histgen.o
	cd ${FINTIME_CODE_PATH}; make clean; make;\
	./histgen ${BENCHMARKSIZE}; mkdir -p ${DATA_PATH}; mv -f ./hist-* ${DATA_PATH}/
	
# create partitioned database
qdata:
	nohup q -p 7089 < /dev/null &\
	nohup q -p 7090 < /dev/null &\
	q make_parallel_data.q -s -2 -workers localhost:7089,localhost:7090;\
	killall q

		
		
		
	