/* code generation for aquery to q */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtable.h"
#include "codegen.h"


#define print_code(...) fprintf(DEST_FILE, __VA_ARGS__)
#define CG_DEBUG 0
#define CG_PRINT_DEBUG(...) if(CG_DEBUG) printf("---->CG DEBUGGING\n"); if(CG_DEBUG) printf(__VA_ARGS__)


/*
 some useful q functions, which we define from the onset
*/

extern FILE *DEST_FILE; //file to write out code to
extern Symtable *env; //we use the environment ocassionally
int IN_QUERY = 0; //are we generating code within a query?

//Mapping q and aquery builtins
char *aquery_builtins[] = { "abs", "avg", "avgs", "count", "deltas", "distinct", "drop", "fill", "first", "last", "max", "maxs", 
                            "min", "mins", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "sqrt", "stddev", "make_null" };
                            
char *q_builtins[] = { "abs", "avg", "avgs", "count", "deltas", "distinct", "_", "^", "first", "last", "max", "maxs", 
                        "min", "mins", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "sqrt", "dev", "first 0#" };



ExprNodeType aquery_op_types[] = { LT_EXPR, GT_EXPR, LE_EXPR, GE_EXPR, EQ_EXPR, NEQ_EXPR, LOR_EXPR, 
                                  LAND_EXPR, PLUS_EXPR, MINUS_EXPR, MULT_EXPR, DIV_EXPR, POW_EXPR };

char *q_ops[] = { "<", ">", "<=", ">=", "=", "<>", "|",  "&", "+", "-", "*", "%", "xexp" };


void native_comma_enlist()
{
    printf(",");
}

void native_kw_enlist()
{
    printf("enlist ");
}




/*** Constants and Identifiers ***/
void remove_quotes(char **quoted)
{
    (*quoted)++; //remove quote at start
    (*quoted)[strlen(*quoted) - 1] = '\0'; //remove quote at end
}

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
            remove_quotes(&c->data.str);
            print_code("\"D\"$\"%s\"", c->data.str); //let q parse date
            break;
        case STRING_TYPE: //become symbols, TODO: char lists?
            remove_quotes(&c->data.str);
            print_code("`$\"%s\"", c->data.str);
            break;
        case HEX_TYPE:
            print_code("%s", c->data.str); //already in right format
            break;
        case BOOLEAN_TYPE:
            print_code("%db", c->data.ival); //already stored as 1 or 0
            break;
        default:
            CG_PRINT_DEBUG("non-constant in cg_Constant\n");
            exit(1);
    }
}

