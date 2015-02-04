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

 /* 
  ********************
  *Token definitions *
  ********************
  */
  
 /* SQL: select query key words */
 
%token WITH UC_AS SELECT FROM ASSUMING ORDER WHERE GROUP BY HAVING LC_AS

 /* SQL: indexing */
%token ROWID ODD EVEN EVERY

 /* SQL: table operations */
%token FLATTEN

 /* SQL: joins */
%token CROSS JOIN NATURAL INNER OUTER LEFT RIGHT FULL ON USING 
 
 /* SQL: views/tables */
%token CREATE TABLE VIEW

 /* SQL: update/insert/delete statements */
%token UPDATE SET INSERT INTO VALUES DELETE

 /* SQL: search conditions */
%token AND OR IS NOT BETWEEN IN LIKE NULL_KEYWORD OVERLAPS

 /* SQL: case statement */
%token CASE END WHEN THEN ELSE

 /* SQL: type names */
%token TYPE_INT TYPE_FLOAT TYPE_STRING TYPE_DATE TYPE_BOOLEAN  TYPE_HEX
 
 /* SQL: user defined functions */
%token FUNCTION LOCAL_ASSIGN
  
 /* built-in functions */
 /* non-moving variants */
%token ABS AVG COUNT DISTINCT DROP FILL FIRST LAST MAX MIN MOD NEXT PREV PRD REV SUM STDDEV
 /* moving variants */
%token AVGS DELTAS MAXS MINS PRDS SUMS
%token MAKENULL
 
 /* literals and identifiers */
%token INT FLOAT STRING DATE TRUE FALSE HEX ID 
 
 /* Math operators */
%token EXP_OP TIMES_OP DIV_OP PLUS_OP MINUS_OP LE_OP GE_OP L_OP G_OP EQ_OP NEQ_OP AND_OP OR_OP
  
 
%start program

%%

 /* 
 ****************
 *Aquery Grammar*
 ****************
 
 For additional information, 
 please refer to the pdf document Aquery to Q Compiler: Parser Grammar
 
 */
 
 /******* 2.1: Top level program definition *******/

program: top_level

top_level: global_query top_level
	|	create_table_or_view top_level
	|	insert_statement top_level
	|	update_statement top_level
	|	delete_statement top_level
	|	user_function_definition top_level
	| /* epsilon */
	;

 /******* 2.2: Local and global queries *******/
 
global_query: local_queries base_query;

local_queries: WITH local_query local_queries_tail
	|	/* epsilon */
	;
	
local_queries_tail: local_query local_queries_tail
	| /* epsilon */
	;

local_query: ID col_aliases UC_AS '(' base_query ')' ;

col_aliases: '(' comma_identifier_list ')' 
	| /* epsilon */
	;

comma_identifier_list: ID comma_identifier_list_tail;

comma_identifier_list_tail: ',' ID comma_identifier_list_tail
	|	/* epsilon */
	;

column_list: column_elem column_list_tail ;

column_elem: ID | column_access ;

column_access: ID '.' ID ;

column_list_tail: ',' column_elem column_list_tail
	| /* epsilon */
	;



 /******* 2.3: Base query *******/
 
base_query: select_clause from_clause order_clause where_clause groupby_clause ;
 
select_clause: SELECT select_elem select_clause_tail ;

select_elem: value_expression LC_AS ID
	|	value_expression
	;
	
select_clause_tail: ',' select_elem select_clause_tail
	| /* epislon */
	;
		
from_clause: FROM table_expressions ;

order_clause: ASSUMING ORDER column_list
	| /* epsilon */
	;
	 
where_clause: WHERE search_condition 
	| /* epsilon */
	;
	
groupby_clause: GROUP BY comma_value_expression_list having_clause
	| /* epsilon */
	;
	
having_clause: HAVING search_condition 
	| /* epsilon */
	;


 /******* 2.3.1: search condition *******/
search_condition: boolean_term
	| search_condition OR boolean_term
	;
	
boolean_term: boolean_factor
	| boolean_term AND boolean_factor
	;
	
boolean_factor: boolean_primary
	| NOT boolean_primary
	;

boolean_primary: predicate | '(' search_condition ')' ;

predicate: value_expression postfix_predicate 
	| overlaps_predicate
	;

postfix_predicate: between_predicate
	| in_predicate
	| null_predicate
	| like_predicate
	| is_predicate
	| /* epsilon */ //ie, our value_expression already generated a boolean
	;
	
between_predicate: BETWEEN value_expression AND value_expression
	|  NOT BETWEEN value_expression AND value_expression
	;
	
in_predicate: IN in_pred_spec
	| NOT IN in_pred_spec
	;
	
in_pred_spec: '(' comma_value_expression_list ')'  //explicit list
	| value_expression //implicit list e.g a function call returning a list, a column name
	;
	
like_predicate: LIKE value_expression
	| NOT LIKE value_expression
	;
	
