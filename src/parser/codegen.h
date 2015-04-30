#ifndef AQUERY_CG_H
#define AQUERY_CG_H

#include "aquery_types.h"
#include "ast.h"

void native_comma_enlist();
void native_kw_enlist();

/* q utilities for aquery */
void init_aq_helpers();
void add_to_dc(char *alias, char *tbl);
void init_dc();
void add_to_dt(char *alias, char *tbl);
void sort_where_clause_by_ix(char *tbl);
char *gen_table_nm();



/* Expressions */
void cg_Constant(ExprNode *c);
void cg_LookupCol(char *nm);
void cg_ID(ExprNode *id);
void cg_rowId();
void cg_allCols(char *table_name);
int aquery_to_q_builtin_ix(char *fun);
void cg_callNode(ExprNode *call);
void cg_Oddix();
void cg_Evenix();
void cg_Everynix(int everyn);
void cg_indexNode(ExprNode *ixnode);
void cg_Neg(ExprNode *expr);
char *aquery_to_q_op(ExprNodeType op_type);
void cg_OpNode(ExprNode *expr);
void cg_ExprList(ExprNode *expr);
void cg_ExprNode(ExprNode *expr);

/* overloads */
int is_overloaded(char *name);
int ct_exprs(ExprNode *expr);

/* function definitions */
void cg_UDFDefNode(UDFDefNode *fundef);
void cg_DefArgList(IDListNode *args);
void cg_UDFBodyNode(UDFBodyNode *body);
void cg_LocalVar(NamedExprNode *vardef);

/* query related */
char *cg_SimpleTable(LogicalQueryNode *node);
char *cg_Alias(LogicalQueryNode *a);
char *cg_FilterWhere(LogicalQueryNode *where);
char *gc_ProjectSelect(LogicalQueryNode *proj);
void cg_NameExprTuples(char *tblnm, NamedExprNode *nexpr, int id_ctr); //dictionary
char *cg_groupBy(LogicalQueryNode *node);
NamedExprNode *groupExpr_to_NamedGroupExpr(ExprNode *exprs);
char *cg_flatten(LogicalQueryNode *node);
char *cg_LogicalQueryNode(LogicalQueryNode *node);
char *cg_queryPlan(LogicalQueryNode *node);


/* local and full queries */
void cg_LocalQueryNode(LocalQueryNode *local);
void cg_colRename(IDListNode *names);
void cg_LocalQueries(LocalQueryNode *locals);
void cg_FullQuery(FullQueryNode *full_query);


/* sorting related */
char *cg_Sort(LogicalQueryNode *node); //naive
void cg_SimpleOrder(OrderNode *ordnode); //naive
void cg_SortIx(OrderNode *ordnode); //optimized
char *cg_SortCols(LogicalQueryNode *node); //optimized



#endif