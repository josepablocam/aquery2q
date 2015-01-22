%{
#include <stdio.h>
#include <stdlib.h>
#include "aquery.tab.h"

int line_num = 1;
int col_num = 0;

void count(); 
void consume_comment();


%}


%x IN_COMMENT


%%
 /* comments */
 
"/*"			{ count(); consume_comment(); }

 /* SQL key words */
"WITH"			{ count(); return WITH;   	 }
"AS"			{ count(); return TABLE_AS;  }
"SELECT"		{ count(); return SELECT; 	 }
"FROM"			{ count(); return FROM;	 	 }
"ASSUMING"		{ count(); return ASSUMING;  }
"ORDER"			{ count(); return ORDER; 	 }
"WHERE"			{ count(); return WHERE; 	 }
"AND"			{ count(); return AND; 		 }
"GROUP"			{ count(); return GROUP; 	 }
"BY"			{ count(); return BY; 		 }
"FLATTEN"		{ count(); return FLATTEN;	 }
"as"			{ count(); return COL_AS;	 }
"ROWID"			{ count(); return ROWID;	 }
"ODD"			{ count(); return ODD;		 }
"EVEN"			{ count(); return EVEN;		 }
"EVERY"			{ count(); return EVERY;	 }

 /*  built-in operators from q and k */
"abs"			{ count(); return ABS;		}
"avg"			{ count(); return AVG;		}
"avgs"			{ count(); return AVGS;		}
"count"			{ count(); return COUNT;	}
"deltas"		{ count(); return DELTAS; 	}
"distinct"		{ count(); return DISTINCT; }
"drop"			{ count(); return DROP; 	}
"first"			{ count(); return FIRST;    }
"last"			{ count(); return LAST; 	}
"max"			{ count(); return MAX; 		}
"maxs"			{ count(); return MAXS;		}
"min"			{ count(); return MIN;		}
"mins"			{ count(); return MINS; 	}
"mod"			{ count(); return MOD; 		}
"next"			{ count(); return NEXT; 	}
"prev"			{ count(); return PREV;		}
"prd"			{ count(); return PRD;		}
"prds"			{ count(); return PRDS;		}
"reverse"		{ count(); return REV;		}
"sum"			{ count(); return SUM;		}
"sums"			{ count(); return SUMS;		}
"stddev"		{ count(); return STDDEV;   }


 /* Standard tokens including spaces, floats, integers, strings, and identifiers */

[ \t\n]    																		{ count(); 					 } //spaces
-?[0-9]+\.[0-9]+																{ count(); return FLOAT;   	  } //floats
-?[0-9]+																		{ count(); return INTEGER; 	  }	//integer
\'(([0][1-9])|([1][0-2]))\/(([0][1-9])|([1-2][0-9])|([3][0-1]))\/[0-9]{4}\'		{ count(); return DATE;		  } //date	
\"(\\.|[^"])*\"																	{ count(); return STRING;       }	//string
[a-zA-Z]+[a-zA-Z0-9_]*															{ count(); return ID; 		  }	//identifiers


 /* Standard mathematical operators */
"*"			{ count(); return TIMES_OP; }
"/"			{ count(); return DIV_OP;  	}
"+"			{ count(); return PLUS_OP; 	}	
"-"			{ count(); return MINUS_OP; }
"<="		{ count(); return LE_OP; 	}
">="		{ count(); return GE_OP; 	}
"<"			{ count(); return L_OP; 	}
">"			{ count(); return G_OP; 	}	
"="			{ count(); return EQ_OP; 	}
"!="		{ count(); return NEQ_OP; 	}
"&"			{ count(); return AND_OP;	}
"|"			{ count(); return OR_OP;	}

 /* miscellaneous */
 "("		{ count(); return '('; }
 ")"		{ count(); return ')'; }
 "."		{ count(); return '.'; }
 ","		{ count(); return ','; }
 ";"		{ count(); return ';'; }





.		     { printf("Unidentified token:%s, line:%d, column:%d\n", yytext, line_num, col_num); exit(1); } //TODO: add better error handling/reporting
%%

void count()
{ /* inspired from  http://www.lysator.liu.se/c/ANSI-C-grammar-l.html */
	int i = 0;
	char c;
	while((c = yytext[i++]) != '\0')
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
}

void consume_comment() {
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
			comment_end = (c == '*') && (c1 == '/');
			c = c1;
			
		}
	}
	while(!comment_end);
	
	
}





