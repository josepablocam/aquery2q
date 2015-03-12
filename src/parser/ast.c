/* Building an AST for aquery, builds during the parse traversal in bison */
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "aquery_types.h"
#include "symtable.h"
#include "ast_print.h"

#define AST_DEBUG 0
#define AST_PRINT_DEBUG(str) if(AST_DEBUG) printf("---->AST DEBUGGING: %s\n", str)
#define STAND_ALONE 0
#define SAFE_ORDER_DEP(x) ((x) != NULL && (x)->order_dep)
#define SAFE_SUB_ORDER_DEP(x) ((x) != NULL && (x)->sub_order_dep)

void spread_order(ExprNode *parent, ExprNode *child)
{
    parent->order_dep |= SAFE_ORDER_DEP(child);
    parent->sub_order_dep |= SAFE_ORDER_DEP(child) || SAFE_SUB_ORDER_DEP(child);
}


/******* 2.8: value expressions *******/

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
	node->order_dep = 0;
    node->sub_order_dep = 0;
    node->can_sort = 0;
	return node;
}

/* Constants or Identifiers */
/* 
    Note: currently all values except int,boolean, and float are being stored as strings.
    We'll have to eventually parse those or offload to q....

 */

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
	node->data_type = UNKNOWN_TYPE; //TODO: fix this: (info != NULL) ? info->type : 
	node->data.str = id;
    node->can_sort = 1;
	return node;
}

/* Table constants */
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


/* Case Expressions */
//Case Node
ExprNode *make_caseNode(ExprNode *case_clause, ExprNode *when_clauses, ExprNode *else_clause)
{
	AST_PRINT_DEBUG("making case expression node");
	ExprNode *new_node = make_EmptyExprNode(CASE_EXPR);
	
	//TODO: add error reporting
	new_node->first_child = case_clause;
	case_clause->next_sibling = when_clauses;
	when_clauses->next_sibling = else_clause;
    
    spread_order(new_node, case_clause);
    spread_order(new_node, when_clauses);
    spread_order(new_node, else_clause);

	return new_node;
}

//Case-clause, meaning CASE x .... x is this node.
ExprNode *make_caseClauseNode(ExprNode *exp)
{
	AST_PRINT_DEBUG("making case clause node");
	ExprNode *new_node = make_EmptyExprNode(CASE_CLAUSE);
	new_node->first_child = exp;
    spread_order(new_node, exp);
	return new_node;
}

ExprNode *make_caseWhenNode(ExprNode *when, ExprNode *conseq)
{
	AST_PRINT_DEBUG("making when clause node");
	ExprNode *new_node = make_EmptyExprNode(CASE_WHEN_CLAUSE);
	new_node->first_child = when;
	when->next_sibling = conseq;
    spread_order(new_node, when);
    spread_order(new_node, conseq);
    return new_node;
}

ExprNode *make_whenClausesNode(ExprNode *h, ExprNode *t)
{
	AST_PRINT_DEBUG("making when clauses node");
	ExprNode *new_node = make_EmptyExprNode(CASE_WHEN_CLAUSES);
	new_node->first_child = h;
	h->next_sibling = t;
    spread_order(new_node, h);
    spread_order(new_node, t);
	return new_node;
}

ExprNode *make_elseClauseNode(ExprNode *exp)
{
	AST_PRINT_DEBUG("making else clause node");
	ExprNode *new_node = make_EmptyExprNode(CASE_ELSE_CLAUSE);
	new_node->first_child = exp;
	spread_order(new_node, exp);
	return new_node;
}



/* Application of expressions: indexing, function calls */
ExprNode *make_indexNode(ExprNode *src, ExprNode *ix)
{
	AST_PRINT_DEBUG("making indexing node");
	ExprNode *new_node = make_EmptyExprNode(INDEX_EXPR);
	new_node->first_child = src;
	src->next_sibling = ix;
    spread_order(new_node, src);
	return new_node;
}

ExprNode *make_callNode(ExprNode *fun, ExprNode *args)
{
	AST_PRINT_DEBUG("making call node");
	ExprNode *new_node = make_EmptyExprNode(CALL_EXPR);
	new_node->data_type = UNKNOWN_TYPE;
	new_node->first_child = fun;
	fun->next_sibling = args;
    spread_order(new_node, args);
    new_node->order_dep = fun->order_dep;
    new_node->sub_order_dep |= new_node->order_dep;
    new_node->can_sort = fun->order_dep; //we can sort stuff
	return new_node;	
}

