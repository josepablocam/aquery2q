/*
	This file contains functions necessary for aquery optimizations
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aquery_types.h"
#include "ast.h"
#include "ast_print.h"
#include "optimizer.h"

#define STAND_ALONE 1
#define OPTIM_DEBUG 1
#define OPTIM_PRINT_DEBUG(str) if(OPTIM_DEBUG) printf("---->OPTIM DEBUGGING: %s\n", str)

extern const char *ExprNodeTypeName[]; //aquery_print.c

const char *UNKNOWN_TABLE_NM = "UNKNOWN";

#if !STAND_ALONE
extern int optim_level; //aquery.y
extern Symtable *env; //aquery.y
#endif

#if STAND_ALONE
int optim_level = 1;
Symtable *env;
#endif




GenList *list_alloc(void *data)
{
    GenList *new =  malloc(sizeof(GenList));
    new->id = 0;
    new->data = data;
    new->next = NULL;
    return new;
}

GenList *list_append(GenList *list, void *data)
{
    GenList *curr = list, *prev = NULL;
    
    while(curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }
    
    if(prev == NULL)
    { //list was empty
        return list_alloc(data);
    }
    else
    { 
       GenList *new = list_alloc(data);
       prev->next = new;
       new->id = prev->id + 1;
       return list; 
    }
}


GenList *list_prepend(GenList *list, void *data)
{
    GenList *new = list_alloc(data);
    
    if(list == NULL)
    {
        return new;
    }
    else
    {
        new->next = list;
        new->id = list->id - 1;
        return new;
    }
}

//Compares pointer, removes a node if pointer values are equal
//Note that this doesn't
GenList *list_remove_first(GenList *list, void *data)
{
    GenList *curr = list, *prev = NULL;
    
    while(curr != NULL)
    {
        if(curr->data == data)
        {
            if(prev == NULL)
            {   //elem is at start of list
                GenList *new_list = curr->next;
                free(curr);
                return new_list;
            }
            else
            {
                prev->next = curr->next;
                free(curr);
                return list;
            }
        }
        
        prev = curr;
        curr = curr->next;
    }
    
    return list;
}

void list_foreach(GenList *list, void (*fun)(GenList *))
{
    GenList *curr = list;
    
    while(curr != NULL)
    {
        fun(curr);
        curr = curr->next;
    }
}

void list_foreach_warg(GenList *list, void (*fun)(GenList *, void *), void *arg)
{
    while(curr != NULL)
    {
        fun(curr, arg);
        curr = curr->next;
    }
}


int list_length(GenList *list)
{
   int len = 0;
   GenList *curr = list;
   
   while(curr != NULL)
   {
       len++;
       curr = curr->next;
   }
   
   return len; 
}



void print_str(GenList *elem)
{
    char *str =(char *) elem->data;
    printf("%s\n", str);
}



//Creating deep copies of LogicalQueryNodes in order to reproduce the original plan
//before any optimizations, so we can create multiple options
LogicalQueryNode *deepcopy_LogicalQueryNode(LogicalQueryNode *node)
{
    OPTIM_PRINT_DEBUG("deep copying logical query node");
    LogicalQueryNode *copy = NULL;
    
    if(node != NULL)
    {
        copy = make_EmptyLogicalQueryNode(node->node_type);
        copy->order_dep = node->order_dep;
        copy->tables_involved = deepcopy_IDListNode(node->tables_involved);
        
        //copying any information necessary
        switch(node->node_type)
        {
            case SIMPLE_TABLE: //intentional fall through
            case ALIAS: //intentional fall through
                copy->params.name = strdup(node->params.name);
                break;
            case INNER_JOIN_ON: //intentional fall through
            case FULL_OUTER_JOIN_ON: //intentional fall through
            case FILTER_WHERE: //intentional fall through
            case FILTER_HAVING: //intentional fall through
            case GROUP_BY: //intentional fall through
            case EXPLICIT_VALUES: //intentional fall through
                copy->params.exprs = deepcopy_ExprNode(node->params.exprs);
                break;
            case INNER_JOIN_USING: //intentional fall through
            case FULL_OUTER_JOIN_USING: //intentional fall through
            case DELETION: //intentional fall through
            case COL_NAMES: //intentional fall through
                copy->params.cols = deepcopy_IDListNode(node->params.cols);
                break;
            case PROJECT_SELECT: //intentional fall through
            case PROJECT_UPDATE: //intentional fall through
                copy->params.namedexprs = deepcopy_NamedExprNode(node->params.namedexprs);
                break;
           case SORT: //intentional fall through
           case SORT_COLS: //intentional fall through
           case SORT_EACH_COLS: //intentional fall through
               copy->params.order = deepcopy_OrderNode(node->params.order);
               break;
            default:
                break;
        }
        
        copy->arg = deepcopy_LogicalQueryNode(node->arg);
        copy->next_arg = deepcopy_LogicalQueryNode(node->next_arg);
    }
    
    return copy;
}

NamedExprNode *deepcopy_NamedExprNode(NamedExprNode *node)
{
    OPTIM_PRINT_DEBUG("deep copying named expression node");
    NamedExprNode *copy = NULL;
    char *name = NULL;
    
    if(node != NULL)
    {
        if(node->name != NULL)
        {
            name = strdup(node->name);
        }
        
        copy = make_NamedExprNode(name, deepcopy_ExprNode(node->expr));
        copy->order_dep = node->order_dep;
        copy->sub_order_dep = node->sub_order_dep;
        copy->next_sibling = deepcopy_NamedExprNode(node->next_sibling);
    }
    
    return copy;
}

IDListNode *deepcopy_IDListNode(IDListNode *node)
{
    OPTIM_PRINT_DEBUG("deep copying id list node");
    IDListNode *copy = NULL;
    
    if(node != NULL)
    {
        copy = make_IDListNode(strdup(node->name), deepcopy_IDListNode(node->next_sibling));
    }
    
    return copy;
}
    
    
    
OrderNode *deepcopy_OrderNode(OrderNode *node)
{
    OPTIM_PRINT_DEBUG("deep copying order node");
    OrderNode *copy = NULL;
    
    if(node != NULL)
    {
        copy = make_OrderNode(node->node_type, deepcopy_ExprNode(node->col));
        copy->next = deepcopy_OrderNode(node->next);
    }
    
    return copy;
}




//Create a deepcopy of an expression AST
ExprNode *deepcopy_ExprNode(ExprNode *node)
{
    OPTIM_PRINT_DEBUG("deep copying expression node");
    ExprNode *copy= NULL;
    
    if(node != NULL)
    {
        //Create an empty expression node with your general info
        copy = make_EmptyExprNode(node->node_type);
        copy->data_type = node->data_type;
        copy->order_dep = node->order_dep;
        copy->sub_order_dep = node->sub_order_dep;
        copy->uses_agg = node->uses_agg;
        copy->tables_involved = deepcopy_IDListNode(node->tables_involved);
        
        //Copy any data necessary, note strings need to be copied deeply too
        //We free some stuff as we manipulate optimizations
        switch(node->node_type)
        {
            case CONSTANT_EXPR:
                if(node->data_type == FLOAT_TYPE)
                {
                    copy->data.fval = node->data.fval;
                }
                else if(node->data_type == INT_TYPE || node->data_type == BOOLEAN_TYPE)
                {
                    copy->data.ival = node->data.ival;
                }
                else
                { //strings, hex, dates...
                    copy->data.str = strdup(node->data.str);
                }
                break;
            case ID_EXPR: //intentional fall through
            case BUILT_IN_FUN_CALL: //intentional fall through
            case UDF_CALL:
                copy->data.str = strdup(node->data.str);
                break;
            case EVERY_N_IX:
                copy->data.ival = node->data.ival;
                break;
            default: //nothing to do for now
                break;
        }
        
        copy->first_child  = deepcopy_ExprNode(node->first_child);
        copy->next_sibling = deepcopy_ExprNode(node->next_sibling);
    }
    
    return copy;
}


ExprNode *append_Exprs(ExprNode *existing, ExprNode *new)
{
    ExprNode *curr = existing, *prev = NULL;
    
    while(curr != NULL)
    {
        prev = curr;
        curr = curr->next_sibling;
    }
    
    if(prev == NULL)
    {
        return new;
    }
    else
    {
        prev->next_sibling = new;
        return existing;
    }
}



//returns 1 if name is in list, 0 otherwise, uses strcmp
int in_IDList(const char *name, IDListNode *list)
{
    IDListNode *curr;

    for(curr = list; curr != NULL; curr = curr->next_sibling)
    {
        if(strcmp(name, curr->name) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}

//returns 1 if any element of l1 is in l2
int any_in_IDList(IDListNode *l1, IDListNode *l2)
{
    IDListNode *curr = l1;
    
    while(curr != NULL)
    {
        if(in_IDList(curr->name, l2))
        {
            return 1;
        }
    }
    
    return 0;
}

//returns length of an IDListNode
int length_IDList(IDListNode *l)
{
    IDListNode *curr = l;
    int len = 0;
    
    while(curr != NULL)
    {
        len++;
        curr = curr->next_sibling;
    }
    
    return len;
}

//return 1 if first list is a subset of l2 (returns true if l1 and l2 are set equivalent)
//as well, so is_setEquivIDLists should be used first in any kind of branching
int is_subsetIDLists(IDListNode *l1, IDListNode *l2)
{
    IDListNode *curr = l1;
    int in_list = 1;
    
    while(curr != NULL && in_list)
    {
        in_list = in_IDList(curr->name, l2);
        curr = curr->next_sibling;
    }
    
    return in_list;   
}


//return 1 if they are set equivalent (i.e. order irrelevant)
int is_setEquivIDLists(IDListNode *l1, IDListNode *l2)
{
    if(length_IDList(l1) != length_IDList(l2))
    { //don't even bother checking if lengths don't match, since these are sets
      //diff length mean different elements
        return 0;
    }
    else
    {
        //since length matches, a subset check returning true means they are the same set
        return is_subsetIDLists(l1, l2);   
    }
}


///Unions x and y, so that there are no repetitions. Returns pointer to result
//Works by modifying pointer x when necessary, so neither x nor y should be relied upon after use
IDListNode *unionIDList(IDListNode *x, IDListNode *y)
{
    OPTIM_PRINT_DEBUG("---->new union");
    IDListNode *curr_y, *next_y, *to_free;
    
    if(y == NULL)
    { //no point searching concatenation location if y is empty
        return x;
    }
    else if(x == NULL)
    {
        return y;
    }
    else
    {
        for(curr_y = y; curr_y != NULL; curr_y = next_y)
        {
            if(!in_IDList(curr_y->name, x))
            { 
                next_y = curr_y->next_sibling; //save down the sibling for y
                curr_y->next_sibling = x; //cons element in y to x
                x = curr_y; //set x to head of consed list
            }
            else
            { //if we didn't add it, free-it
                to_free = curr_y;
                next_y = curr_y->next_sibling;
                free_single_IDListNode(to_free);
                to_free = NULL;
            }
        }
               
        return x;
    }
}





//Account for interactions between order-dependent and order-independent columns. Adds otherwise order-independent cols to sorting list
//based on interactions
IDListNode *add_interactionsToSort(GenList *interact, IDListNode *need_sort)
{
    int added = 1;
    GenList *curr_interact = NULL;
    IDListNode *col = NULL;
    
    while(added != 0)
    {
        added = 0;
        for(curr_interact = interact ; curr_interact != NULL; curr_interact = curr_interact->next)
        {   
            OPTIM_PRINT_DEBUG("Checking related:");
            //print_id_list(curr_interact->list, n, &n);
            for(col = (IDListNode *) curr_interact->data; col != NULL; col = col->next_sibling)
            {
                if(in_IDList(col->name, need_sort))
                {
                    OPTIM_PRINT_DEBUG("found contaminated list");
                    need_sort = unionIDList(need_sort, (IDListNode *) curr_interact->data); //add to sort
                    curr_interact->data = NULL; //we have added everything we needed, rest has been freed during union
                    added = 1;
                    break;
                }
            }
        }
    }
    //Anything that is not null in potential was never added to sort list and will never be added, so free it
    GenList *to_free_nested = NULL;
    IDListNode *to_free_list = NULL; 
    
    curr_interact = interact;
    while(curr_interact != NULL)
    {
        to_free_nested = curr_interact; 
        curr_interact = curr_interact->next;
        
        if(to_free_nested->data != NULL)
        { //free any contents
            OPTIM_PRINT_DEBUG("freeing a list of ids");
            free_IDListNode((IDListNode *)to_free_nested->data);
        }
        
        free(to_free_nested);
    }

    return need_sort;
}

//Collect the columns that need to be sorted given dependencies in an expression AST
IDListNode *collect_sortCols(ExprNode *od_expr, int add_from_start)
{
    IDListNode **need_sort_ptr = malloc(sizeof(IDListNode *));
    *need_sort_ptr = NULL; 
    
    GenList **potential_ptr = malloc(sizeof(GenList *));
    *potential_ptr = NULL;
    
    IDListNode *top = collect_sortCols0(od_expr, add_from_start, need_sort_ptr, potential_ptr);
    *potential_ptr = list_prepend(*potential_ptr, top);
    
    OPTIM_PRINT_DEBUG("returned from collect_sortCols0");
    return add_interactionsToSort(*potential_ptr, *need_sort_ptr);
}



//Collect the columns that need to be sorted given dependencies in a named expression AST
IDListNode *collect_sortColsNamedExpr(NamedExprNode *nexprs, int add_from_start)
{
    IDListNode **need_sort_ptr = malloc(sizeof(IDListNode *));
    *need_sort_ptr = NULL; 
    
    GenList **potential_ptr = malloc(sizeof(GenList *));
    *potential_ptr = NULL;
    
    IDListNode *top = NULL;
    
    NamedExprNode *curr_nexpr = nexprs;
    int x = 0;
    
    while(curr_nexpr != NULL)
    { 
        OPTIM_PRINT_DEBUG("running over named expression");
        //print_expr(curr_nexpr->expr, x, &x);
        top = collect_sortCols0(curr_nexpr->expr, add_from_start, need_sort_ptr, potential_ptr);
        *potential_ptr = list_prepend(*potential_ptr, top);
        
        curr_nexpr = curr_nexpr->next_sibling;
    }

    OPTIM_PRINT_DEBUG("returned from collect_sortCols0");
    //TODO: free up memory for structures used in this search
    return add_interactionsToSort(*potential_ptr, *need_sort_ptr);
}


IDListNode *collect_sortCols0(ExprNode *node, int add_flag, IDListNode **need_sort_ptr, GenList **potential_ptr)
{
    IDListNode *child = NULL;
    IDListNode *sibling = NULL;
    int new_add_flag = 0;

    if(node == NULL)
    { //nothing to do if we're at the end
        return NULL;   
    }
    else if(node->node_type == ID_EXPR)
    {
        OPTIM_PRINT_DEBUG("found id");
        
        if(add_flag)
        {
            OPTIM_PRINT_DEBUG("adding id to sort list");
            *need_sort_ptr = unionIDList(*need_sort_ptr, make_IDListNode(strdup(node->data.str), NULL));//union with list of def sorted
            collect_sortCols0(node->next_sibling, add_flag, need_sort_ptr, potential_ptr); //explore sibling
            return NULL; //already appending to need_sort here, don't need to add to potential, so just return a null
        }
        else
        {
            OPTIM_PRINT_DEBUG("sending id back up");
            child = make_IDListNode(strdup(node->data.str), NULL); //return id to add to potential
            sibling = collect_sortCols0(node->next_sibling, add_flag, need_sort_ptr, potential_ptr);
            return unionIDList(child, sibling);
        }       
    }
    else if(node->node_type == COLDOTACCESS_EXPR)
    { //TODO: figure out how to handle dot column accesses correctly
       OPTIM_PRINT_DEBUG("found col dot access, accessing dest child");
       child =  collect_sortCols0(node->first_child->next_sibling, add_flag, need_sort_ptr, potential_ptr);
       sibling = collect_sortCols0(node->next_sibling, add_flag, need_sort_ptr, potential_ptr);
       return unionIDList(child, sibling);
    }
    else if(node->node_type == CALL_EXPR)
    {
        //whether or not we continue to add to sort list can change based on operator properties
        new_add_flag = node->order_dep; 

        if(!new_add_flag)
        { //we have reached an order-independent function call, like max/min
            OPTIM_PRINT_DEBUG("found order annihilating call, exploring child");
            child = collect_sortCols0(node->first_child, new_add_flag, need_sort_ptr, potential_ptr);
            OPTIM_PRINT_DEBUG("appending potential list at order annihilating call");
            *potential_ptr = list_prepend(*potential_ptr, child); //we stop "bubbling up" interactions here
            OPTIM_PRINT_DEBUG("exploring call's sibling");
            return collect_sortCols0(node->next_sibling, add_flag, need_sort_ptr, potential_ptr); //send back interactions in sibling node, not your own anymore
        }
        else
        {
            OPTIM_PRINT_DEBUG("found order dependent call, exploring args");
            child = collect_sortCols0(node->first_child, new_add_flag, need_sort_ptr, potential_ptr); //no need to add to potential, adding to need_sort
            OPTIM_PRINT_DEBUG("done exploring order dependent call, returning list of ");
            return collect_sortCols0(node->next_sibling, add_flag, need_sort_ptr, potential_ptr); //return interactions in sibling node
        }
    }
    else
    {
        OPTIM_PRINT_DEBUG("found random node, exploring child");
        child = collect_sortCols0(node->first_child, add_flag | node->order_dep, need_sort_ptr, potential_ptr);
        OPTIM_PRINT_DEBUG("exploring random node's sibling");
        sibling = collect_sortCols0(node->next_sibling, add_flag, need_sort_ptr, potential_ptr);
        return unionIDList(child, sibling);
    }
    
}


//Extract all ids referenced in an expression
IDListNode *collect_AllCols(ExprNode *node)
{
    OPTIM_PRINT_DEBUG("collecting all col refs");
    IDListNode *child = NULL;
    IDListNode *sibling = NULL;

    if(node == NULL)
    {
        return NULL;   
    }
    else if(node->node_type == ID_EXPR)
    {
        child = make_IDListNode(strdup(node->data.str), NULL);
        sibling = collect_AllCols(node->next_sibling);
        return unionIDList(child, sibling);     
    }
    else if(node->node_type == COLDOTACCESS_EXPR)
    { //TODO: figure out how to handle dot column accesses
       child = collect_AllCols(node->first_child->next_sibling);
       sibling = collect_AllCols(node->next_sibling);
       return unionIDList(child, sibling);
    }
    else if(node->node_type == BUILT_IN_FUN_CALL || node->node_type == UDF_CALL)
    {
        return collect_AllCols(node->next_sibling);
    }
    else
    {
        child = collect_AllCols(node->first_child);
        sibling =  collect_AllCols(node->next_sibling);
        return unionIDList(child, sibling);
    }
    
}

IDListNode *collect_AllColsProj(LogicalQueryNode *node)
{
    OPTIM_PRINT_DEBUG("collecting all col refs in named expr");
    IDListNode *result = NULL;
    NamedExprNode *curr = node->params.namedexprs;

    while(curr != NULL)
    {
        result = unionIDList(result, collect_AllCols(curr->expr));
        curr = curr->next_sibling;
    }
    
    return result;
}

//Collects all columns referenced in a group-by/having clause
IDListNode *collect_AllColsGroupby(LogicalQueryNode *groupby)
{
    if(groupby == NULL)
    {
        return NULL;
    }
    else
    {
        return unionIDList(collect_AllCols(groupby->params.exprs), collect_AllColsGroupby(groupby->arg));
    }
}


//Add element add to end of list, expression order might matter, so this maintains
ExprNode *append_toExpr(ExprNode *list, ExprNode *add)
{
    ExprNode *prev, *curr;
    
    for(prev = curr = list; curr != NULL; prev = curr, curr = curr->next_sibling)
    {
        /* searching for first empty spot at end of list */
    }
    
    if(prev == NULL)
    {
        return add;
    }
    else
    {
        prev->next_sibling = add;
        return list;
    }    
}


