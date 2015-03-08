#ifndef AQUERY_AST_H
#define AQUERY_AST_H
#include "aquery_types.h"
#include "symtable.h"

/******* 2.8: value expressions *******/
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
  PRED_EXPR, //predicate
  WHERE_AND_EXPR,
  WHERE_OR_EXPR,
  //sorting optimizations
  SORT_IX,
  DE_SORT_IX
} ExprNodeType;


typedef struct ExprNode {
	ExprNodeType node_type;
	DataType data_type;
	int order_dep; //is this node order dependent
    int sub_order_dep; //does it have an order dependency somewhere in subtree?
    int can_sort; //we should only index things that are sortable to begin with
	union {
		int ival;
		float fval;
		char *str;
	} data;
	struct ExprNode *first_child;
	struct ExprNode *next_sibling;
} ExprNode;

typedef struct NamedExprNode {
	char *name;
	ExprNode *expr;
	int order_dep;
    int sub_order_dep;
	struct NamedExprNode *next_sibling;
 } NamedExprNode;


/* Constants or Identifiers */
void spread_order(ExprNode *parent, ExprNode *child);
ExprNode *make_EmptyExprNode(ExprNodeType type);
ExprNode *make_int(int i);
ExprNode *make_float(float f);
ExprNode *make_date(char *date);
ExprNode *make_string(char *str);
ExprNode *make_hex(char *hex);
ExprNode *make_bool(int boolean);
ExprNode *make_id(Symtable *symtable, char *id);
/* Table constants */
ExprNode *make_rowId();
ExprNode *make_colDotAccessNode(ExprNode *src, ExprNode *dest);
ExprNode *make_allColsNode();
/* Case Expressions */
ExprNode *make_caseNode(ExprNode *case_clause, ExprNode *when_clauses, ExprNode *else_clause);
ExprNode *make_caseClauseNode(ExprNode *exp);
ExprNode *make_caseWhenNode(ExprNode *when, ExprNode *conseq);
ExprNode *make_whenClausesNode(ExprNode *h, ExprNode *t);
ExprNode *make_elseClauseNode(ExprNode *exp);
/* Application of expressions: indexing, function calls */
ExprNode *make_callNode(ExprNode *fun, ExprNode *args);
ExprNode *make_indexNode(ExprNode *src, ExprNode *ix);
/* Types of functions: built-ins vs UDF */
ExprNode *make_builtInFunNode(Symtable *symtable, char *nm);
ExprNode *make_udfNode(Symtable *symtable, char *nm);
/* Safe indexing: EVEN/ODD/EVERY N */
ExprNode *make_oddix();
ExprNode *make_evenix();
ExprNode *make_everynix(int ix);
/* Simple arithmetic, comparison and logical operations */
ExprNode *make_compNode(ExprNodeType op, ExprNode *x, ExprNode *y);
ExprNode *make_logicOpNode(ExprNodeType op, ExprNode *x, ExprNode *y);
ExprNode *make_arithNode(ExprNodeType op, ExprNode *x, ExprNode *y);
/* expression lists */
ExprNode *make_exprListNode(ExprNode *data);
/* exlusively for search conditions */
ExprNode *make_predNode(char *nm);

 /******* Query related nodes *******/

typedef struct IDListNode {
	char *name;
	struct IDListNode *next_sibling;
 } IDListNode;

typedef enum OrderNodeType { ASC_SORT, DESC_SORT } OrderNodeType;

typedef struct OrderNode {
	OrderNodeType node_type;
	ExprNode *col;
	struct OrderNode *next;
 } OrderNode;

typedef enum LogicalQueryNodeType { 
	PROJECT_SELECT, 
	PROJECT_UPDATE, 
	DELETION, 
	FILTER_WHERE, 
	FILTER_HAVING, 
	CARTESIAN_PROD, 
	INNER_JOIN_ON, 
	FULL_OUTER_JOIN_ON, 
	INNER_JOIN_USING,
	FULL_OUTER_JOIN_USING,
	GROUP_BY, 
	SIMPLE_TABLE, 
	ALIAS, 
	SORT, 
	FLATTEN_FUN, 
	EXPLICIT_VALUES,
	COL_NAMES,
    SORT_COLS,
    SORT_EACH_COLS
	} LogicalQueryNodeType;


