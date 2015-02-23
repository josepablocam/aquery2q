#ifndef AST_PRINT_H
#define AST_PRINT_H


void print_expr(ExprNode *n, ExprNodeType p, int type, int indent);

void print_udf_def(UDFDefNode *udf);
void print_udf_args(IDListNode *args, int ct);
void print_udf_body(UDFBodyNode *body);
void print_var_def(LocalVarDefNode *vardef);
void print_logical_query(LogicalQueryNode *l);
void print_create(CreateNode *create);
void print_full_query(FullQueryNode *full);
void print_local_queries(LocalQueryNode *local);
void print_create(CreateNode *create);
void print_create_source(CreateSourceNode *src);
void print_schema(SchemaNode *schema);
void print_top_level(TopLevelNode *top);
void print_insert(InsertNode *ins);
void print_id_list(IDListNode *ids);

#endif