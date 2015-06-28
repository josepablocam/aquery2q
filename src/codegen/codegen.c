/* code generation for aquery to q */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../ast/ast.h"
#include "../ast/ast_print.h"
#include "../parser/symtable.h"
#include "../optimizer/optimizer.h"
#include "codegen.h"


#define print_code(...) if(GEN_CODE) fprintf(DEST_FILE, __VA_ARGS__)
//#define GEN_CODE 1
#define CG_DEBUG 0
#define CG_PRINT_DEBUG(...) if(CG_DEBUG) printf("---->CG DEBUGGING\n"); if(CG_DEBUG) printf(__VA_ARGS__)
#define AQ_VER "1.0"
#define AQ_MAINT "jpc485@nyu.edu"




extern int GEN_CODE;
extern FILE *DEST_FILE; //file to write out code to
extern Symtable *env; //we use the environment ocassionally
int IN_QUERY = 0; //are we generating code within a query?
int TABLE_CT = 1; //used to generate intermediate names for aquery tables, reset every function
int QUERY_CT = 0; //used to name the functions that contain queries


//Mapping q and aquery builtins and predicates
char *aquery_builtins[] = { "abs", "avg", "avgs", "avgs", "count", "deltas", "distinct", "drop", "fill", "first", "first", "last", "last", "max", "maxs", "maxs", 
                            "min", "mins", "mins", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "sums", "sqrt", "stddev", "make_null",
                            "not", "is", "between", "in", "like", "null", "overlaps", "enlist"};
                            
char *q_builtins[] = { "abs", "avg", "avgs", "mavg", "count", "deltas", "distinct", "_", "^", "first", "sublist", "last", ".aq.negsublist", "max", "maxs", "mmax", 
                        "min", "mins", "mmin", "mod", "next", "prev", "prd", "prds", "reverse", "sum", "sums", "msum", "sqrt", "dev", "first 0#",
                        "not", "::", "within", "in", "{[x;y] x like string y}", "null", "{[x;y] not (x[1]<y[0])|y[1]<x[0]}", "enlist"};
                        
                        
char *aquery_overloads[] = { "avgs", "maxs", "mins", "sums" , "first", "last"};
int LEN_OVERLOADS = sizeof(aquery_overloads) / sizeof(char *);


/* Aquery data structures for code generation */
char *AQ_COL_NM = "aq__";
char *AQ_TABLE_NM = ".aq.t";
char *AQ_COL_DICT = ".aq.cd"; //mapping of column names (A(c1) creates entries as c1 -> A__c1, A.c1 -> A__c1)
char *AQ_COL_LIST = ".aq.pc"; //prior columns involved, used to detect conflicts
char *AQ_COL_DELIM = "__";
char *AQ_TABLE_DICT = ".aq.ct";
char *AQ_SORT_IX = ".aq.six";
char *AQ_QUERY_NM = ".aq.q";
char *AQ_JOIN_USING_INFO = ".aq.jui";
char *AQ_CHECK_ATTR = ".aq.chkattr";
char *AQ_GROUPED_EXPR = ".aq.grpexpr"; // keep track of what the group by has, to avoid recalc in projection



//generate some aquery functions into the file
void init_aq_helpers()
{
    print_code("// Code generated by a2q version %s please report any bugs to %s\n",AQ_VER, AQ_MAINT);
    print_code(
        "// ***** Aquery utilities ***** ///\n"
        "//table related\n"
        );
    //generate column name dictionary
    print_code(".aq.gencd:{[t;sn] ((`$(sn,\".\"),/:sc),c)!(2*count c)#`$(sn,\"%s\"),/:sc:string c:cols t}\n", AQ_COL_DELIM);
    //rename columns to aquery column name standard
    print_code(".aq.rcols:{[t;p] (`$(p,\"%s\"),/:string cols t) xcol t};\n", AQ_COL_DELIM);
    //collect information about column names for a JOIN USING
    print_code(".aq.ju:{[cs;j] $[2<>count m:cs where cs like \"*%s\",s:string j;'\"ambig-join:\",s;`rename`remap!(m!2#n;((%s?m),j)!(1+count m)#n:`$\"_\"sv string m)]}\n", AQ_COL_DELIM, AQ_COL_DICT);
    
    print_code(
        ".aq.scbix:{[v] m[`c] iasc `s`p`g`u?(m:0!meta v)`a}; //sort column names by attribute\n"
        ".aq.swix:{[v;w] w iasc .aq.scbix[v]?w@'where each type[`]=(type each) each w} //sort where clause by attributes of cols used\n"
        ".aq.negsublist:{[x;y] neg[x] sublist y}\n"
        ".aq.chkattr:{[x;t] any (.aq.cd where any each flip .aq.cd like/: \"*\",/:string (),x) in exec c from meta t where not null a}\n"    
        ".aq.acctgrps:{[p;g] @[p;key[p] ix;:;key[g] ix:where any each value[p]~/:\\:vg:value g]}\n"
        "\n\n"
        "// Start of code\n"
    );
}

