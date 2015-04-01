#ifndef AQUERY_OPTIMIZER_H
#define AQUERY_OPTIMIZER_H

#include "ast.h"
#include "aquery_types.h"


//Implementing a generic single linked list for use in the optimizer
typedef struct GenList {
    int id; //useful sometimes to compare positions in list
    void *data;
    struct GenList *next;
} GenList;

//Operations on generic linked list
GenList *list_alloc(void *data);
GenList *list_append(GenList *list, void *data);
GenList *list_prepend(GenList *list, void *data);
GenList *list_remove_first(GenList *list, void *data);
void list_foreach(GenList *list, void (*fun)(GenList *));
void list_foreach_warg(GenList *list, void (*fun)(GenList *, void *), void *arg);
int list_length(GenList *list);


//Deep-copies of parts of AST 
LogicalQueryNode *deepcopy_LogicalQueryNode(LogicalQueryNode *node);
NamedExprNode *deepcopy_NamedExprNode(NamedExprNode *node);
IDListNode *deepcopy_IDListNode(IDListNode *node);
OrderNode *deepcopy_OrderNode(OrderNode *node);
ExprNode *deepcopy_ExprNode(ExprNode *node);



//Mapping Lists of TableNames to expressions
typedef struct TablesToExprsMap
{
    IDListNode *tables;
    ExprNode *exprs;
    struct TablesToExprsMap *next_tuple;
} TablesToExprsMap;

TablesToExprsMap *make_TablesToExprsMap(IDListNode *tables, ExprNode *exprs, TablesToExprsMap *map);


//Manipulating exprnodes as lists and splitting
void partExpr_atFirst(ExprNode *orig, ExprNode **before, ExprNode **after, int (*pred)(ExprNode *));
void groupExpr_onUnaryPred(ExprNode *orig, ExprNode **true, ExprNode **false, int (*pred)(ExprNode *));
void groupExpr_onBinaryPred(ExprNode *orig, ExprNode **true, ExprNode **false, int (*pred)(ExprNode *, void*), void* data);



//ID lists utilities
IDListNode *unionIDList(IDListNode *x, IDListNode *y);
int in_IDList(const char *name, IDListNode *list);
int length_IDList(IDListNode *l);
int is_subsetIDLists(IDListNode *l1, IDListNode *l2);
int is_setEquivIDLists(IDListNode *l1, IDListNode *l2);



IDListNode *add_interactionsToSort(GenList *interact, IDListNode *need_sort);
IDListNode *collect_sortCols(ExprNode *od_expr, int add_from_start);
IDListNode *collect_sortColsNamedExpr(NamedExprNode *nexprs, int add_from_start);
IDListNode *collect_sortCols0(ExprNode *node, int add_flag, IDListNode **need_sort, GenList **potential);

ExprNode *append_toExpr(ExprNode *list, ExprNode *add);
void partExpr_OnOrder(ExprNode *expr, ExprNode **order_indep, ExprNode **order_dep);

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


//Optimizations relating to join-based from clauses
GenList *split_from(LogicalQueryNode *node);
void partExpr_OnAgg(ExprNode *expr, ExprNode **no_agg, ExprNode **agg);
char *get_table_src(ExprNode *expr);
IDListNode *collect_TablesExpr(ExprNode *exp);
int is_JoinClause(ExprNode *expr);
void groupExpr_OnJoin(ExprNode *expr, ExprNode **join_filters, ExprNode **other_filters);
void check_warn_Join(LogicalQueryNode *from, ExprNode *join_filters);
void part_ExprOnTableNms(ExprNode *expr, ExprNode **refs, ExprNode **no_refs);


#endif