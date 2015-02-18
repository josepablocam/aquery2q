/* Building an AST for aquery, builds during the parse traversal in bison */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ast.h"
#include "aquery_types.h"
#include "symtable.h"


ASTNode *make_EmptyNode(NodeType type)
{
	ASTNode *node = malloc(sizeof(ASTNode));
	if(node == NULL)
	{
		printf("Error: unable to allocate AST Node\n");
		exit(1);
	}
	node->first_child = node->first_sibling = NULL;
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


*/



// Expressions
ASTNode *make_int(int i)
{
	ASTNode *node = make_EmptyNode(COMPUTABLE_NODE);
	node->data_type = INT_TYPE;
	node->data.ival = i;
	return node;
}

ASTNode *make_float(float f)
{
	ASTNode *node = make_EmptyNode(COMPUTABLE_NODE);
	node->data_type = FLOAT_TYPE;
	node->data.fval = f;
	return node;
}

ASTNode *make_date(char *date)
{
	ASTNode *node = make_EmptyNode(CONSTANT_NODE);
	node->data_type = DATE_TYPE;
	node->data.date = date; //any memory necessary was already allocated by flex
	return node;
}

ASTNode *make_hex(char *hex)
{
	ASTNode *node = make_EmptyNode(CONSTANT_NODE);
	node->data_type = HEX_TYPE;
	node->data.hex = hex; //any memory necessary was already allocated by flex
	return node;
}

ASTNode *make_bool(int boolean)
{
	ASTNode *node = make_EmptyNode(COMPUTABLE_NODE);
	node->data_type = BOOLEAN_TYPE;
	node->data.ival = boolean; 
	return node;
}

ASTNode *make_oddix()
{
	return make_EmptyNode(ODD_IX);
}

ASTNode *make_evenix()
{
	return make_EmptyNode(ODD_IX);
}

ASTNode *make_intix(int ix)
{
	ASTNode *new_node = make_EmptyNode(INT_IX);
	new_node->data.ival = ix;
	return new_node;
}


//Non-reducible operations
ASTNode *make_valListNode(ASTNode *h, ASTNode *t)
{
	ASTNode *new_node = make_EmptyNode(VAL_LIST);
	new_node->first_child = h;
	h->first_sibling = t;
	return new_node;
}

ASTNode *make_callNode(ASTNode *fun, ASTNode *args)
{
	ASTNode *new_node = make_EmptyNode(CALL_NODE);
	new_node->data_type = UNKNOWN_TYPE;
	new_node->first_child = fun;
		
	if(args != NULL)
	{
		new_node->first_child->first_sibling = args;
	}
	
	if(fun->data_type == ERROR_TYPE)
	{
		new_node->data_type = ERROR_TYPE;
	}
	
	return new_node;	
}

ASTNode *make_builtInFunNode(char *nm)
{
	ASTNode *new_node = make_EmptyNode(BUILT_IN_FUN_NODE);
	new_node->data.str = nm;
	return new_node;
}

ASTNode *make_udfNode(Symtable *symtable, char *nm)
{
	ASTNode *new_node = make_EmptyNode(BUILT_IN_FUN_NODE);
	Symentry *entry = lookup_sym(symtable, nm);
	
	if(entry != NULL && entry->type != FUNCTION_TYPE)
	{
		new_node->data_type = ERROR_TYPE; //TODO: add reporting here....
	}
	
	return new_node;
}

///Case experssions
ASTNode *make_caseNode(ASTNode *case_clause, ASTNode *when_clauses, ASTNode *else_clauses)
{
	ASTNode *new_node = make_EmptyNode(CASE_EXP_NODE);
	
	//TODO: think about this
	if(is_error(case_clause->data_type) || is_error(when_clauses->data_type) || is_error(else_clauses->data_type))
	{
		new_node->data_type = ERROR_TYPE;
	}
	
	new_node->first_child = case_clause;
	case_clause->first_sibling = when_clauses;
	when_clauses->first_sibling = else_clauses;
	
	return new_node;
}

ASTNode *make_caseExpCaseNode(ASTNode *exp)
{
	ASTNode *new_node = make_EmptyNode(CASE_EXP_CASE_NODE);
	new_node->first_child = exp;
	return new_node;
}

ASTNode *make_caseWhenNode(ASTNode *exps)
{
	ASTNode *new_node = make_EmptyNode(CASE_WHEN_NODE);
	new_node->first_child = exps;
	return new_node;
}

ASTNode *make_WhenClausesNode(ASTNode *h, ASTNode *t)
{
	ASTNode *new_node = make_EmptyNode(CASE_WHEN_NODE);
	new_node->first_child = h;
	h->first_sibling = t;
	return new_node;
}

ASTNode *make_elseClauseNode(ASTNode *exp)
{
	ASTNode *new_node = make_EmptyNode(CASE_ELSE_NODE);
	new_node->first_child = exp;
	return new_node;
}

ASTNode *make_rowId()
{
	return make_EmptyNode(ROWID_NODE);
}

ASTNode *make_colDotAccessNode(char *nm)
{
	ASTNode *new_node = make_EmptyNode(ROWID_NODE);
	new_node->data.str = nm;
	return new_node;
}

ASTNode *make_allColsNode()
{
	return make_EmptyNode(ALL_COLS_NODE);
}


//Simple arithmetic expressions
/* Reduceable expressions */
//comparison operations
ASTNode *make_ltNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_comp(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = LT_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.ival = x->data.fval < y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.ival = x->data.fval < y->data.ival;
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.ival = x->data.ival < y->data.fval;
		}
		else
		{
			new_node->data.ival = x->data.ival < y->data.ival;
		}
	} 	
	return new_node;	
}

