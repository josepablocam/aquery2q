#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "aquery_types.h"
#include "ast_print.h"

#define STAND_ALONE 0

char *ExprNodeTypeName[]= {
	"const",
	"var",
	"rowid",
	"col.dot.access",
	"all_cols",
	"case_expr",
	"case_clause",
	"case_when",
	"case_when_clause",
	"case_else",
	"call",
	"built-in",
	"udf",
	"index_expr",
	"odd",
	"even",
	"every n",
	"pow",
	"*",
	"/",
	"+",
	"-",
	"<",
	"<=",
	">",
	">=",
	"==",
	"!=",
	"||",
	"&&",
	"expr_list",
	"predicate",
	"AND",
	"OR",
	};

const char* LogicalQueryNodeTypeName[] = {
	"project_select", 
	"project_update", 
	"deletion", 
	"filter_where", 
	"filter_having", 
	"cartesian_prod", 
	"inner_join_on",
	"full_outer_join_on", 
	"inner_join_using", 
	"full_outer_join_using",
	"group_by", 
	"simple_table", 
	"alias", 
	"sort", 
	"flatten", 
	"values"
};

const char* CreateNodeTypeName[] = {
	"create_table",
	"create_view"
};

const char* TopLevelNodeTypeName[] = {
	"global query",
	"udf def",
	"insert stmt",
	"update/delete stmt",
	"create stmt"
};

const char *OrderNodeTypeName[] = {
	"ascending",
	"descending"
};

////////////*************************/////

//Printing in Dot
void print_node(int id, const char *label)
{
	if(label[0] != '"')
	{ //strings need to be handled 
		printf("\t%d [label=\"%s\"];\n", id, label);
	}
	else
	{
		printf("\t%d [label=%s];\n", id, label);
	}
	
}

void print_edge(int src, int dest)
{
	printf("\t%d -> %d;\n", src, dest);
}

int print_self(int parent_id, int *id, const char *label)
{
	int self_id = ++(*id);
	print_node(self_id, label);
	print_edge(parent_id, self_id);
	return self_id;
}


void print_dot(TopLevelNode *prog)
{
	int id = 0;
	printf("digraph a2q{\n");
	print_node(id, "program"); 
	print_top_level(prog, id, &id);
	printf("}\n");
}


void print_top_level(TopLevelNode *top, int parent_id, int *id)
{
	if(top != NULL)
	{
		int self_id = print_self(parent_id, id, TopLevelNodeTypeName[top->node_type]);
	
		//print children
		switch(top->node_type)
		{
			case GLOBAL_QUERY:
				print_full_query(top->elem.query, self_id, id);
				break;
			case UDF_DEF:
				print_udf_def(top->elem.udf, self_id, id);
				break;	
			case CREATE_STMT:
				print_create(top->elem.create, self_id, id);
				break;
			case INSERT_STMT:
				print_insert(top->elem.insert, self_id, id);
				break;
			case UPDATE_DELETE_STMT:
				print_logical_query(top->elem.updatedelete, self_id, id);
				break;
			}
	
		//print sibling nodes
		print_top_level(top->next_sibling, parent_id, id);
	}
}

void print_full_query(FullQueryNode *full, int parent_id, int *id)
{
	if(full != NULL)
	{
		int main_id = print_self(parent_id, id, "Fully Query");
		//Printing local queries
		if(full->local_queries != NULL)
		{
			int local_queries_id = print_self(main_id, id, "local_queries");
			print_local_query(full->local_queries, local_queries_id, id);
		}
		//Print logical query plan for main query
		int plan_id = print_self(main_id, id, "query_plan");
		print_logical_query(full->query_plan, plan_id, id);
	}	
}

void print_local_query(LocalQueryNode *local, int parent_id, int *id)
{
	if(local != NULL)
	{
		int main_id = print_self(parent_id, id, "Local Query");
		//print children
		int name_id = print_self(main_id, id, "name");
		print_name(local->name, name_id, id);
		int cols_id = print_self(main_id, id, "col_names");
		print_id_list(local->col_names, cols_id, id);
		int query_id = print_self(main_id, id, "query_plan");
		print_logical_query(local->query_plan, query_id, id);
		//print next logical query
		print_local_query(local->next_sibling, parent_id, id);		
	}
}

void print_name(const char *name, int parent_id, int *id)
{
	if(name != NULL)
	{
		print_self(parent_id, id, name);
	}
}

