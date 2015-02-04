all: aquery

aquery: lex.yy.c aquery.tab.c aquery.tab.h
	gcc aquery.tab.c lex.yy.c -o aquery

aquery.tab.c aquery.tab.h: aquery.y
	bison -d aquery.y

lex.yy.c: aquery.l aquery.tab.h
	flex aquery.l

aquery_zip: aquery.l aquery.y Makefile grammar.pdf examples.a
	zip aquery_zip aquery.l aquery.y Makefile grammar.pdf examples.a

clean:
	rm -rf lex.yy.c aquery.tab.* aquery.output aquery_zip.zip
