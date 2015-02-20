/* Building an AST for aquery, builds during the parse traversal in bison */
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "aquery_types.h"
#include "symtable.h"
#include "ast_print.h"

#define AST_DEBUG 1
#define AST_PRINT_DEBUG(str) if(AST_DEBUG) printf("---->AST DEBUGGING: %s\n", str)

#define STAND_ALONE 0






ExprNode *make_EmptyExprNode(ExprNodeType type)
{
	ExprNode *node = malloc(sizeof(ExprNode));
	
	if(node == NULL)
	{
		printf("Error: unable to allocate Expression Node\n");
		exit(1);
	}
	node->first_child = node->next_sibling = NULL;
	node->node_type = type;
	node->data_type = UNKNOWN_TYPE;
	return node;
}

/*
	TODO: USER DEFINED FUNCTIONS (2.7)
	TODO: UPDATE/INSERT/DELETE STATEMENTS (2.6)
	TODO: TABLE/VIEW CREATION (2.5)
	TODO: TABLE EXPRESSIONS (2.3.2)
	TODO: SEARCH CONDITION (2.3.1)
	TODO: BASE QUERY (2.3)
	TODO: LOCAL/GLOBAL QUERY (2.2)
	TODO: TOP LEVEL (2.1)
Consider breaking up node types by tyep of expression, so everything up until now
has been expressio nodes

set up query nodes as logical query plan (or close enough)

create printers void (*print)(void *)
just printout label

*/



// Expressions
ExprNode *make_int(int i)
{
	AST_PRINT_DEBUG("making int node");
	ExprNode *node = make_EmptyExprNode(CONSTANT_EXPR);
	node->data_type = INT_TYPE;
	node->data.ival = i;
	return node;
}

ExprNode *make_float(float f)
{
	AST_PRINT_DEBUG("making float node");
	ExprNode *node = make_EmptyExprNode(CONSTANT_EXPR);
	node->data_type = FLOAT_TYPE;
	node->data.fval = f;
	return node;
}

ExprNode *make_date(char *date)
{
	AST_PRINT_DEBUG("making date node");
	ExprNode *node = make_EmptyExprNode(CONSTANT_EXPR);
	node->data_type = DATE_TYPE;
	node->data.str = date; //any memory necessary was already allocated by flex
	return node;
}

ExprNode *make_string(char *str)
{
	AST_PRINT_DEBUG("making string node");
	ExprNode *node = make_EmptyExprNode(CONSTANT_EXPR);
	node->data_type = STRING_TYPE;
	node->data.str = str; //any memory necessary was already allocated by flex
	return node;
}

ExprNode *make_hex(char *hex)
{
	AST_PRINT_DEBUG("making hex node");
	ExprNode *node = make_EmptyExprNode(CONSTANT_EXPR);
	node->data_type = HEX_TYPE;
	node->data.str = hex; //any memory necessary was already allocated by flex
	return node;
}

ExprNode *make_bool(int boolean)
{
	AST_PRINT_DEBUG("making boolean node");
	ExprNode *node = make_EmptyExprNode(CONSTANT_EXPR);
	node->data_type = BOOLEAN_TYPE;
	node->data.ival = boolean; 
	return node;
}

ExprNode *make_id(Symtable *symtable, char *id)
{
	AST_PRINT_DEBUG("making id node");
	ExprNode *node = make_EmptyExprNode(ID_EXPR);
	Symentry *info = lookup_sym(symtable, id);
	node->data_type = (info != NULL) ? info->type : UNKNOWN_TYPE;
	node->data.str = id;
	return node;
}

ExprNode *make_oddix()
{
	AST_PRINT_DEBUG("making odd index");
	return make_EmptyExprNode(ODD_IX);
}

ExprNode *make_evenix()
{
	AST_PRINT_DEBUG("making even index");
	return make_EmptyExprNode(EVEN_IX);
}

ExprNode *make_everynix(int ix)
{
	AST_PRINT_DEBUG("making every n index node");
	ExprNode *new_node = make_EmptyExprNode(EVERY_N_IX);
	new_node->data.ival = ix;
	return new_node;
}

ExprNode *make_indexNode(ExprNode *src, ExprNode *ix)
{
	AST_PRINT_DEBUG("making indexing node");
	ExprNode *new_node = make_EmptyExprNode(INDEX_EXPR);
	new_node->first_child = src;
	src->next_sibling = ix;
	return new_node;
}

ExprNode *make_callNode(ExprNode *fun, ExprNode *args)
{
	AST_PRINT_DEBUG("making call node");
	ExprNode *new_node = make_EmptyExprNode(CALL_EXPR);
	new_node->data_type = UNKNOWN_TYPE;
	new_node->first_child = fun;
	fun->next_sibling = args;
	return new_node;	
}

ExprNode *make_builtInFunNode(char *nm)
{
	AST_PRINT_DEBUG("making built in function node");
	ExprNode *new_node = make_EmptyExprNode(BUILT_IN_FUN_CALL);
	new_node->data.str = nm;
	return new_node;
}

