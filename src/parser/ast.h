#ifndef AQUERY_AST_H
#define AQUERY_AST_H
#include "aquery_types.h"
#include "symtable.h"

typedef struct ASTNode {
	NodeType node_type;
	DataType data_type;
	union {
		int ival;
		float fval;
		char *str;
		char *hex;
		char *date;
	} data;
	struct ASTNode *first_child;
	struct ASTNode *first_sibling;
} ASTNode;

int is_computable(ASTNode *x, ASTNode *y);


//Expressions
ASTNode *make_EmptyNode(NodeType type);
ASTNode *make_int(int i);
ASTNode *make_float(float f);
ASTNode *make_date(char *date);
ASTNode *make_hex(char *hex);
ASTNode *make_bool(int boolean);

ASTNode *make_oddix();
ASTNode *make_evenix();
ASTNode *make_intix(int ix);
ASTNode *make_ixNode(ASTNode *ix);

ASTNode *make_valListNode(ASTNode *h, ASTNode *t);

ASTNode *make_callNode(ASTNode *fun, ASTNode *args);
ASTNode *make_builtInFunNode(char *nm);
ASTNode *make_udfNode(Symtable *symtable, char *nm);

ASTNode *make_caseNode(ASTNode *case_clause, ASTNode *when_clauses, ASTNode *else_clauses);
ASTNode *make_caseExpCaseNode(ASTNode *exp);
ASTNode *make_caseWhenNode(ASTNode *exps);
ASTNode *make_WhenClausesNode(ASTNode *h, ASTNode *t);
ASTNode *make_elseClauseNode(ASTNode *exp);
ASTNode *make_rowId();
ASTNode *make_colDotAccessNode(char *nm);
ASTNode *make_allColsNode();



ASTNode *make_ltNode(ASTNode *x, ASTNode *y);
ASTNode *make_gtNode(ASTNode *x, ASTNode *y);
ASTNode *make_leNode(ASTNode *x, ASTNode *y);
ASTNode *make_geNode(ASTNode *x, ASTNode *y);
ASTNode *make_eqNode(ASTNode *x, ASTNode *y);
ASTNode *make_neqNode(ASTNode *x, ASTNode *y);
ASTNode *make_lorNode(ASTNode *x, ASTNode *y);
ASTNode *make_landNode(ASTNode *x, ASTNode *y);

ASTNode *make_addNode(ASTNode *x, ASTNode *y);
ASTNode *make_minusNode(ASTNode *x, ASTNode *y);
ASTNode *make_multNode(ASTNode *x, ASTNode *y);
ASTNode *make_divNode(ASTNode *x, ASTNode *y);
ASTNode *make_expNode(ASTNode *x, ASTNode *y);




#endif