//add to the column dictionary
void add_to_dc(char *tbl, char *alias)
{
    print_code(" %s:{(key[y] inter %s) _ x,y}[%s;.aq.gencd[%s;\"%s\"]]; //drop ambiguous cols from map\n", AQ_COL_DICT, AQ_COL_LIST, AQ_COL_DICT, tbl, alias);
    print_code(" %s:%s union cols %s; //store orig col names to avoid collisions\n",AQ_COL_LIST, AQ_COL_LIST, tbl); //store down table column
}

void cols_to_Aquery(char *new, char *t, char *p)
{
    print_code(" %s:.aq.rcols[%s;\"%s\"]; //rename cols to t__c format\n", new, t, p);
}

//initialize our column dictionary
void init_dc()
{
    print_code(" %s:(); //init col names list\n", AQ_COL_LIST);
    print_code(" %s:(`$())!`$(); //init col names map\n", AQ_COL_DICT);
    print_code(" %s:(`$())!(); //init grouped expr map\n", AQ_GROUPED_EXPR);
}

//add entry to table dictionary
//used to trace information about underlying q name
//e.g. say t1 has a foreign key into t
//t0:filter(t); ej[t0;t1]; 
//we would like to avoid the join, since t1 has a foreign key, we should just use that
//however, that means we need to know that t0 is really a transformation of t
//TODO: we need to use this but unsure about implications
//e.g. what if we group t0, that is not really t any more
//perhaps that kind of action should remove that key from the dictionary?
void add_to_dt(char *alias, char *tbl)
{
    print_code(" %s[`%s]:%s;\n", AQ_TABLE_DICT, alias, tbl);
}

//order column names so that those with a faster index come first
void sort_where_clause_by_ix(char *tbl)
{
    print_code(" .aq.swix[%s;] ", tbl);
}

//account for pre-computed group expressions when projecting
//e.g. if you calculated 2 + c1 as a group by, and then your projection has an element
// 2 + c1 as ..., then you should not compute 2 + c1 again, but just taking the value of the grouped
//column. This solves having to apply first to get it in atom form. Matches up with mysql semantics
//and avoid unnecessary recomputing. This is done by explicitly checking the value in a dictionary
//used for projection with equality with the value in a dictionary used for grouping. So x + 2 is
//different from 2 + x
void acct_for_computed_groupBys() {
    print_code(" .aq.acctgrps[ ; %s]", AQ_GROUPED_EXPR); // done as projected q function
}


//issue 'each' needed to handle nested vectors
void poss_add_each(ExprNode *expr)
{
    if(expr->is_grouped)
    {
        print_code("'"); //each
    }
}


//generates a locally fresh name for an aquery intermediate table
//caller has responsibility of freeing when done with name...
char *gen_table_nm()
{
    int num_ints = ((int) log((double) TABLE_CT)) + 1;
    char *nm = malloc((strlen(AQ_TABLE_NM) + num_ints + 1) * sizeof(char));
    sprintf(nm, "%s%d", AQ_TABLE_NM, TABLE_CT);
    TABLE_CT++;
    return nm;
}


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


