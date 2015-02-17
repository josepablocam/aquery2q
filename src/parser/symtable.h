#ifndef AQUERY_SYM_TABLE_H

#define AQUERY_SYM_TABLE_H
#define SYM_TABLE_SIZE 32

typedef enum types { INT_TYPE, FLOAT_TYPE, DATE_TYPE, BOOLEAN_TYPE, HEX_TYPE, TABLE_TYPE, VIEW_TYPE, FUNCTION_TYPE, CALL_TYPE, UNKNOWN_TYPE } Type;//UNKNOWN_TYPE represents dynamic type info unavailable to us at compile time

typedef struct symentry {
	char *name;
	Type type;
	struct symentry* next; //linking
} Symentry;

typedef struct symtable {
	Symentry *table[SYM_TABLE_SIZE];
	struct symtable *next; //to stack together symtables
} Symtable;


//Memory allocation and construction functions
Symentry *make_symentry(char *name, Type type);
Symtable *make_symtable();

//Manipulating the symtable stack
Symtable *push_env(Symtable *curr_env);
Symtable *pop_env(Symtable *curr_env);

//Freeing memory and structures
void free_symtable(Symtable *symtable);
void free_names(Symentry *names[]);
void free_symchain(Symentry *this);

//Operations for symbol tables
int symhash(char *name);
Symentry *lookup_sym(Symtable *symtable, char *name);
void put_sym(Symtable *curr_env, char *name, Type type);
void print_symtable(Symtable *env);

#endif