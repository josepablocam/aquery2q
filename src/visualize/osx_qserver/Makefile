MS=$(shell getconf LONG_BIT)  # 32/64

CC=gcc48
CFLAGS=-g -O -fpic -m$(MS) -shared -D KXVER=3

# use R to figure out R environment information
R_HOME=$(shell R RHOME)
R_SHARE_OPT=/usr/lib64/R/include/
REXE=$(R_HOME)/bin/R CMD

INCLUDES=-I. -I$(R_HOME)/include -I$(R_SHARE_OPT)
LIBS=-lpthread -L$(R_HOME)/lib -lR

SRC=base.c c.o
TGT=qserver.so

all:
	$(REXE) $(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(TGT)

clean:
	rm -rf $(TGT)
