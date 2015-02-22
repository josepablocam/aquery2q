#ifndef AQUERY_AST_H
#define AQUERY_AST_H
//#include "aquery_types.h"
#include "symtable.h"

/* Section 2.8: Value Expressions */
typedef enum ExprNodeType {
  ///value expressions
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
  //search conditions
  PRED_EXPR, //predicate
  WHERE_AND_EXPR,
  WHERE_OR_EXPR,
  DUMMY
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
	struct ExprNode *next_sibling;
} ExprNode;

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



ExprNode *make_compNode(ExprNodeType op, ExprNode *x, ExprNode *y);
ExprNode *make_logicOpNode(ExprNodeType op, ExprNode *x, ExprNode *y);
ExprNode *make_arithNode(ExprNodeType op, ExprNode *x, ExprNode *y);

ExprNode *make_exprListNode(ExprNode *data);


ExprNode *make_predNode(char *nm);


void print_expr(ExprNode *n, ExprNodeType p, int type, int indent);



/*
// Section 2.1: Top level program definition

typedef struct TopLevelNode {
	TopLevelNodeType node_type;
	union {
		FullQueryNode *global_query; //top level query
		UDFDefNode *udf_def; //user function definition
		CreateNode *create; //create table/view
		ModifyNode *modify; //update/delete/select
	} elem;
	struct TopLevelNode *next_sibling;
} TopLevelNode;

typedef enum TopLevelType { GLOBAL_QUERY_N, UDF_DEF_N, MODIFY_N, CREATE_N } TopLevelType;
*/




//Logical Query Plan Nodes

typedef struct IDListNode {
	char *name;
	struct IDListNode *next_sibling;
} IDListNode;

//Used to optimize queries
typedef enum OrderNodeType { ASC_SORT, DESC_SORT } OrderNodeType;

typedef struct OrderNode {
	OrderNodeType node_type;
	ExprNode *col;
	struct OrderNode *next;
} OrderNode;

typedef struct NamedExprNode {
	char *name;
	ExprNode *expr;
	struct NamedExprNode *next_sibling;
} NamedExprNode;

typedef enum LogicalQueryNodeType { PROJECT_SELECT, PROJECT_UPDATE, DELETION, FILTER_WHERE, FILTER_HAVING, CARTESIAN_PROD, 
	INNER_JOIN_ON, FULL_OUTER_JOIN_ON, INNER_JOIN_USING, FULL_OUTER_JOIN_USING,
	GROUP_BY, SIMPLE_TABLE, ALIAS, SORT, FLATTEN_FUN, EXPLICIT_VALUES
	} LogicalQueryNodeType;


typedef struct LogicalQueryNode {
	LogicalQueryNodeType node_type;
	struct LogicalQueryNode *arg; //argument to operation
	struct LogicalQueryNode *next_arg; //potential additional arguments
	union {
		char *name		 		; //table name or alias
		NamedExprNode 	*namedexprs; //c1 * 2 as c2, c1 * 2 (nil)
		ExprNode			*exprs; //on, search conditions, grouping
		IDListNode 			*cols; //using
		OrderNode 			*order; //sorting
		} params;
} LogicalQueryNode;


//Logical query nodes
NamedExprNode *make_NamedExprNode(char *name, ExprNode *expr);
LogicalQueryNode *make_EmptyLogicalQueryNode(LogicalQueryNodeType type);
LogicalQueryNode *make_table(char *name);
LogicalQueryNode *make_alias(LogicalQueryNode *t, char *alias);
LogicalQueryNode *make_joinOn(LogicalQueryNodeType jointype, LogicalQueryNode *t1, LogicalQueryNode *t2, ExprNode *cond);
LogicalQueryNode *make_joinUsing(LogicalQueryNodeType jointype, LogicalQueryNode *t1, LogicalQueryNode *t2, IDListNode *cols);
LogicalQueryNode *make_cross(LogicalQueryNode *t1, LogicalQueryNode *t2);
LogicalQueryNode *make_filterWhere(LogicalQueryNode *t, ExprNode *conds);
LogicalQueryNode *make_groupby(LogicalQueryNode *t, ExprNode *exprs);
LogicalQueryNode *make_filterHaving(LogicalQueryNode *t, ExprNode *conds);
LogicalQueryNode *make_flatten(LogicalQueryNode *t);
LogicalQueryNode *make_project(LogicalQueryNodeType proj_type, LogicalQueryNode *t, NamedExprNode *namedexprs);
LogicalQueryNode *make_delete(LogicalQueryNode *t, IDListNode *cols);
OrderNode *make_OrderNode(OrderNodeType type, ExprNode *cols);
LogicalQueryNode *make_sort(LogicalQueryNode *t, OrderNode *order);
LogicalQueryNode *pushdown_logical(LogicalQueryNode *lhs, LogicalQueryNode *rhs);
LogicalQueryNode *assemble_logical(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);




typedef struct LocalQueryNode {
	char *name;
	IDListNode *col_names;
	LogicalQueryNode *query_plan; //optimizable
	struct LocalQueryNode *next_sibling; //next local query..chained
} LocalQueryNode;

typedef struct FullQueryNode {
	LocalQueryNode *local_queries;
	LogicalQueryNode *query_plan;
} FullQueryNode;

// Section 2.7: user defined functions definition
typedef struct UDFArgsNode {
	char *name;
	struct UDFArgsNode *next_sibling;
} UDFArgsNode;

typedef struct LocalVarDefNode {
	char *name;
	ExprNode *expr;
} LocalVarDefNode;


typedef enum UDFBodyNodeType { EXPR, VARDEF, QUERY } UDFBodyNodeType;

typedef struct UDFBodyNode {
	UDFBodyNodeType node_type;
	union {
		ExprNode *expr;
		LocalVarDefNode *vardef;
		FullQueryNode *query;
	} elem;
	struct UDFBodyNode *next_sibling;
} UDFBodyNode;

typedef struct UDFDefNode {
	char *name;
	IDListNode *args;
	UDFBodyNode *body;
} UDFDefNode;




//UDFs
LocalVarDefNode *make_LocalVarDefNode(char *name, ExprNode *expr);
IDListNode *make_IDListNode(char *arg, IDListNode *next);
UDFBodyNode *make_UDFEmptyBodyNode(UDFBodyNodeType type);
UDFBodyNode *make_UDFExpr(ExprNode *expr);
UDFBodyNode *make_UDFVardef(LocalVarDefNode *vardef);
UDFBodyNode *make_UDFQuery(FullQueryNode *query);
UDFDefNode *make_UDFDefNode(char *name, IDListNode *args, UDFBodyNode *body);






#endif