ExprNode *make_udfNode(Symtable *symtable, char *nm)
{
	AST_PRINT_DEBUG("making udf node");
	ExprNode *new_node = make_EmptyExprNode(UDF_CALL);
	Symentry *entry = lookup_sym(symtable, nm);
	
	if(entry != NULL && entry->type != FUNCTION_TYPE)
	{
		new_node->data_type = ERROR_TYPE; //TODO: add reporting here....
	}
	
	return new_node;
}

///Case experssions
ExprNode *make_caseNode(ExprNode *case_clause, ExprNode *when_clauses, ExprNode *else_clause)
{
	AST_PRINT_DEBUG("making case expression node");
	ExprNode *new_node = make_EmptyExprNode(CASE_EXPR);
	
	//TODO: add error reporting
	new_node->first_child = case_clause;
	case_clause->next_sibling = when_clauses;
	when_clauses->next_sibling = else_clause;
	return new_node;
}

ExprNode *make_caseClauseNode(ExprNode *exp)
{
	AST_PRINT_DEBUG("making case clause node");
	ExprNode *new_node = make_EmptyExprNode(CASE_CLAUSE);
	new_node->first_child = exp;
	return new_node;
}

ExprNode *make_caseWhenNode(ExprNode *when, ExprNode *conseq)
{
	AST_PRINT_DEBUG("making when clause node");
	ExprNode *new_node = make_EmptyExprNode(CASE_WHEN_CLAUSE);
	new_node->first_child = when;
	when->next_sibling = conseq;
	return new_node;
}

ExprNode *make_whenClausesNode(ExprNode *h, ExprNode *t)
{
	AST_PRINT_DEBUG("making when clauses node");
	ExprNode *new_node = make_EmptyExprNode(CASE_WHEN_CLAUSES);
	new_node->first_child = h;
	h->next_sibling = t;
	return new_node;
}

ExprNode *make_elseClauseNode(ExprNode *exp)
{
	AST_PRINT_DEBUG("making else clause node");
	ExprNode *new_node = make_EmptyExprNode(CASE_ELSE_CLAUSE);
	new_node->first_child = exp;
	return new_node;
}

ExprNode *make_rowId()
{
	AST_PRINT_DEBUG("making row id node");
	return make_EmptyExprNode(ROWID_EXPR);
}

ExprNode *make_colDotAccessNode(ExprNode *src, ExprNode *dest)
{
	AST_PRINT_DEBUG("making column dot access node");
	ExprNode *new_node = make_EmptyExprNode(COLDOTACCESS_EXPR);
	new_node->first_child = src;
	src->next_sibling = dest;
	return new_node;
}

ExprNode *make_allColsNode()
{
	AST_PRINT_DEBUG("making all columns node");
	return make_EmptyExprNode(ALLCOLS_EXPR);
}


//Simple arithmetic expressions
/* Reduceable expressions */
//comparison operations

// <, > , <=, >=, ==, !=
ExprNode *make_compNode(ExprNodeType op, ExprNode *x, ExprNode *y)
{
	AST_PRINT_DEBUG("making comparison node");
	ExprNode *new_node = make_EmptyExprNode(op);
	new_node->data_type = unif_comp(x->data_type, y->data_type);
	new_node->first_child = x;
	x->next_sibling = y;
	return new_node;	
}

// || and &&
ExprNode *make_logicOpNode(ExprNodeType op, ExprNode *x, ExprNode *y)
{
	AST_PRINT_DEBUG("making logical operation node");
	ExprNode *new_node = make_EmptyExprNode(op);
	new_node->data_type = unif_logic(x->data_type, y->data_type);
	new_node->first_child = x;
	x->next_sibling = y;
	return new_node;
}

// Arithmetic Operations
ExprNode *make_arithNode(ExprNodeType op, ExprNode *x, ExprNode *y)
{
	AST_PRINT_DEBUG("making arithmetic node");
	ExprNode *new_node = make_EmptyExprNode(op);
	new_node->data_type = unif_numeric(x->data_type, y->data_type);
	
	if(op == DIV_EXPR || op == POW_EXPR)
	{ //Division and Exponentiation result in floats regardless of underlying type
		new_node->data_type = unif_numeric(FLOAT_TYPE, new_node->data_type);
	}
	
	new_node->first_child = x;
	x->next_sibling = y;
	return new_node;
}

ExprNode *make_exprListNode(ExprNode *data)
{
	AST_PRINT_DEBUG("making expression list");
	ExprNode *list = make_EmptyExprNode(LIST_EXPR);
	list->first_child = data;
	return list;
}




