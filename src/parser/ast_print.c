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
	"search_exp",
	"dummy"
	};

const char* UDFBodyNodeTypeName[] = {
	"UDF_body_expr",
	"UDF_var_def",
	"UDF_query"
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

void print_udf_args(UDFArgsNode *args, int ct)
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




