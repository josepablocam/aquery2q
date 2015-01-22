%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

 /* SQL key words */
"WITH"			{ return WITH;   	}
"AS"			{ return TABLE_AS;  }
"SELECT"		{ return SELECT; 	}
"FROM"			{ return FROM;	 	}
"ASSUMING"		{ return ASSUMING;  }
"ORDER"			{ return ORDER; 	}
"WHERE"			{ return WHERE; 	}
"AND"			{ return AND; 		}
"GROUP"			{ return GROUP; 	}
"BY"			{ return BY; 		}
"FLATTEN"		{ return FLATTEN;	}
"as"			{ return COL_AS;	}
"ROWID"			{ return ROWID;		}
"ODD"			{ return ODD;		}
"EVEN"			{ return EVEN;		}
"EVERY"			{ return EVERY;		}

 /*  built-in operators from q and k */
"abs"			{ return ABS;		}
"avg"			{ return AVG;		}
"avgs"			{ return AVGS;		}
"count"			{ return COUNT;		}
"deltas"		{ return DELTAS; 	}
"distinct"		{ return DISTINCT; 	}
"drop"			{ return DROP; 		}
"first"			{ return FIRST;    	}
"last"			{ return LAST; 	   	}
"max"			{ return MAX; 		}
"maxs"			{ return MAXS;		}
"min"			{ return MIN;		}
"mins"			{ return MINS; 		}
"mod"			{ return MOD; 		}
"next"			{ return NEXT; 		}
"prev"			{ return PREV;		}
"prd"			{ return PRD;		}
"prds"			{ return PRDS;		}
"reverse"		{ return REV;		}
"sum"			{ return SUM;		}
"sums"			{ return SUMS;		}
"stddev"		{ return STDDEV;    }


 /* Standard tokens including spaces, floats, integers, strings, and identifiers */

[ \t\n]    																		; 							//spaces
-?[0-9]+\.[0-9]+																{ return FLOAT;   	  } 	//floats
-?[0-9]+																		{ return INTEGER; 	}	  //integer
\'(([0][1-9])|([1][0-2]))\/(([0][1-9])|([1-2][0-9])|([3][0-1]))\/[0-9]{4}\'		{ return DATE;		  }		//date	
\"(\\.|[^"])*\"																	{ return STRING;    }	//string
[a-zA-Z_]+[a-zA-Z0-9]*															{ return ID; 		}	//identifiers


 /* Standard mathematical operators */
"*"			{ return TIMES_OP; 	}
"/"			{ return DIV_OP;  	}
"+"			{ return PLUS_OP; 	}	
"-"			{ return MINUS_OP; 	}
"<="		{ return LE_OP; 	}
">="		{ return GE_OP; 	}
"<"			{ return L_OP; 		}
">"			{ return G_OP; 		}	
"="			{ return EQ_OP; 	}
"<>"		{ return NEQ_OP; 	}
"&"			{ return AND_OP;	}
"|"			{ return OR_OP;		}

 /* miscellaneous */
 "("		{ return '('; }
 ")"		{ return ')'; }
 "."		{ return '.'; }
 ","		{ return ','; }





.							{ printf("Unidentifier token\n"); exit(1); 	} //TODO: add error handling (print out token etc)
%%



