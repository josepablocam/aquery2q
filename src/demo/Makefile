.PHONY: clean

# set up parameter for size of data (# of tickers, for 4000 days of EOD data)
ifndef BENCHMARKSIZE
BENCHMARKSIZE=2000
endif

FINTIME_CODE_PATH=$(shell echo "`pwd`/fintime")
DATA_PATH=$(shell echo "`pwd`/data")
DEMO_PATH=$(shell echo "`pwd`/examples")
A2Q=$(shell echo "`cd ..; pwd`/a2q")

# the whole shebang
all: a2q qdata demo
	
a2q:
	cd ../; make

clean:
	rm -rf *.pyc;\
	cd ${DATA_PATH}; rm -rf tables parameters hist-*;\
	cd ${FINTIME_CODE_PATH}; make clean;\
	cd ${DEMO_PATH}; rm -rf compiled.q
	
# make fintime code generation
# and fintime data
fintime: ${FINTIME_CODE_PATH}/histgen.C ${FINTIME_CODE_PATH}/histgen.o
	cd ${FINTIME_CODE_PATH}; make clean; make;\
	./histgen ${BENCHMARKSIZE}; mkdir -p ${DATA_PATH}; mv -f ./hist-* ${DATA_PATH}/
	
# create q-serialized version of data for demo
qdata:
	q make_data.q;\
	q data_to_q.q -csv ${DATA_PATH} -save ${DATA_PATH};
	
# compile demo code
demo: ${DEMO_PATH}/fintime_aquery.a ${DEMO_PATH}/eod_aquery.a ${DEMO_PATH}/load_data.q
	cd ${DEMO_PATH};\
	${A2Q} -a 1 -s -c -o compiled_fintime.q fintime_aquery.a;\
	${A2Q} -a 1 -s -c -o compiled_eod.q eod_aquery.a
	
		
		
		
	