typedef struct LogicalQueryNode {
	LogicalQueryNodeType node_type;
	struct LogicalQueryNode *after; //we will move a lot of these around
	struct LogicalQueryNode *arg; //argument to operation
	struct LogicalQueryNode *next_arg; //potential additional arguments
	int order_dep;
	union {
		char *name		 		; //table name or alias
		NamedExprNode 	*namedexprs; //c1 * 2 as c2, c1 * 2 (nil)
		ExprNode			*exprs; //on, search conditions, grouping
		IDListNode 			*cols; //using
		OrderNode 			*order; //sorting
		} params;
} LogicalQueryNode;

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
OrderNode *make_OrderNode(OrderNodeType type, ExprNode *col);
LogicalQueryNode *make_sort(LogicalQueryNode *t, OrderNode *order);
LogicalQueryNode *make_values(ExprNode *exprs);

LogicalQueryNode *pushdown_logical(LogicalQueryNode *lhs, LogicalQueryNode *rhs);
LogicalQueryNode *assemble_base(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);


/******* 2.2: Local and global queries *******/
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

LocalQueryNode *make_LocalQueryNode(char *name, IDListNode *colnames, LogicalQueryNode *plan);
FullQueryNode *make_FullQueryNode(LocalQueryNode *local, LogicalQueryNode *plan);


/******* 2.7: user defined functions *******/
typedef enum UDFBodyNodeType { EXPR, VARDEF, QUERY } UDFBodyNodeType;

typedef struct UDFBodyNode {
	UDFBodyNodeType node_type;
	union {
		ExprNode *expr;
		NamedExprNode *vardef;
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
IDListNode *make_IDListNode(char *arg, IDListNode *next);
UDFBodyNode *make_UDFEmptyBodyNode(UDFBodyNodeType type);
UDFBodyNode *make_UDFExpr(ExprNode *expr);
UDFBodyNode *make_UDFVardef(NamedExprNode *vardef);
UDFBodyNode *make_UDFQuery(FullQueryNode *query);
UDFDefNode *make_UDFDefNode(char *name, IDListNode *args, UDFBodyNode *body);



/******* Mostly 2.6: update, insert, delete statements and 2.5: table and view creation *******/
typedef struct InsertNode {
	LogicalQueryNode *dest; //destination for data
	IDListNode *modifier;
	FullQueryNode *src; //source of data
} InsertNode;


InsertNode *make_insert(LogicalQueryNode *dest, IDListNode *modifier, FullQueryNode *src);

typedef struct SchemaNode {
	char *fieldname;
	char *typename;
	struct SchemaNode *next_sibling;
} SchemaNode;

typedef enum CreateSourceNodeType { SCHEMA_SOURCE, QUERY_SOURCE } CreateSourceNodeType;

typedef struct CreateSourceNode {
	CreateSourceNodeType node_type;
	union {
		FullQueryNode *query;
		SchemaNode *schema;
	} load;
} CreateSourceNode ;


typedef enum CreateNodeType { CREATE_TABLE, CREATE_VIEW } CreateNodeType ;

typedef struct CreateNode {
	CreateNodeType node_type;
	char *name;
	CreateSourceNode *src;
} CreateNode;


CreateNode *make_createNode(CreateNodeType type, char *name, CreateSourceNode *src);
SchemaNode *make_schemaNode(char *fieldname, char *typename);
CreateSourceNode *make_schemaSource(SchemaNode *schema);
CreateSourceNode *make_querySource(FullQueryNode *query);


 /******* 2.1: Top level program definition *******/

typedef enum TopLevelNodeType { 
	GLOBAL_QUERY, 
	UDF_DEF, 
	INSERT_STMT, 
	UPDATE_DELETE_STMT, 
	CREATE_STMT 
 } TopLevelNodeType;

typedef struct TopLevelNode {
	TopLevelNodeType node_type;
	union {
		FullQueryNode *query; //top level query
		UDFDefNode *udf; //user function definition
		CreateNode *create; //create table/view
		InsertNode *insert; //insert statement
		LogicalQueryNode *updatedelete;
	} elem;
	struct TopLevelNode *next_sibling;
} TopLevelNode;

TopLevelNode *make_EmptyTopLevelNode(TopLevelNodeType type);
TopLevelNode *make_Top_GlobalQuery(FullQueryNode *query, TopLevelNode *next);
TopLevelNode *make_Top_UDF(UDFDefNode *def, TopLevelNode *next);
TopLevelNode *make_Top_Create(CreateNode *create, TopLevelNode *next);
TopLevelNode *make_Top_Insert(InsertNode *ins, TopLevelNode *next);
TopLevelNode *make_Top_UpdateDelete(LogicalQueryNode *ud, TopLevelNode *next);


#endif