//An abstraction of a pattern we commonly need to for expression nodes: separating a list of expressions into 2, upon the first true instance of predicate
//Renders original list useless, since manipulates pointers
void partExpr_atFirst(ExprNode *orig, ExprNode **before, ExprNode **after, int (*pred)(ExprNode *))
{
       OPTIM_PRINT_DEBUG("partitioning expression list based on first instance of predicate");
       ExprNode *curr, *next;
       int hit_pred = 0;

       for(next = NULL, curr = orig; curr != NULL; curr = next)
       {
           next = curr->next_sibling; //store next expression
           curr->next_sibling = NULL; //remove link between current and next expression
           
           if(!hit_pred)
           { //only test predicate if we haven't already tripped it
               hit_pred = pred(curr);
           }
        
           //if predicate hasn't tripped, then add to before list
           if(!hit_pred)
           {
               *before = append_toExpr(*before, curr); 
           }
           else
           {
              *after = append_toExpr(*after, curr);
           }
       }
}


//groups list of expressions into 2 lists, one where the predicate is true, and the other where it is false
//Renders original list useless, since manipulates pointers
void groupExpr_onUnaryPred(ExprNode *orig, ExprNode **true, ExprNode **false, int (*pred)(ExprNode *))
{
       OPTIM_PRINT_DEBUG("grouping expr list into true and false based on predicate");
       ExprNode *curr, *next;

       for(next = NULL, curr = orig; curr != NULL; curr = next)
       {
           next = curr->next_sibling; //store next expression
           curr->next_sibling = NULL; //remove link between current and next expression
           
           //add to appropriate list based on predicate
           if(pred(curr))
           {
               *true = append_toExpr(*true, curr); 
           }
           else
           {
              *false = append_toExpr(*false, curr);
           }
       }
}


