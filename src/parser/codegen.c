/* code generation for aquery to q */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symtable.h"

#define print_code(...) fprintf(DEST_FILE, __VA_ARGS__)

/*
 some useful q functions, which we define from the onset
*/

extern FILE DEST_FILE; //file to write out code to
extern Symtable *env; //we use the environment ocassionally
int IN_QUERY = 0; //are we generating code within a query?

//Mapping q and aquery builtins
char *aquery_builtins[] = { "abs", "avg", "avgs", "count", "deltas", "distinct", "drop", "fill", "first", "last", "max", "maxs", 
                            "min", "mins", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "stddev", "make_null" };
                            
char *q_builtins[] = { "abs", "avg", "avgs", "count", "deltas", "distinct", "_", "^", "first", "last", "max", "maxs", 
                        "min", "mins", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "dev", "first 0#" };




void native_comma_enlist()
{
    printf(",");
}

void native_kw_enlist()
{
    printf("enlist ");
}




/*** Constants and Identifiers ***/
void cg_Constant(ExprNode *c)
{
    switch(c->data_type)
    {
        case INT_TYPE:
            print_code("%d", c->data.ival);
            break;
        case FLOAT_TYPE:
            print_code("%f", c->data.fval);
            break;
        case DATE_TYPE:
            print_code("D$\"%s\"", c->data.str); //let q parse date
            break;
        case STRING_TYPE: //become symbols, TODO: char lists?
            print_code("`$\"%s\"", c->data.str);
            break;
        case HEX_TYPE:
            print_code("%s", c->data.str); //already in right format
            break;
        case BOOLEAN_TYPE:
            print_code("%db", c->data.intval); //already stored as 1 or 0
            break;
    }
}

void cg_ID(ExprNode *id)
{
    if(!IN_QUERY)
    { //means we're not in a functional query, so just use id as variable
        print_code("%s", c->data.str);
    }
    else
    { //means we're in functional form, so id in an expression is a column
      //so should be in symbol 
        print_code("`$\"%s\"", c->data.str);
    }
}

void cg_rowId()
{
    print_code("i"); //only in queries, corresponds to q's virtual column i
}

void cg_allColsNode(char *table_name)
{ //can only be used in select, so return a dictionary in q
    print_code("({x!x}cols %s)", table_name);
}


//TODO: case expressions
void aquery_to_q_builtin(char *fun)
{
    int i = 0;
    while(strcmp(aquery_builtins[i], fun) != 0)
    {
        i++; //continue searching
    }
    print_code("%s", q_builtins[i]); //translated to q
}


void cg_callNode(ExprNode *call)
{
    ExprNode *fun = call->first_child;
    ExprNode *args = fun->next_sibling;
    
    if(fun->node_type == BUILT_IN_FUN_CALL)
    { //builtin
        aquery_to_q_builtin("%s", )
    }
    else
    { //UDF
        print_code("%s", fun->data.str);
    }
    
    print_code(";"); //arguments start
    
    if(args == NULL)
    {
        print_code("::"); //null argument
    }
    else
    {
        cg_CallArgList(args); //generate code for argument list
    }
    
}

void cg_CallArgList(ExprNode *arg_list)
{
    ExprNode *curr = arg_list->first_child; //it is a list, take out contents
    ExprNode *next;
    
    while(curr != NULL)
    {
        next = curr->next_sibling; //break link between siblings
        curr->next = NULL;
        
        cg_ExprNode(curr); //generate code for first param
        
        if(next != NULL)
        {
            print_code(";"); //separate from next arg
        }
        
        curr = next; //next argument
    }
}


void cg_OddIx()
{
    print_code("{x where x mod 2 til count x}");
}

void cg_EvenIx(char *name)
{
    print_code("")
}







/******* 2.7: user defined functions *******/
void cg_UDFDefNode(UDFDefNode *fundef)
{
    print_code("%s:{", fundef->name); //assign to function name
    cg_DefArgList(fundef->args); //arguments
    cg_UDFBodyNode(fundef->body); //body
    print_code(" }"); //closing brace must be indented   
}

void cg_DefArgList(IDListNode *args)
{
    IDListNode *curr = args;
    print_code(DEST_FILE, "["); //opening brace for args
    while(curr != NULL)
    {
        print_code(DEST_FILE, "%s", curr->name);
        curr = curr->next;
        if(curr != NULL)
        {
            print_code(";");
        }
        
    }
    print_code(DEST_FILE, "]\n");
}

void cg_UDFBodyNode(UDFBodyNode *body)
{
    if(body != NULL)
    {
		switch(body->node_type)
		{
			case EXPR:
			{
                print_code("eval ");
                cg_ExprNode(body->elem.expr);
				break;
			}
			case VARDEF:
				cg_LocalVar(body->elem.vardef);
				break;
			case QUERY:
                //written in functinoal form, no need for eval
				cg_FullQuery(body->elem.query);
				break;
		}
        
        if(body->next_sibling != NULL)
        {
            print_code(";\n");
            cg_UDFBodyNode(body->next_sibling);
        }
    }
}

void cg_LocalVar(NamedExprNode *vardef)
{
    print_code("%s:eval ", vardef->name); //name to assign to
    cg_ExprNode(vardef->expr);
}

void cg_FullQuery(FullQueryNode *full_query)
{
    print_code("{"); //queries are placed as anonymous functions
    cg_LocalQueries(full_query->local_queries);
    cg_LogicalQueryPlan(full_query->query_plan); //hardest part
    print_code{"}[]"}; //execute function
}

