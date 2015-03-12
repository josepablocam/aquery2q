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
#define OPTIM_DEBUG 0
#define OPTIM_PRINT_DEBUG(str) if(OPTIM_DEBUG) printf("---->OPTIM DEBUGGING: %s\n", str)


extern const char *ExprNodeTypeName[]; //aquery_print.c

#if !STAND_ALONE
extern int optim_level; //aquery.y
extern Symtable *env; //aquery.y
#endif

#if STAND_ALONE
int optim_level = 1;
Symtable *env;
#endif


//Creating deep copies of LogicalQueryNodes in order to reproduce the original plan
//before any optimizations, so we can create multiple options
LogicalQueryNode *deepcopy_LogicalQueryNode(LogicalQueryNode *node)
{
    LogicalQueryNode *copy = NULL;
    
    if(node != NULL)
    {
        copy = make_EmptyLogicalQueryNode(node->node_type);
        copy->order_dep = node->order_dep;
        
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
    NamedExprNode *copy = NULL;
    
    if(node != NULL)
    {
        copy = make_NamedExprNode(strdup(node->name), deepcopy_ExprNode(node->expr));
        copy->next_sibling = deepcopy_NamedExprNode(node->next_sibling);
    }
    
    return copy;
}

IDListNode *deepcopy_IDListNode(IDListNode *node)
{
    IDListNode *copy = NULL;
    
    if(node != NULL)
    {
        copy = make_IDListNode(strdup(node->name), deepcopy_IDListNode(node->next_sibling));
    }
    
    return copy;
}
    
    
    
OrderNode *deepcopy_OrderNode(OrderNode *node)
{
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
    ExprNode *copy= NULL;
    
    if(node != NULL)
    {
        //Create an empty expression node with your general info
        copy = make_EmptyExprNode(node->node_type);
        copy->data_type = node->data_type;
        copy->order_dep = node->order_dep;
        copy->sub_order_dep = node->sub_order_dep;
        copy->can_sort = node->can_sort;
        
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
                {
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













//Used to keep track of interactions between columns that might lead to sorting otherwise order-independent columns
//Consider an expression such as (c1 * c3) + max(sums(c3 + c2))  -> c2 and c3 sorted because of sums, but c1 too because of *c3
NestedIDList *make_NestedIDList(IDListNode *list, NestedIDList *next_list)
{
    if(list == NULL)
    {
        return next_list;
    }
    else
    {
       NestedIDList *nl = malloc(sizeof(NestedIDList));
       nl->list = list;
       nl->next_list = next_list;
       return nl; 
    }
}

//Crude printing of nested list, really just for quick debugging....
void print_nested_id_list(NestedIDList *nl)
{
    NestedIDList *curr = nl;
    IDListNode *list;
    
    while(curr != NULL)
    {
        putchar('(');
        list = curr->list;
        while(list != NULL)
        {
            printf("%s,", list->name);
            list = list->next_sibling;
        }
        printf(")\n");
        curr = curr->next_list;     
    }
    
}

//returns 1 if name is in list, 0 otherwise, uses strcmp
int in_IDList(char *name, IDListNode *list)
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
IDListNode *add_interactionsToSort(NestedIDList *interact, IDListNode *need_sort)
{
    int added = 1;
    NestedIDList *curr_interact = NULL;
    IDListNode *col = NULL;
    
    while(added != 0)
    {
        added = 0;
        for(curr_interact = interact ; curr_interact != NULL; curr_interact = curr_interact->next_list)
        {   
            OPTIM_PRINT_DEBUG("Checking related:");
            //print_id_list(curr_interact->list, n, &n);
            for(col = curr_interact->list; col != NULL; col = col->next_sibling)
            {
                if(in_IDList(col->name, need_sort))
                {
                    OPTIM_PRINT_DEBUG("found contaminated list");
                    need_sort = unionIDList(need_sort, curr_interact->list); //add to sort
                    curr_interact->list = NULL; //we have added everything we needed, rest has been freed during union
                    added = 1;
                    break;
                }
            }
        }
    }
    
    //Anything that is not null in potential was never added to sort list and will never be added, so free it
    
    NestedIDList *to_free_nested = NULL;
    IDListNode *to_free_list = NULL; 
    
    curr_interact = interact;
    while(curr_interact != NULL)
    {
        to_free_nested = curr_interact; 
        curr_interact = curr_interact->next_list;
        
        if(to_free_nested->list != NULL)
        { //free any contents
            OPTIM_PRINT_DEBUG("freeing a list of ids");
            free_IDListNode(to_free_nested->list);
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
    
    NestedIDList **potential_ptr = malloc(sizeof(NestedIDList *));
    *potential_ptr = NULL;
    
    IDListNode *top = collect_sortCols0(od_expr, add_from_start, need_sort_ptr, potential_ptr);
    *potential_ptr = make_NestedIDList(top, *potential_ptr);
    
    OPTIM_PRINT_DEBUG("returned from collect_sortCols0");

    return add_interactionsToSort(*potential_ptr, *need_sort_ptr);
}



//Collect the columns that need to be sorted given dependencies in a named expression AST
IDListNode *collect_sortColsNamedExpr(NamedExprNode *nexprs, int add_from_start)
{
    IDListNode **need_sort_ptr = malloc(sizeof(IDListNode *));
    *need_sort_ptr = NULL; 
    
    NestedIDList **potential_ptr = malloc(sizeof(NestedIDList *));
    *potential_ptr = NULL;
    
    IDListNode *top = NULL;
    
    NamedExprNode *curr_nexpr = nexprs;
    int x = 0;
    
    while(curr_nexpr != NULL)
    { 
        OPTIM_PRINT_DEBUG("running over named expression");
        //print_expr(curr_nexpr->expr, x, &x);
        top = collect_sortCols0(curr_nexpr->expr, add_from_start, need_sort_ptr, potential_ptr);
        *potential_ptr = make_NestedIDList(top, *potential_ptr);
        
        curr_nexpr = curr_nexpr->next_sibling;
    }

    OPTIM_PRINT_DEBUG("returned from collect_sortCols0");
    //TODO: free up memory for structures used in this search
    return add_interactionsToSort(*potential_ptr, *need_sort_ptr);
}


IDListNode *collect_sortCols0(ExprNode *node, int add_flag, IDListNode **need_sort_ptr, NestedIDList **potential_ptr)
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
       return collect_sortCols0(node->first_child->next_sibling, add_flag, need_sort_ptr, potential_ptr);
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
            *potential_ptr = make_NestedIDList(child, *potential_ptr);  //we stop "bubbling up" interactions here
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
       return collect_AllCols(node->first_child->next_sibling);
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

//Partition a list of expressions into order independent and order dependent lists
//NOTE: renders original expression useless, since manipulates all the pointers etc
void part_ExprOnOrder(ExprNode *expr, ExprNode **order_indep, ExprNode **order_dep)
{
    OPTIM_PRINT_DEBUG("partitioning expression list on order");
    ExprNode *curr, *next;
 
    for(next = NULL, curr = expr->first_child; curr != NULL; curr = next)
    {
        next = curr->next_sibling; //store next expression
        curr->next_sibling = NULL; //remove link between current and next expression
        
        //Put current expresion in right list based on order dependence info
        if(curr->order_dep || curr->sub_order_dep)
        {
            *order_dep = append_toExpr(*order_dep, curr);
        }
        else
        {
           *order_indep = append_toExpr(*order_indep, curr); 
        }
    }    
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

//Returns additional sorting missing from have order to get to want order
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
    
    OrderNode *to_free = want;
    //free up any information no longer needed
    while(want_curr != want)
    {
        to_free = want;
        want = want->next;
        
        OPTIM_PRINT_DEBUG("freeing order information");
        free(to_free->col->data.str); //free string
        free(to_free->col); //free expression node
        free(to_free); //free order node
    }
    
    return want;
}




LogicalQueryNode *optim_sort_where(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
    OPTIM_PRINT_DEBUG("optimizing where clause");
    LogicalQueryNode *order_indep_filter = NULL;
    LogicalQueryNode *order_dep_filter = NULL;
    LogicalQueryNode *sort = NULL;
    ExprNode *order_indep_exprs = NULL;
    ExprNode *order_dep_exprs = NULL;
    
    part_ExprOnOrder(where->params.exprs, &order_indep_exprs, &order_dep_exprs);
    
    if(order_indep_exprs != NULL)
    { //perform any order-independent filtering first
        OPTIM_PRINT_DEBUG("found order independent where predicates");
        //print_expr(order_indep_exprs, i, &i);
        order_indep_filter = make_filterWhere(NULL, order_indep_exprs);
        
    }
    
    order_dep_filter = make_filterWhere(NULL, order_dep_exprs);
    
    //Find all column references in projection and groupbyclauses
    
    OPTIM_PRINT_DEBUG("collecting where OD references");
    IDListNode *order_cols_where = collect_sortCols(order_dep_exprs, 0);
    
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
    where = pushdown_logical(order_dep_filter, where);
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
    { //else sort-each order dependent columns
       sort = make_sortEachCols(order->params.order, proj_order_cols);
       return pushdown_logical(sort, grouphaving);
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
   
    //find what subset of sort do we need to execute
    
    if(order != NULL)
    { //try to remove order clause first as a result of existing order
        Symentry *entry = lookup_sym(env, get_table_name(from));
        OrderNode *want_order = order->params.order;
        OrderNode *have_order = (entry == NULL) ? NULL : entry->order_spec;
        //incremental sorting needed
        want_order = get_NeededSort(have_order, want_order);
        
        if(want_order == NULL)
        {
            //printf("******** don't need order anymore\n");
            free(order);
            order = NULL;
        }
        else
        {
            order->params.order = want_order;
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
    //return assemble_base(proj, from, order, where, grouphaving);
    return assemble_opt1(proj, from, order, where, grouphaving);
}




#if STAND_ALONE
int main()
{
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
    ExprNode *copy_of_comb = deepcopy_ExprNode(comb); 
     
    int x = 0;
    printf("digraph {\n");
    print_expr(comb, x, &x);
    printf("}\n");
     
    IDListNode *deps = collect_sortCols(comb, 0);
    OPTIM_PRINT_DEBUG("final sorting list");
    print_id_list(deps, x, &x);
    
    //Testing partitioning an expression list based on order dependency information
    //Need to allocate mem for strings to simulate how things wokr when within bison
    ExprNode *p_id1 = make_id(env, strdup("c1"));
    ExprNode *p_id2 = make_id(env, strdup("c2"));
    p_id1->order_dep = 1;
    p_id2->order_dep = 1;
    
    ExprNode *p_id3 = make_id(env, strdup("c3"));
    p_id3->order_dep = 0;
    
    ExprNode *p_id4 = make_id(env, strdup("c4"));
    p_id4->order_dep = 1;
    
    p_id1->next_sibling = p_id2;
    p_id2->next_sibling = p_id3;
    p_id3->next_sibling = p_id4;
    
    
    ExprNode *exprlist = make_exprListNode(p_id1);
    ExprNode *order_dep = NULL;
    ExprNode *order_indep = NULL;
    
    part_ExprOnOrder(exprlist,&order_indep, &order_dep);
    OPTIM_PRINT_DEBUG("order-independent expressions from paritioning");
    print_expr(order_indep, x, &x);
    OPTIM_PRINT_DEBUG("order-dependent expressions from paritioning");
    print_expr(order_dep, x, &x);
    
    OPTIM_PRINT_DEBUG("All columns");
    print_id_list(collect_AllCols(comb), x, &x);
    OPTIM_PRINT_DEBUG("expression");
    print_expr(comb, x, &x);

    
    NamedExprNode *n1 = make_NamedExprNode(strdup("calc_1"), comb);
    ExprNode *idx = make_id(env,strdup("rand"));
    ExprNode *idx2 = make_id(env, strdup("c4"));
    ExprNode *add_em = make_arithNode(PLUS_EXPR, idx, idx2);
    NamedExprNode *n2 = make_NamedExprNode(strdup("calc_2"), add_em);
    n1->next_sibling = n2;
    OPTIM_PRINT_DEBUG("******looking for order dependencies in named expressions");
    IDListNode *found =  collect_sortColsNamedExpr(n1, 0);
    print_id_list(found, x, &x);
    
    OPTIM_PRINT_DEBUG("******testing deep copies");
    OPTIM_PRINT_DEBUG("original");
    print_expr(comb, x, &x);
    OPTIM_PRINT_DEBUG("deep copy");
    print_expr(copy_of_comb, x, &x);
    
}
#endif