void groupExpr_onBinaryPred(ExprNode *orig, ExprNode **true, ExprNode **false, int (*pred)(ExprNode *, void*), void* data)
{
       OPTIM_PRINT_DEBUG("grouping expr list into true and false based on predicate");
       ExprNode *curr, *next;

       for(next = NULL, curr = orig; curr != NULL; curr = next)
       {
           next = curr->next_sibling; //store next expression
           curr->next_sibling = NULL; //remove link between current and next expression
           
           //add to appropriate list based on predicate
           if(pred(curr, data))
           {
               *true = append_toExpr(*true, curr); 
           }
           else
           {
              *false = append_toExpr(*false, curr);
           }
       }
}



int is_od(ExprNode *expr)
{
    return expr->order_dep || expr->sub_order_dep;
}

int uses_agg(ExprNode *expr)
{
    return expr->uses_agg;
}


//Partition a list of expressions into all expressions up to (but not including) the first order-dependent operation
//So your lists is (all_order_independent_ops_before_first_OD) (remaining)
void partExpr_OnOrder(ExprNode *expr, ExprNode **order_indep, ExprNode **remaining)
{
     OPTIM_PRINT_DEBUG("partitioning expression list based on first OD");
     partExpr_atFirst(expr, order_indep, remaining, is_od);
}