/* Types of functions: built-ins vs UDF */
ExprNode *make_builtInFunNode(Symtable *symtable, char *nm)
{
	AST_PRINT_DEBUG("making built in function node");
	ExprNode *new_node = make_EmptyExprNode(BUILT_IN_FUN_CALL);
	Symentry *meta_info = lookup_sym(symtable, nm);
	new_node->data.str = nm;
	new_node->order_dep = meta_info->order_dep;
	return new_node;
}

ExprNode *make_udfNode(Symtable *symtable, char *nm)
{
	AST_PRINT_DEBUG("making udf node");
	ExprNode *new_node = make_EmptyExprNode(UDF_CALL);
	Symentry *meta_info = lookup_sym(symtable, nm);
	
	if(meta_info != NULL && meta_info->type != FUNCTION_TYPE)
	{
		new_node->data_type = ERROR_TYPE; //TODO: type error reporting add...
	}
	
	//TODO: we should reason about whether a user function is order dependent, not assume
	new_node->data.str = nm;
    new_node->order_dep = meta_info == NULL || SAFE_ORDER_DEP(meta_info);
	return new_node;
}


 /* Safe indexing: EVEN/ODD/EVERY N */
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




/* Simple arithmetic, comparison and logical operations */

// <, > , <=, >=, ==, !=
ExprNode *make_compNode(ExprNodeType op, ExprNode *x, ExprNode *y)
{
	AST_PRINT_DEBUG("making comparison node");
	ExprNode *new_node = make_EmptyExprNode(op);
	new_node->data_type = unif_comp(x->data_type, y->data_type);
	new_node->first_child = x;
	x->next_sibling = y;
    spread_order(new_node, x);
    spread_order(new_node, y);
    new_node->can_sort = x->can_sort || y->can_sort;
	return new_node;	
}

// || and &&, or search and and search or
ExprNode *make_logicOpNode(ExprNodeType op, ExprNode *x, ExprNode *y)
{
	AST_PRINT_DEBUG("making logical operation node");
	ExprNode *new_node = make_EmptyExprNode(op);
	new_node->data_type = unif_logic(x->data_type, y->data_type);
	new_node->first_child = x;
	x->next_sibling = y;
    spread_order(new_node, x);
    spread_order(new_node, y);
    new_node->can_sort = x->can_sort || y->can_sort;
	return new_node;
}

// +-*/^
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
    spread_order(new_node, x);
    spread_order(new_node, y);
    new_node->can_sort = x->can_sort || y->can_sort;
	return new_node;
}


//Lists of expressions handled as a linked list
//This node becomes parent and all expressions in the list are siblings of the first child
ExprNode *make_exprListNode(ExprNode *data)
{
	AST_PRINT_DEBUG("making expression list");
	ExprNode *list = make_EmptyExprNode(LIST_EXPR);
	list->first_child = data;
    
    ExprNode *child;
    
    for(child = data; child != NULL; child = child->next_sibling)
    {
        spread_order(list, child);
    }
    
	return list;
}





/******* 2.7: user defined functions *******/

//A named expression associates a name with an expression
//It can be used for local variable definitions, or 'as' statements in query projections
//A query projection with no alias name, becomes a NamedExpr with a NULL name.
NamedExprNode *make_NamedExprNode(char *name, ExprNode *expr)
{
	NamedExprNode *new_tuple = malloc(sizeof(NamedExprNode));
	new_tuple->name = name;
	new_tuple->expr = expr;
	new_tuple->next_sibling = NULL;
	new_tuple->order_dep = SAFE_ORDER_DEP(expr);
    new_tuple->sub_order_dep = SAFE_SUB_ORDER_DEP(expr);
	return new_tuple;
}

//A linked list of identifiers...useful for arguments etc
IDListNode *make_IDListNode(char *id, IDListNode *next)
{
	IDListNode *ids = malloc(sizeof(IDListNode));
	ids->name = id;
	ids->next_sibling = next;
	return ids;
}

//Frees this id list node, note that you must store the next pointer and free yourself
void free_single_IDListNode(IDListNode *node)
{
    if(node != NULL)
    {
       AST_PRINT_DEBUG("freeing single_ID");
       AST_PRINT_DEBUG(node->name);
       free(node->name);
       free(node); 
       node = NULL;
    }
    
}

//Chases and frees entire list
void free_IDListNode(IDListNode *list)
{
    IDListNode *to_free, *curr;
    
    curr = list;
    while(curr != NULL)
    {
        to_free = curr;
        curr = curr->next_sibling;
        free_single_IDListNode(to_free);
        to_free = NULL;
    }
}

//We create body node which can hold a query, expression or local variable declaration
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