int ct_exprs(ExprNode *expr)
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
                                  LAND_EXPR, PLUS_EXPR, MINUS_EXPR, MULT_EXPR, DIV_EXPR, POW_EXPR, WHERE_OR_EXPR };

char *q_ops[] = { "<", ">", "<=", ">=", "=", "<>", "|",  "&", "+", "-", "*", "%", "xexp", "|" };


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

void cg_LookupCol(char *nm)
{
    print_code("{x^%s x}", AQ_COL_DICT);
    print_code("`%s",nm);
}


void cg_ID(ExprNode *id)
{
    if(!IN_QUERY)
    { //means we're not in a functional query, so just use id as variable
        print_code("%s", id->data.str);
    }
    else
    { //means we're in functional form, look up in column dictionary
     // this in turn means that if a function has the same name as a column
    //the columns masks the function, as happens in q usually
        cg_LookupCol(id->data.str);
    }
}

void cg_rowId()
{
    if(IN_QUERY)
    {
        print_code("`i"); //only in queries, corresponds to q's virtual column i
    }
    else
    {
       printf("\nERROR:ROWID can only be used in queries\n");
       exit(1); 
    }
    
}

void cg_allCols(char *table_name)
{ //can only be used in select, so return a dictionary in q
    if(IN_QUERY)
    {
        print_code("({x!x}cols %s)", table_name);
    }
    else
    {
        printf("\nERROR:asterisk for columns can only be used in queries\n");
        exit(1);
    }
}

void cg_colDotAccess(ExprNode *access)
{
    char *tbl = access->first_child->data.str;
    char *col = access->first_child->next_sibling->data.str;
    
    if(IN_QUERY)
    {
        print_code("({x^%s x}", AQ_COL_DICT);
        print_code("`%s.%s)", tbl, col);
    }
    else
    {
        printf("\nERROR:correlation name access can only be used in queries\n");
        printf("\tOffender:%s.%s\n", tbl, col);
        exit(1);
    }
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
        print_code("("); 
        
        print_code("?");
        poss_add_each(expr);
        print_code(";");
        
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
        print_code(")");
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
    
    print_code("(");
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
            int num_args = ct_exprs(args->first_child); //use # of args to resolve
            int offset = (num_args == 1) ? 0 : 1;
            print_code("%s", q_builtins[fun_ix + offset]); //organized so that the 2 argument overload comes after
        } 
    }
    else
    { //UDF
        print_code("%s", fun->data.str);
    }
    
    poss_add_each(call);
    print_code(";"); //arguments start
    
    if(args == NULL)
    {
        print_code("::"); //null argument
    }
    else
    {
        cg_ExprNode(args->first_child); //it is a list, take out contents
    }
    print_code(")");
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
    print_code("(");
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
    
    poss_add_each(indexing);
    print_code(";");
    src->next_sibling = NULL; //break link with sibling, already generated index code
    cg_ExprNode(src); //generate code
    print_code(")");
}

void cg_Neg(ExprNode *expr)
{
    print_code("(");
    print_code("neg"); //no need for each, neg is atomic
    print_code(";");
    cg_ExprNode(expr->first_child);
    print_code(")");
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
    print_code("(");
    print_code("%s", aquery_to_q_op(expr->node_type)); //no need for each, operators are atomic
    print_code(";");
    cg_ExprNode(expr->first_child);
    print_code(")");
}

void cg_ExprList(ExprNode *expr)
{
    print_code("(");
    print_code("enlist;");
    cg_ExprNode(expr->first_child);
    print_code(")");
}