//Parition a list of expression into all expression up to (but not including) the first use of an agreggate
void partExpr_OnAgg(ExprNode *expr, ExprNode **no_agg, ExprNode **agg)
{
   OPTIM_PRINT_DEBUG("partitioning expression list based on first agg");
   partExpr_atFirst(expr, no_agg, agg, uses_agg);  
}




//New type of node needed to plug into query step sorting certain columns
LogicalQueryNode *make_specCols(IDListNode *cols)
{
    LogicalQueryNode *spec_cols = make_EmptyLogicalQueryNode(COL_NAMES);
    spec_cols->params.cols = cols; 
    return spec_cols;
}

//Sort cols based on order node
LogicalQueryNode *make_sortCols(OrderNode *order, IDListNode *cols)
{
    LogicalQueryNode *sort = make_EmptyLogicalQueryNode(SORT_COLS);
    sort->params.order = order;
    sort->next_arg = make_specCols(cols);
    return sort;
}

//Sort-each cols based on order node
LogicalQueryNode *make_sortEachCols(OrderNode *order, IDListNode *cols)
{
    LogicalQueryNode *sort = make_EmptyLogicalQueryNode(SORT_EACH_COLS);
    sort->params.order = order;
    sort->next_arg = make_specCols(cols);
    return sort;
}

//if want is a prefix of have, then return null, else return want...
OrderNode *get_NeededSort(OrderNode *have, OrderNode *want)
{
    OPTIM_PRINT_DEBUG("searching for incremental sort needed");
    OrderNode *want_curr, *have_curr;
    
    want_curr = want;
    have_curr = have;
    
    while(want_curr != NULL && have_curr != NULL)
    {
        if(want_curr->node_type == have_curr->node_type && strcmp(want_curr->col->data.str, have_curr->col->data.str) == 0)
        { //no need do anythign with a given order spec, if we already have it sorted
          //along that dimension
            OPTIM_PRINT_DEBUG("found matching sort prefix along 1 dimension");
            want_curr = want_curr->next;
            have_curr = have_curr->next;     
        }
        else
        { //none matching
            OPTIM_PRINT_DEBUG("found end of matching sort prefix");
            break;
        }   
    }
    
    if(want_curr == NULL)
    { //we don't need any order info anymore, so free
        free_OrderNode(want);
        want = NULL;
    }

    return want; //return either NULL if we had the order, otherwise whole order required
}



//Name of table source in a dot expression
char *get_table_src(ExprNode *expr)
{
    OPTIM_PRINT_DEBUG("extracting table name");
    int x = 0;
    print_expr(expr, x, &x);
    if(expr == NULL || expr->node_type != COLDOTACCESS_EXPR)
    {
        //printf("Error: attempting to extract table name from non-dot-access expression\n");
        return NULL;
    }
    else
    {
        return expr->first_child->data.str;
    }
}

int is_comparison(ExprNodeType type)
{
    return type == EQ_EXPR || type == LT_EXPR || type == LE_EXPR || type == GT_EXPR || type == GE_EXPR || type == NEQ_EXPR ;
}

//Is an expression that should be interpreted as a join clause
int is_JoinClause(ExprNode *expr)
{
    OPTIM_PRINT_DEBUG("testing expression for join clause status");
    if(expr == NULL)
    {   
        return 0;
    }
    else
    {
        if(!is_comparison(expr->node_type))
        {
            return 0;
        }
        else 
        {
            IDListNode *left_names = collect_TablesExpr(expr->first_child);
            IDListNode *right_names =collect_TablesExpr(expr->first_child->next_sibling);
            IDListNode *names = unionIDList(left_names, right_names);
            return !in_IDList(UNKNOWN_TABLE_NM, names) && length_IDList(names) > 1; //we need to know the tables being used, and there must be more than 1 table referenced  
        }
    }
}


//Separate join clauses from normal filters
void groupExpr_OnJoin(ExprNode *expr, ExprNode **join_filters, ExprNode **other_filters)
{
    groupExpr_onUnaryPred(expr, join_filters, other_filters, is_JoinClause);
}

//Return true if expr involves a subset of names
int Expr_has_tables(ExprNode *expr, void *names)
{
    IDListNode *expr_names = collect_TablesExpr(collect_expr);
    return is_subsetIDLists(expr_names, names);
}



