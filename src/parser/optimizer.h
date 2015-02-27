#ifndef AQUERY_OPTIMIZER_H
#define AQUERY_OPTIMIZER_H

#include "ast.h"
#include "aquery_types.h"

int is_sortable(ExprNodeType type);

//Optimization 1: sorting only necessary columns
ExprNode *make_singleColSort(ExprNode *expr);
ExprNode *make_singleColDeSort(ExprNode *expr);
LogicalQueryNode *make_computeSortIx(LogicalQueryNode *ord);
ExprNode *minsort_ixSortExpr(ExprNode *node, int create_ix);
LogicalQueryNode *minsort_where(LogicalQueryNode *where, LogicalQueryNode *order);
LogicalQueryNode *assemble_optim1(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);
LogicalQueryNode *assemble_plan(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving);



#endif