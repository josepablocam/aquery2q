#ifndef AST_PRINT_H
#define AST_PRINT_H


void print_node(int id, const char *label);
void print_edge(int src, int dest);
int print_self(int parent_id, int *id, const char *label);
void print_dot(TopLevelNode *prog);

//toplevel
void print_top_level(TopLevelNode *top, int parent_id, int *id);

//queries
void print_full_query(FullQueryNode *full, int parent_id, int *id);
void print_local_query(LocalQueryNode *local, int parent_id, int *id);
void print_name(const char *name, int parent_id, int *id);
void print_id_list(IDListNode *list, int parent_id, int *id);
void print_logical_query(LogicalQueryNode *step, int parent_id, int *id);
void print_project(LogicalQueryNode *proj, int parent_id, int *id);
void print_delete(LogicalQueryNode *del, int parent_id, int *id);
void print_filter(LogicalQueryNode *filter, int parent_id, int *id);
void print_cartesian(LogicalQueryNode *cart, int parent_id, int *id);
void print_joinOn(LogicalQueryNode *joinOn, int parent_id, int *id);
void print_joinUsing(LogicalQueryNode *joinUsing, int parent_id, int *id);
void print_groupBy(LogicalQueryNode *groupBy, int parent_id, int *id);
void print_table(LogicalQueryNode *table, int parent_id, int *id);
void print_alias(LogicalQueryNode *alias, int parent_id, int *id);
void print_sort(LogicalQueryNode *sort, int parent_id, int *id);
void print_flatten(LogicalQueryNode *flat, int parent_id, int *id);
void print_values(LogicalQueryNode *vals, int parent_id, int *id);
void print_expr(ExprNode *expr, int parent_id, int *id);
void print_named_expr(NamedExprNode *nexpr, int parent_id, int *id);
void print_order(OrderNode *order, int parent_id, int *id);




#endif