//Separate clauses into those referencing 
void groupExpr_OnTables(ExprNode *expr, ExprNode **have, ExprNode **dont, IDListNode *names)
{
    groupExpr_onBinaryPred(expr, have, dont, Expr_has_tables, names);
}





//What tables are involved in an expression
IDListNode *collect_TablesExpr(ExprNode *node)
{
    IDListNode *child = NULL, *sibling = NULL; 
    
    OPTIM_PRINT_DEBUG("collecting tables involved in expression");
    
    if(node == NULL)
    {
        return NULL;
    }
    else if(node->tables_involved != NULL)
    {    //if we already have it, just create a copy of it (need to copy to be able to union without messing up results)
         child = deepcopy_IDListNode(node->tables_involved);
         sibling = collect_TablesExpr(node->next_sibling);
         return unionIDList(child, sibling);
    }
    else if(node->node_type == ID_EXPR)
    {
        child = make_IDListNode(strdup(UNKNOWN_TABLE_NM), NULL);
        node->tables_involved = deepcopy_IDListNode(child);
        sibling = collect_TablesExpr(node->next_sibling);
        return unionIDList(child, sibling);
    }
    else if(node->node_type == COLDOTACCESS_EXPR)
    {
        child = make_IDListNode(strdup(get_table_src(node)), NULL);
        node->tables_involved = deepcopy_IDListNode(child);
        sibling = collect_TablesExpr(node->next_sibling);
        return unionIDList(child, sibling);
    }
    else
    {
        child = collect_TablesExpr(node->first_child);
        node->tables_involved = deepcopy_IDListNode(child);
        sibling = collect_TablesExpr(node->next_sibling);
        return unionIDList(child, sibling);
    }   
}

IDListNode *collect_TablesFrom(LogicalQueryNode *ts)
{
    IDListNode *child = NULL, *sibling = NULL;
    
    if(ts == NULL)
    {
        return NULL;
    }
    else if(ts->tables_involved != NULL)
    { //we already have it, just return a copy
        child = deepcopy_IDListNode(ts->tables_involved);
        sibling = collect_TablesFrom(ts->next_arg);
        return unionIDList(child, sibling); 
        
    }
    else if(ts->node_type == SIMPLE_TABLE)
    {
        child = make_IDListNode(strdup(ts->params.name), NULL);
        ts->tables_involved = deepcopy_IDListNode(child); //memoize
        sibling = collect_TablesFrom(ts->next_arg);
        return unionIDList(child, sibling);
    }
    else if(ts->node_type == ALIAS)
    {
        //in the case of the alias, the alias name is the table name as far as we are concerned
        child = make_IDListNode(strdup(ts->params.name), NULL);
        ts->tables_involved = deepcopy_IDListNode(child); //memoize
        sibling = collect_TablesFrom(ts->next_arg);
        return unionIDList(child, sibling);
    }
    else
    {   
        child = collect_TablesFrom(ts->arg);
        ts->tables_involved = deepcopy_IDListNode(child); //memoize
        sibling = collect_TablesFrom(ts->next_arg);
        return unionIDList(child, sibling);
    }
}



//Split from clause into a list of list of units to use for joins, returns a generic list
GenList *split_from(LogicalQueryNode *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    else if(node->node_type == CARTESIAN_PROD)
    { //break up crosses
        return list_prepend(split_from(node->next_arg), (void *) node->arg);
    }
    else
    { //return joins as given and others as well
        return list_alloc((void *) node);
    }
}


//Create a filter node with an expression as deeply as you can (i.e. as close to the
//tables being referenced
LogicalQueryNode *deposit_filter_deeply(LogicalQueryNode *node, ExprNode *filter)
{
    if(node == NULL || filter == NULL)
    {
        return node;
    }
    else
    {
        IDListNode *filter_tables = collect_TablesExpr(filter);
        IDListNode *node_tables = collect_TablesFrom(node);
        
        if(is_setEquivIDLists(filter_tables, node_tables))
        { //we've arrived to node where we should deposit the filtr
            return make_filterWhere(node, filter);
        }
        else if(is_subsetIDLists(filter_tables, node_tables))
        { //our target is somewhere in the subtree, search both branches
            node->arg = deposit_filter_deeply(node->arg, filter);
            node->next_arg = deposit_filter_deeply(node->next_arg, filter);
            return node;
        }
        else
        { //our target is not in this part of the tree, return tree intact
            return node;
        }
    }
}

void deposit_filter_deeply_wrap(GenList *elem, ExprNode *filters)
{
    elem->data = (void *) deposit_filter_deeply((LogicalQueryNode *) elem->data;  filters);
}


//Returns a general list of logical query nodes that have added the
//filters possible from filters argument
//filters argument is modified to end up only with filters that weren't applied
//no need to free filters that were applied as they have been reused in the plan's AST
GenList *add_filters(GenList *ts, ExprNode **filters)
{
    ExprNode *all_filters = filters;
    ExprNode *relevant = NULL;
    ExprNode *irrelevant = NULL;
    GenList *curr = ts;
    
    while(curr != NULL)
    {
        groupExpr_OnTables(filters, &relevant, &irrelevant);
        
        if(relevant != NULL)
        { //there are applicable filters
            deposit_filter_deeply_wrap(curr, relevant); //deposit relevant filters  
        }
        
        *filters = irrelevant; //remaining filters are only the irrelevant ones...
        curr = curr->next;
    }
       
    return ts; 
}

//returns 1 if the join_filter has at least 1 name in common with both arguments to a join
int join_is_possible(IDListNode *left, IDListNode *right, IDListNode *join_filter)
{
    return any_in_IDList(join_filter, left) && any_in_IDList(join_filter, right);
}

//count the number of equality filters that can be applied given a list of table names
int Expr_count_eq_filters(ExprNode *filters, IDListNode *table_names)
{
    ExprNode *curr = filters;
    int count = 0;
    
    while(curr != NULL)
    {
        if(curr->node_type == EQ_EXPR || curr->node_type == NEQ_EXPR)
        {
            if(is_subsetIDLists(collect_TablesExpr(curr), table_names))
            {
                count++;
            }
        }
        
        curr = curr->next_sibling;
    }
    
    return count;
}

//Warn user if a cross is missing a join clause and returns the union
void check_warn_Join()
{
    printf("Warning: there is a missing join clause for an implicit join. Please make sure your join clauses use table prefixes in column references\n");    
    printf("Offeding query at line %d\n", ...);
    printf("Silence these warnings with -s");
}