void print_id_list(IDListNode *list, int parent_id, int *id)
{
	if(list != NULL)
	{
		print_self(parent_id, id, list->name);
		print_id_list(list->next_sibling, parent_id, id);
	}
}

void print_logical_query(LogicalQueryNode *step, int parent_id, int *id)
{
	if(step != NULL)
	{
		switch(step->node_type)
		{
			case PROJECT_SELECT:
			case PROJECT_UPDATE:
				print_project(step, parent_id, id);
				break;
			case DELETION:
				print_delete(step, parent_id, id);
				break;
			case FILTER_WHERE:
			case FILTER_HAVING:
				print_filter(step, parent_id, id);
				break;
			case CARTESIAN_PROD:
				print_cartesian(step, parent_id, id);
				break;
			case INNER_JOIN_ON:
			case FULL_OUTER_JOIN_ON:
				print_joinOn(step, parent_id, id);
				break;
			case INNER_JOIN_USING:
			case FULL_OUTER_JOIN_USING:
				print_joinUsing(step, parent_id, id);
				break;
			case GROUP_BY:
				print_groupBy(step, parent_id, id);
				break;
			case SIMPLE_TABLE:
				print_table(step, parent_id, id);
				break;
			case ALIAS:
				print_alias(step, parent_id, id);
				break;
			case SORT:
				print_sort(step, parent_id, id);
				break;
			case FLATTEN_FUN:
				print_flatten(step, parent_id, id);
				break;
			case EXPLICIT_VALUES:
				print_values(step, parent_id, id);
		}
		
	}
}			


void print_project(LogicalQueryNode *proj, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[proj->node_type]);
	int cols_id = print_self(self_id, id, "expressions");
	print_named_expr(proj->params.namedexprs, cols_id, id);
	print_logical_query(proj->arg, self_id, id);
}

void print_delete(LogicalQueryNode *del, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[del->node_type]);
	int cols_id = print_self(self_id, id, "cols");
	print_id_list(del->params.cols, cols_id, id);
	print_logical_query(del->arg, self_id, id);
}	

void print_filter(LogicalQueryNode *filter, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[filter->node_type]);
	int conds_id = print_self(self_id, id, "conds");
	print_expr(filter->params.exprs, conds_id, id);
	print_logical_query(filter->arg, self_id, id);
}	

void print_cartesian(LogicalQueryNode *cart, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[cart->node_type]);
	print_logical_query(cart->arg, self_id, id);
	print_logical_query(cart->next_arg, self_id, id);
}

void print_joinOn(LogicalQueryNode *joinOn, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[joinOn->node_type]);
	int conds_id = print_self(self_id, id, "on_conds");
	print_expr(joinOn->params.exprs, conds_id, id);
	print_logical_query(joinOn->arg, self_id, id);
	print_logical_query(joinOn->next_arg, self_id, id);
}

void print_joinUsing(LogicalQueryNode *joinUsing, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[joinUsing->node_type]);
	int cols_id = print_self(self_id, id, "using_cols");
	print_id_list(joinUsing->params.cols, cols_id, id);
	print_logical_query(joinUsing->arg, self_id, id);
	print_logical_query(joinUsing->next_arg, self_id, id);
}

void print_groupBy(LogicalQueryNode *groupBy, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[groupBy->node_type]);
	int groups_id = print_self(self_id, id, "group_exprs");
	print_expr(groupBy->params.exprs, groups_id, id);
	print_logical_query(groupBy->arg, self_id, id);
}

void print_table(LogicalQueryNode *table, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[table->node_type]);
	print_name(table->params.name, self_id, id);
}

void print_alias(LogicalQueryNode *alias, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[alias->node_type]);
	int alias_id = print_self(self_id, id, "aka");
	print_name(alias->params.name, alias_id, id);
	print_logical_query(alias->arg, self_id, id);
}

void print_sort(LogicalQueryNode *sort, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[sort->node_type]);
	int ords_id = print_self(self_id, id, "ordering");
	print_order(sort->params.order, ords_id, id);
	print_logical_query(sort->arg, self_id, id);
}

void print_flatten(LogicalQueryNode *flat, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[flat->node_type]);
	print_logical_query(flat->arg, self_id, id);
}

void print_values(LogicalQueryNode *vals, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, LogicalQueryNodeTypeName[vals->node_type]);
	print_expr(vals->params.exprs, self_id, id);
}

