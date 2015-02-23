#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "aquery_types.h"
#include "ast_print.h"

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
	"pred_expr",
	"where_and_expr",
	"where_or_expr",
	"dummy"
	};

const char* UDFBodyNodeTypeName[] = {
	"UDF_body_expr",
	"UDF_var_def",
	"UDF_query"
};


const char* LogicalQueryNodeTypeName[] = {
	"PROJECT_SELECT", 
	"PROJECT_UPDATE", 
	"DELETION", 
	"FILTER_WHERE", 
	"FILTER_HAVING", 
	"CARTESIAN_PROD", 
	"INNER_JOIN_ON",
	"FULL_OUTER_JOIN_ON", 
	"INNER_JOIN_USING", 
	"FULL_OUTER_JOIN_USING",
	"GROUP", 
	"SIMPLE_TABLE", 
	"ALIAS", 
	"SORT", 
	"FLATTEN_FUN", 
	"EXPLICIT_VALUES"
};

const char* CreateNodeTypeName[] = {
	"CREATE_TABLE",
	"CREATE_VIEW"
};




//Printing Expressions
void print_expr(ExprNode *n, ExprNodeType p, int type, int indent)
{
	
	if(n != NULL)
	{
		
			
		if(n->node_type == CONSTANT_EXPR)
		{
			if(n->data_type == INT_TYPE || n->data_type == BOOLEAN_TYPE)
			{
				printf("%*s%d", indent,"", n->data.ival);
			}
			else if(n->data_type == FLOAT_TYPE)
			{
				printf("%*s%f", indent,"", n->data.fval);
			}
			else
			{
				printf("%*s%s", indent,"", n->data.str);
			}
		}
		else
		{
			printf("%*s%s", indent, "", ExprNodeTypeName[n->node_type]);
		}
		printf(" coming from %s as %s\n", ExprNodeTypeName[p], (type == 0) ? "parent" : "sibling");
		print_expr(n->first_child, n->node_type , 0, indent + 5);
		print_expr(n->next_sibling, n->node_type, 1, indent);	
		
	}
}


//Printing UDF definitions
void print_udf_def(UDFDefNode *udf)
{
	printf("Defining UDF:%s\n", udf->name);
	print_udf_args(udf->args, 0);
	print_udf_body(udf->body);
}

void print_udf_args(IDListNode *args, int ct)
{
	if(args != NULL)
	{
		printf("w/ arg #%d:%s\n", ct, args->name);
		print_udf_args(args->next_sibling, ct + 1);
	}
}

void print_udf_body(UDFBodyNode *body)
{
	
	if(body != NULL)
	{	
		printf("%s\n", UDFBodyNodeTypeName[body->node_type]);
		switch(body->node_type)
		{
			case EXPR:
				print_expr(body->elem.expr, DUMMY, 0, 0);
				break;
			case VARDEF:
				print_var_def(body->elem.vardef);
				break;
			case QUERY:
				printf("A query\n");
				break;
				//TODO: print_query(body->elem.query);
		}
		print_udf_body(body->next_sibling);
	}
}


void print_var_def(LocalVarDefNode *vardef)
{
	printf("%s as ", vardef->name); 	
	print_expr(vardef->expr, DUMMY, 0, 5);
	
	putchar('\n');
}


void print_logical_query(LogicalQueryNode *l)
{
	printf("--->%s at %d\n", LogicalQueryNodeTypeName[l->node_type], l);
	if(l->arg != NULL) print_logical_query(l->arg);
	if(l->next_arg != NULL) print_logical_query(l->next_arg);
}

void print_full_query(FullQueryNode *full)
{
	printf("--->full query node\n");
	if(full != NULL)
	{
		printf("local queries\n");
		print_local_queries(full->local_queries);
		printf("main query\n");
		print_logical_query(full->query_plan);
	}
	
}

void print_local_queries(LocalQueryNode *local)
{
	if(local != NULL)
	{
		printf("-->local query node\n");
		printf("local table:%s\n", local->name);
		//skipping column names
		print_logical_query(local->query_plan);
		print_local_queries(local->next_sibling);
	}
}

void print_create(CreateNode *create)
{
	printf("--->%s with name %s at %d\n", CreateNodeTypeName[create->node_type], create->name, create);
	print_create_source(create->src);
}

void print_create_source(CreateSourceNode *src)
{
	printf("--->source\n");
	//printf("source is null:%d\n", src == NULL);
	if(src->node_type == SCHEMA_SOURCE)
	{
		print_schema(src->load.schema);
	}
	else
	{
		print_full_query(src->load.query);
	}
}

void print_schema(SchemaNode *schema)
{
	printf("schema goes here\n");
}

void print_top_level(TopLevelNode *top)
{
	if(top != NULL)
	{
		printf("------>****top level element*****\n");
		switch(top->node_type)
		{
			case GLOBAL_QUERY:
				print_full_query(top->elem.query);
				break;
			case UDF_DEF:
				print_udf_def(top->elem.udf);
				break;	
			case CREATE_STMT:
				print_create(top->elem.create);
				break;
			case INSERT_STMT:
				print_insert(top->elem.insert);
				break;
			case UPDATE_DELETE_STMT:
				print_logical_query(top->elem.updatedelete);
				break;
		}
		
		print_top_level(top->next_sibling);
	}
}


void print_insert(InsertNode *ins)
{
	printf("Insert statement\n");
	print_logical_query(ins->dest);
	print_id_list(ins->modifier);
	print_full_query(ins->src);
}


void print_id_list(IDListNode *ids)
{
	IDListNode *curr = ids;
	
	while(curr != NULL)
	{
		printf("id: %s\n", curr->name);
		curr = curr->next_sibling;
	}
}

