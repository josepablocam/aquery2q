/*
	Building out a symbol table to use with bison parser. We maintain the symbol table as  a 
	stack of hash tables (so that we can push/pop easily as we enter different scopes). Within
	a table we handle collisions via chaining.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symtable.h"


//Allocate memory for a symbol table entry, copy variable name, initialize and return
//Exits with error if memory is not succesfully allocated with malloc
Symentry *make_symentry(char *name, Type type)
{
	Symentry *newentry = malloc(sizeof(Symentry));
	
	if(newentry == NULL)
	{
		printf("Unable to allocate Symentry\n");
		exit(1);
	}
	
	newentry->name = strdup(name); //copy the string name
	newentry->type = type;
	newentry->next = NULL;
	
	return newentry;
}

//Allocate memory for symbol table and initializes struct. Exits with error if memory allocation fails
Symtable *make_symtable()
{
	Symtable *symtable = malloc(sizeof(Symtable));
	
	if(symtable == NULL)
	{
		printf("Unable to allocate Symtable\n");
		exit(1);
	}
	
	int i;
	for(i = 0; i < SYM_TABLE_SIZE; i++)
	{
		symtable->table[i] = NULL;
	}
	
	symtable->next = NULL;
	return symtable;
}

//Creates a new symbol table and pushes it onto the stack of symbol tables, returns
//a pointer to the top of the stack
Symtable *push_env(Symtable *curr_env)
{
	Symtable *new_env = make_symtable();
	new_env->next = curr_env;
	return new_env;
}

//Pops the top of the stack of symbol tables, frees the popped table
//and returns a pointer to the new top of the stack
Symtable *pop_env(Symtable *curr_env)
{
	printf("****Popping environment****\n");
	Symtable* next_env = curr_env->next;
	free_symtable(curr_env);
	return next_env;
}

//Frees all memory associated with a symbol table 
//(this needs to be called on every table in a symbol table stack to correctly free the whole symbol table)
void free_symtable(Symtable *symtable)
{
	free_names(symtable->table);
	free(symtable);
}

//Frees the array of symbol table entries held in a symbol table structure.
void free_names(Symentry *names[])
{
	int i;
	Symentry *this;
	
	for(i = 0; i < SYM_TABLE_SIZE; i++)
	{
		if((this = names[i]) != NULL)
		{
			free_symchain(this);
		}
	}
}

//Follows a chain of symbol table entries and frees each of them
void free_symchain(Symentry *this)
{
	Symentry *delete;
	
	for(delete = NULL; this != NULL; )
	{  //follow linked list of entries and free all
		delete = this;
		this = this->next; //advance our pointer along the chain of collisions
		free(delete->name); //free copy of variable name
		free(delete); //free structure as a whole
	}
}


//Create a hash code for a name to correctly index into a symbol table name array
int symhash(char *name)
{
	int code, i;
	char c;
	
	for(code = 0, i = 0; (c = name[i]) != '\0'; i++)
	{
		code += c;
	}
	
	return code % SYM_TABLE_SIZE;
}

//Searches for a given symbol in our symbol table. It scans the stack of symbol tables in order, and returns the first match
//If no match is found, NULL is returned
Symentry *lookup_sym(Symtable *symtable, char *name)
{
	Symtable *curr_env = symtable;
	Symentry *result = NULL;
	Symentry *entry = NULL;
	int hash_index = symhash(name);
	
	for(result = NULL; result == NULL && curr_env != NULL; curr_env = curr_env->next)
	{	
		for(entry = curr_env->table[hash_index]; entry != NULL; entry = entry->next)
		{			
			if(strcmp(entry->name, name) == 0)
			{ //we found our symbol
				result = entry;
				break;
			}
		}
	}
	
	return result;
}

//Places a given symbol into our symbol table (creating any necessary structure along the way)
//Symbols are placed in stack order, with the latest put shadowing repetitions placed prior
void put_sym(Symtable *curr_env, char *name, Type type)
{
	Symentry *new_entry = make_symentry(name, type);
	int hash_index = symhash(name);
	new_entry->next = curr_env->table[hash_index];
	curr_env->table[hash_index] = new_entry; //we place new symbol at start of list, this achieves shadowing semantics in same scope
}

//Yes...breaks are redundant here, but leaving in case we change this later
const char* print_type_name(Type type)
{
	switch(type)
	{
		case INT_TYPE:
			return "int";
			break;
		case FLOAT_TYPE:
			return "float";
			break;
		case DATE_TYPE:
			return "date";
			break;
		case BOOLEAN_TYPE:
			return "boolean";
			break;
		case HEX_TYPE:
			return "hex";
			break;
		case TABLE_TYPE:
			return "table";
			break;
		case FUNCTION_TYPE:
			return "function";
			break;
		case CALL_TYPE:
			return "call";
			break;
		case UNKNOWN_TYPE:
			return "unknown";
			break;
		default:
			return "Error: undefined type";
			break;
	}
}



void print_symtable(Symtable *symtable)
{
	int scope, i;
	Symtable *env;
	Symentry *entry = NULL;
	printf("Symtable\n");
	printf("------------------------\n");
		
	for(env = symtable, scope = 0; env != NULL; env = env->next, scope++)
	{
		for(i = 0; i < SYM_TABLE_SIZE; i++)
		{
			for(entry = symtable->table[i]; entry != NULL; entry = entry->next)
			{
				printf("%.3d %9.9s %9.9s\n", scope, entry->name, print_type_name(entry->type));
			}
		}
	}

}


//A simple set of tests for our symbol table implementation
void ignore_symtable_test()
{ 
	//scope 1
	char *names[][4]= { 
			{ "var_1","var_2","var_3", "var_4" }, //scope 0
			{ "var_1", "var_5", "var_6", "var_5" }, //scope 1
			};
			
	Type types[][4] = { 
			{ INT_TYPE, FLOAT_TYPE, FUNCTION_TYPE, TABLE_TYPE }, //scope 0
			{ FUNCTION_TYPE, INT_TYPE, TABLE_TYPE, FUNCTION_TYPE }, //scope 1
			};
	
	int depth = 2, len = 4, i, j;
	Symtable *symtable = make_symtable();
	Symentry *entry = NULL;
	
	//inserting symbols for scope 0
	i = 0;
	for(j = 0; j < len; j++)
	{	
		printf("Putting:%s with type %s\n", names[i][j], print_type_name(types[i][j]));
		put_sym(symtable, names[i][j], types[i][j]);
	}
	
	//retrieveing symbols for scope 0
	i = 0;
	for(j = 0; j < len; j++)
	{
		entry = lookup_sym(symtable, names[i][j]);
		
		if(entry == NULL)
		{
			printf("--> Warning: %s not found\n", names[i][j]);
		}
		else
		{
			printf("Found %s with type %s\n", names[i][j], print_type_name(entry->type));
		}
	}
	
	//Create another scope
	symtable = push_env(symtable);
		
	//inserting symbols for scope 1
	i = 1;
	for(j = 0; j < len; j++)
	{	
		printf("Putting:%s with type %s\n", names[i][j], print_type_name(types[i][j]));
		put_sym(symtable, names[i][j], types[i][j]);
	}
	
	//Looking up all symbols
	for(i = 0; i < depth; i++)
	{
		for(j = 0; j < len; j++)
		{
			entry = lookup_sym(symtable, names[i][j]);
		
			if(entry == NULL)
			{
				printf("--> Warning: %s not found\n", names[i][j]);
			}
			else
			{
				printf("Found %s with type %s\n", names[i][j], print_type_name(entry->type));
			}
		}
	}
	
	print_symtable(symtable);
	symtable = pop_env(symtable); //remove scope 1
	symtable = pop_env(symtable); //remove scope 0
}



/*
int main(int argc, char *argv[])
{
	ignore_symtable_test();
	return 0;
}
*/


