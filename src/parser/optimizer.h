#ifndef AQUERY_OPTIMIZER_H
#define AQUERY_OPTIMIZER_H

#include "ast.h"
#include "aquery_types.h"

//Deep-copies of parts of AST 
LogicalQueryNode *deepcopy_LogicalQueryNode(LogicalQueryNode *node);
NamedExprNode *deepcopy_NamedExprNode(NamedExprNode *node);
IDListNode *deepcopy_IDListNode(IDListNode *node);
OrderNode *deepcopy_OrderNode(OrderNode *node);
ExprNode *deepcopy_ExprNode(ExprNode *node);


typedef struct NestedIDList
{
    IDListNode *list;
    struct NestedIDList *next_list;
} NestedIDList;

NestedIDList *make_NestedIDList(IDListNode *list, NestedIDList *next_list);

//Mapping Lists of TableNames to expressions
typedef struct TablesToExprsMap
{
    IDListNode *tables;
    ExprNode *exprs;
    struct TablesToExprsMap *next_tuple;
} TablesToExprsMap;

TablesToExprsMap *make_TablesToExprsMap(IDListNode *tables, ExprNode *exprs, TablesToExprsMap *map);




IDListNode *unionIDList(IDListNode *x, IDListNode *y);
int in_IDList(char *name, IDListNode *list);
int length_IDList(IDListNode *l);
int is_setEquivLists(IDListNode *l1, IDListNode *l2);

IDListNode *add_interactionsToSort(NestedIDList *interact, IDListNode *need_sort);
IDListNode *collect_sortCols(ExprNode *od_expr, int add_from_start);
IDListNode *collect_sortColsNamedExpr(NamedExprNode *nexprs, int add_from_start);
IDListNode *collect_sortCols0(ExprNode *node, int add_flag, IDListNode **need_sort, NestedIDList **potential);

ExprNode *append_toExpr(ExprNode *list, ExprNode *add);
void part_ExprOnOrder(ExprNode *expr, ExprNode **order_indep, ExprNode **order_dep);

IDListNode *collect_AllCols(ExprNode *node);
IDListNode *collect_AllColsProj(LogicalQueryNode *node);
IDListNode *collect_AllColsGroupby(LogicalQueryNode *groupby);


//Optimization 1: sorting only necessary columns
OrderNode *get_NeededSort(OrderNode *have, OrderNode *want);
char *get_table_name(LogicalQueryNode *from);
LogicalQueryNode *make_specCols(IDListNode *cols);
LogicalQueryNode *make_sortCols(OrderNode *order, IDListNode *cols);
LogicalQueryNode *make_sortEachCols(OrderNode *order, IDListNode *cols);

LogicalQueryNode *optim_sort_where(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);
LogicalQueryNode *optim_sort_group_od(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);
LogicalQueryNode *optim_sort_group_oi(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);
LogicalQueryNode *optim_sort_proj(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);


LogicalQueryNode *assemble_opt1(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);
LogicalQueryNode *assemble_plan(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);

//Optimization 2: separating order-dependent from order-independent expressions in a list
void print_nested_id_list(NestedIDList *nl);

//Optimizations relating to join-based from clauses
char *get_table_src(ExprNode *expr);
IDListNode *collect_TablesExpr(ExprNode *exp);
int is_JoinClause(ExprNode *expr);
void part_ExprOnJoin(ExprNode *expr, ExprNode **join_filters, ExprNode **other_filters);
void check_warn_Join(LogicalQueryNode *from, ExprNode *join_filters);
void part_ExprOnTableNms(ExprNode *expr, ExprNode **refs, ExprNode **no_refs);


#endif