//UDF Body wrappers for different types of contents
UDFBodyNode *make_UDFExpr(ExprNode *expr)
{
	UDFBodyNode *body_elem = make_UDFEmptyBodyNode(EXPR);
	body_elem->elem.expr = expr;
	return body_elem;
}

UDFBodyNode *make_UDFVardef(NamedExprNode *vardef)
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

//A UDF definition node
UDFDefNode *make_UDFDefNode(char *name, IDListNode *args, UDFBodyNode *body)
{
	UDFDefNode *new_fun = malloc(sizeof(UDFDefNode));
	new_fun->name = name;
	new_fun->args = args;
	new_fun->body = body;
	return new_fun;
}


 /******* 2.3.1: search condition *******/
 /* For the most part we can simply use the expression nodes for search conditions
    The only search-condition specific node (which is still represented as type ExprNode)
    is the predicate node, so we include that below 
 */
ExprNode *make_predNode(char *nm)
{
	AST_PRINT_DEBUG("making search condition predicate node");
	ExprNode *new_node = make_EmptyExprNode(PRED_EXPR);
	new_node->data.str = nm;
	return new_node;
}




 /******* Query related nodes *******/
  /*
    This section does not correspond directly to any specific part of the grammar
    but rather overlaps various sections. We represent queries as a logical query plan.
    This is our attempt of implementing nodes that are akin to relational algebra operators
    For example a query like select c1 from t assuming asc c1 where c2=3  becomes
    projection(c1)-->filter(c2=3)-->sort(asc c1)-->simple_table(t)
    which we can then "plug" into our traditional AST. 

    In traditional relational algebra, this might be something like
        project_c1(select_c2=3(sort_asc-c1(t)))

    Each logical query node is structured to be part of a linked list of query nodes, with deeper nodes representing earlier
    steps. Each node takes a pointer to an arg (the next query node) and has space
    for additional parameters. Additionally, some nodes (like joins) need more than 1 arg
    so there is a next_arg pointer which allow us to chain undetermined amounts of arguments.
 */
    
 /******* Mostly 2.3: Base query  and 2.3.2: table expressions *******/    
    
//Order nodes represent the order specification required for a sort
//The only reason col here is an ExprNode is that we allow dot-access for columns
//in order specifications, which in turn is considered to be an expression.
//This should not cause any issues.
OrderNode *make_OrderNode(OrderNodeType type, ExprNode *col)
{
	OrderNode *new_order = malloc(sizeof(OrderNode));
	new_order->node_type = type;
	new_order->col = col;
	new_order->next = NULL;
	return new_order;
}

void free_OrderNode(OrderNode *order)
{
    OrderNode *to_free = NULL;
    
    while(order != NULL)
    {
        to_free = order;
        order = order->next;
        //TODO: replace with free_ExprNode when written
        free(to_free->col->data.str); //column name
        free(to_free->col); //free expression node
        free(to_free);  //free order node
    }
}

LogicalQueryNode *make_EmptyLogicalQueryNode(LogicalQueryNodeType type)
{	
	AST_PRINT_DEBUG("making logical query node");
	LogicalQueryNode *logical_unit =  malloc(sizeof(LogicalQueryNode));
	logical_unit->node_type = type;
	logical_unit->after = logical_unit->arg = logical_unit->next_arg = NULL;
	logical_unit->order_dep = 0;
	return logical_unit;
} 

LogicalQueryNode *make_table(char *name)
{
	LogicalQueryNode *t = make_EmptyLogicalQueryNode(SIMPLE_TABLE);
	t->params.name = name;
	return t;
}

LogicalQueryNode *make_alias(LogicalQueryNode *t, char *alias)
{
	LogicalQueryNode *aliasing = make_EmptyLogicalQueryNode(ALIAS);
	aliasing->arg = t;
	aliasing->params.name = alias;
	return aliasing;
}


LogicalQueryNode *make_joinOn(LogicalQueryNodeType jointype, LogicalQueryNode *t1, LogicalQueryNode *t2, ExprNode *cond)
{
	LogicalQueryNode *join = make_EmptyLogicalQueryNode(jointype);
	join->arg = t1;
	join->next_arg = t2;
	join->params.exprs = cond;
	join->order_dep = SAFE_ORDER_DEP(cond);
	return join;
}

LogicalQueryNode *make_joinUsing(LogicalQueryNodeType jointype, LogicalQueryNode *t1, LogicalQueryNode *t2, IDListNode *cols)
{
	LogicalQueryNode *join = make_EmptyLogicalQueryNode(jointype);
	join->arg = t1;
	join->next_arg = t2;
	join->params.cols = cols;
	return join;
}

