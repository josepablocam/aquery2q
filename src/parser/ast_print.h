#ifndef AST_PRINT_H
#define AST_PRINT_H


void print_expr(ExprNode *n, ExprNodeType p, int type, int indent);

void print_udf_def(UDFDefNode *udf);
void print_udf_args(UDFArgsNode *args, int ct);
void print_udf_body(UDFBodyNode *body);
void print_var_def(LocalVarDefNode *vardef);

#endif