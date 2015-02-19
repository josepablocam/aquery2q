%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"	
#include "ast.h"

	
#define YYDEBUG 1
#define ERRORCOLOR  "\x1B[32m"

extern int yyleng;
extern FILE *yyin;
extern int yylex();
extern int yyparse();

//for debugging purposes, defined in flex
extern int line_num; 
extern int col_num;

//Symbol table
Symtable *env;	


void yyerror(const char *);



%}

 /* 
  ********************
  *Token definitions *
  ********************
  */
  
 /* SQL: select query key words */
 
%token WITH UC_AS SELECT FROM ASSUMING ASC DESC WHERE GROUP BY HAVING LC_AS

 /* SQL: indexing */
%token ROWID ODD EVEN EVERY

 /* SQL: table operations */
%token FLATTEN

 /* SQL: joins */
%token JOIN INNER OUTER FULL ON USING 
 
 /* SQL: views/tables */
%token CREATE TABLE VIEW

 /* SQL: update/insert/delete statements */
%token UPDATE SET INSERT INTO VALUES DELETE

 /* SQL: search conditions */
%token AND OR IS NOT BETWEEN IN LIKE NULL_KEYWORD OVERLAPS

 /* SQL: case statement */
%token CASE END WHEN THEN ELSE

 /* SQL: type names */
%token TYPE_INT TYPE_FLOAT TYPE_STRING TYPE_DATE TYPE_BOOLEAN TYPE_HEX
 
 /* SQL: user defined functions */
%token FUNCTION LOCAL_ASSIGN
  
 /* built-in functions */
 /* non-moving variants */
%token <str> ABS AVG COUNT DISTINCT DROP FILL FIRST LAST MAX MIN MOD NEXT PREV PRD REV SUM STDDEV
 /* moving variants */
%token <str> AVGS DELTAS MAXS MINS PRDS SUMS
%token <str> MAKENULL
 
 /* literals and identifiers, and assocating storage in the yyval union */ 
%token <floatval> FLOAT
%token <intval> INT TRUE FALSE 
%token <str> DATE HEX ID STRING
 
 /* Math operators */
%token EXP_OP TIMES_OP DIV_OP PLUS_OP MINUS_OP LE_OP GE_OP L_OP G_OP EQ_OP NEQ_OP AND_OP OR_OP
  
 
 /* Abstract Syntax Tree Types */
/* types for expressions */
%type <exprnode> constant truth_value table_constant column_dot_access
%type <exprnode> case_expression case_clause when_clauses when_clause when_clauses_tail else_clause
%type <exprnode> call built_in_fun 
%type <exprnode> main_expression
%type <exprnode> indexing
%type <exprnode> exp_expression mult_expression add_expression rel_expression eq_expression 
%type <exprnode> and_expression or_expression value_expression
%type <exprnode> comma_value_expression_list comma_value_expression_list_tail
%type <exprnode> search_condition

%start program

%union {
  int   intval;
  float floatval;
  char* str;
  struct ExprNode *exprnode;
}


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
 
global_query:               {print_symtable(env);  env = push_env(env); /* create a new scope to handle local query names */ }
			  local_queries 
              base_query
			                { print_symtable(env); env = pop_env(env); /* remove local queries from scope */ }
		      ; 

local_queries: WITH local_query local_queries_tail 
	|	/* epsilon */	
	;
	
local_queries_tail: local_query local_queries_tail
	| /* epsilon */
	;

local_query: ID                        { put_sym(env, $1, TABLE_TYPE); /* add local query table name to symbol table */ }
             col_aliases 				//TODO: eventually we will use this to rename cols
			 UC_AS '(' base_query ')' ; 

col_aliases: '(' comma_identifier_list ')' 
	| /* epsilon */
	;

comma_identifier_list: ID comma_identifier_list_tail; 

comma_identifier_list_tail: ',' ID comma_identifier_list_tail
	|	/* epsilon */
	;

column_list: column_name column_list_tail ;

column_name: ID | column_dot_access ;

column_dot_access: ID '.' ID  {$$ = make_colDotAccessNode(make_id(env, $1), make_id(env, $3)); }
	;

column_list_tail: ',' column_name column_list_tail
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
		
from_clause: FROM table_expressions ; //TODO: check that table_expressions is of type table or unknown

order_clause: ASSUMING order_specs
	| /* epsilon */
	;
	
order_specs: order_spec order_specs_tail ;
	
order_spec: ASC column_name
	 | DESC column_name
	 ;
	 
order_specs_tail: ',' order_spec order_specs_tail 
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
search_condition: boolean_term				{$$ = make_EmptyExprNode(SEARCH_EXPR); }
	| search_condition OR boolean_term		{$$ = make_EmptyExprNode(SEARCH_EXPR);}
	;
	
boolean_term: boolean_factor				
	| boolean_term AND boolean_factor		//TODO: check that this is boolean type, unknown, or function call
	;
	
boolean_factor: boolean_primary
	| NOT boolean_primary
	;

boolean_primary: predicate | '(' search_condition ')' ;

