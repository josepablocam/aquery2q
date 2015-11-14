.PHONY: clean

EXPPATH=./experiments

all: a2q tables

clean:
	cd ${EXPPATH}; rm -rf compiled.q tables/
	
# make compiler for aquery and set alias
a2q:
	cd ../../../; make
	
# create tables for each system
tables:
	cd ${EXPPATH};\
	mkdir -p tables/;\
	./monetdb_server.sh -init