null_predicate: IS NOT NULL_KEYWORD
	| IS NULL_KEYWORD
	;
	
is_predicate: IS truth_value
	| IS NOT truth_value
	;

truth_value: TRUE | FALSE ;	

overlaps_predicate: range_value_expression OVERLAPS range_value_expression ;	
	
range_value_expression: '(' value_expression ',' value_expression ')' ;	
	


/******* 2.3.2: table expressions *******/

joined_table: qualified_join 
	| qualified_join CROSS JOIN joined_table 
	;

qualified_join: table_expression
	| table_expression NATURAL join_type JOIN qualified_join
	| table_expression join_type JOIN qualified_join join_spec
	;
	
table_expression: table_expression_main
	| built_in_table_fun '(' table_expression_main ')'	
	;
		
table_expression_main: ID ID 
	| ID UC_AS ID 
	| ID
	| '(' joined_table ')' 
	;
	
built_in_table_fun: FLATTEN ;

table_expressions: joined_table table_expressions_tail ;

table_expressions_tail: ',' joined_table table_expressions_tail
	| /* epsilon */
	;
		
join_type: INNER | LEFT OUTER | LEFT | RIGHT | OUTER | FULL | FULL OUTER | /* epsilon */ ;

join_spec: on_clause | using_clause ;

on_clause: ON search_condition ;

using_clause: USING '(' comma_identifier_list ')' ;


/******* 2.5: table and view creation *******/	 
create_table_or_view: CREATE TABLE ID create_spec 
	| CREATE VIEW ID create_spec
	;

create_spec: UC_AS global_query	
	|	'(' schema ')'
 	;
	
schema: schema_element schema_tail ;

schema_element: ID type_name ;

schema_tail: ',' schema_element schema_tail
	| /* epsilon */
	;
	
type_name: TYPE_INT | TYPE_FLOAT | TYPE_STRING | TYPE_DATE | TYPE_BOOLEAN | TYPE_HEX ;	


/******* 2.6: update, insert, delete statements *******/
update_statement: UPDATE ID SET set_clauses order_clause where_clause;

set_clauses: set_clause set_clauses_tail ;

set_clauses_tail: ',' set_clause set_clauses_tail
	| /* epsilon */
	;

set_clause: ID EQ_OP value_expression ;

insert_statement: INSERT INTO ID order_clause insert_modifier insert_source;

insert_modifier: '(' comma_identifier_list ')'	
	| /* epsilon */
	;
	
insert_source: global_query
	| VALUES '(' comma_value_expression_list ')'
	;
	
delete_statement: DELETE from_clause order_clause where_clause
	| DELETE column_list from_clause 
	;

/******* 2.7: user defined functions *******/
user_function_definition: FUNCTION ID '(' comma_identifier_list ')' '{' function_body '}' ;

function_body: function_body_elem function_body_tail
	| /* epsilon */
	;
	
function_body_tail: ';' function_body_elem function_body_tail
	| /* epsilon */
	;
	
function_body_elem: value_expression
	| function_local_var_def
	| local_queries base_query
	;
	
function_local_var_def: ID LOCAL_ASSIGN value_expression ;


/******* 2.8: value expressions *******/
constant: INT | FLOAT | DATE | STRING | HEX | truth_value ;

table_constant: ROWID | column_access | TIMES_OP ;


case_expression: CASE case_clause when_clauses else_clause END ;

case_clause: value_expression
	| /* epsilon */
	;
	
when_clauses: when_clause when_clauses_tail ;

when_clauses_tail: when_clause when_clauses_tail 
	| /* epsilon */
	;
	
when_clause: WHEN search_condition THEN value_expression ;

else_clause: ELSE value_expression
	| /* epsilon */
	;
	
main_expression: constant | table_constant | ID | '(' value_expression ')' | case_expression ;

call: main_expression
	| main_expression '[' indexing ']'
	| built_in_fun '(' comma_value_expression_list ')'
	| built_in_fun '(' ')' 
	| ID '(' comma_value_expression_list ')'
	| ID '(' ')'
	;

indexing: ODD | EVEN | EVERY INT ;

built_in_fun: ABS | AVG | AVGS | COUNT | DELTAS | DISTINCT | DROP | FILL | FIRST | LAST | MAX | MAXS | MIN
	| MINS | MOD | NEXT | PREV | PRD | PRDS | REV | SUM | SUMS | STDDEV | MAKENULL
	;
exp_expression: call 
	| call EXP_OP exp_expression
	;

mult_expression: exp_expression
	| mult_expression TIMES_OP exp_expression
	| mult_expression DIV_OP exp_expression
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
	
value_expression: or_expression ;

 
comma_value_expression_list: value_expression comma_value_expression_list_tail ;

comma_value_expression_list_tail: ',' value_expression comma_value_expression_list_tail 
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
	
	yydebug = 1;
	
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