//Given a list of tables, picks a join based on heuristic
//returns new list of tables, and modifies the join_filter list to remove those used
//uses reg_filters in the heuristic, but doesn't modify them
GenList *choose_next_join(GenList *tables, ExprNode **join_filter_ptr, ExprNode *reg_filters)
{
    int max_ct_eq_filters = -1; //number of equality filters resulting from best join
    int ct_eq_filters = 0; //count of equality filters resulting from curr join
    LogicalQueryNode *chosen_left = NULL, *chosen_right = NULL;
    Exprnode *chosen_join = NULL;
    
    if(list_length(tables) == 1)
    { //there is nothing to join
        return tables; 
    }
    
    if(*join_filter_ptr == NULL)
    {
        //we should warn the user, that there are join clauses missing
        check_warn_Join();
        //use heuristic of 
    }
    
    //otherwise pick best join based on heuristic
    GenList *left = tables, *right = tables;
    ExprNode *join_filters = *join_filters_ptr;
    ExprNode *curr_join_filter = *join_filters;
    IDListNode *left_names, *right_names, *join_names;
    
    while(curr_join_filter != NULL)
    {
        left = tables;
        join_names = collect_TablesExpr(curr_join_filter);
        while(left != NULL)
        {
            right = tables;
            left_names = collect_TablesFrom(left->data);
            
            while(right != NULL)
            {
               if(right->id > left->id)
               { //we check ids to avoid testing A join B and B join A both
                   //using GenList->id as a relative position marker solves this issue
                   right_names = collect_TablesFrom(right->data);
                
                   if(join_is_possible(left_names, right_names, join_names))
                   {
                    
                       ct_eq_filters = Expr_count_eq_filters(reg_filters, unionIDList(left_names, right_names));
                    
                       if(ct_eq_filters > max_ct_eq_filters)
                       {
                           chosen_left = left->data;
                           chosen_right = right->data;
                           chosen_join = curr_join_filter;
                       }
                   }    
               }
                   
                right = right->next;
            }
            
            left = left->next;
        }
        
        curr_join_filter = curr_join_filter->next_sibling;
    }
    
    //all join filters relating to the current join
    ExprNode *relevant_join_filters = NULL;
    ExprNode *other_join_filters = NULL;
    IDListNode *combined_tables = unionIDList(collect_TablesFrom(chosen_left->data), collect_TablesFrom(chosen_right->data));
    groupExpr_OnTables(join_filters, &relevant_join_filters, &other_join_filters, combined_tables);
    
    //remove from list nodes that will combined by join 
    tables = list_remove_first(tables, chosen_left);
    tables = list_remove_first(tables, chosen_right);
    
    //create new node and add to list
    tables = list_append(list, make_joinOn(EQUIJOIN_ON, chosen_left, chosen_right, relevant_join_filters));
     
    //the join filters that remain are those that are irrelevant
    *join_filters_ptr = other_join_filters;
    
    return tables;
}



LogicalQueryNode *optim_sort_where(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
    OPTIM_PRINT_DEBUG("optimizing where clause");
    LogicalQueryNode *order_indep_filter = NULL;
    LogicalQueryNode *remaining_filter = NULL;
    LogicalQueryNode *sort = NULL;
    ExprNode *order_indep_exprs = NULL;
    ExprNode *remaining_exprs = NULL;
    
    partExpr_OnOrder(where->params.exprs->first_child, &order_indep_exprs, &remaining_exprs);
    
    if(order_indep_exprs != NULL)
    { //perform any order-independent filtering up to first order-dependent first
        OPTIM_PRINT_DEBUG("found order independent where predicates");
        //print_expr(order_indep_exprs, i, &i);
        order_indep_filter = make_filterWhere(NULL, order_indep_exprs);
        
    }
    
    remaining_filter = make_filterWhere(NULL, remaining_exprs);
    
    //Find all column references in projection and groupbyclauses
    
    OPTIM_PRINT_DEBUG("collecting where OD references");
    IDListNode *order_cols_where = collect_sortCols(remaining_exprs, 0);
    
    OPTIM_PRINT_DEBUG("collecting projection all col references");
    IDListNode *all_cols_proj = collect_AllColsProj(proj);
    
    OPTIM_PRINT_DEBUG("collecting projection all col references");
    IDListNode *all_cols_group = collect_AllColsGroupby(grouphaving); 
    
    
    IDListNode *all_cols = unionIDList(all_cols_proj, all_cols_group);
    all_cols = unionIDList(all_cols, order_cols_where);
    
    if(in_IDList("*", all_cols))
    { //referencing "all columns" results in a full sort
        sort = order; 
    }
    else
    {
       sort = make_sortCols(order->params.order, all_cols);
    }
   
    //filter order independent, then sort, then filter order dependent
    where = pushdown_logical(sort, order_indep_filter); 
    where = pushdown_logical(remaining_filter, where);
    return where;  
}


