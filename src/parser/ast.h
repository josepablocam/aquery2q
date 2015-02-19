#ifndef AQUERY_AST_H
#define AQUERY_AST_H
//#include "aquery_types.h"
#include "symtable.h"

/* Section 2.8: Value Expressions */
typedef enum ExprNodeType {
  CONSTANT_EXPR = 0,
  ID_EXPR,
  ROWID_EXPR,
  COLDOTACCESS_EXPR,
  ALLCOLS_EXPR,
  CASE_EXPR,
  CASE_CLAUSE,
  CASE_WHEN_CLAUSE,
  CASE_WHEN_CLAUSES,
  CASE_ELSE_CLAUSE,
  CALL_EXPR,
  BUILT_IN_FUN_CALL,
  UDF_CALL,
  INDEX_EXPR,
  ODD_IX,
  EVEN_IX,
  EVERY_N_IX,
  POW_EXPR,
  MULT_EXPR,
  DIV_EXPR,
  PLUS_EXPR,
  MINUS_EXPR,
  LT_EXPR,
  LE_EXPR,
  GT_EXPR,
  GE_EXPR,
  EQ_EXPR,
  NEQ_EXPR,
  LOR_EXPR,
  LAND_EXPR,
  LIST_EXPR,
  SEARCH_EXPR
} ExprNodeType;




typedef struct ExprNode {
	ExprNodeType node_type;
	DataType data_type;
	union {
		int ival;
		float fval;
		char *str;
	} data;
	struct ExprNode *first_child;
	struct ExprNode *first_sibling;
} ExprNode;





/*
// Section 2.1: Top level program definition

typedef struct TopLevelNode {
	TopLevelType node_type;
	union {
		GlobalQueryNode *global_query; //top level query
		UDFDefNode *udf_def; //user function definition
		CreateNode *create; //create table/view
		ModifyNode *modify; //update/delete/select
	}
	struct TopLevelNode *next;
} TopLevelNode;

typedef enum TopLevelType { GLOBAL_QUERY_N, UDF_DEF_N, MODIFY_N, CREATE_N } TopLevelType;


// Section 2.2: Local and Global Queries 
//Used to optimize queries
typedef struct LogicalQueryNode {
	LogicalQueryNodeType node_type;
	struct LogicalQueryNode *first_table;
	struct LogicalQueryNode *second_table;
	ExprNode	*exp_list;
}

typedef enum LogicalQueryType { PROJECT, SELECT_WHERE, SELECT_HAVING, ORDER, JOIN, GROUP_BY }

typedef struct QueryNode {
	LogicalQueryNode *logical_plan;
}


typedef struct LocalQueryNode {
	//name
	//columns
	LogicalQueryNode *query;
	struct LocalQueryNode *next;
}

typedef struct GlobalQueryNode {
	LocalQueryNode *local_queries;
	LogicalQueryNode *main_query;
}

*/







//Expressions
ExprNode *make_EmptyExprNode(ExprNodeType type);
ExprNode *make_int(int i);
ExprNode *make_float(float f);
ExprNode *make_date(char *date);
ExprNode *make_string(char *str);
ExprNode *make_hex(char *hex);
ExprNode *make_bool(int boolean);
ExprNode *make_id(Symtable *symtable, char *id);

ExprNode *make_rowId();
ExprNode *make_colDotAccessNode(ExprNode *src, ExprNode *dest);
ExprNode *make_allColsNode();

ExprNode *make_oddix();
ExprNode *make_evenix();
ExprNode *make_everynix(int ix);
ExprNode *make_indexNode(ExprNode *src, ExprNode *ix);

ExprNode *make_callNode(ExprNode *fun, ExprNode *args);
ExprNode *make_builtInFunNode(char *nm);
ExprNode *make_udfNode(Symtable *symtable, char *nm);


ExprNode *make_caseNode(ExprNode *case_clause, ExprNode *when_clauses, ExprNode *else_clause);
ExprNode *make_caseClauseNode(ExprNode *exp);
ExprNode *make_caseWhenNode(ExprNode *when, ExprNode *conseq);
ExprNode *make_whenClausesNode(ExprNode *h, ExprNode *t);
ExprNode *make_elseClauseNode(ExprNode *exp);




ExprNode *make_exprListNode(ExprNode *h, ExprNode *t);


ExprNode *make_compNode(ExprNodeType op, ExprNode *x, ExprNode *y);
ExprNode *make_logicOpNode(ExprNodeType op, ExprNode *x, ExprNode *y);
ExprNode *make_arithNode(ExprNodeType op, ExprNode *x, ExprNode *y);

void print_expr(ExprNode *n, int indent);



#endif