predicate: value_expression postfix_predicate //TODO: check that type of value expression works with postfix_predicate?
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

truth_value: TRUE 				{$$ = make_bool(1); }
			| FALSE 			{$$ = make_bool(0); }
			;	

overlaps_predicate: range_value_expression OVERLAPS range_value_expression ;	
	
range_value_expression: '(' value_expression ',' value_expression ')' ;	
	


/******* 2.3.2: table expressions *******/

joined_table: table_expression									//TODO: check that types here work (don't suddenly want a function here...so either table or unknown)
	| table_expression join_type JOIN joined_table join_spec
	;

join_type: INNER | FULL OUTER ;	

join_spec: on_clause | using_clause ;

on_clause: ON search_condition ;

using_clause: USING '(' comma_identifier_list ')' ;
	
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
	| // epsilon 
	;

/******* 2.5: table and view creation *******/	 
create_table_or_view: CREATE TABLE ID create_spec             { put_sym(env, $3, TABLE_TYPE); }
	| CREATE VIEW ID create_spec                              { put_sym(env, $3, VIEW_TYPE);  }
	;

create_spec: UC_AS global_query	
	|	'(' schema ')'
 	;
	
schema: schema_element schema_tail ;

schema_element: ID type_name ; //TODO: use this info to create new table

schema_tail: ',' schema_element schema_tail
	| /* epsilon */
	;
	
type_name: TYPE_INT | TYPE_FLOAT | TYPE_STRING | TYPE_DATE | TYPE_BOOLEAN | TYPE_HEX ;	


/******* 2.6: update, insert, delete statements *******/
update_statement: UPDATE ID SET set_clauses order_clause where_clause groupby_clause;

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
user_function_definition: FUNCTION ID         { put_sym(env, $2, FUNCTION_TYPE); env = push_env(env);  /* define function, create new scope for args*/ }
                        '(' 
						    def_arg_list 	  
					     ')' 
						'{' 
						    function_body 	  { print_symtable(env); /* this is what is reachable during function body*/ }
						'}'                   { env = pop_env(env); /* remove latest scope*/ } 
						; 

def_arg_list: ID                              { put_sym(env, $1, UNKNOWN_TYPE); }
              def_arg_list_tail			
	| /* epsilon */
	;
	
def_arg_list_tail: ',' ID                     { put_sym(env, $2, UNKNOWN_TYPE ); }
                   def_arg_list_tail
	| /* epsilon */
	;


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
	
function_local_var_def: ID LOCAL_ASSIGN value_expression   { put_sym(env, $1, UNKNOWN_TYPE); } ; //TODO: replace UNKNOWN_TYPE with the type of the value expression node


/******* 2.8: value expressions *******/
constant: INT 				{ $$ = make_int($1); }
		| FLOAT 			{ $$ = make_float($1); }
		| DATE 				{ $$ = make_date($1); }
		| STRING 			{ $$ = make_string($1); }
		| HEX 				{ $$ = make_hex($1); }
		| truth_value 		{ $$ = $1; }
		;

table_constant:  ROWID 					{ $$ = make_rowId(); }
				| column_dot_access 	{ $$ = $1; 			}
				| TIMES_OP 				{ $$ = make_allColsNode(); }
				;


case_expression: CASE case_clause when_clauses else_clause END 					{$$ = make_caseNode($2, $3, $4); }   
				  ;

case_clause: value_expression	 { $$ = make_caseClauseNode($1);  }
	| /* epsilon */				 { $$ = make_caseClauseNode(NULL); }
	;
	
when_clauses: when_clause when_clauses_tail {$$ = make_whenClausesNode($1, $2); }
	;

when_clauses_tail: when_clause when_clauses_tail {$$ = make_whenClausesNode($1, $2); }
	| /* epsilon */	{$$ = NULL; }
	;
	
when_clause: WHEN search_condition THEN value_expression  {$$ = make_caseWhenNode($2, $4); }
	;

else_clause: ELSE value_expression  { $$ = make_elseClauseNode($2); }
	;
	
main_expression: constant 					{ $$ = $1; }
			| table_constant 				{ $$ = $1; } 
			| ID 							{ $$ = make_id(env, $1); }
			| '(' value_expression ')'		{ $$ = $2; }
			| case_expression 				{ $$ = $1; }
			; 

call: main_expression						{ $$ = $1; }
	| main_expression '[' indexing ']' 		{ $$ = make_indexNode($1, $3); }
	| built_in_fun '(' comma_value_expression_list ')' {$$ = make_callNode($1, $3); }
	| built_in_fun '(' ')' 								{$$ = make_callNode($1, NULL); }
	| ID '(' comma_value_expression_list ')' {$$ = make_callNode(make_udfNode(env, $1), $3); }
	| ID '(' ')' 							 {$$ = make_callNode(make_udfNode(env, $1), NULL); }
	;


indexing: ODD 				{$$ = make_oddix();     }
		| EVEN 				{$$ = make_evenix();     }
		| EVERY INT 		{$$ = make_everynix($2); }
		;

