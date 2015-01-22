all: aquery


aquery: lex.yy.c aquery.tab.c aquery.tab.h
	gcc aquery.tab.c lex.yy.c -ll -o aquery

aquery.tab.c aquery.tab.h: aquery.y
	bison -d aquery.y

lex.yy.c: aquery.l aquery.tab.h
	flex aquery.l

clean:
	rm -rf lex.yy.c aquery.tab.* aquery	