LogicalQueryNode *make_cross(LogicalQueryNode *t1, LogicalQueryNode *t2)
{
	LogicalQueryNode *cross = make_EmptyLogicalQueryNode(CARTESIAN_PROD);
	cross->arg = t1;
	cross->next_arg = t2;
	return cross;
}

LogicalQueryNode *make_filterWhere(LogicalQueryNode *t, ExprNode *conds)
{
	LogicalQueryNode *where = make_EmptyLogicalQueryNode(FILTER_WHERE);
	where->arg = t;
	where->params.exprs = conds;
	where->order_dep = SAFE_ORDER_DEP(conds) | SAFE_SUB_ORDER_DEP(conds);
	return where;
}

LogicalQueryNode *make_filterHaving(LogicalQueryNode *t, ExprNode *conds)
{
	LogicalQueryNode *having = make_EmptyLogicalQueryNode(FILTER_HAVING);
	having->arg = t;
	having->params.exprs = conds;
	having->order_dep = SAFE_ORDER_DEP(conds) | SAFE_SUB_ORDER_DEP(conds);
	return having;
	
}

LogicalQueryNode *make_flatten(LogicalQueryNode *t)
{
	LogicalQueryNode *app = make_EmptyLogicalQueryNode(FLATTEN_FUN);
	app->arg = t;
	return app;
}

LogicalQueryNode *make_project(LogicalQueryNodeType proj_type, LogicalQueryNode *t, NamedExprNode *namedexprs)
{
	LogicalQueryNode *proj = make_EmptyLogicalQueryNode(proj_type);
	proj->arg = t;
	proj->params.namedexprs = namedexprs;
	proj->order_dep = SAFE_ORDER_DEP(namedexprs);
	return proj;
}

LogicalQueryNode *make_delete(LogicalQueryNode *t, IDListNode *cols)
{
	LogicalQueryNode *del = make_EmptyLogicalQueryNode(DELETION);
	del->arg = t;
	del->params.cols = cols;
	return del;
}

LogicalQueryNode *make_groupby(LogicalQueryNode *t, ExprNode *exprs)
{
	LogicalQueryNode *group = make_EmptyLogicalQueryNode(GROUP_BY);
 	group->arg = t;
	group->params.exprs = exprs;
	group->order_dep = SAFE_ORDER_DEP(exprs);
	return group;
}

LogicalQueryNode *make_sort(LogicalQueryNode *t, OrderNode *order)
{
	LogicalQueryNode *sort = make_EmptyLogicalQueryNode(SORT);
	sort->arg = t;
	sort->params.order = order;
	return sort;
}

LogicalQueryNode *make_values(ExprNode *exprs)
{
	LogicalQueryNode *vals = make_EmptyLogicalQueryNode(EXPLICIT_VALUES);
	vals->params.exprs = exprs;
	return vals;
}


//We need a way to send down an argument into the logical query plan
//place RHS within lhs
LogicalQueryNode *pushdown_logical(LogicalQueryNode *lhs, LogicalQueryNode *rhs)
{
	LogicalQueryNode *prev, *curr;
   
    if(lhs == NULL)
    {
        return rhs;
    }
    else if(rhs == NULL)
    {
        return lhs;
    }
    else
    {
   	    for(prev = curr = lhs; curr != NULL; prev = curr, curr = curr->arg)
   	    {
   		/* find empty slot for rhs argument */
   	    } 
        
		prev->arg = rhs;
		rhs->after = prev; //next step in logical plan
		return lhs;
    }
}

//Assembling a naive query plan directly extracted from the syntax
LogicalQueryNode *assemble_base(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
	LogicalQueryNode *plan = from;
	plan = pushdown_logical(order, plan);
	plan = pushdown_logical(where, plan);
	plan = pushdown_logical(grouphaving, plan);
	plan = pushdown_logical(proj, plan);
    return plan;
}

 /******* 2.2: Local and global queries *******/
LocalQueryNode *make_LocalQueryNode(char *name, IDListNode *colnames, LogicalQueryNode *plan)
{
	LocalQueryNode *local_query = malloc(sizeof(LocalQueryNode));
	local_query->name = name;
	local_query->col_names = colnames;
	local_query->query_plan = plan;
	local_query->next_sibling = NULL;
	return local_query;
}

FullQueryNode *make_FullQueryNode(LocalQueryNode *local, LogicalQueryNode *plan)
{
	FullQueryNode *query = malloc(sizeof(FullQueryNode));
	query->local_queries = local;
	query->query_plan = plan;
	return query;
}