built_in_fun: ABS 				{ $$ = make_builtInFunNode($1); }
	| AVG 						{ $$ = make_builtInFunNode($1); }
	| AVGS 						{ $$ = make_builtInFunNode($1); }
	| COUNT 				{ $$ = make_builtInFunNode($1); }
	| DELTAS 			{ $$ = make_builtInFunNode($1); }
	| DISTINCT 			{ $$ = make_builtInFunNode($1); }
	| DROP 	{ $$ = make_builtInFunNode($1); }
	| FILL 	{ $$ = make_builtInFunNode($1); }
	| FIRST 	{ $$ = make_builtInFunNode($1); }
	| LAST 	{ $$ = make_builtInFunNode($1); }
	| MAX 	{ $$ = make_builtInFunNode($1); }
	| MAXS 	{ $$ = make_builtInFunNode($1); }
	| MIN	{ $$ = make_builtInFunNode($1); }
	| MINS 	{ $$ = make_builtInFunNode($1); }
	| MOD 	{ $$ = make_builtInFunNode($1); }
	| NEXT 		{ $$ = make_builtInFunNode($1); }
	| PREV 	{ $$ = make_builtInFunNode($1); }
	| PRD 	{ $$ = make_builtInFunNode($1); }
	| PRDS 	{ $$ = make_builtInFunNode($1); }
	| REV 	{ $$ = make_builtInFunNode($1); }
	| SUM 	{ $$ = make_builtInFunNode($1); }
	| SUMS 		{ $$ = make_builtInFunNode($1); }
	| STDDEV 	{ $$ = make_builtInFunNode($1); }
	| MAKENULL	{ $$ = make_builtInFunNode($1); }
	;
	
exp_expression: call 				{ $$ = $1; }
	| call EXP_OP exp_expression	{ $$ = make_arithNode(POW_EXPR, $1, $3); }
	;

mult_expression: exp_expression					{ $$ = $1; }
	| mult_expression TIMES_OP exp_expression		{ $$ = make_arithNode(MULT_EXPR, $1, $3); }
	| mult_expression DIV_OP exp_expression			{ $$ = make_arithNode(DIV_EXPR, $1, $3); }
	;
	

add_expression: mult_expression						{ $$ = $1; }
 	| add_expression PLUS_OP mult_expression		{ $$ = make_arithNode(PLUS_EXPR, $1, $3); }
	| add_expression MINUS_OP mult_expression		{ $$ = make_arithNode(MINUS_EXPR, $1, $3); }
	;
	
rel_expression: add_expression						{ $$ = $1; }
	| rel_expression L_OP add_expression			{ $$ = make_compNode(LT_EXPR, $1, $3); }
	| rel_expression G_OP add_expression			{ $$ = make_compNode(GT_EXPR, $1, $3); }
	| rel_expression LE_OP add_expression			{ $$ = make_compNode(LE_EXPR, $1, $3); }
	| rel_expression GE_OP add_expression			{ $$ = make_compNode(GE_EXPR, $1, $3); }
	;

eq_expression: rel_expression						{$$ = $1; }
	| eq_expression EQ_OP rel_expression			{ $$ = make_compNode(EQ_EXPR, $1, $3); }
	| eq_expression NEQ_OP rel_expression			{ $$ = make_compNode(NEQ_EXPR, $1, $3); }
	;

and_expression: eq_expression						{ $$ = $1; }
	| and_expression AND_OP eq_expression			{ $$ = make_logicOpNode(LAND_EXPR, $1, $3); }
	;

or_expression: and_expression						{ $$ = $1; }
	| or_expression OR_OP and_expression			{ $$ = make_logicOpNode(LOR_EXPR, $1, $3); }
	;
	
value_expression: or_expression 					{ $$ = $1; }
	;

 
comma_value_expression_list: value_expression comma_value_expression_list_tail 	{ $$ = make_exprListNode($1, $2); }
		;

comma_value_expression_list_tail: ',' value_expression comma_value_expression_list_tail { $$ = make_exprListNode($2, $3); }
	| /* epsilon */																		{ $$ = NULL; }
	;
	



%%

void yyerror(const char *s) 
{
	//TODO: rewrite with more robust fgets wrapper
	//rewind file and find error
	rewind(yyin);
	int lines = line_num, cols = col_num;
	int max_size = 500;
	
	char *line = malloc(sizeof(char) * (max_size - 1));
	char *marker = malloc(sizeof(char) * (col_num + 2));
	memset(marker, ' ', col_num + 1);
	marker[col_num - yyleng] = '^';
	marker[col_num + 1] = '\0';
	
	while(lines-- > 0) 
	{ //find line with error
		fgets(line, max_size, yyin);
	}
	
	printf("%s at line %d, column %d\n%s" ERRORCOLOR "%s\n", s, line_num, col_num - yyleng, line, marker);
	fclose(yyin);
	free(line); free(marker);
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
	
	env = make_symtable(); //create the global environment
	
	do 
	{
		yyparse();
	} 
	while(!feof(yyin));
	
	print_symtable(env);
	
	printf("File conforms to Aquery grammar... now on to building AST\n");
}

