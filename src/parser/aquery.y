%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYDEBUG 1
#define ERRORCOLOR  "\x1B[32m"

extern int yyleng;
extern FILE *yyin;
extern int yylex();
extern int yyparse();

//for debugging purposes, defined in flex
extern int line_num; 
extern int col_num;

	
void yyerror(const char *);



%}

 /* defining tokens for aquery */
 /* sql keywords */
 
%token WITH TABLE_AS SELECT FROM ASSUMING ORDER WHERE AND GROUP BY FLATTEN COL_AS ROWID ODD EVEN EVERY
 
 /* built-ins */
%token ABS AVG AVGS COUNT DELTAS DISTINCT DROP FIRST LAST MAX MAXS MIN MINS MOD NEXT PREV
%token PRD PRDS REV SUM SUMS STDDEV

 /* other operators */
%token TIMES_OP DIV_OP PLUS_OP MINUS_OP LE_OP GE_OP L_OP G_OP EQ_OP NEQ_OP AND_OP OR_OP
 
 /* constants and identifiers */
%token FLOAT INTEGER DATE STRING ID
 
%start program

%%

/* top level */

program: global_queries

global_queries: global_query global_queries
	| /*epsilon*/
	;

global_query: local_queries query ';';


 /* local queries, only accesible within [WITH..., global query]; */
local_queries: WITH local_query local_queries_tail
	|	/* epsilon */
	;
	
local_queries_tail: ',' local_query local_queries_tail
	| /* epsilon */
	;

local_query: ID col_aliases TABLE_AS '(' query ')' ;

col_aliases: '(' comma_identifier_list ')' 
	| /* epsilon */
	;

comma_identifier_list: ID comma_identifier_list_tail;

comma_identifier_list_tail: ',' ID comma_identifier_list_tail
	|	/* epsilon */
	;

 /* main query syntax */
 
query: select_clause from_clause order_clause where_clause groupby_clause ;
 
 /* select */
select_clause: SELECT select_elem select_clause_tail ;

select_elem: expression COL_AS ID
	|	expression
	;
	
select_clause_tail: ',' select_elem select_clause_tail
		| /* epislon */
		;
		
 /* from */
from_clause: FROM table_expressions ;

 /* order by [optional] */
order_clause: ASSUMING ORDER comma_identifier_list
	 | /* epsilon */
	 ;
/* where [optional] */
where_clause: WHERE and_expression_list 
	| /* epsilong */
	;

/* group by [optional] */
groupby_clause: GROUP BY comma_expression_list 
	| /* epsilong */
	;

/* table expressions */
table_expressions: table_expression table_expression_tail ;

table_expression_tail: ',' table_expression table_expression_tail
		 | /* epsilon */
		 ;
		 
table_expression: table_exp ID
	|	table_exp		 
	;
	
table_exp: FLATTEN '(' ID ')'
		| ID
		;
	 

/* expressions, inspiration from http://www.lysator.liu.se/c/ANSI-C-grammar-y.html */
literal: ROWID | ID | TIMES_OP | column_access | INTEGER | FLOAT | DATE | STRING | '(' expression ')';

column_access: ID '.' ID;

call: literal
	| literal '[' indexing ']'
	| built_in '(' comma_expression_list ')'
	| built_in '(' ')' /* niladic */
	;

indexing: ODD | EVEN | EVERY INTEGER ;

built_in: ABS | AVG | AVGS | COUNT | DELTAS | DISTINCT | DROP | FIRST | LAST | MAX | MAXS | MIN
	| MINS | MOD | NEXT | PREV | PRD | PRDS | REV | SUM | SUMS | STDDEV
	;

mult_expression: call
	| mult_expression TIMES_OP call
	| mult_expression DIV_OP call
	;
	

add_expression: mult_expression
 	| add_expression PLUS_OP mult_expression
	| add_expression MINUS_OP mult_expression
	;
	
rel_expression: add_expression
	| rel_expression L_OP add_expression
	| rel_expression G_OP add_expression
	| rel_expression LE_OP add_expression
	| rel_expression GE_OP add_expression
	;

eq_expression: rel_expression
	| eq_expression EQ_OP rel_expression
	| eq_expression NEQ_OP rel_expression
	;

and_expression: eq_expression
	| and_expression AND_OP eq_expression
	;

or_expression: and_expression
	| or_expression OR_OP and_expression
	;
	
expression: or_expression ;

 /* lists of expressions */
 
comma_expression_list: expression comma_expression_list_tail ;

comma_expression_list_tail: ',' expression comma_expression_list_tail 
	| /* epsilon */
	;
	
and_expression_list: expression and_expression_list_tail ;

and_expression_list_tail: AND expression and_expression_list_tail
	| /* epsilon */
	;



%%
void yyerror(const char *s) 
{
	//TODO: handle end of file errors
	//rewind file and find error
	rewind(yyin);
	int lines = line_num, cols = col_num;
	size_t max_size = 256;
	
	char *line = NULL;
	char *marker = malloc(sizeof(char) * (col_num + 2));
	memset(marker, ' ', col_num + 1);
	marker[col_num - yyleng] = '^';
	marker[col_num + 1] = '\0';
	
	while(lines-- > 0) 
	{ //find line with error
		getline(&line, &max_size, yyin);
	}
	
	printf("%s at line %d, column %d\n%s" ERRORCOLOR "%s\n", s, line_num, col_num, line,marker);
	fclose(yyin);
	exit(1);
}

int main(int argc, char *argv[]) {
	
	yydebug = 0;
	
	if(argc < 2) 
	{
		printf("Usage: aquery <file_name_to_parse>\n");
		exit(1);
	}
	
	FILE *to_parse = fopen(argv[1], "r");
	
	if(to_parse == NULL)
	{
		printf("Unable to open %s for reading\n", argv[1]);
		exit(1);
	}
	else
	{
		yyin = to_parse;
	}
	
	do 
	{
		yyparse();
	} 
	while(!feof(yyin));
	
	printf("File conforms to Aquery grammar... now on to building AST\n");
}

