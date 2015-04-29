.PHONY: clean
all: aquery

aquery: lex.yy.c aquery.tab.c aquery.tab.h symtable.c symtable.h ast.c ast.h aquery_types.c aquery_types.h ast_print.c ast_print.h optimizer.c optimizer.h codegen.c codegen.h
	gcc aquery.tab.c lex.yy.c symtable.c ast.c aquery_types.c ast_print.c optimizer.c codegen.c -o aquery

aquery.tab.c aquery.tab.h: aquery.y
	bison -d aquery.y

lex.yy.c: aquery.l aquery.tab.h
	flex aquery.l

aquery_zip: aquery.l aquery.y Makefile ../../doc/grammar.pdf ../../doc/shiftreduce.pdf examples.a
	zip aquery_zip aquery.l aquery.y Makefile ../../doc/grammar.pdf ../../doc/shiftreduce.pdf examples.a

clean:
	rm -rf aquery lex.yy.c aquery.tab.* aquery.output aquery_zip.zip
