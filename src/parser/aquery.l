%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aquery.tab.h"

int line_num = 1;
int col_num = 0;

void count(); 
void consume_multi_line_comment();
void consume_single_line_comment();


%}

%option noyywrap

%%
 /* comments */
 
"/*"			{ count(); consume_multi_line_comment();  }
"//"			{ count(); consume_single_line_comment(); }

 /* SQL: select query key words */
"WITH"			{ count(); return WITH;      }
"ASC"			{ count(); return ASC;       }
"DESC"			{ count(); return DESC;      }
"AS"			{ count(); return UC_AS;     }
"SELECT"		{ count(); return SELECT;    }
"FROM"			{ count(); return FROM;      }
"ASSUMING"		{ count(); return ASSUMING;  }
"WHERE"			{ count(); return WHERE;     }
"GROUP"			{ count(); return GROUP;     }
"BY"			{ count(); return BY;        }
"HAVING"		{ count(); return HAVING;    }
"as"			{ count(); return LC_AS;     }

 /* SQL: indexing */
"ROWID"			{ count(); return ROWID;     }
"ODD"			{ count(); return ODD;       }
"EVEN"			{ count(); return EVEN;      }
"EVERY"			{ count(); return EVERY;     }

 /* SQL: table operations */
"FLATTEN"		{ count(); return FLATTEN;	 }

 /* SQL: joins */
"JOIN"			{ count(); return JOIN;     }
"INNER"			{ count(); return INNER;    }	
"OUTER"			{ count(); return OUTER;    }
"FULL"			{ count(); return FULL;     }
"ON"			{ count(); return ON;       }
"USING"			{ count(); return USING;    }

 /* SQL: Views/Tables */
"CREATE"	{ count(); return CREATE;   }
"TABLE"		{ count(); return TABLE;    }
"VIEW"		{ count(); return VIEW;     }

 /* SQL: update/insert/delete statements */
"UPDATE"	{ count(); return UPDATE;   }
"SET"		{ count(); return SET;      }
"INSERT"	{ count(); return INSERT;   }
"INTO"		{ count(); return INTO;     }
"VALUES"	{ count(); return VALUES;   }
"DELETE"	{ count(); return DELETE;   }

 /* SQL: search conditions */
"AND"		{ count(); return AND;          }
"OR"		{ count(); return OR;           }
"IS"		{ count(); return IS;           }
"NOT"		{ count(); return NOT;          }
"BETWEEN"	{ count(); return BETWEEN;      }
"IN"		{ count(); return IN;           }
"LIKE"		{ count(); return LIKE;         }
"NULL"		{ count(); return NULL_KEYWORD; }
"OVERLAPS"	{ count(); return OVERLAPS;     }

 /* SQL: case statements */
"CASE"	{ count(); return CASE; }
"END"	{ count(); return END;  }
"WHEN"	{ count(); return WHEN; }
"THEN"	{ count(); return THEN; }
"ELSE"	{ count(); return ELSE; }
 
 /* SQL: type names */
"INT"		{ count(); return TYPE_INT;     }
"FLOAT"		{ count(); return TYPE_FLOAT;   }
"STRING"	{ count(); return TYPE_STRING;  }
"DATE"		{ count(); return TYPE_DATE;    }
"BOOLEAN"	{ count(); return TYPE_BOOLEAN; }
"HEX"		{ count(); return TYPE_HEX;     }

 /* SQL: user defined functions */
"FUNCTION"	{ count(); return FUNCTION;     }
":="		{ count(); return LOCAL_ASSIGN; } 
 
 /* Built-in functions from q and k */
"abs"			{ count(); return ABS;      }
"avg"			{ count(); return AVG;      }
"avgs"			{ count(); return AVGS;     }
"count"			{ count(); return COUNT;    }
"deltas"		{ count(); return DELTAS;   }
"distinct"		{ count(); return DISTINCT; }
"drop"			{ count(); return DROP;     }
"fill"			{ count(); return FILL;     }
"first"			{ count(); return FIRST;    }
"last"			{ count(); return LAST;     }
"max"			{ count(); return MAX;      }
"maxs"			{ count(); return MAXS;     }
"min"			{ count(); return MIN;      }
"mins"			{ count(); return MINS;     }
"mod"			{ count(); return MOD;      }
"next"			{ count(); return NEXT;     }
"prev"			{ count(); return PREV;     }
"prd"			{ count(); return PRD;      }
"prds"			{ count(); return PRDS;     }
"reverse"		{ count(); return REV;      }
"sum"			{ count(); return SUM;      }
"sums"			{ count(); return SUMS;     }
"stddev"		{ count(); return STDDEV;   }
"make_null"		{ count(); return MAKENULL; }
		


 /* Space definitions */
[ \t\n]    						{ count(); 	} 


 /* Literals */
-?[0-9]+                        { count(); return INT;     }	
-?[0-9]+\.[0-9]+                { count(); return FLOAT;   } 
\"(\\.|[^"])*\"                 { count(); return STRING;  } 
\'(([0][1-9])|([1][0-2]))\/(([0][1-9])|([1-2][0-9])|([3][0-1]))\/[0-9]{4}\'		{ count(); return DATE; } 
"TRUE"                          { count(); return TRUE;	   }
"FALSE"                         { count(); return FALSE;   }
"0x"[0-9a-fA-F]+                { count(); return HEX;	   }

 /* Variables */
[a-zA-Z]+[a-zA-Z0-9_]*	{ count(); return ID; }	 


 /* Standard mathematical operators */
"^"         { count(); return EXP_OP;   }
"*"         { count(); return TIMES_OP; }
"/"         { count(); return DIV_OP;   }
"+"         { count(); return PLUS_OP;  }	
"-"         { count(); return MINUS_OP; }
"<="        { count(); return LE_OP;    }
">="        { count(); return GE_OP;    }
"<"         { count(); return L_OP;     }
">"         { count(); return G_OP;     }	
"="         { count(); return EQ_OP;    }
"!="        { count(); return NEQ_OP;   }
"&"         { count(); return AND_OP;   }
"|"         { count(); return OR_OP;   }

 /* miscellaneous */
 "("		{ count(); return '('; }
 ")"		{ count(); return ')'; }
 "."		{ count(); return '.'; }
 ","		{ count(); return ','; }
 ";"		{ count(); return ';'; }
 "{"		{ count(); return '{'; } 
 "}"		{ count(); return '}'; }




 /* TODO: add better error handling/reporting */
.		     { printf("Unidentified token:%s, line:%d, column:%d\n", yytext, line_num, col_num); exit(1); }

%%
void move_col_line(char c)
{
	if(c == '\n')
	{
		col_num = 0;
		line_num++;
	}
	else if(c == '\t')
	{
		col_num += 4;
	}
	else
	{
		col_num++;
	}
}


void count()
{ /* inspired from  http://www.lysator.liu.se/c/ANSI-C-grammar-l.html */
	int i = 0;
	char c;
	while((c = yytext[i++]) != '\0')
	{
		move_col_line(c);
	}
}

void consume_single_line_comment() {
	char c;
	
	while((c = input()) != '\n')
	{
		//consume comment
	}
	col_num = 0;
	line_num++;
}

void consume_multi_line_comment() {
	char c = input(), c1;
	int comment_end = 0;
	
	do
	{
		/* consume comments */
		if(c == '\0')
		{
			comment_end = 1;
		}
		else
		{	
			c1 = input();
			move_col_line(c);
			comment_end = (c == '*') && (c1 == '/');
			c = c1;
			
			
		}
	}
	while(!comment_end);
	
	
}





