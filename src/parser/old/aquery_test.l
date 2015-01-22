%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

 /* SQL key words */
"WITH"			{ printf("WITH\n"); }//{ return WITH;   	}
"AS"			{ printf("AS\n"); }//{ return AS;     	}
"SELECT"		{ printf("SELECT\n"); }//{ return SELECT; 	}
"FROM"			{ printf("FROM\n"); }//{ return FROM;	 	}
"ASSUMING"		{ printf("ASSUMING\n"); }//{ return ASSUMING;  }
"ORDER"			{ printf("ORDER\n"); }//{ return ORDER; 	}
"WHERE"			{ printf("WHERE\n"); }//{ return WHERE; 	}
"AND"			{ printf("AND\n"); }//{ return AND; 		}
"GROUP"			{ printf("GROUP\n"); }//{ return GROUP; 	}
"BY"			{ printf("BY\n"); }//{ return BY; 		}
"FLATTEN"		{ printf("FLATTEN\n"); }//{ return FLATTEN;	}

 /*  built-ins from q and k */
"abs"			{ printf("abs\n"); }//{ return ABS;		}
"avg"			{ printf("avg\n"); }//{ return AVG;		}
"avgs"			{ printf("avgs\n"); }//{ return AVGS;		}
"count"			{ printf("count\n"); }//{ return COUNT;		}
"deltas"		{ printf("deltas\n"); }//{ return DELTAS; 	}
"distinct"		{ printf("distinct\n"); }//{ return DISTINCT; 	}
"first"			{ printf("first\n"); }//{ return FIRST;    	}
"last"			{ printf("last\n"); }//{ return LAST; 	   	}
"max"			{ printf("max\n"); }//{ return MAX; 		}
"maxs"			{ printf("maxs\n"); }//{ return MAXS;		}
"min"			{ printf("min\n"); }//{ return MIN;		}
"mins"			{ printf("mins\n"); }//{ return MINS; 		}
"mod"			{ printf("mod\n"); }//{ return MOD; 		}
"sum"			{ printf("sum\n"); }//{ return SUM;		}
"sums"			{ printf("sums\n"); }//{ return SUMS;		}


 /* Standard tokens including spaces, floats, integers, strings, and identifiers */

[ \t\n]    						; 						//spaces
-?[0-9]+\.[0-9]+				{ printf("float\n"); }//{ return FLOAT;   	}  	//floats
-?[0-9]+						{ printf("integer\n"); }//{ return INTEGER; 	}	//integer
\"(([0][1-9])|([1][0-2]))\/(([0][1-9])|([1-2][0-9])|([3][0-1]))\/[0-9]{4}\"		{printf("date\n");}
\"(\\.|[^"])*\"				{ printf("string\n"); }//{ return STRING;    }	//string
[a-zA-Z_]+[a-zA-Z0-9]*		{ printf("id\n"); }//{ return ID; 		}	//identifiers


 /* Standard mathematical operators */
"*"			{printf("times\n");}
"/"			{printf("divide\n");}
"+"			{printf("plus\n");}
"-"			{printf("minus\n");}
"<="	{printf("LESSEQUALTHAN\n");}
">="	{printf("GREATEREQUALTHAN\n");}
"<"		{printf("LESSTHAN");}
">"		{printf("GREATHAN");}
"="		{printf("EQUALS");}

 /* miscellaneous */
 "("		{printf("LEFTPARENS\n");}
 ")"		{printf("RIGHTPARENS\n");}
 "."		{printf("DOT\n");}
 ","		{printf("COMMA\n");}





.							{ printf("Unidentifier token\n"); exit(1); 	}
%%