/******* Mostly 2.6: update, insert, delete statements and 2.5: table and view creation *******/
  /* Note that some of the 2.6 operations are already handled within
    the logical query section. For example, update consists for the most
    part on similar operations as a select, we simply project in a different fashion
   */

InsertNode *make_insert(LogicalQueryNode *dest, IDListNode *modifier, FullQueryNode *src)
{
	InsertNode *ins= malloc(sizeof(InsertNode));
	ins->dest = dest;
	ins->modifier = modifier;
	ins->src = src;
	return ins;
}

CreateNode *make_createNode(CreateNodeType type, char *name, CreateSourceNode *src)
{
	CreateNode *create = malloc(sizeof(CreateNode));
	create->node_type = type;
	create->name = name;
	create->src = src;
	return create;
}


SchemaNode *make_schemaNode(char *fieldname, char *typename)
{
	SchemaNode *schema = malloc(sizeof(SchemaNode));
	schema->fieldname = fieldname;
	schema->typename = typename;
	schema->next_sibling = NULL;
	return schema;
}

CreateSourceNode *make_schemaSource(SchemaNode *schema)
{
	CreateSourceNode *src = malloc(sizeof(CreateSourceNode));
	src->node_type = SCHEMA_SOURCE;
	src->load.schema = schema;
	return src;
}

CreateSourceNode *make_querySource(FullQueryNode *query)
{
	CreateSourceNode *src = malloc(sizeof(CreateSourceNode));
	src->node_type = QUERY_SOURCE;
	src->load.query = query;
	return src;
}


 /******* 2.1: Top level program definition *******/
TopLevelNode *make_EmptyTopLevelNode(TopLevelNodeType type)
{
	TopLevelNode *node = malloc(sizeof(TopLevelNode));
	node->node_type = type;
	node->next_sibling = NULL;
	return node;
}

TopLevelNode *make_Top_GlobalQuery(FullQueryNode *query, TopLevelNode *next)
{
	TopLevelNode *top = make_EmptyTopLevelNode(GLOBAL_QUERY);
	top->elem.query = query;
	top->next_sibling = next;
	return top;
}

TopLevelNode *make_Top_UDF(UDFDefNode *def, TopLevelNode *next)
{
	TopLevelNode *top = make_EmptyTopLevelNode(UDF_DEF);
	top->elem.udf = def;
	top->next_sibling = next;
	return top;
}

TopLevelNode *make_Top_Create(CreateNode *create, TopLevelNode *next)
{
	TopLevelNode *top = make_EmptyTopLevelNode(CREATE_STMT);
	top->elem.create = create;
	top->next_sibling = next;
	return top;
}

TopLevelNode *make_Top_Insert(InsertNode *ins, TopLevelNode *next)
{
	TopLevelNode *top = make_EmptyTopLevelNode(INSERT_STMT);
	top->elem.insert = ins;
	top->next_sibling = next;
	return top;
}

TopLevelNode *make_Top_UpdateDelete(LogicalQueryNode *ud, TopLevelNode *next)
{
	TopLevelNode *top = make_EmptyTopLevelNode(UPDATE_DELETE_STMT);
	top->elem.updatedelete = ud;
	top->next_sibling = next;
	return top;
}

#if STAND_ALONE
int main()
{
	//Simple expressions
	printf("--->printing an expression\n");
	ExprNode *n1 = make_int(2);
	ExprNode *n2 = make_int(3);
	ExprNode *n3 = make_int(4);
	ExprNode *add = make_arithNode(PLUS_EXPR, n1, n2);
	ExprNode *times = make_arithNode(MULT_EXPR,n3, add);
	print_expr(times, DUMMY, 0, 0);
	
	/*Functions*/
	printf("--->printing an UDF\n");
	//args
	IDListNode *arg2 = make_IDListNode("y", NULL);
	IDListNode *arg1 = make_IDListNode("x", arg2);
	//body
	NamedExprNode *local_var_def = make_NamedExprNode("x", times);
	UDFBodyNode *body1 = make_UDFVardef(local_var_def);
	UDFBodyNode *body2 = make_UDFQuery(NULL);
	body1->next_sibling = body2;
	UDFDefNode *udf = make_UDFDefNode("my_function", arg1, body1);
	print_udf_def(udf);
	
	/* logical query plan */
	printf("--->printing a logical query plan\n");
	LogicalQueryNode *table = make_table("my_table");
	LogicalQueryNode *aliased = make_alias(table, "other_name");
	ExprNode *less_than = make_compNode(LE_EXPR, n1, n2);
	LogicalQueryNode *filter = make_filterWhere(aliased, less_than);
	
	
	return 0;
}
#endif