void cg_ExprNode(ExprNode *expr)
{
    if(expr != NULL)
    {
        CG_PRINT_DEBUG("generated expr code\n");
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
                cg_colDotAccess(expr);
                break;
            case ALLCOLS_EXPR:
                //TODO: handling all columns
                printf("\nERROR:* for now just implemented in queries as standalone, use ROWID or alternative column name\n");
                printf("\tfor things like count(*)\n");
                exit(1);
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
            case WHERE_AND_EXPR: //TODO: remove this type of node, deprecated
                //print_code("where_and_expr_code_here");
                printf("Reached deprecated WHERE_AND_EXPR node in AST, exiting\n");
                exit(1);
                break;
            case WHERE_OR_EXPR: 
                cg_OpNode(expr);
                break;
            case NEG_EXPR:
                cg_Neg(expr);
                break;
        }
        
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
    print_code("\n }\n"); //on another line for readability, brace be indented for scripts
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


/* Logical Query Plans */

char *cg_SimpleTable(LogicalQueryNode *node)
{
    char *new_name = gen_table_nm();
    char *orig_name = node->params.name;
    //add column mappings
    add_to_dc(orig_name, orig_name);
    //rename cols
    cols_to_Aquery(new_name, orig_name, orig_name);
    return new_name;
}

// char *cg_Alias(LogicalQueryNode *node)
// {
//     char *orig_name = node->arg->params.name;
//     char *alias_name = node->params.name;
//     add_to_dc(alias_name, orig_name);
//     //print_code("%s:%s\n", alias_name, orig_name); do we need this?
//     //free(orig_name);
//     return orig_name;
// }

char *cg_Alias(LogicalQueryNode *node)
{
    char *orig_name = node->arg->params.name;
    char *alias_name = node->params.name;
    char *new_name = gen_table_nm();
    //add column mappings
    add_to_dc(orig_name, alias_name);
    //rename cols
    cols_to_Aquery(new_name, orig_name, alias_name);
    return new_name;
}

//TODO: joins of all sorts....
//TODO: place clauses that have best index first, to take advantage
char *cg_FilterWhere(LogicalQueryNode *where)
{
    char *t1 = cg_LogicalQueryNode(where->arg);
    char *t2 = gen_table_nm();
    print_code(" %s:", t2);
    cg_FilterWhere0(where->params.exprs, t1);
    print_code(";\n");
    free(t1);
    return t2;  
}


void cg_FilterWhere0(ExprNode *selection, char *from)
{
    int n_conds = ct_exprs(selection);
    
    print_code("?[%s;", from);

    if(n_conds == 1)
    { //clauses of 1 element need to be enlisted
        print_code("enlist ");
        cg_ExprNode(selection);
    }
    else
    {
        sort_where_clause_by_ix(from);
        print_code("(");
        cg_ExprNode(selection);
        print_code(")");
    }
    

    print_code(";0b;()]");    
}

//TODO: need to account for grouping!!!
char *cg_ProjectSelect(LogicalQueryNode *proj)
{
    char *t1 = cg_LogicalQueryNode(proj->arg);
    char *t2 = gen_table_nm();
    print_code(" %s:?[%s;();0b;", t2, t1);
    acct_for_computed_groupBys();
    cg_NameExprTuples(t1, proj->params.namedexprs, 0);
    print_code("];\n");
    free(t1);
    return t2;
}



//TODO: make name resolution better, imitate q's
void cg_NameExprTuples(char *tblnm, NamedExprNode *nexpr, int id_ctr)
{
    NamedExprNode *next_nexpr = nexpr->next_sibling;
    char *col_nm = nexpr->name;
    ExprNode *expr = nexpr->expr;

    if(expr->node_type == ALLCOLS_EXPR)
    { //asterisk needs to be handled differently
        cg_allCols(tblnm);
    }
    else
    {
        print_code("(enlist[`");
        if(col_nm != NULL)
        {
            print_code("%s", col_nm);
        }
        else
        {
            print_code("x__%d", id_ctr++);
        }
        print_code("]!enlist ");
        cg_ExprNode(nexpr->expr);
        print_code(")"); 
    }

    if(next_nexpr != NULL)
    {
        print_code(",");
        cg_NameExprTuples(tblnm, next_nexpr, id_ctr);
    }
}


//Sorting whole table, naive, and is only here in case people want to generated code
//without the optimizations, for comparison purposes, or readability
//TODO: it seems that the table using an index
//is significantly faster than the built in `c1 xasc `c2 etc
//so it might be worth changing this to that.....
//first run some experiments though to make sure this is true (generally)
char *cg_Sort(LogicalQueryNode *node)
{
    char *t1 = cg_LogicalQueryNode(node->arg);
    char *t2 = gen_table_nm();
    print_code(" %s:", t2);
    cg_SimpleOrder(node->params.order); //`c1 xasc `c2 xdesc ....
    print_code("%s;\n", t1);
    free(t1);
    return t2;
}



void cg_orderVerb(OrderNodeType type)
{
    if(type == ASC_SORT)
    {
        print_code(" xasc ");
    }
    else
    {
        print_code(" xdesc ");
    }
}

void cg_orderIxVerb(OrderNodeType type)
{
    if(type == ASC_SORT)
    {
        print_code("iasc");
    }
    else
    {
        print_code("idesc");
    }
}


void cg_SimpleOrder(OrderNode *ordnode)
{
    if(ordnode != NULL)
    {
        print_code("(");
        cg_ExprNode(ordnode->col);
        print_code(")");
        cg_orderVerb(ordnode->node_type);
        cg_SimpleOrder(ordnode->next);
    }
}


//Optimized sort: calculate the sort index and only apply to columns that need it
char *cg_SortCols(LogicalQueryNode *node)
{
    char *t1 = cg_LogicalQueryNode(node->arg);
    char *t2 = gen_table_nm();
    
    print_code(" %s:?[%s;();();", AQ_SORT_IX, t1); //assign to our sorting index
    cg_SortIx(node->params.order); //generate index code
    print_code("];\n");
    
    //Now for each column in node->next_arg, generate a dictionary
    //of enlist[`col_name]!enlist(`col_name; .aq.six)  
    IDListNode *curr_col = node->next_arg->params.cols;
    print_code(" %s:![%s;();0b;", t2, t1);
    while(curr_col != NULL)
    {
        print_code("(enlist[");
        cg_LookupCol(curr_col->name); //want to make sure column mappings are preserved
        print_code("]!enlist (");
        cg_LookupCol(curr_col->name);
        print_code("; %s", AQ_SORT_IX);
        print_code("))");
        
        curr_col = curr_col->next_sibling;
        if(curr_col != NULL)
        {
            print_code(",");
        }
        
    }
    print_code("];\n");
    
    free(t1);
    return t2; 
}

void cg_SortIx(OrderNode *ordnode)
{
    OrderNode *curr_order = ordnode;
    OrderNode *next_order = NULL;
    
    if(curr_order != NULL)
    {
        next_order = curr_order->next;
        
        if(next_order == NULL)
        { //use iasc/idesc directly if this is the deepest sorting
            print_code("(");
            cg_orderIxVerb(curr_order->node_type);
            print_code(";");
            cg_ExprNode(curr_order->col);
            print_code(")");
        }
        else
        {
            print_code("(");
            print_code("{y ");
            cg_orderIxVerb(curr_order->node_type);
            print_code(" x y};");
            cg_ExprNode(curr_order->col);
            print_code(";");
            cg_SortIx(next_order);
            print_code(")");
        }
    }
}


char *cg_groupBy(LogicalQueryNode *node)
{
    char *t1 = cg_LogicalQueryNode(node->arg);
    char *t2 = gen_table_nm();
    NamedExprNode *named_groups = groupExpr_to_NamedGroupExpr(node->params.exprs->first_child); //expressions are in list container, so take out with ->first_child
    print_code(" %s:?[%s;();", t2, t1);
    print_code("%s:", AQ_GROUPED_EXPR); //store the group by expression info
    cg_NameExprTuples(t1, named_groups, 0);
    print_code(";");
    cg_allCols(t1); //generate dict of all column names
    print_code("];\n");
    free(t1);
    free_NamedExprNode(named_groups);
    return t2;
}


NamedExprNode *groupExpr_to_NamedGroupExpr(ExprNode *exprs)
{
    ExprNode *curr = exprs;
    ExprNode *next = NULL;
    NamedExprNode *nexprs = NULL;
    NamedExprNode *named = NULL;
    NamedExprNode *prev = NULL;
    char *temp_name = NULL;
    int temp_name_len = 0;
    int col_ct = 1;
    
    while(curr != NULL)
    {
        next = curr->next_sibling; //store sibling
        curr->next_sibling = NULL; //remove link to sibling expression (want each group-by expression separately)
        
        temp_name_len = ((int) log((double) col_ct)) + 1 + strlen(AQ_COL_NM);
        temp_name = malloc((temp_name_len + 1) * sizeof(char));
        sprintf(temp_name, "%s%d", AQ_COL_NM, col_ct);
        
        named = make_NamedExprNode(temp_name, curr);
        
        if(nexprs == NULL)
        {
            
            nexprs = named; //this is the start of our named expression list
            prev = nexprs; //store separately so that we can advance along the list and always add to end
        }
        else
        {
            prev->next_sibling = named; //add in the next element
            prev = named; //make this the end of the list
        }
        
        curr = next;
        col_ct++;
    }
    
    return nexprs;
}

char *cg_flatten(LogicalQueryNode *node)
{
    char *t1 = cg_LogicalQueryNode(node->arg);
    char *t2 = gen_table_nm();
    print_code(" %s:ungroup %s;\n", t2, t1);
    free(t1);
    return t2;
}


char *cg_queryPlan(LogicalQueryNode *node)
{
    IN_QUERY = 1; //turn on our flag for query 
    init_dc(); //initialize our dictionary that keeps track of column names
    return cg_LogicalQueryNode(node); //generate query plan and return table name
}


/* JOINS */
//inner join using -> the simpliest
void cg_colList(IDListNode *cols)
{
    IDListNode *curr = cols;
    
    while(curr != NULL)
    {
        print_code("`%s", curr->name);
        curr = curr->next_sibling;
    }
}

void cg_PrepareJoinUsing(char *t1, char *t2, IDListNode *using)
{
    //collect information on columns etc
    print_code(" %s:raze each flip .aq.ju[cols[%s],cols %s;] each (),", AQ_JOIN_USING_INFO, t1, t2);
    cg_colList(using);
    print_code(";\n");
    
    //update column dictionary
    print_code(" %s,:%s`remap;\n", AQ_COL_DICT, AQ_JOIN_USING_INFO);
}

void cg_RenameColsJoinUsing(char *t)
{
    print_code(" {(c^%s[`rename] c:cols x) xcol x}%s", AQ_JOIN_USING_INFO, t);
}


char *cg_IJUsing(LogicalQueryNode *ij)
{
    char *t1 = cg_LogicalQueryNode(ij->arg);
    char *t2 = cg_LogicalQueryNode(ij->next_arg);
    char *joined_nm = gen_table_nm();

    //inner joing semantics from sql correspond to an equijoin (ej) in q
    cg_IJUsing0(ij, joined_nm, t1, t2);
    print_code("; //inner join using\n");
    free(t1);
    free(t2);
    return joined_nm;
}

void cg_IJUsing0(LogicalQueryNode *ij, char *joined, char *t1, char *t2)
{
    IDListNode *using = ij->params.cols;
    cg_PrepareJoinUsing(t1, t2, using);
    //inner joing semantics from sql correspond to an equijoin (ej) in q
    print_code(" %s:ej[%s ", joined, AQ_COL_DICT);
    cg_colList(using);
    print_code(";");
    cg_RenameColsJoinUsing(t1);
    print_code(";");
    cg_RenameColsJoinUsing(t2);
    print_code("]");  
}



char *cg_CartesianProd(LogicalQueryNode *cart)
{
    char *t1 = cg_LogicalQueryNode(cart->arg);
    char *t2 = cg_LogicalQueryNode(cart->next_arg);
    char *crossed_name = gen_table_nm();
    print_code(" %s:%s cross %s;\n", crossed_name, t1, t2);
    free(t1);
    free(t2);
    return crossed_name;
}


//potentially push a filter down below a join
//If there is no attribute on join columns, push, otherwise join first
char *cg_PossPushFilter(LogicalQueryNode *poss_push)
{
    LogicalQueryNode *join = poss_push->arg;
    ExprNode *selection = poss_push->params.exprs;
    
    //generate code for tables involved
    char *t1 = cg_LogicalQueryNode(join->arg); //LHS
    char *t2 = cg_LogicalQueryNode(join->next_arg); //RHS
    char *joined_name = gen_table_nm();
    
    int push_left = pushToLeftPossPush(poss_push);
    char *push_to = push_left ? t1 : t2; //which side to push to
    char *push_to_filtered = gen_table_nm();
    
    //columns used in join clause and that should be checked for attributes
    IDListNode *cols_in_join = colsCheckPossPush(join);
    cg_join_push join_fun = pickJoinTypePossPush(join); //cg function for join
    
    print_code(" %s:$[", joined_name);
    //check attribute
    cg_AttributeCheckPossPush(cols_in_join, push_to);
    print_code("; //check attributes\n");
    
    //Case 1: there is an attribute in join clause, join and then select
    print_code(" [\n"); //multiple actions associated with this if statement
    //execute join
    join_fun(join, joined_name, t1, t2);
    print_code(";\n");
    //execute selection
    print_code(" ");
    cg_FilterWhere0(selection, joined_name);
    print_code(" \n ] //join then select\n");
    print_code(" ;\n");

    //Case 2: there is no attribute, select and then join
    print_code(" [\n");
    print_code(" %s:", push_to_filtered);
    cg_FilterWhere0(selection, push_to);
    print_code(";\n");
    //execute join
    // execute appropriate join (need to make sure order is still same to maintain semantics)
    push_left ? 
        join_fun(join, joined_name, push_to_filtered, t2) 
        : 
        join_fun(join, joined_name, t1, push_to_filtered);
    print_code("\n ] //select then join\n");       
    print_code(" ];\n");
    free(t1);
    free(t2);
    free(push_to_filtered);
    
    return joined_name;
    
}

IDListNode *colsCheckPossPush(LogicalQueryNode *join)
{
    switch(join->node_type)
    {
        case INNER_JOIN_USING:
        case FULL_OUTER_JOIN_USING:
            return join->params.cols;
            break;
        case INNER_JOIN_ON:
        case FULL_OUTER_JOIN_ON:
            return collect_AllCols(join->params.exprs);
            break;
        default:
            print_code("'\"Error generating code for possible push selection\n\"");
            exit(0);
            break;
    }
}


int pushToLeftPossPush(LogicalQueryNode *poss_push)
{
    IDListNode *tables_filter = collect_TablesExpr(poss_push->params.exprs);
    IDListNode *tables_left = collect_TablesFrom(poss_push->arg->arg);
    return any_in_IDList(tables_filter, tables_left);
}

cg_join_push pickJoinTypePossPush(LogicalQueryNode *join)
{
   switch(join->node_type)
   {
       case INNER_JOIN_USING:
           return cg_IJUsing0;
           break;
       default:
           print_code("'\"nyi push filter of this join\"");
           return NULL;
   } 
}
    
    
    
//q code for checking if a any list of ids is found in a set of attributes
void cg_AttributeCheckPossPush(IDListNode *cols, char *table)
{
    print_code("%s[", AQ_CHECK_ATTR);
    cg_colList(cols);
    print_code(";");
    print_code("%s]", table);
}


char *cg_LogicalQueryNode(LogicalQueryNode *node)
{
    
    char *result_table = NULL;
    
    if(node != NULL)
    {
        switch(node->node_type)
        {
        	case PROJECT_SELECT:
                result_table = cg_ProjectSelect(node);
                break;
        	case PROJECT_UPDATE:
                print_code("'\"nyi update\"\n");
                break;
        	case DELETION:
                print_code("'\"nyi deletion\"\n");
                break;
        	case FILTER_WHERE:
                result_table = cg_FilterWhere(node);
                break;
        	case FILTER_HAVING:
                result_table = cg_FilterWhere(node);        
                break;
        	case CARTESIAN_PROD:
                result_table = cg_CartesianProd(node);     
                break;
        	case INNER_JOIN_ON:
                print_code("'\"nyi inner join on\"\n");
                break;
        	case FULL_OUTER_JOIN_ON:
                print_code("'\"nyi full outer join on\"\n");          
                break;
        	case INNER_JOIN_USING:
                result_table = cg_IJUsing(node);      
                break;
        	case FULL_OUTER_JOIN_USING:
                print_code("'\"nyi full outer join using\"\n");    
                break;
        	case GROUP_BY:
                result_table = cg_groupBy(node);         
                break;
        	case SIMPLE_TABLE:
                result_table = cg_SimpleTable(node);
                break;
        	case ALIAS:
                result_table = cg_Alias(node);
                break;
        	case SORT:
                result_table = cg_Sort(node);
                break;
        	case FLATTEN_FUN:
                result_table = cg_flatten(node);         
                break;
        	case EXPLICIT_VALUES:
                print_code("'\"nyi explicit values\"\n");
                break;
        	case COL_NAMES:
                print_code("'\"nyi explicit COL NAMES\"\n");    
                break;
            case SORT_COLS:
                result_table = cg_SortCols(node);   
                break;
            case SORT_EACH_COLS:
                print_code("'\"nyi sort each cols\"\n");  
                //we did away with this, since performance tests
                //showed it was better to sort before grouping
                break;
            case EQUI_JOIN_ON:
                print_code("'\"nyi equi join on\"\n");
                break;
            case POSS_PUSH_FILTER:
                result_table = cg_PossPushFilter(node);
                break;
        }
    }
    
    return result_table;
}

/* local queries */
//generate code for 1 local query
void cg_LocalQueryNode(LocalQueryNode *local)
{
    char *t1 = cg_queryPlan(local->query_plan); //run query and store name

    print_code(" %s:", local->name);
    if(local->col_names != NULL)
    {
        cg_colRename(local->col_names);  
    }
    print_code("%s;\n", t1);
    free(t1);
}

void cg_colRename(IDListNode *names)
{
    cg_colList(names);
    print_code(" xcol ");
}


void cg_LocalQueries(LocalQueryNode *locals)
{
    if(locals != NULL)
    {
        cg_LocalQueryNode(locals);
        cg_LocalQueries(locals->next_sibling);
    }
}


    
/* full query */
void cg_FullQuery(FullQueryNode *full_query)
{
    int query_id = QUERY_CT++;
    print_code("%s%d:", AQ_QUERY_NM, query_id); //query placed into named function
    print_code("{[]\n");
    cg_LocalQueries(full_query->local_queries); //any code for local queries
    char *result_table = cg_queryPlan(full_query->query_plan); //generate main query
    print_code(" %s\n", result_table);
    print_code(" }\n"); //store function
    print_code("%s%d[]\n", AQ_QUERY_NM, query_id); //call function
    free(result_table);
}


/* creating tables or views */

//TODO: create view....how do we do this? considering views in q...
//Think about this
/*
void cg_CreateTable(CreateNode* create)
{
    char *src_fun_nm = NULL;
    CreateSourceNodeType src_type = create->src->node_type;
    
    if(src_type == QUERY_SOURCE)
    {
        cg_FullQuery(create->src->load.query)
        //TODO: might be better to have cg_FullQuery return the name of the function
        //and it then only gets call when it needs to be
        print_code("%s: %s%d[];\n", create->name, AQ_QUERY_NM, QUERY_CT - 1);
    }
    else
    {
        print_code("%s:");
        cg_Schema(create->src->load.schema);
    }
}
    
//TODO: complete schema
void cg_Schema(SchemaNode *schema)
{
    //generate code for pairs, should be easy!
}
    
    
   
}
*/

void cg_TopLevel(TopLevelNode *node)
{
    if(node != NULL)
    {
        switch(node->node_type)
        {
            case GLOBAL_QUERY:
                cg_FullQuery(node->elem.query);
                break;
            case UDF_DEF:
                cg_UDFDefNode(node->elem.udf);
                break;
            case INSERT_STMT:
                print_code("'\"nyi insert statements\"\n");
                break;
            case UPDATE_DELETE_STMT:
                print_code("'\"nyi update/delete statements\"\n");
                break; 
            case CREATE_STMT:
                print_code("'\"nyi create statements\"\n");
                break;
        }
        
        cg_TopLevel(node->next_sibling);
    }
}


void cg_AQUERY2Q(TopLevelNode *node)
{
    init_aq_helpers();
    cg_TopLevel(node);
}






