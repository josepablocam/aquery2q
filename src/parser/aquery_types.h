#ifndef AQUERY_TYPES_H
#define AQUERY_TYPES_H
//Datatypes used for symbol table, and AST storage
//UNKNOWN_TYPE represents dynamic type info unavailable to us at compile time
typedef enum DataTypes {
     INT_TYPE, 
     FLOAT_TYPE, 
     DATE_TYPE, 
     BOOLEAN_TYPE, 
     HEX_TYPE, 
     TABLE_TYPE, 
     VIEW_TYPE, 
     FUNCTION_TYPE, 
     CALL_TYPE, 
     UNKNOWN_TYPE,  //unknown dynamic types (column names, external tables, function calls etc)
	 ERROR_TYPE, //we create a type error that we can use to point out issues later on
     } DataType;

typedef enum NodeTypes {
	//Expressions
	COMPUTABLE_NODE, //nodes that we can reduce while we build the AST
	CONSTANT_NODE, 
	ROWID_NODE,
	COLUMN_DOT_ACCESS_NODE,
	ASTERISK_NODE,
	//Case expressions
	CASE_EXP_NODE,
	CASE_CASE_CLAUS_NODE,
	CASE_WHEN_NODE,
	CASE_ELSE_NODE,
	NILADIC_CALL_NODE, //no arguments
	CALL_NODE, //we can view indexing as a call as well
	INDEX_NODE,
	BUILT_IN_FUN_NODE, 
	//Math operations
	EXP_NODE,
	MULT_NODE,
	DIV_NODE,
	ADD_NODE,
	MINUS_NODE,
	LT_NODE,
	GT_NODE,
	LE_NODE,
	GE_NODE,
	EQ_NODE,
	NEQ_NODE,
	LAND_NODE, //logical and from expression section
	LOR_NODE,
	VAL_LIST //comma value expression list 
	} NodeType;
	
	
	
	//Type checking operations
int is_int(DataType x);
int is_float(DataType x);
int is_bool(DataType x);
int is_numeric(DataType x);
int is_error(DataType x);
DataType unif_numeric(DataType x, DataType y);
DataType unif_override(DataType poss, DataType override, DataType x, DataType y);
DataType unif_comp(DataType x, DataType y);
DataType unif_logic(DataType x, DataType y);





	

#endif