///****** Queries and their nodes etc *//////////
/*
FullQueryNode *make_FullQueryNode(LocalQueryNode *local, LogicalQueryNode *plan)
{
	FullQueryNode *query = malloc(sizeof(FullQueryNode));
	query->local_queries = local;
	query->query_plan = plan;
	return query;
}


LogicalQueryNode *make_LogicalQueryNode(LogicalQueryType type)
{
	LogicalQueryNode *plan = malloc(sizeof(LogicalQueryNode));
	plan->node_type = type;
	plan->first_table = plan->second_table = NULL;
	return plan;
}

LogicalQueryNode *make_





IDListNode *make_IDListNode(char *id)
{
	IDListNode *ids = malloc(sizeof(IDListNode));
	ids->name = id;
	ids->next_sibling = NULL;
	return ids;
}


LocalQueryNode *make_LocalQueryNode(char *name, IDListNode *colnames, LogicalQueryNode *plan)
{
	LocalQueryNode *local_query = malloc(sizeof(LocalQueryNode));
	local_query->name = name;
	local_query->col_names = colnames;
	local_query->query_plan = plan;
	local_query->next = NULL;
	return local_query;
}


OrderNode *make_OrderNode(OrderNodeType type, char *colname)
{
	OrderNode *new_order = malloc(sizeof(OrderNode));
	new_order->node_type = type;
	new_order->col_name = colname;
	new_order->next = NULL;
}
*/


/// User Defined Functions 
LocalVarDefNode *make_LocalVarDefNode(char *name, ExprNode *expr)
{
	LocalVarDefNode *vardef = malloc(sizeof(LocalVarDefNode));
	vardef->name = name;
	vardef->expr = expr;
	return vardef;
}


UDFArgsNode *make_UDFArgsNode(char *name, UDFArgsNode *next)
{
	UDFArgsNode *new_node = malloc(sizeof(UDFArgsNode));
	new_node->name = name;
	new_node->next_sibling = next;
	return new_node;
}

UDFBodyNode *make_UDFEmptyBodyNode(UDFBodyNodeType type)
{
	UDFBodyNode *new_node = malloc(sizeof(UDFBodyNode));
	
	if(new_node == NULL)
	{
		printf("AST Error: unable to allocate memory for UDFEmptyBodyNode\n");
	}
	
	new_node->node_type = type;
	new_node->next_sibling = NULL;

	return new_node;
}

UDFBodyNode *make_UDFExpr(ExprNode *expr)
{
	UDFBodyNode *body_elem = make_UDFEmptyBodyNode(EXPR);
	body_elem->elem.expr = expr;
	return body_elem;
}

UDFBodyNode *make_UDFVardef(LocalVarDefNode *vardef)
{
	UDFBodyNode *body_elem = make_UDFEmptyBodyNode(VARDEF);
	body_elem->elem.vardef = vardef;
	return body_elem;
}

UDFBodyNode *make_UDFQuery(FullQueryNode *query)
{
	UDFBodyNode *body_elem = make_UDFEmptyBodyNode(QUERY);
	body_elem->elem.query = query;
	return body_elem;
}



UDFDefNode *make_UDFDefNode(char *name, UDFArgsNode *args, UDFBodyNode *body)
{
	UDFDefNode *new_fun = malloc(sizeof(UDFDefNode));
	new_fun->name = name;
	new_fun->args = args;
	new_fun->body = body;
	return new_fun;
}





#if STAND_ALONE
int main()
{
	ExprNode *n1 = make_int(2);
	ExprNode *n2 = make_int(3);
	ExprNode *n3 = make_int(4);
	ExprNode *add = make_arithNode(PLUS_EXPR, n1, n2);
	ExprNode *times = make_arithNode(MULT_EXPR,n3, add);
	//print_expr(times, DUMMY, 0, 0);
	
	UDFArgsNode *arg2 = make_UDFArgsNode("y", NULL);
	UDFArgsNode *arg1 = make_UDFArgsNode("x", arg2);
	
	LocalVarDefNode *local_var_def = make_LocalVarDefNode("x", times);
	UDFBodyNode *body1 = make_UDFVardef(local_var_def);
	UDFBodyNode *body2 = make_UDFQuery(NULL);
	body1->next_sibling = body2;
	UDFDefNode *udf = make_UDFDefNode("my_function", arg1, body1);
	print_udf_def(udf);
	
	
	return 0;
}
#endif




/*
//This is currently just a general sketch
Node { type_of_node;
	   type_of_data; ///unknown etc
	   union {int, float, string, date, hex, bool, etc} data; //hold values (only leaves)
	   pointer to first child;
	   pointer to sibling; 
	}
all should return Node
	
	
make_binop('+', Node(int, int, 6), Node(int, int, 5))
Node(int, int, 11)







	
make_binop('+', $1, $2)// should set $2 to be sibling for $1 and then set that to child, and return
make_unop('+', $1)
make_leaf(int, int, 5) should return Node(exp, val.int = 5)
make_binop('call', function, list_of_args)
make_select etc etc etc
get_val(Node(_,x,_,_)) should return the concrete value



reduction (ie. make_binop('+', 4, 5) shouldn't create the whole thing, it should just return Node(int, 9))

print_ast
*/