//print expr
void print_expr(ExprNode *expr, int parent_id, int *id)
{
	if(expr != NULL)
	{
		char val[200];
		
		if(expr->node_type == CONSTANT_EXPR || expr->node_type == ID_EXPR)
		{
			if(expr->data_type == INT_TYPE || expr->data_type == BOOLEAN_TYPE)
			{
				sprintf(val,"%d", expr->data.ival);
				int self_id = print_self(parent_id, id, val);
			}
			else if(expr->data_type == FLOAT_TYPE)
			{
				sprintf(val,"%f", expr->data.fval);
				int self_id = print_self(parent_id, id, val);
			}
			else if(expr->data_type == STRING_TYPE || expr->data_type == DATE_TYPE)
			{
				int self_id = print_self(parent_id, id, expr->data.str);
			}
			else
			{
				int self_id = print_self(parent_id, id, expr->data.str);
			}
			
		}
		else
		{
			int self_id = print_self(parent_id, id, ExprNodeTypeName[expr->node_type]);
			print_expr(expr->first_child, self_id, id);
		}
		
		print_expr(expr->next_sibling, parent_id, id);
	}
}



//print named_exprs
void print_named_expr(NamedExprNode *nexpr, int parent_id, int *id)
{
	if(nexpr != NULL)
	{
		int self_id = print_self(parent_id, id, "assign");
		print_name(nexpr->name, self_id, id);
		print_expr(nexpr->expr, self_id, id);
		print_named_expr(nexpr->next_sibling, parent_id, id);
	}
}

void print_order(OrderNode *order, int parent_id, int *id)
{
	if(order != NULL)
	{
		int self_id = print_self(parent_id, id, "ordering");
		print_name(OrderNodeTypeName[order->node_type], self_id, id);
		print_expr(order->col, self_id, id);
		print_order(order->next, self_id, id);
	}
}


void print_udf_def(UDFDefNode *udf, int parent_id, int *id)
{
	int name_id = print_self(parent_id, id, "name");
	print_name(udf->name, name_id, id);
	int args_id = print_self(parent_id, id, "args");
	print_id_list(udf->args, args_id, id);
	int body_id = print_self(parent_id, id, "body");
	print_body(udf->body, body_id, id);
}


void print_body(UDFBodyNode *body, int parent_id, int *id)
{
	if(body != NULL)
	{
		switch(body->node_type)
		{
			case EXPR:
			{
				int expr_id = print_self(parent_id, id, "expr");
				print_expr(body->elem.expr, expr_id, id);
				break;
			}
			case VARDEF:
				print_named_expr(body->elem.vardef, parent_id, id);
				break;
			case QUERY:
				print_full_query(body->elem.query, parent_id, id);
				break;
		}
		
		print_body(body->next_sibling, parent_id, id);	
	}
}

//Create statement
void print_create(CreateNode *cr, int parent_id, int *id)
{
	int self_id = print_self(parent_id, id, CreateNodeTypeName[cr->node_type]);
	int name_id = print_self(self_id, id, "name");
	print_create_source(cr->src, self_id, id);
}

void print_create_source(CreateSourceNode *src, int parent_id, int *id)
{
	int source_id;
	
	switch(src->node_type)
	{
		case SCHEMA_SOURCE:
		{
			int source_id = print_self(parent_id, id, "schema");
			print_schema(src->load.schema, source_id, id);
			break;
		}
		case QUERY_SOURCE:
			print_full_query(src->load.query, parent_id, id);
			break;
	}
}

void print_schema(SchemaNode *elem, int parent_id, int *id)
{
	if(elem != NULL)
	{
		int self_id = print_self(parent_id, id, "schema_elem");
		print_name(elem->fieldname, self_id, id);
		print_name(elem->typename, self_id, id);
		print_schema(elem->next_sibling, parent_id, id);
	}
}

void print_insert(InsertNode *ins, int parent_id, int *id)
{
	int dest_id = print_self(parent_id, id, "destination");
	print_logical_query(ins->dest, dest_id, id);
	
	if(ins->modifier != NULL)
	{
		int mod_id = print_self(parent_id, id, "modifier");
		print_id_list(ins->modifier, mod_id, id);
	}
	print_full_query(ins->src, parent_id, id);
}

//#ifdef STAND_ALONE
//	int main()
//	{
//		print_dot(NULL);
//		return 0;
//	}
//#endif