ASTNode *make_gtNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_comp(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = GT_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.ival = x->data.fval > y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.ival = x->data.fval > y->data.ival;
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.ival = x->data.ival > y->data.fval;
		}
		else
		{
			new_node->data.ival = x->data.ival > y->data.ival;
		}
	} 	
	return new_node;	
}

ASTNode *make_leNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_comp(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = LE_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.ival = x->data.fval <= y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.ival = x->data.fval <= y->data.ival;
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.ival = x->data.ival <= y->data.fval;
		}
		else
		{
			new_node->data.ival = x->data.ival <= y->data.ival;
		}
	} 	
	return new_node;	
}


ASTNode *make_geNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_comp(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = GE_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.ival = x->data.fval >= y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.ival = x->data.fval >= y->data.ival;
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.ival = x->data.ival >= y->data.fval;
		}
		else
		{
			new_node->data.ival = x->data.ival >= y->data.ival;
		}
	} 	
	return new_node;	
}


ASTNode *make_eqNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_comp(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = EQ_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.ival = x->data.fval == y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.ival = x->data.fval == y->data.ival;
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.ival = x->data.ival == y->data.fval;
		}
		else
		{
			new_node->data.ival = x->data.ival == y->data.ival;
		}
	} 	
	return new_node;	
}

ASTNode *make_neqNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_comp(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = NEQ_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.ival = x->data.fval != y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.ival = x->data.fval != y->data.ival;
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.ival = x->data.ival != y->data.fval;
		}
		else
		{
			new_node->data.ival = x->data.ival != y->data.ival;
		}
	} 	
	return new_node;	
}

ASTNode *make_lorNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_logic(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = LOR_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		new_node->data.ival = x->data.ival || y->data.ival;

	} 	
	return new_node;	
}

ASTNode *make_landNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_logic(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_bool(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = LAND_NODE;
		new_node->data_type = unif_override(new_data_type,  BOOLEAN_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{
		new_node->data.ival = x->data.ival && y->data.ival;

	} 	
	return new_node;	
}


//Math operations
//Note: with plus/minus/mult type of outcome depends on operands
//While for exp and div outcome is always a float, regardless of underlying types
ASTNode *make_addNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_numeric(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_numeric(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = ADD_NODE;
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else if(is_float(new_data_type))
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.fval = x->data.fval + y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.fval = x->data.fval + y->data.ival;
		}
		else //is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.fval = x->data.ival + y->data.fval;
		}
	} 
	else 
	{ //this situation only occurs if neither x nor y are floats, so both store in ival
		new_node->data.ival = x->data.ival + y->data.ival;
	}
	
	return new_node;	
}