//Operations associated with a order-dependent group-by/having
LogicalQueryNode *optim_sort_group_od(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{    
    OPTIM_PRINT_DEBUG("optimizing order-dependent group-by/having");
    LogicalQueryNode *sort = NULL;
    
    IDListNode *all_cols_proj = collect_AllColsProj(proj);
    IDListNode *all_cols_group = collect_AllColsGroupby(grouphaving); 
    IDListNode *all_cols = unionIDList(all_cols_group, all_cols_proj);
    
    if(in_IDList("*", all_cols))
    { //referencing "all columns" results in a full sort
        sort = order; 
    }
    else
    {
       sort = make_sortCols(order->params.order, all_cols);
    }
    
    return pushdown_logical(grouphaving, sort);
}

    
//Operations associated with a order-independenr group-by/having
LogicalQueryNode *optim_sort_group_oi(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{   
    OPTIM_PRINT_DEBUG("optimizing order-independent group-by/having");
    LogicalQueryNode *sort = NULL;
    
    //assume need sorting in proj clause unless order annihilating operators applied
    IDListNode *proj_order_cols = collect_sortColsNamedExpr(proj->params.namedexprs, 1);
    
    if(proj_order_cols == NULL)
    { //no order dependencies in projection
        return grouphaving; 
    }
    else if(in_IDList("*", proj_order_cols))
    { //referencing "all columns" results in a full sort
        sort = order; 
        return pushdown_logical(grouphaving, sort);
    }
    else 
    { //else sort dependent columns, then group (based on experimental results found in aquery/test/groupsorting.q and aquery/test/grp_viz.r)
        sort = make_sortCols(order->params.order, proj_order_cols);
        return pushdown_logical(grouphaving, sort);
    }
    
    return grouphaving;
}

LogicalQueryNode *optim_sort_proj(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
    OPTIM_PRINT_DEBUG("optimizing projection");
    //assume need sorting in proj clause unless order annihilating operators applied
    IDListNode *proj_order_cols = collect_sortColsNamedExpr(proj->params.namedexprs, 1);
    LogicalQueryNode *sort = NULL;
     
    if(proj_order_cols == NULL)
    { //no order dependencies
        return proj; 
    }
    else if(in_IDList("*", proj_order_cols))
    { //referencing "all columns" results in a full sort
        sort = order; 
        return pushdown_logical(proj, sort);     
    }
    else
    { //only sort specific columns necessary
        sort = make_sortCols(order->params.order, proj_order_cols);
        return pushdown_logical(proj, sort);
    }
     
}

//TODO: modify to handle more complicated froms....
char *get_table_name(LogicalQueryNode *from)
{
    if(from->node_type == SIMPLE_TABLE)
    {
        return from->params.name;
    }
    else
    {
        return get_table_name(from->arg);
    }
}




LogicalQueryNode *assemble_opt1(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
    if(order == NULL)
    {
        return assemble_base(proj, from, order, where, grouphaving);
    }
    
    if(order != NULL)
    { //try to remove order clause first as a result of existing order
        Symentry *entry = lookup_sym(env, get_table_name(from));
        OrderNode *want_order = order->params.order;
        OrderNode *have_order = (entry == NULL) ? NULL : entry->order_spec;
        
        order->params.order = get_NeededSort(have_order, want_order);
        
        if(order->params.order == NULL)
        {
            order = NULL;
        }
    }
    
    if(order != NULL)
    {
        if(where != NULL && where->order_dep)
        {
            where = optim_sort_where(proj, from, order, where, grouphaving);
        }
        else if(grouphaving != NULL && grouphaving->order_dep)
        { 
            grouphaving = optim_sort_group_od(proj, from, order, where, grouphaving);
        }
        else if(grouphaving != NULL && !grouphaving->order_dep)
        {
            grouphaving = optim_sort_group_oi(proj, from, order, where, grouphaving);
        }
        else //just check projection clauses
        {
            proj = optim_sort_proj(proj, from, order, where, grouphaving);
        }
    }
    
    //send things along to assemble as usual...
    return assemble_base(proj, from, NULL, where, grouphaving);
}




LogicalQueryNode *assemble_plan(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
    OPTIM_PRINT_DEBUG("building query");
    return assemble_opt1(proj, from, order, where, grouphaving);
}


void print_table_dummy(GenList *t)
{
    OPTIM_PRINT_DEBUG("-->ELEM IN LIST");
    int x = 0; 
    print_logical_query((LogicalQueryNode *) t->data, x, &x);
}

void print_join_clause(GenList *e)
{
    printf("%d ", is_JoinClause((ExprNode *) e->data));
}



#if STAND_ALONE
int main()
{
    int x = 0;
        
    //Testing generic lists
    OPTIM_PRINT_DEBUG("testing generic list");
    GenList *list = NULL;
    char *str1 = "this";
    char *str2 = "is";
    char *str3 = "fun";
    list = list_append(list, (void *) str2);
    list = list_prepend(list, (void *) str1);
    list = list_append(list, (void *) str3);
    list_foreach(list, print_str);
    list = list_remove_first(list, str2);
    OPTIM_PRINT_DEBUG("removing is");
    list_foreach(list, print_str);
    char *other = "bla";
    
    OPTIM_PRINT_DEBUG("removing something that is not in list");
    list = list_remove_first(list, other);
    list_foreach(list, print_str);
    
    
    
    ///Testing extracting indirect order dependencies affected by sorting
    Symtable *env = init_symtable();
    ExprNode *id1 = make_id(env, strdup("c1"));
    ExprNode *id2 = make_id(env, strdup("c2"));
    ExprNode *id31 = make_id(env, strdup("c3"));
    ExprNode *id32 = make_id(env, strdup("c3"));
    ExprNode *id4 = make_id(env, strdup("c4"));
    
    ExprNode *op1  = make_arithNode(PLUS_EXPR, id31, id4); //c3 + c4
    ExprNode *op2  = make_callNode(make_builtInFunNode(env, strdup("min")), op1); //min(c3+c4)
    ExprNode *op3  = make_arithNode(PLUS_EXPR, id2, op2); //c2 + min(c3+c4)
    ExprNode *op4  = make_arithNode(MULT_EXPR, id1, op3); //c1 * (c2 + min(c3+c4))
    ExprNode *op5  = make_callNode(make_builtInFunNode(env, strdup("max")), op4); //max(c1 * (c2 + min(c3 + c4)))
    ExprNode *op6  = make_callNode(make_builtInFunNode(env, strdup("sums")), id32); //sums(c3)
    ExprNode *comb = make_arithNode(MULT_EXPR, op5, op6); //max(c1 * (c2 + min(c3 + c4))) * sums(c3)   

     
    printf("digraph {\n");
    print_expr(comb, x, &x);
    printf("}\n");
     
    IDListNode *deps = collect_sortCols(comb, 0);
    OPTIM_PRINT_DEBUG("final sorting list");
    print_id_list(deps, x, &x); //should be c3 and c4
    
    //Testing partitioning an expression list based on order dependency information
    //Need to allocate mem for strings to simulate how things wokr when within bison
    ExprNode *p_id1 = make_id(env, strdup("c1"));
    ExprNode *p_id2 = make_id(env, strdup("c2"));
    p_id1->order_dep = 0;
    p_id2->order_dep = 0;
    
    ExprNode *p_id3 = make_id(env, strdup("c3"));
    p_id3->order_dep = 1;
    
    ExprNode *p_id4 = make_id(env, strdup("c4"));
    p_id4->order_dep = 1;
    
    p_id1->next_sibling = p_id2;
    p_id2->next_sibling = p_id3;
    p_id3->next_sibling = p_id4;
    
    ExprNode *exprlist = make_exprListNode(p_id1);
    ExprNode *order_dep = NULL;
    ExprNode *order_indep = NULL;
    
    partExpr_OnOrder(exprlist->first_child,&order_indep, &order_dep);
    OPTIM_PRINT_DEBUG("order-independent expressions from paritioning");
    print_expr(order_indep, x, &x);
    OPTIM_PRINT_DEBUG("order-dependent expressions from paritioning");
    print_expr(order_dep, x, &x);
    
    //Testing extracting all column references...
    OPTIM_PRINT_DEBUG("All columns");
    print_id_list(collect_AllCols(comb), x, &x);
    OPTIM_PRINT_DEBUG("expression");
    print_expr(comb, x, &x);

    //Testing order dependencies in named expressions
    NamedExprNode *n1 = make_NamedExprNode(strdup("calc_1"), comb);
    ExprNode *idx = make_id(env,strdup("rand"));
    ExprNode *idx2 = make_id(env, strdup("c4"));
    ExprNode *add_em = make_arithNode(PLUS_EXPR, idx, idx2); //contaminate rand with c4, so now need to sort rand, c4, c3
    NamedExprNode *n2 = make_NamedExprNode(strdup("calc_2"), add_em);
    n1->next_sibling = n2;
    OPTIM_PRINT_DEBUG("looking for order dependencies in named expressions");
    IDListNode *found =  collect_sortColsNamedExpr(n1, 0);
    print_id_list(found, x, &x);
    
    //Testing deep copy of expressions
    OPTIM_PRINT_DEBUG("testing deep copies of expressions");
    OPTIM_PRINT_DEBUG("original");
    print_expr(comb, x, &x);
    OPTIM_PRINT_DEBUG("deep copy");
    ExprNode *copy_of_comb = deepcopy_ExprNode(comb); 
    print_expr(copy_of_comb, x, &x);
    
    //Testing deep copy of named expression
    OPTIM_PRINT_DEBUG("testing deep copies of expressions");
    OPTIM_PRINT_DEBUG("original");
    print_named_expr(n1, x, &x);
    OPTIM_PRINT_DEBUG("deep copy");
    NamedExprNode *copy_of_n1 = deepcopy_NamedExprNode(n1);
    print_named_expr(copy_of_n1, x, &x);


    //Testing extraction of join clauses
    ExprNode *table_A = make_id(env, "A");
    ExprNode *table_B = make_id(env, "B");
    ExprNode *table_C = make_id(env, "C");
    ExprNode *col_1 = make_id(env, "c1");
    ExprNode *col_2 = make_id(env, "c2");
    ExprNode *acc1 = make_colDotAccessNode(deepcopy_ExprNode(table_A), deepcopy_ExprNode(col_1));
    ExprNode *acc2 = make_colDotAccessNode(deepcopy_ExprNode(table_B), deepcopy_ExprNode(col_1));
    ExprNode *acc3 = make_colDotAccessNode(deepcopy_ExprNode(table_C), deepcopy_ExprNode(col_2));
    ExprNode *jc_1 = make_compNode(NEQ_EXPR, deepcopy_ExprNode(acc1), deepcopy_ExprNode(acc2));
    ExprNode *jc_2 = make_compNode(EQ_EXPR, deepcopy_ExprNode(acc2), deepcopy_ExprNode(acc3));
    ExprNode *reg = make_compNode(LT_EXPR, deepcopy_ExprNode(col_1), make_int(10));
    
    
    ExprNode *full = deepcopy_ExprNode(jc_1);
    full->next_sibling = deepcopy_ExprNode(reg);
    full->next_sibling->next_sibling = deepcopy_ExprNode(jc_2);
    ExprNode *full_list = make_exprListNode(full);
    print_expr(full_list, x, &x);
    
    OPTIM_PRINT_DEBUG("testing grouping join clauses and separating from others");
    ExprNode *join_filters = NULL;
    ExprNode *other_filters = NULL;    
    groupExpr_OnJoin(full_list->first_child, &join_filters, &other_filters);
    OPTIM_PRINT_DEBUG("printing join clauses");
    print_expr(join_filters, x, &x);
    OPTIM_PRINT_DEBUG("printing remaining clauses");
    print_expr(other_filters, x, &x);
    
    
    
    

    //Testing split from clause
    LogicalQueryNode *table1 = make_table("t1");
    LogicalQueryNode *table2 = make_table("t2");
    LogicalQueryNode *table3 = make_table("t3");
    LogicalQueryNode *table4 = make_table("t4");
    ExprNode *join_cond = deepcopy_ExprNode(jc_1);
    LogicalQueryNode *joined_tables = make_joinOn(INNER_JOIN_ON, table3, table4, join_cond);
    LogicalQueryNode *cross1 = make_cross(table1, table2);
    LogicalQueryNode *cross2 = make_cross(joined_tables, cross1);
    GenList *split = split_from(cross2);
    OPTIM_PRINT_DEBUG("PRINTING SPLIT LIST");
    list_foreach(split, print_table_dummy);
    
    //Splitting an expression based on aggregate use
    OPTIM_PRINT_DEBUG("testing parting expressions based on first use of aggregate");
    ExprNode *agg_id1 = make_id(env,"c1");
    ExprNode *agg_id2 = make_id(env,"c2");
    ExprNode *agg_id3 = make_id(env,"c3");
    ExprNode *agg_id4 = make_id(env,"c4");
    ExprNode *agg_id5 = make_id(env,"c5");
    ExprNode *agg_id6 = make_id(env,"c1");
    ExprNode *agg_e1 = make_logicOpNode(EQ_EXPR, deepcopy_ExprNode(agg_id1), deepcopy_ExprNode(agg_id2));
    ExprNode *agg_e2 = make_logicOpNode(EQ_EXPR, deepcopy_ExprNode(agg_id3), deepcopy_ExprNode(agg_id4));
    
    
    //add a fake UDF that does not use aggregates
    put_sym(env, "my_fake_fun", FUNCTION_TYPE, 0, 0);
    
    ExprNode *agg_e3 = make_callNode(make_udfNode(env, "my_fake_fun"), deepcopy_ExprNode(agg_id5));
    ExprNode *agg_e4 = make_logicOpNode(EQ_EXPR, deepcopy_ExprNode(agg_id5), deepcopy_ExprNode(agg_id6));
    agg_e1->next_sibling = agg_e2;
    agg_e2->next_sibling = agg_e3;
    agg_e3->next_sibling = agg_e4;
    ExprNode *no_agg = NULL;
    ExprNode *agg = NULL;
    partExpr_OnAgg(agg_e1, &no_agg, &agg);
    OPTIM_PRINT_DEBUG("pre-aggregate");
    print_expr(no_agg, x, &x);
    OPTIM_PRINT_DEBUG("post-aggregate");
    print_expr(agg, x, &x);

    
    
    
    /*

    
    //Testing cross warnings (when tables referenced in  where clause do not match those in  join clauses)
    LogicalQueryNode *cross1 = make_cross(make_table("A"), make_table("B"));
    LogicalQueryNode *cross2 = make_cross(cross1, make_table("D"));
    IDListNode *table_from_refs = collect_TablesFrom(cross2);
    IDListNode *table_expr_refs = collect_TablesExpr(join_filters);
    OPTIM_PRINT_DEBUG("printing list of tables involved in cross");
    print_id_list(table_from_refs, x, &x);
    OPTIM_PRINT_DEBUG("printing list of tables involved in join filters");
    print_id_list(table_expr_refs,x, &x);
    
    
    //Testing collection and memoization of tables referenced in an expression
    ExprNode *full_list2 = deepcopy_ExprNode(full_list);
    IDListNode *full_list2_refs = collect_TablesExpr(full_list);
    OPTIM_PRINT_DEBUG("printing list of tables involved in an expression");
    print_id_list(full_list2_refs,x, &x);
    OPTIM_PRINT_DEBUG("printing list of tables memoized for each expression");
    ExprNode *curr, *next;
    for(curr = full_list2->first_child; curr != NULL; curr = next)
    {
        next = curr->next_sibling;
        curr->next_sibling = NULL;
        OPTIM_PRINT_DEBUG("expression");
        print_expr(curr, x, &x);
        
        if(curr->tables_involved == NULL)
        {
            OPTIM_PRINT_DEBUG("no tables memoized!");
        }
        else
        {
            OPTIM_PRINT_DEBUG("tables memoized!");
            print_id_list(curr->tables_involved, x, &x);
        }
        
    }
    */
    
    
    
    
    
    
}
#endif



