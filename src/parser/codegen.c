/* code generation for aquery to q */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_print.h"
#include "symtable.h"
#include "codegen.h"


#define print_code(...) if(GEN_CODE) fprintf(DEST_FILE, __VA_ARGS__)
#define GEN_CODE 1
#define CG_DEBUG 0
#define CG_PRINT_DEBUG(...) if(CG_DEBUG) printf("---->CG DEBUGGING\n"); if(CG_DEBUG) printf(__VA_ARGS__)


/*
 some useful q functions, which we define from the onset
*/

extern FILE *DEST_FILE; //file to write out code to
extern Symtable *env; //we use the environment ocassionally
int IN_QUERY = 0; //are we generating code within a query?

//Mapping q and aquery builtins and predicates
char *aquery_builtins[] = { "abs", "avg", "avgs", "avgs", "count", "deltas", "distinct", "drop", "fill", "first", "last", "max", "maxs", "maxs", 
                            "min", "mins", "mins", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "sums", "sqrt", "stddev", "make_null",
                            "not", "is", "between", "in", "like", "null", "overlaps", "enlist"};
                            
char *q_builtins[] = { "abs", "avg", "avgs", "mavg", "count", "deltas", "distinct", "_", "^", "first", "last", "max", "maxs", "mmax", 
                        "min", "mins", "mmin", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "msum", "sqrt", "dev", "first 0#",
                        "not", "::", "within", "in", "{[x;y] x like string y}", "null", "{[x;y] not (x[1]<y[0])|y[1]<x[0]}", "enlist"};
                        
                        
char *aquery_overloads[] = { "avgs", "maxs", "mins", "sums" };
int LEN_OVERLOADS = sizeof(aquery_overloads) / sizeof(char *);

int is_overloaded(char *name)
{
    int i;
        
    for(i = 0; i < LEN_OVERLOADS; i++)
    {
        if(strcmp(name, aquery_overloads[i]) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}


int get_nargs(ExprNode *expr)
{
    int num = 0;
    ExprNode *curr = expr;
    
    while(curr != NULL)
    {
        num++;
        curr = curr->next_sibling;
    }
    
    return num;
}



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
            print_code("enlist `$\"%s\"", c->data.str);
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


void cg_caseExpr(ExprNode *expr)
{
    CG_PRINT_DEBUG("generating code for case expression\n");
    ExprNode *case_clause = expr->first_child;
    ExprNode *when_clauses = case_clause->next_sibling;
    ExprNode *else_clause = when_clauses->next_sibling;
    
    ExprNode *tuple = when_clauses->first_child;
    
    //we've reached our base case, once we've processed all when clauses
    if(tuple == NULL)
    {
        CG_PRINT_DEBUG("generating code for else statement\n");
        cg_ExprNode(else_clause->first_child);
    }
    else
    {
        ExprNode *when_clause = tuple->first_child;
        ExprNode *then_clause = when_clause->next_sibling;
        when_clause->next_sibling = NULL; //break link for code generation
        
        //is this a simple case expr (case x when 2 then ble when 3 then meh..)
        //or is it a searched case expression(case when x>2 then bleh)
        int is_simple_case = case_clause->first_child != NULL;
        print_code("?;");
        
        if(is_simple_case)
        { //generate code for implicit equality comparison
          //TODO: think about how to memoize this!
           //int x = 0;
           CG_PRINT_DEBUG("case clause:\n");
           //print_expr(case_clause->first_child, x, &x);
           
           CG_PRINT_DEBUG("when clause:\n");
           //print_expr(when_clause, x, &x);
           
           
           CG_PRINT_DEBUG("generating code for simple case expression\n");
           print_code("(=;"); 
           cg_ExprNode(case_clause->first_child);  //this implies we reevaluate every time, so be careful 
           print_code(";"); 
           cg_ExprNode(when_clause); //simply an expression
           print_code(")");
        }
        else
        {
            CG_PRINT_DEBUG("generating code for searched case expression\n");
            cg_ExprNode(when_clause);
        }
        
        print_code(";"); 
        //generate code for consequence
        cg_ExprNode(then_clause);
        print_code(";");
        
        //adjust cases to remove the case-consequence pair handled
        ExprNode *next_tuple= tuple->next_sibling;
        //free_ExprNode(tuple); TODO: free this node
        when_clauses->first_child = next_tuple;
        
        cg_ExprNode(expr); //call recursively, so that multiple cases become nested vector conditionals
    }
}




int aquery_to_q_builtin_ix(char *fun)
{
    int i = 0;
   
    while(strcmp(aquery_builtins[i], fun) != 0)
    {
        i++; //continue searching
    }
    
    return i;
}


void cg_callNode(ExprNode *call)
{
    CG_PRINT_DEBUG("call node\n");
    ExprNode *fun = call->first_child;
    ExprNode *args = fun->next_sibling;
    
    if(fun->node_type == BUILT_IN_FUN_CALL || fun->node_type == PRED_EXPR)
    { //builtin
        int fun_ix = aquery_to_q_builtin_ix(fun->data.str);
        char *fun_nm = aquery_builtins[fun_ix];
        
        if(!is_overloaded(fun_nm))
        {
            print_code("%s", q_builtins[fun_ix]); //nothing to disambiguate
        }
        else
        {
            int num_args = get_nargs(args->first_child); //use # of args to resolve
            int offset = (num_args == 1) ? 0 : 1;
            print_code("%s", q_builtins[fun_ix + offset]); //organized so that the 2 argument overload comes after
        } 
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

void cg_ExprList(ExprNode *expr)
{
    print_code("enlist;");
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
                cg_caseExpr(expr);
                break;
            case CALL_EXPR:
            case BUILT_IN_FUN_CALL:
            case UDF_CALL:
            case PRED_EXPR: //predicates are handled like calls
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
                cg_ExprList(expr);
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