void cg_ID(ExprNode *id)
{
    if(!IN_QUERY)
    { //means we're not in a functional query, so just use id as variable
        print_code("%s", id->data.str);
    }
    else
    { //means we're in functional form, so id in an expression is a column
      //so should be in symbol 
        print_code("`$\"%s\"", id->data.str);
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
char  *aquery_to_q_builtin(char *fun)
{
    int i = 0;
   
    while(strcmp(aquery_builtins[i], fun) != 0)
    {
        i++; //continue searching
    }
    
    return q_builtins[i];
}


void cg_callNode(ExprNode *call)
{
    CG_PRINT_DEBUG("call node\n");
    ExprNode *fun = call->first_child;
    ExprNode *args = fun->next_sibling;
    
    if(fun->node_type == BUILT_IN_FUN_CALL)
    { //builtin
        print_code("%s", aquery_to_q_builtin(fun->data.str));
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
        cg_ExprNode(args->first_child); //it is a list, take out contents
    }
    
}



void cg_Oddix()
{
    print_code("{x ix where mod[ ;2] ix:til count x}");
}

void cg_Evenix()
{
    print_code("{x ix where not mod[ ;2] ix:til count x}");
}

void cg_Everynix(int everyn)
{ //includes 0 for all, since every 1 should correspond to original vector
    print_code("{x ix where not mod[ ;%d] ix:til count x}", everyn);
}

void cg_indexNode(ExprNode *indexing)
{
    ExprNode *src = indexing->first_child;
    ExprNode *ix = src->next_sibling;
    switch(ix->node_type)
    {
        case ODD_IX:
            cg_Oddix();
            break;
        case EVEN_IX:
            cg_Evenix();
            break;
        case EVERY_N_IX:    
            cg_Everynix(ix->data.ival);
            break;
        default:
            CG_PRINT_DEBUG("undefined index\n");
            exit(1);
    }
    print_code(";");
    src->next_sibling = NULL; //break link with sibling, already generated index code
    cg_ExprNode(src); //generate code
}

void cg_Neg(ExprNode *expr)
{
    print_code("neg");
    print_code(";");
    cg_ExprNode(expr->first_child);
}

char *aquery_to_q_op(ExprNodeType op_type)
{
    int i = 0;
   
    while(aquery_op_types[i] != op_type)
    {
        i++; //keep searching
    }
    
    return q_ops[i];
}


void cg_OpNode(ExprNode *expr)
{  
    CG_PRINT_DEBUG("cg_OpNode\n");
    print_code("%s", aquery_to_q_op(expr->node_type));
    print_code(";");
    cg_ExprNode(expr->first_child);
}


void cg_ExprNode(ExprNode *expr)
{
    if(expr != NULL)
    {
        CG_PRINT_DEBUG("generated expr code\n");
        print_code("(");  
        //generate code for this child
        switch(expr->node_type)
        {
            case CONSTANT_EXPR:
                cg_Constant(expr);
                break;
            case ID_EXPR:
                cg_ID(expr);
                break;
            case ROWID_EXPR:
                cg_rowId();
                break;
            case COLDOTACCESS_EXPR:
                //TODO: column dot access handling.....
                print_code("col_dot_access_code_here");
                break;
            case ALLCOLS_EXPR:
                //TODO: handling all columns
                print_code("all_cols_code_here");
                break;
            case CASE_EXPR:
            case CASE_CLAUSE:
            case CASE_WHEN_CLAUSE:
            case CASE_WHEN_CLAUSES:
            case CASE_ELSE_CLAUSE:
                print_code("case_code_here");
                break; //TODO: handle case clauses
            case CALL_EXPR:
            case BUILT_IN_FUN_CALL:
            case UDF_CALL:
                cg_callNode(expr);
                break;
            case INDEX_EXPR:
            case ODD_IX:
            case EVEN_IX:
            case EVERY_N_IX:
                cg_indexNode(expr);
                break;
            case POW_EXPR:
            case MULT_EXPR:
            case DIV_EXPR:
            case PLUS_EXPR:
            case MINUS_EXPR:
            case LT_EXPR:
            case LE_EXPR:
            case GT_EXPR:
            case GE_EXPR:
            case EQ_EXPR:
            case NEQ_EXPR:
            case LOR_EXPR:
            case LAND_EXPR:
                cg_OpNode(expr);
                break;
            case LIST_EXPR:
                CG_PRINT_DEBUG("ran into an expression list\n");
                exit(1);
            case PRED_EXPR: //TODO: implement predicates
                print_code("predicate_code_here");
                break;
            case WHERE_AND_EXPR: //TODO implement where and
                print_code("where_and_expr_code_here");
                break;
            case WHERE_OR_EXPR: //TODO: implement where or
                print_code("where_or_expr_code_here");
                break;
            case NEG_EXPR:
                cg_Neg(expr);
                break;
        }
        
        print_code(")");  
        if(expr->next_sibling != NULL)
        {
            print_code(";");
            cg_ExprNode(expr->next_sibling);
        }
    
        
    }
}








/******* 2.7: user defined functions *******/
void cg_UDFDefNode(UDFDefNode *fundef)
{
    print_code("%s:{", fundef->name); //assign to function name
    cg_DefArgList(fundef->args); //arguments
    cg_UDFBodyNode(fundef->body); //body
    print_code("\n }"); //on another line for readability, brace be indented for scripts
}

void cg_DefArgList(IDListNode *args)
{
    IDListNode *curr = args;
    print_code("["); //opening brace for args
    while(curr != NULL)
    {
        print_code("%s", curr->name);
        curr = curr->next_sibling;
        
        if(curr != NULL)
        {
            print_code(";");
        }
        
    }
    print_code("]\n");
}

void cg_UDFBodyNode(UDFBodyNode *body)
{
    if(body != NULL)
    {
        print_code("  "); //indent function lines to avoid issues with scripts
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
				//cg_FullQuery(body->elem.query);
				print_code("query_code_here");
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
    print_code("%s:", vardef->name); //name to assign to
    print_code("eval "); //evaluate the expression below
    cg_ExprNode(vardef->expr); //gen code for expression
}

/*
void cg_FullQuery(FullQueryNode *full_query)
{
   print_code("{"); //queries are placed as anonymous functions
    cg_LocalQueries(full_query->local_queries);
    cg_LogicalQueryPlan(full_query->query_plan); //hardest part
    print_code{"}[]"}; //execute function
}
*/