ASTNode *make_minusNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_numeric(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_numeric(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = MINUS_NODE;
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else if(is_float(new_data_type))
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.fval = x->data.fval - y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.fval = x->data.fval - y->data.ival;
		}
		else //is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.fval = x->data.ival - y->data.fval;
		}
	} 
	else 
	{ //this situation only occurs if neither x nor y are floats, so both store in ival
		new_node->data.ival = x->data.ival - y->data.ival;
	}
	
	return new_node;	
}

ASTNode *make_multNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_numeric(x->data_type, y->data_type);
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_numeric(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = MULT_NODE;
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else if(is_float(new_data_type))
	{
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.fval = x->data.fval * y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.fval = x->data.fval * y->data.ival;
		}
		else //is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.fval = x->data.ival * y->data.fval;
		}
	} 
	else 
	{ //this situation only occurs if neither x nor y are floats, so both store in ival
		new_node->data.ival = x->data.ival * y->data.ival;
	}
	
	return new_node;	
}

ASTNode *make_divNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_numeric(FLOAT_TYPE, unif_numeric(x->data_type, y->data_type));
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_numeric(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = DIV_NODE;
		new_node->data_type = unif_override(new_data_type, FLOAT_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{ 
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.fval = x->data.fval / y->data.fval;
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.fval = x->data.fval / ((float) y->data.ival);
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.fval = ((float) x->data.ival) / y->data.fval;
		}
		else
		{
			new_node->data.fval = ((float) x->data.ival) / ((float)y->data.ival);
		}
	} 

	
	return new_node;	
}


ASTNode *make_expNode(ASTNode *x, ASTNode *y)
{
	ASTNode *new_node = make_EmptyNode(COMPUTABLE_NODE);
	DataType new_data_type = unif_numeric(FLOAT_TYPE, unif_numeric(x->data_type, y->data_type));
	new_node->data_type = new_data_type;
	
	if(!is_computable(x, y) || !is_numeric(new_data_type))
	{ //We cannot compute using this node, or we have unknowns/errors in type
		new_node->node_type = EXP_NODE;
		new_node->data_type = unif_override(new_data_type, FLOAT_TYPE, x->data_type, y->data_type);
		new_node->first_child = x;
		x->first_sibling = y;
	}
	else
	{ //exponetiation always promotes to floating point
		if(is_float(x->data_type) && is_float(y->data_type))
		{
			new_node->data.fval = pow(x->data.fval, y->data.fval);
		}
		else if(is_float(x->data_type) && (is_int(y->data_type) || is_bool(y->data_type)))
		{
			new_node->data.fval = pow(x->data.fval, (float) y->data.ival);
		}
		else if(is_float(y->data_type) && (is_int(x->data_type) || is_bool(x->data_type)))
		{
			new_node->data.fval = pow((float) x->data.ival, y->data.fval);
		}
		else
		{
			new_node->data.fval = pow((float) x->data.ival, (float) y->data.ival);
		}
	} 
	
	return new_node;	
}


//Printing out AST









/* this should be in a type checking file */
int is_computable(ASTNode *x, ASTNode *y)
{
	return x->node_type == COMPUTABLE_NODE && y->node_type == COMPUTABLE_NODE;
}




int main()
{
	ASTNode *n1 = make_int(2);
	ASTNode *n2 = make_int(3);
	ASTNode *r = NULL;
	ASTNode *e = make_expNode(n1, n2);
	printf("%d ^ %d: %f\n", n1->data.ival, n2->data.ival, make_expNode(n1, n2)->data.fval);
	printf("%d / %d: %f\n", n1->data.ival, n2->data.ival, make_divNode(n1, n2)->data.fval);
	printf("%d * %d: %d\n", n1->data.ival, n2->data.ival, make_multNode(n1, n2)->data.fval);
	printf("%d - %d: %d\n", n1->data.ival, n2->data.ival, make_minusNode(n1, n2)->data.ival);
	printf("%d + %d: %d\n", n1->data.ival, n2->data.ival, make_addNode(n1, n2)->data.ival);

	
	return 0;
}







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