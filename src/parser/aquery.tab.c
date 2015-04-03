/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WITH = 258,
     UC_AS = 259,
     SELECT = 260,
     FROM = 261,
     ASSUMING = 262,
     ASC = 263,
     DESC = 264,
     WHERE = 265,
     GROUP = 266,
     BY = 267,
     HAVING = 268,
     LC_AS = 269,
     ROWID = 270,
     ODD = 271,
     EVEN = 272,
     EVERY = 273,
     FLATTEN = 274,
     JOIN = 275,
     INNER = 276,
     OUTER = 277,
     FULL = 278,
     ON = 279,
     USING = 280,
     CREATE = 281,
     TABLE = 282,
     VIEW = 283,
     UPDATE = 284,
     SET = 285,
     INSERT = 286,
     INTO = 287,
     VALUES = 288,
     DELETE = 289,
     AND = 290,
     OR = 291,
     IS = 292,
     NOT = 293,
     BETWEEN = 294,
     IN = 295,
     LIKE = 296,
     NULL_KEYWORD = 297,
     OVERLAPS = 298,
     CASE = 299,
     END = 300,
     WHEN = 301,
     THEN = 302,
     ELSE = 303,
     TYPE_INT = 304,
     TYPE_FLOAT = 305,
     TYPE_STRING = 306,
     TYPE_DATE = 307,
     TYPE_BOOLEAN = 308,
     TYPE_HEX = 309,
     FUNCTION = 310,
     LOCAL_ASSIGN = 311,
     ABS = 312,
     AVG = 313,
     COUNT = 314,
     DISTINCT = 315,
     DROP = 316,
     FILL = 317,
     FIRST = 318,
     LAST = 319,
     MAX = 320,
     MIN = 321,
     MOD = 322,
     NEXT = 323,
     PREV = 324,
     PRD = 325,
     REV = 326,
     SUM = 327,
     STDDEV = 328,
     AVGS = 329,
     DELTAS = 330,
     MAXS = 331,
     MINS = 332,
     PRDS = 333,
     SUMS = 334,
     MAKENULL = 335,
     FLOAT = 336,
     INT = 337,
     TRUE = 338,
     FALSE = 339,
     DATE = 340,
     HEX = 341,
     ID = 342,
     STRING = 343,
     EXP_OP = 344,
     TIMES_OP = 345,
     DIV_OP = 346,
     PLUS_OP = 347,
     MINUS_OP = 348,
     LE_OP = 349,
     GE_OP = 350,
     L_OP = 351,
     G_OP = 352,
     EQ_OP = 353,
     NEQ_OP = 354,
     AND_OP = 355,
     OR_OP = 356
   };
#endif
/* Tokens.  */
#define WITH 258
#define UC_AS 259
#define SELECT 260
#define FROM 261
#define ASSUMING 262
#define ASC 263
#define DESC 264
#define WHERE 265
#define GROUP 266
#define BY 267
#define HAVING 268
#define LC_AS 269
#define ROWID 270
#define ODD 271
#define EVEN 272
#define EVERY 273
#define FLATTEN 274
#define JOIN 275
#define INNER 276
#define OUTER 277
#define FULL 278
#define ON 279
#define USING 280
#define CREATE 281
#define TABLE 282
#define VIEW 283
#define UPDATE 284
#define SET 285
#define INSERT 286
#define INTO 287
#define VALUES 288
#define DELETE 289
#define AND 290
#define OR 291
#define IS 292
#define NOT 293
#define BETWEEN 294
#define IN 295
#define LIKE 296
#define NULL_KEYWORD 297
#define OVERLAPS 298
#define CASE 299
#define END 300
#define WHEN 301
#define THEN 302
#define ELSE 303
#define TYPE_INT 304
#define TYPE_FLOAT 305
#define TYPE_STRING 306
#define TYPE_DATE 307
#define TYPE_BOOLEAN 308
#define TYPE_HEX 309
#define FUNCTION 310
#define LOCAL_ASSIGN 311
#define ABS 312
#define AVG 313
#define COUNT 314
#define DISTINCT 315
#define DROP 316
#define FILL 317
#define FIRST 318
#define LAST 319
#define MAX 320
#define MIN 321
#define MOD 322
#define NEXT 323
#define PREV 324
#define PRD 325
#define REV 326
#define SUM 327
#define STDDEV 328
#define AVGS 329
#define DELTAS 330
#define MAXS 331
#define MINS 332
#define PRDS 333
#define SUMS 334
#define MAKENULL 335
#define FLOAT 336
#define INT 337
#define TRUE 338
#define FALSE 339
#define DATE 340
#define HEX 341
#define ID 342
#define STRING 343
#define EXP_OP 344
#define TIMES_OP 345
#define DIV_OP 346
#define PLUS_OP 347
#define MINUS_OP 348
#define LE_OP 349
#define GE_OP 350
#define L_OP 351
#define G_OP 352
#define EQ_OP 353
#define NEQ_OP 354
#define AND_OP 355
#define OR_OP 356




/* Copy the first part of user declarations.  */
#line 1 "aquery.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "symtable.h"  /* manages the symbol table, to enable meta data lookup */	
#include "ast.h"       /* builds ast for parser */
#include "ast_print.h" /* provides dot printing of ast */
#include "optimizer.h" /* optimizing for query plans */
	
#define YYDEBUG 1
#define ERRORCOLOR  "\x1B[32m"
#define SAFE_ORDER_DEP(x) ((x) != NULL && (x)->order_dep);

extern int yyleng;
extern FILE *yyin;
extern int yylex();
extern int yyparse();
void warning_Cross();

//for debugging purposes, defined in flex
extern int line_num; 
extern int col_num;

//Symbol table
Symtable *env;	/* global symbol table: stack of hash tables */
Symentry *entry; /* place holder for entry pointers to perform modifications ad-hoc */

//AST
TopLevelNode* ast; /* holds any asts created during compilation */
LogicalQueryNode *curr_order;

void yyerror(const char *);

//Command line options
int optim_level; //level of optimization in ast
int silence_warnings;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 162 "aquery.y"
{
  int   intval;
  float floatval;
  char* str;
  struct ExprNode *exprnode;
  struct UDFDefNode *udfdef;
  struct IDListNode *idlist;
  struct LocalVarDefNode *localvardef;
  struct UDFBodyNode *udfbody;
  struct FullQueryNode *fullquery; 
  struct LocalQueryNode *localquery;
  struct LogicalQueryNode *plan;
  struct OrderNode *order;
  struct NamedExprNode *namedexpr;
  struct InsertNode *insert;
  struct CreateNode *create;
  struct CreateSourceNode *createsrc;
  struct SchemaNode *schema;
  struct TopLevelNode *top;
}
/* Line 193 of yacc.c.  */
#line 360 "aquery.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 373 "aquery.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   807

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  111
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNRULES -- Number of states.  */
#define YYNSTATES  374

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   356

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     102,   103,     2,     2,   104,     2,   105,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   108,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   109,     2,   110,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   106,     2,   107,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      24,    26,    27,    31,    35,    36,    39,    40,    47,    51,
      52,    55,    59,    60,    66,    70,    74,    76,    80,    81,
      84,    87,    88,    91,    94,    97,    99,   103,   107,   108,
     111,   112,   117,   118,   121,   122,   125,   129,   130,   132,
     136,   138,   141,   143,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   169,   176,   180,   185,   189,   191,   195,
     200,   205,   209,   213,   218,   220,   222,   226,   232,   234,
     240,   246,   253,   260,   263,   268,   270,   275,   278,   282,
     284,   288,   291,   295,   296,   301,   306,   309,   313,   316,
     319,   323,   324,   326,   328,   330,   332,   334,   336,   344,
     347,   351,   352,   356,   363,   367,   368,   370,   375,   381,
     386,   387,   397,   400,   401,   405,   406,   409,   410,   414,
     415,   417,   419,   421,   425,   427,   429,   431,   433,   435,
     437,   439,   443,   445,   451,   453,   454,   457,   460,   461,
     466,   469,   471,   473,   475,   479,   481,   483,   488,   493,
     497,   502,   506,   508,   510,   513,   515,   517,   519,   521,
     523,   525,   527,   529,   531,   533,   535,   537,   539,   541,
     543,   545,   547,   549,   551,   553,   555,   557,   559,   561,
     563,   567,   569,   573,   577,   579,   583,   587,   589,   593,
     597,   601,   605,   607,   611,   615,   617,   621,   623,   627,
     629,   632,   636
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     112,     0,    -1,   113,    -1,   114,   113,    -1,   159,   113,
      -1,   169,   113,    -1,   165,   113,    -1,   172,   113,    -1,
     173,   113,    -1,    -1,   115,    -1,    -1,   116,   117,   123,
      -1,     3,   119,   118,    -1,    -1,   119,   118,    -1,    -1,
      87,   120,     4,   102,   123,   103,    -1,   102,   121,   103,
      -1,    -1,    87,   122,    -1,   104,    87,   122,    -1,    -1,
     124,   127,   128,   133,   134,    -1,     5,   125,   126,    -1,
     200,    14,    87,    -1,   200,    -1,   104,   125,   126,    -1,
      -1,     6,   157,    -1,     7,   129,    -1,    -1,   130,   132,
      -1,     8,   131,    -1,     9,   131,    -1,    87,    -1,    87,
     105,    87,    -1,   104,   130,   132,    -1,    -1,    10,   136,
      -1,    -1,    11,    12,   201,   135,    -1,    -1,    13,   138,
      -1,    -1,   138,   137,    -1,    35,   138,   137,    -1,    -1,
     139,    -1,   138,    36,   139,    -1,   140,    -1,    38,   140,
      -1,   141,    -1,   102,   138,   103,    -1,   200,    -1,   142,
      -1,   150,    -1,   143,    -1,   144,    -1,   147,    -1,   146,
      -1,   148,    -1,   200,    39,   200,    35,   200,    -1,   200,
      38,    39,   200,    35,   200,    -1,   200,    40,   145,    -1,
     200,    38,    40,   145,    -1,   102,   201,   103,    -1,   200,
      -1,   200,    41,   200,    -1,   200,    38,    41,   200,    -1,
     200,    37,    38,    42,    -1,   200,    37,    42,    -1,   200,
      37,   149,    -1,   200,    37,    38,   149,    -1,    83,    -1,
      84,    -1,   151,    43,   151,    -1,   102,   200,   104,   200,
     103,    -1,   155,    -1,   155,    21,    20,   152,   153,    -1,
     155,    21,    20,   152,   154,    -1,   155,    23,    22,    20,
     152,   153,    -1,   155,    23,    22,    20,   152,   154,    -1,
      24,   136,    -1,    25,   102,   121,   103,    -1,   156,    -1,
      19,   102,   156,   103,    -1,    87,    87,    -1,    87,     4,
      87,    -1,    87,    -1,   102,   152,   103,    -1,   152,   158,
      -1,   104,   152,   158,    -1,    -1,    26,    27,    87,   160,
      -1,    26,    28,    87,   160,    -1,     4,   115,    -1,   102,
     161,   103,    -1,   162,   163,    -1,    87,   164,    -1,   104,
     162,   163,    -1,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    29,    87,    30,   166,
     128,   133,   134,    -1,   168,   167,    -1,   104,   168,   167,
      -1,    -1,    87,    98,   200,    -1,    31,    32,    87,   128,
     170,   171,    -1,   102,   121,   103,    -1,    -1,   115,    -1,
      33,   102,   201,   103,    -1,    34,     6,    87,   128,   133,
      -1,    34,   121,     6,    87,    -1,    -1,    55,    87,   174,
     102,   175,   103,   106,   177,   107,    -1,    87,   176,    -1,
      -1,   104,    87,   176,    -1,    -1,   179,   178,    -1,    -1,
     108,   179,   178,    -1,    -1,   200,    -1,   180,    -1,   115,
      -1,    87,    56,   200,    -1,    82,    -1,    81,    -1,    85,
      -1,    88,    -1,    86,    -1,   149,    -1,    15,    -1,    87,
     105,    87,    -1,    90,    -1,    44,   184,   185,   188,    45,
      -1,   200,    -1,    -1,   187,   186,    -1,   187,   186,    -1,
      -1,    46,   138,    47,   200,    -1,    48,   200,    -1,   181,
      -1,   182,    -1,    87,    -1,   102,   200,   103,    -1,   183,
      -1,   189,    -1,   189,   109,   191,   110,    -1,   192,   102,
     201,   103,    -1,   192,   102,   103,    -1,    87,   102,   201,
     103,    -1,    87,   102,   103,    -1,    16,    -1,    17,    -1,
      18,    82,    -1,    57,    -1,    58,    -1,    74,    -1,    59,
      -1,    75,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    64,    -1,    65,    -1,    76,    -1,    66,    -1,    77,
      -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,    78,
      -1,    71,    -1,    72,    -1,    79,    -1,    73,    -1,    80,
      -1,   190,    -1,   190,    89,   193,    -1,   193,    -1,   194,
      90,   193,    -1,   194,    91,   193,    -1,   194,    -1,   195,
      92,   194,    -1,   195,    93,   194,    -1,   195,    -1,   196,
      96,   195,    -1,   196,    97,   195,    -1,   196,    94,   195,
      -1,   196,    95,   195,    -1,   196,    -1,   197,    98,   196,
      -1,   197,    99,   196,    -1,   197,    -1,   198,   100,   197,
      -1,   198,    -1,   199,   101,   198,    -1,   199,    -1,   200,
     202,    -1,   104,   200,   202,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   200,   201,   202,   203,   204,   205,   206,
     211,   214,   214,   221,   222,   225,   226,   229,   234,   235,
     238,   241,   242,   248,   251,   254,   255,   258,   259,   262,
     265,   266,   269,   272,   273,   276,   277,   280,   281,   288,
     289,   292,   293,   296,   297,   311,   314,   315,   318,   319,
     322,   323,   326,   327,   331,   332,   333,   337,   338,   339,
     340,   341,   347,   348,   351,   352,   355,   356,   359,   360,
     363,   364,   367,   368,   371,   372,   375,   378,   385,   386,
     387,   388,   389,   393,   396,   399,   400,   403,   404,   405,
     406,   411,   414,   415,   419,   420,   423,   424,   427,   430,
     433,   434,   437,   438,   439,   440,   441,   442,   447,   450,
     453,   454,   457,   460,   463,   464,   467,   468,   471,   472,
     477,   477,   486,   487,   490,   491,   495,   496,   499,   500,
     503,   504,   505,   508,   512,   513,   514,   515,   516,   517,
     520,   521,   522,   526,   529,   530,   533,   536,   537,   540,
     543,   546,   547,   548,   549,   550,   553,   554,   555,   556,
     557,   558,   562,   563,   564,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   593,
     594,   597,   598,   599,   603,   604,   605,   608,   609,   610,
     611,   612,   615,   616,   617,   620,   621,   624,   625,   628,
     632,   635,   636
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "UC_AS", "SELECT", "FROM",
  "ASSUMING", "ASC", "DESC", "WHERE", "GROUP", "BY", "HAVING", "LC_AS",
  "ROWID", "ODD", "EVEN", "EVERY", "FLATTEN", "JOIN", "INNER", "OUTER",
  "FULL", "ON", "USING", "CREATE", "TABLE", "VIEW", "UPDATE", "SET",
  "INSERT", "INTO", "VALUES", "DELETE", "AND", "OR", "IS", "NOT",
  "BETWEEN", "IN", "LIKE", "NULL_KEYWORD", "OVERLAPS", "CASE", "END",
  "WHEN", "THEN", "ELSE", "TYPE_INT", "TYPE_FLOAT", "TYPE_STRING",
  "TYPE_DATE", "TYPE_BOOLEAN", "TYPE_HEX", "FUNCTION", "LOCAL_ASSIGN",
  "ABS", "AVG", "COUNT", "DISTINCT", "DROP", "FILL", "FIRST", "LAST",
  "MAX", "MIN", "MOD", "NEXT", "PREV", "PRD", "REV", "SUM", "STDDEV",
  "AVGS", "DELTAS", "MAXS", "MINS", "PRDS", "SUMS", "MAKENULL", "FLOAT",
  "INT", "TRUE", "FALSE", "DATE", "HEX", "ID", "STRING", "EXP_OP",
  "TIMES_OP", "DIV_OP", "PLUS_OP", "MINUS_OP", "LE_OP", "GE_OP", "L_OP",
  "G_OP", "EQ_OP", "NEQ_OP", "AND_OP", "OR_OP", "'('", "')'", "','", "'.'",
  "'{'", "'}'", "';'", "'['", "']'", "$accept", "program", "top_level",
  "global_query", "full_query", "@1", "local_queries",
  "local_queries_tail", "local_query", "col_aliases",
  "comma_identifier_list", "comma_identifier_list_tail", "base_query",
  "select_clause", "select_elem", "select_clause_tail", "from_clause",
  "order_clause", "order_specs", "order_spec", "column_name",
  "order_specs_tail", "where_clause", "groupby_clause", "having_clause",
  "and_search_condition", "and_search_condition_tail", "search_condition",
  "boolean_factor", "boolean_primary", "predicate", "postfix_predicate",
  "between_predicate", "in_predicate", "in_pred_spec", "like_predicate",
  "null_predicate", "is_predicate", "truth_value", "overlaps_predicate",
  "range_value_expression", "joined_table", "on_clause", "using_clause",
  "table_expression", "table_expression_main", "table_expressions",
  "table_expressions_tail", "create_table_or_view", "create_spec",
  "schema", "schema_element", "schema_tail", "type_name",
  "update_statement", "set_clauses", "set_clauses_tail", "set_clause",
  "insert_statement", "insert_modifier", "insert_source",
  "delete_statement", "user_function_definition", "@2", "def_arg_list",
  "def_arg_list_tail", "function_body", "function_body_tail",
  "function_body_elem", "function_local_var_def", "constant",
  "table_constant", "case_expression", "case_clause", "when_clauses",
  "when_clauses_tail", "when_clause", "else_clause", "main_expression",
  "call", "indexing", "built_in_fun", "exp_expression", "mult_expression",
  "add_expression", "rel_expression", "eq_expression", "and_expression",
  "or_expression", "value_expression", "comma_value_expression_list",
  "comma_value_expression_list_tail", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,    40,    41,    44,    46,   123,   125,    59,    91,
      93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   111,   112,   113,   113,   113,   113,   113,   113,   113,
     114,   116,   115,   117,   117,   118,   118,   119,   120,   120,
     121,   122,   122,   123,   124,   125,   125,   126,   126,   127,
     128,   128,   129,   130,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   141,   141,   141,   142,   142,   142,
     142,   142,   143,   143,   144,   144,   145,   145,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   151,   152,   152,
     152,   152,   152,   153,   154,   155,   155,   156,   156,   156,
     156,   157,   158,   158,   159,   159,   160,   160,   161,   162,
     163,   163,   164,   164,   164,   164,   164,   164,   165,   166,
     167,   167,   168,   169,   170,   170,   171,   171,   172,   172,
     174,   173,   175,   175,   176,   176,   177,   177,   178,   178,
     179,   179,   179,   180,   181,   181,   181,   181,   181,   181,
     182,   182,   182,   183,   184,   184,   185,   186,   186,   187,
     188,   189,   189,   189,   189,   189,   190,   190,   190,   190,
     190,   190,   191,   191,   191,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   193,
     193,   194,   194,   194,   195,   195,   195,   196,   196,   196,
     196,   196,   197,   197,   197,   198,   198,   199,   199,   200,
     201,   202,   202
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     0,
       1,     0,     3,     3,     0,     2,     0,     6,     3,     0,
       2,     3,     0,     5,     3,     3,     1,     3,     0,     2,
       2,     0,     2,     2,     2,     1,     3,     3,     0,     2,
       0,     4,     0,     2,     0,     2,     3,     0,     1,     3,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     6,     3,     4,     3,     1,     3,     4,
       4,     3,     3,     4,     1,     1,     3,     5,     1,     5,
       5,     6,     6,     2,     4,     1,     4,     2,     3,     1,
       3,     2,     3,     0,     4,     4,     2,     3,     2,     2,
       3,     0,     1,     1,     1,     1,     1,     1,     7,     2,
       3,     0,     3,     6,     3,     0,     1,     4,     5,     4,
       0,     9,     2,     0,     3,     0,     2,     0,     3,     0,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     5,     1,     0,     2,     2,     0,     4,
       2,     1,     1,     1,     3,     1,     1,     4,     4,     3,
       4,     3,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       2,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     0,     0,     0,     0,     0,     2,    11,    10,
      14,    11,    11,    11,    11,    11,     0,     0,     0,     0,
       0,    22,     0,   120,     1,     3,     0,     0,     4,     6,
       5,     7,     8,     0,     0,     0,    31,    31,     0,    20,
       0,     0,    19,    16,     0,    12,     0,    11,     0,    94,
      95,     0,    31,   111,     0,   115,    40,    22,   119,   123,
       0,     0,    13,    16,   140,   145,   165,   166,   168,   170,
     171,   172,   173,   174,   175,   177,   179,   180,   181,   182,
     184,   185,   187,   167,   169,   176,   178,   183,   186,   188,
     135,   134,    74,    75,   136,   138,   153,   137,   142,     0,
      28,   139,   151,   152,   155,   156,   189,     0,   191,   194,
     197,   202,   205,   207,   209,    26,     0,    31,    96,     0,
       0,   101,     0,    40,     0,   109,     0,     0,    30,    38,
       0,    11,     0,   118,    21,   125,     0,     0,     0,    15,
       0,   144,     0,     0,     0,     0,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,     0,    93,    78,    85,    29,
      40,   102,   103,   104,   105,   106,   107,    99,    97,     0,
      98,   112,    42,   111,    35,    33,    34,     0,    32,     0,
       0,   116,   113,     0,     0,    39,    47,    48,    50,    52,
      55,    57,    58,    60,    59,    61,    56,     0,    54,     0,
     122,     0,    18,     0,     0,     0,   148,   161,   212,     0,
     141,   154,    28,   162,   163,     0,     0,   190,   159,     0,
     192,   193,   195,   196,   200,   201,   198,   199,   203,   204,
     206,   208,    25,     0,     0,    87,     0,     0,    91,     0,
       0,    42,   101,     0,   108,   110,     0,    38,   114,     0,
      51,     0,    54,     0,     0,    45,     0,     0,     0,     0,
       0,     0,   125,    11,     0,     0,     0,     0,   146,   148,
       0,   210,   160,    27,   164,   157,   158,     0,    88,    90,
      93,     0,     0,    23,   100,     0,    36,    37,     0,    53,
       0,    47,    49,     0,    76,     0,    71,    72,     0,     0,
       0,     0,     0,    64,    67,    68,   124,   153,   132,     0,
     129,   131,   130,    17,     0,   150,   143,   147,   212,    86,
      92,     0,     0,    44,   117,     0,    46,     0,    70,    73,
       0,    65,    69,     0,     0,     0,     0,   121,    11,   126,
     149,   211,     0,     0,    79,    80,     0,     0,    41,    77,
       0,    62,    66,   133,   129,    83,     0,    81,    82,    43,
      63,   128,     0,    84
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    27,    62,    63,    61,
      22,    39,    45,    46,   100,   146,   117,    55,   128,   129,
     185,   188,   133,   254,   358,   195,   265,   196,   197,   198,
     199,   200,   201,   202,   313,   203,   204,   205,   101,   206,
     207,   166,   354,   355,   167,   168,   169,   248,    11,    49,
     120,   121,   180,   177,    12,    52,   125,    53,    13,   131,
     192,    14,    15,    41,   136,   210,   319,   349,   320,   321,
     102,   103,   104,   140,   215,   278,   279,   277,   105,   106,
     226,   107,   108,   109,   110,   111,   112,   113,   114,   208,
     219,   281
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -249
static const yytype_int16 yypact[] =
{
      10,    82,   -62,    11,     5,   -31,    58,  -249,    10,  -249,
      69,    10,    10,    10,    10,    10,   -17,    -8,    52,    12,
      37,    27,   128,  -249,  -249,  -249,    48,   131,  -249,  -249,
    -249,  -249,  -249,     2,     2,    50,   132,   132,    51,  -249,
      53,    39,    40,    48,   483,  -249,   137,  -249,    57,  -249,
    -249,    47,   132,    42,   103,    45,   138,    27,  -249,    62,
      65,   149,  -249,    48,  -249,   483,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,   -28,  -249,  -249,   483,
      54,  -249,  -249,  -249,  -249,    46,    68,    59,  -249,    26,
      21,   -43,    20,    56,    61,   140,   -12,   132,  -249,    -4,
      60,   100,   483,   138,    50,  -249,    73,    73,  -249,   102,
      65,   133,   409,  -249,  -249,   104,    66,   106,    63,  -249,
     118,  -249,   261,    84,   107,   483,  -249,    71,   483,   335,
     483,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   120,   109,     4,   -12,   108,    14,  -249,  -249,
     138,  -249,  -249,  -249,  -249,  -249,  -249,  -249,  -249,    57,
    -249,  -249,   202,    42,   111,  -249,  -249,   103,  -249,   116,
     112,  -249,  -249,   557,   409,  -249,    85,  -249,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,  -249,   175,    23,   134,
    -249,   114,  -249,   131,   409,   176,   118,  -249,   119,   127,
    -249,  -249,    54,  -249,  -249,   151,   121,  -249,  -249,   135,
    -249,  -249,    26,    26,    21,    21,    21,    21,   -43,   -43,
      20,    56,  -249,   -64,   147,  -249,   136,   -12,  -249,   215,
     218,   202,   100,   225,  -249,  -249,   154,   102,  -249,   483,
    -249,   -27,   -23,   409,   409,  -249,   141,   -16,    67,   483,
     631,   483,   104,   115,   139,    -7,   483,   199,  -249,   118,
     483,  -249,  -249,  -249,  -249,  -249,  -249,   142,  -249,  -249,
     108,   -12,   226,  -249,  -249,   483,  -249,  -249,   144,  -249,
     483,    85,  -249,   483,  -249,     0,  -249,  -249,   483,   631,
     483,   213,   483,  -249,  -249,  -249,  -249,   -36,  -249,   143,
     145,  -249,  -249,  -249,   483,  -249,  -249,  -249,   119,  -249,
    -249,    98,   -12,   236,  -249,   152,  -249,   148,  -249,  -249,
     219,  -249,  -249,   483,    22,   155,   483,  -249,   705,  -249,
    -249,  -249,   409,   158,  -249,  -249,    98,   409,  -249,  -249,
     483,  -249,  -249,  -249,   145,  -249,    65,  -249,  -249,   221,
    -249,  -249,   159,  -249
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -249,  -249,    19,  -249,   -45,  -249,  -249,   198,   237,  -249,
     -59,   210,    64,  -249,   124,    49,  -249,   -24,  -249,    83,
     146,    15,  -111,    24,  -249,   -78,   -22,  -190,    17,    89,
    -249,  -249,  -249,  -249,   -21,  -249,  -249,  -249,  -248,  -249,
      18,  -162,   -73,   -71,  -249,    35,  -249,    -3,  -249,   252,
    -249,   110,    38,  -249,  -249,  -249,   113,   167,  -249,  -249,
    -249,  -249,  -249,  -249,  -249,    25,  -249,   -72,   -55,  -249,
    -249,  -249,  -249,  -249,  -249,    16,   160,  -249,  -249,  -249,
    -249,  -249,   -48,   -25,   -60,   -26,   150,   153,  -249,   -44,
    -144,   -34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -128
static const yytype_int16 yytable[] =
{
     115,   137,   118,   246,   261,   229,    47,   163,   244,   264,
      -9,    20,   182,    56,   267,   268,   269,   270,   271,   307,
     346,   141,   305,   164,   275,    18,   306,    25,   123,   264,
      28,    29,    30,    31,    32,   249,     1,   250,   165,     2,
     324,     3,   338,    19,     4,   171,   172,   173,   174,   175,
     176,   154,   155,   156,   157,   144,    23,   339,    24,   251,
     267,   268,   269,   270,   271,     5,   142,    92,    93,   143,
      33,   189,    26,   301,   142,   164,   299,   143,   181,    34,
     221,   300,    35,    92,    93,   290,   191,   223,   224,   225,
     165,   245,    21,   170,   234,   235,   236,   237,   218,    36,
     227,   115,   230,   231,    48,   218,   308,   309,   310,    16,
      17,   126,   127,   152,   153,   298,   150,   151,   158,   159,
     263,   264,   352,   353,    37,   221,   280,   232,   233,   331,
      64,    38,   238,   239,    40,    42,    44,    51,    57,    54,
      58,    59,    60,   116,   119,   122,   124,   130,   132,   135,
     262,   333,    21,   138,   162,   147,   160,   148,   145,    65,
     184,   149,   161,   178,   214,   213,   190,   369,   345,   211,
     356,   220,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,   317,    97,   179,    98,   187,   242,   209,   212,
     221,   243,   247,   253,   259,   218,   256,    99,   266,   258,
     273,   272,  -127,   280,   276,   311,   314,   315,   318,   322,
     282,   285,   325,   284,   288,   291,   328,   295,   286,   289,
     292,   296,   323,   303,   326,   329,   332,   334,   343,   357,
     347,   218,   300,   348,   360,   359,   335,   264,   362,   337,
     366,   139,   373,    43,   340,   314,   342,   134,   344,   222,
     257,   283,   297,   186,   365,   293,    64,   274,   287,   336,
     350,   302,   260,   367,   304,   368,    50,   330,   341,   252,
     294,   183,   371,   364,   351,   327,   255,   316,     0,   361,
     216,     0,   363,   318,   322,    65,     0,   372,     0,     0,
     240,     0,     0,     0,   241,     0,   370,     0,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      64,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   217,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    64,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   228,     0,
       0,     0,     0,     0,     0,     0,     0,   193,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    64,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   194,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    64,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    64,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      64,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   312,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,   317,    97,     0,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99
};

static const yytype_int16 yycheck[] =
{
      44,    60,    47,   165,   194,   149,     4,    19,     4,    36,
       0,     6,   123,    37,    37,    38,    39,    40,    41,   267,
      56,    65,    38,    87,   214,    87,    42,     8,    52,    36,
      11,    12,    13,    14,    15,    21,    26,    23,   102,    29,
      47,    31,    42,    32,    34,    49,    50,    51,    52,    53,
      54,    94,    95,    96,    97,    99,    87,   305,     0,   170,
      37,    38,    39,    40,    41,    55,   102,    83,    84,   105,
      87,   130,     3,   263,   102,    87,   103,   105,   122,    87,
     103,   104,    30,    83,    84,   247,   131,    16,    17,    18,
     102,    87,    87,   117,   154,   155,   156,   157,   142,    87,
     148,   145,   150,   151,   102,   149,    39,    40,    41,    27,
      28,     8,     9,    92,    93,   259,    90,    91,    98,    99,
      35,    36,    24,    25,    87,   103,   104,   152,   153,   291,
      15,   104,   158,   159,     6,    87,     5,    87,    87,     7,
      87,   102,   102,     6,    87,    98,   104,   102,    10,    87,
     194,   295,    87,     4,    14,   109,   100,    89,   104,    44,
      87,   102,   101,   103,    46,   102,    33,   357,   312,   103,
     332,    87,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   104,    90,   104,    87,   104,   103,
     103,   102,   104,    11,   102,   259,   105,   102,    43,   103,
     106,    87,   107,   104,    48,   269,   270,   271,   273,   273,
     103,   110,   276,    82,    87,    20,   280,    12,   103,   103,
      22,    87,   103,   102,    45,   103,    20,   103,    35,    13,
     107,   295,   104,   108,    35,   103,   300,    36,   103,   303,
     102,    63,   103,    26,   308,   309,   310,    57,   312,   145,
     187,   222,   257,   127,   352,   251,    15,   213,   243,   301,
     324,   264,   193,   356,   266,   356,    34,   290,   309,   179,
     252,   124,   364,   348,   328,   279,   183,   272,    -1,   343,
     140,    -1,   346,   348,   348,    44,    -1,   366,    -1,    -1,
     160,    -1,    -1,    -1,   161,    -1,   360,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      15,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    15,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    15,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    15,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    15,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      15,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    29,    31,    34,    55,   112,   113,   114,   115,
     116,   159,   165,   169,   172,   173,    27,    28,    87,    32,
       6,    87,   121,    87,     0,   113,     3,   117,   113,   113,
     113,   113,   113,    87,    87,    30,    87,    87,   104,   122,
       6,   174,    87,   119,     5,   123,   124,     4,   102,   160,
     160,    87,   166,   168,     7,   128,   128,    87,    87,   102,
     102,   120,   118,   119,    15,    44,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    90,   102,
     125,   149,   181,   182,   183,   189,   190,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     6,   127,   115,    87,
     161,   162,    98,   128,   104,   167,     8,     9,   129,   130,
     102,   170,    10,   133,   122,    87,   175,   121,     4,   118,
     184,   200,   102,   105,   200,   104,   126,   109,    89,   102,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,    14,    19,    87,   102,   152,   155,   156,   157,
     128,    49,    50,    51,    52,    53,    54,   164,   103,   104,
     163,   200,   133,   168,    87,   131,   131,   104,   132,   121,
      33,   115,   171,    38,   102,   136,   138,   139,   140,   141,
     142,   143,   144,   146,   147,   148,   150,   151,   200,   104,
     176,   103,   103,   102,    46,   185,   187,   103,   200,   201,
      87,   103,   125,    16,    17,    18,   191,   193,   103,   201,
     193,   193,   194,   194,   195,   195,   195,   195,   196,   196,
     197,   198,    87,   102,     4,    87,   152,   104,   158,    21,
      23,   133,   162,    11,   134,   167,   105,   130,   103,   102,
     140,   138,   200,    35,    36,   137,    43,    37,    38,    39,
      40,    41,    87,   106,   123,   138,    48,   188,   186,   187,
     104,   202,   103,   126,    82,   110,   103,   156,    87,   103,
     152,    20,    22,   134,   163,    12,    87,   132,   201,   103,
     104,   138,   139,   102,   151,    38,    42,   149,    39,    40,
      41,   200,   102,   145,   200,   200,   176,    87,   115,   177,
     179,   180,   200,   103,    47,   200,    45,   186,   200,   103,
     158,   152,    20,   201,   103,   200,   137,   200,    42,   149,
     200,   145,   200,    35,   200,   201,    56,   107,   108,   178,
     200,   202,    24,    25,   153,   154,   152,    13,   135,   103,
      35,   200,   103,   200,   179,   136,   102,   153,   154,   138,
     200,   178,   121,   103
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 198 "aquery.y"
    { (yyval.top) = (yyvsp[(1) - (1)].top); ast = (yyval.top); ;}
    break;

  case 3:
#line 200 "aquery.y"
    { (yyval.top) = make_Top_GlobalQuery((yyvsp[(1) - (2)].fullquery), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 4:
#line 201 "aquery.y"
    { (yyval.top) = make_Top_Create((yyvsp[(1) - (2)].create), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 5:
#line 202 "aquery.y"
    { (yyval.top) = make_Top_Insert((yyvsp[(1) - (2)].insert), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 6:
#line 203 "aquery.y"
    { (yyval.top) = make_Top_UpdateDelete((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 7:
#line 204 "aquery.y"
    { (yyval.top) = make_Top_UpdateDelete((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 8:
#line 205 "aquery.y"
    { (yyval.top) = make_Top_UDF((yyvsp[(1) - (2)].udfdef), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 9:
#line 206 "aquery.y"
    { (yyval.top) = NULL; ;}
    break;

  case 10:
#line 211 "aquery.y"
    { (yyval.fullquery) = (yyvsp[(1) - (1)].fullquery); ;}
    break;

  case 11:
#line 214 "aquery.y"
    { env = push_env(env); ;}
    break;

  case 12:
#line 216 "aquery.y"
    { env = pop_env(env); (yyval.fullquery) = make_FullQueryNode((yyvsp[(2) - (3)].localquery), (yyvsp[(3) - (3)].plan)); ;}
    break;

  case 13:
#line 221 "aquery.y"
    { (yyvsp[(2) - (3)].localquery)->next_sibling = (yyvsp[(3) - (3)].localquery); (yyval.localquery) = (yyvsp[(2) - (3)].localquery); ;}
    break;

  case 14:
#line 222 "aquery.y"
    { (yyval.localquery) = NULL; ;}
    break;

  case 15:
#line 225 "aquery.y"
    { (yyvsp[(1) - (2)].localquery)->next_sibling = (yyvsp[(2) - (2)].localquery); (yyval.localquery) = (yyvsp[(1) - (2)].localquery); ;}
    break;

  case 16:
#line 226 "aquery.y"
    { (yyval.localquery) = NULL; ;}
    break;

  case 17:
#line 231 "aquery.y"
    { put_sym(env, (yyvsp[(1) - (6)].str), TABLE_TYPE, 0, 0); (yyval.localquery) = make_LocalQueryNode((yyvsp[(1) - (6)].str), (yyvsp[(2) - (6)].idlist), (yyvsp[(5) - (6)].plan)); add_order(env, (yyvsp[(1) - (6)].str), curr_order); ;}
    break;

  case 18:
#line 234 "aquery.y"
    { (yyval.idlist) = (yyvsp[(2) - (3)].idlist); ;}
    break;

  case 19:
#line 235 "aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 20:
#line 238 "aquery.y"
    { (yyval.idlist) = make_IDListNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].idlist)); ;}
    break;

  case 21:
#line 241 "aquery.y"
    { (yyval.idlist) = make_IDListNode((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].idlist));;}
    break;

  case 22:
#line 242 "aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 23:
#line 248 "aquery.y"
    { (yyval.plan) = assemble_plan((yyvsp[(1) - (5)].plan), (yyvsp[(2) - (5)].plan), (yyvsp[(3) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].plan)); curr_order = (yyvsp[(3) - (5)].plan); ;}
    break;

  case 24:
#line 251 "aquery.y"
    { (yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.plan) = make_project(PROJECT_SELECT, NULL, (yyvsp[(2) - (3)].namedexpr)); ;}
    break;

  case 25:
#line 254 "aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode((yyvsp[(3) - (3)].str), (yyvsp[(1) - (3)].exprnode)); ;}
    break;

  case 26:
#line 255 "aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode(NULL, (yyvsp[(1) - (1)].exprnode)); ;}
    break;

  case 27:
#line 258 "aquery.y"
    { (yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.namedexpr) = (yyvsp[(2) - (3)].namedexpr); ;}
    break;

  case 28:
#line 259 "aquery.y"
    { (yyval.namedexpr) = NULL; ;}
    break;

  case 29:
#line 262 "aquery.y"
    { (yyval.plan) = (yyvsp[(2) - (2)].plan); ;}
    break;

  case 30:
#line 265 "aquery.y"
    { (yyval.plan) = make_sort(NULL, (yyvsp[(2) - (2)].order));;}
    break;

  case 31:
#line 266 "aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 32:
#line 269 "aquery.y"
    { (yyvsp[(1) - (2)].order)->next = (yyvsp[(2) - (2)].order); (yyval.order) = (yyvsp[(1) - (2)].order); ;}
    break;

  case 33:
#line 272 "aquery.y"
    { (yyval.order) = make_OrderNode(ASC_SORT, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 34:
#line 273 "aquery.y"
    { (yyval.order) = make_OrderNode(DESC_SORT, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 35:
#line 276 "aquery.y"
    { (yyval.exprnode) = make_id(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 36:
#line 277 "aquery.y"
    { (yyval.exprnode) = make_colDotAccessNode(make_id(env, (yyvsp[(1) - (3)].str)), make_id(env, (yyvsp[(3) - (3)].str))); ;}
    break;

  case 37:
#line 280 "aquery.y"
    { (yyvsp[(2) - (3)].order)->next = (yyvsp[(3) - (3)].order); (yyval.order) = (yyvsp[(2) - (3)].order); ;}
    break;

  case 38:
#line 281 "aquery.y"
    { (yyval.order) = NULL; ;}
    break;

  case 39:
#line 288 "aquery.y"
    { (yyval.plan) = make_filterWhere(NULL, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 40:
#line 289 "aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 41:
#line 292 "aquery.y"
    { (yyval.plan) = pushdown_logical((yyvsp[(4) - (4)].plan), make_groupby(NULL, (yyvsp[(3) - (4)].exprnode)));   ;}
    break;

  case 42:
#line 293 "aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 43:
#line 296 "aquery.y"
    { (yyval.plan) = make_filterHaving(NULL, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 44:
#line 297 "aquery.y"
    { (yyval.plan) =  NULL; ;}
    break;

  case 45:
#line 311 "aquery.y"
    { (yyvsp[(1) - (2)].exprnode)->next_sibling = (yyvsp[(2) - (2)].exprnode); (yyval.exprnode) = make_exprListNode((yyvsp[(1) - (2)].exprnode)); ;}
    break;

  case 46:
#line 314 "aquery.y"
    { (yyvsp[(2) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 47:
#line 315 "aquery.y"
    { (yyval.exprnode) = NULL;                      ;}
    break;

  case 48:
#line 318 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 49:
#line 319 "aquery.y"
    { (yyval.exprnode) = make_logicOpNode(WHERE_OR_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 50:
#line 322 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 51:
#line 323 "aquery.y"
    { (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 52:
#line 326 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 53:
#line 327 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 54:
#line 331 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 55:
#line 332 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 56:
#line 333 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 57:
#line 337 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 58:
#line 338 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 59:
#line 339 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 60:
#line 340 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 61:
#line 341 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 62:
#line 347 "aquery.y"
    { (yyvsp[(1) - (5)].exprnode)->next_sibling = (yyvsp[(3) - (5)].exprnode); (yyvsp[(3) - (5)].exprnode)->next_sibling = (yyvsp[(5) - (5)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (5)].str)), make_exprListNode((yyvsp[(1) - (5)].exprnode))); ;}
    break;

  case 63:
#line 348 "aquery.y"
    { (yyvsp[(1) - (6)].exprnode)->next_sibling = (yyvsp[(4) - (6)].exprnode); (yyvsp[(4) - (6)].exprnode)->next_sibling = (yyvsp[(6) - (6)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (6)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (6)].str)), make_exprListNode((yyvsp[(1) - (6)].exprnode))))); ;}
    break;

  case 64:
#line 351 "aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 65:
#line 352 "aquery.y"
    { (yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 66:
#line 355 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 67:
#line 356 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 68:
#line 359 "aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 69:
#line 360 "aquery.y"
    { (yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 70:
#line 363 "aquery.y"
    { (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(4) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 71:
#line 364 "aquery.y"
    { (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 72:
#line 367 "aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 73:
#line 368 "aquery.y"
    { (yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (4)].str)),  make_exprListNode(make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 74:
#line 371 "aquery.y"
    { (yyval.exprnode) = make_bool(1); ;}
    break;

  case 75:
#line 372 "aquery.y"
    { (yyval.exprnode) = make_bool(0); ;}
    break;

  case 76:
#line 375 "aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 77:
#line 378 "aquery.y"
    { (yyvsp[(2) - (5)].exprnode)->next_sibling = (yyvsp[(4) - (5)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (5)].exprnode); ;}
    break;

  case 78:
#line 385 "aquery.y"
    { (yyval.plan) = (yyvsp[(1) - (1)].plan);                                                ;}
    break;

  case 79:
#line 386 "aquery.y"
    { (yyval.plan) = make_joinOn(INNER_JOIN_ON, (yyvsp[(1) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].exprnode));            ;}
    break;

  case 80:
#line 387 "aquery.y"
    { (yyval.plan) = make_joinUsing(INNER_JOIN_USING, (yyvsp[(1) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].idlist));      ;}
    break;

  case 81:
#line 388 "aquery.y"
    { (yyval.plan) = make_joinOn(FULL_OUTER_JOIN_ON, (yyvsp[(1) - (6)].plan), (yyvsp[(5) - (6)].plan), (yyvsp[(6) - (6)].exprnode));       ;}
    break;

  case 82:
#line 389 "aquery.y"
    { (yyval.plan) = make_joinUsing(FULL_OUTER_JOIN_USING, (yyvsp[(1) - (6)].plan), (yyvsp[(5) - (6)].plan), (yyvsp[(6) - (6)].idlist)); ;}
    break;

  case 83:
#line 393 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (2)].exprnode); ;}
    break;

  case 84:
#line 396 "aquery.y"
    { (yyval.idlist) = (yyvsp[(3) - (4)].idlist); ;}
    break;

  case 85:
#line 399 "aquery.y"
    { (yyval.plan) = (yyvsp[(1) - (1)].plan);               ;}
    break;

  case 86:
#line 400 "aquery.y"
    { (yyval.plan) = make_flatten((yyvsp[(3) - (4)].plan)); ;}
    break;

  case 87:
#line 403 "aquery.y"
    { (yyval.plan) = make_alias(make_table((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 88:
#line 404 "aquery.y"
    { (yyval.plan) = make_alias(make_table((yyvsp[(1) - (3)].str)), (yyvsp[(3) - (3)].str)); ;}
    break;

  case 89:
#line 405 "aquery.y"
    { (yyval.plan) = make_table((yyvsp[(1) - (1)].str));                 ;}
    break;

  case 90:
#line 406 "aquery.y"
    { (yyval.plan) = (yyvsp[(2) - (3)].plan);                             ;}
    break;

  case 91:
#line 411 "aquery.y"
    { if((yyvsp[(2) - (2)].plan) == NULL){ (yyval.plan) = (yyvsp[(1) - (2)].plan); } else { (yyval.plan) = make_cross((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].plan)); } ;}
    break;

  case 92:
#line 414 "aquery.y"
    { if((yyvsp[(3) - (3)].plan) == NULL){ (yyval.plan) = (yyvsp[(2) - (3)].plan); } else { warning_Cross(); (yyval.plan) = make_cross((yyvsp[(2) - (3)].plan), (yyvsp[(3) - (3)].plan)); } ;}
    break;

  case 93:
#line 415 "aquery.y"
    { (yyval.plan) = NULL;                                                   ;}
    break;

  case 94:
#line 419 "aquery.y"
    { put_sym(env, (yyvsp[(3) - (4)].str), TABLE_TYPE, 0, 0); (yyval.create) = make_createNode(CREATE_TABLE, (yyvsp[(3) - (4)].str), (yyvsp[(4) - (4)].createsrc)); ;}
    break;

  case 95:
#line 420 "aquery.y"
    { put_sym(env, (yyvsp[(3) - (4)].str), VIEW_TYPE, 0, 0);  (yyval.create) = make_createNode(CREATE_VIEW, (yyvsp[(3) - (4)].str), (yyvsp[(4) - (4)].createsrc));  ;}
    break;

  case 96:
#line 423 "aquery.y"
    { (yyval.createsrc) = make_querySource((yyvsp[(2) - (2)].fullquery));  ;}
    break;

  case 97:
#line 424 "aquery.y"
    { (yyval.createsrc) = make_schemaSource((yyvsp[(2) - (3)].schema)); ;}
    break;

  case 98:
#line 427 "aquery.y"
    { (yyvsp[(1) - (2)].schema)->next_sibling = (yyvsp[(2) - (2)].schema); (yyval.schema) = (yyvsp[(1) - (2)].schema); ;}
    break;

  case 99:
#line 430 "aquery.y"
    { (yyval.schema) = make_schemaNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 100:
#line 433 "aquery.y"
    { (yyvsp[(2) - (3)].schema)->next_sibling = (yyvsp[(3) - (3)].schema); (yyval.schema) = (yyvsp[(2) - (3)].schema); ;}
    break;

  case 101:
#line 434 "aquery.y"
    { (yyval.schema) = NULL;                      ;}
    break;

  case 102:
#line 437 "aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 103:
#line 438 "aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 104:
#line 439 "aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 105:
#line 440 "aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 106:
#line 441 "aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 107:
#line 442 "aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 108:
#line 447 "aquery.y"
    { (yyval.plan)  = assemble_base(make_project(PROJECT_UPDATE, NULL, (yyvsp[(4) - (7)].namedexpr)), make_table((yyvsp[(2) - (7)].str)), (yyvsp[(5) - (7)].plan), (yyvsp[(6) - (7)].plan), (yyvsp[(7) - (7)].plan)); ;}
    break;

  case 109:
#line 450 "aquery.y"
    { (yyvsp[(1) - (2)].namedexpr)->next_sibling = (yyvsp[(2) - (2)].namedexpr); (yyval.namedexpr) = (yyvsp[(1) - (2)].namedexpr); ;}
    break;

  case 110:
#line 453 "aquery.y"
    { (yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.namedexpr) = (yyvsp[(2) - (3)].namedexpr); ;}
    break;

  case 111:
#line 454 "aquery.y"
    { (yyval.namedexpr) = NULL; ;}
    break;

  case 112:
#line 457 "aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 113:
#line 460 "aquery.y"
    { (yyval.insert) = make_insert(assemble_base(NULL, make_table((yyvsp[(3) - (6)].str)), (yyvsp[(4) - (6)].plan), NULL, NULL), (yyvsp[(5) - (6)].idlist), (yyvsp[(6) - (6)].fullquery)); ;}
    break;

  case 114:
#line 463 "aquery.y"
    {  (yyval.idlist) = (yyvsp[(2) - (3)].idlist); ;}
    break;

  case 115:
#line 464 "aquery.y"
    {  (yyval.idlist) = NULL; ;}
    break;

  case 116:
#line 467 "aquery.y"
    { (yyval.fullquery) = (yyvsp[(1) - (1)].fullquery); ;}
    break;

  case 117:
#line 468 "aquery.y"
    { (yyval.fullquery) = make_FullQueryNode(NULL, make_values((yyvsp[(3) - (4)].exprnode))); ;}
    break;

  case 118:
#line 471 "aquery.y"
    { (yyval.plan) = assemble_base(make_delete(NULL, NULL), make_table((yyvsp[(3) - (5)].str)), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].plan), NULL);   ;}
    break;

  case 119:
#line 472 "aquery.y"
    { (yyval.plan) = assemble_base(make_delete(NULL, (yyvsp[(2) - (4)].idlist)), make_table((yyvsp[(4) - (4)].str)), NULL, NULL, NULL); ;}
    break;

  case 120:
#line 477 "aquery.y"
    { put_sym(env, (yyvsp[(2) - (2)].str), FUNCTION_TYPE, 0, 0); env = push_env(env);  ;}
    break;

  case 121:
#line 483 "aquery.y"
    { env = pop_env(env); (yyval.udfdef) =  make_UDFDefNode((yyvsp[(2) - (9)].str), (yyvsp[(5) - (9)].idlist), (yyvsp[(8) - (9)].udfbody)); entry = lookup_sym(env, (yyvsp[(2) - (9)].str)); entry->order_dep = (yyval.udfdef)->order_dep; entry->uses_agg = (yyval.udfdef)->uses_agg; ;}
    break;

  case 122:
#line 486 "aquery.y"
    { put_sym(env, (yyvsp[(1) - (2)].str), UNKNOWN_TYPE, 0, 0); (yyval.idlist) = make_IDListNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].idlist)); ;}
    break;

  case 123:
#line 487 "aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 124:
#line 490 "aquery.y"
    { put_sym(env, (yyvsp[(2) - (3)].str), UNKNOWN_TYPE, 0, 0); (yyval.idlist) = make_IDListNode((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].idlist)); ;}
    break;

  case 125:
#line 491 "aquery.y"
    {(yyval.idlist) = NULL; ;}
    break;

  case 126:
#line 495 "aquery.y"
    { (yyvsp[(1) - (2)].udfbody)->next_sibling = (yyvsp[(2) - (2)].udfbody); (yyval.udfbody) = (yyvsp[(1) - (2)].udfbody);;}
    break;

  case 127:
#line 496 "aquery.y"
    { (yyval.udfbody) = NULL; ;}
    break;

  case 128:
#line 499 "aquery.y"
    { (yyvsp[(2) - (3)].udfbody)->next_sibling = (yyvsp[(3) - (3)].udfbody); (yyval.udfbody) = (yyvsp[(2) - (3)].udfbody); ;}
    break;

  case 129:
#line 500 "aquery.y"
    { (yyval.udfbody)= NULL; ;}
    break;

  case 130:
#line 503 "aquery.y"
    {(yyval.udfbody) = make_UDFExpr((yyvsp[(1) - (1)].exprnode));   ;}
    break;

  case 131:
#line 504 "aquery.y"
    {(yyval.udfbody) = make_UDFVardef((yyvsp[(1) - (1)].namedexpr)); ;}
    break;

  case 132:
#line 505 "aquery.y"
    {(yyval.udfbody) = make_UDFQuery((yyvsp[(1) - (1)].fullquery));  ;}
    break;

  case 133:
#line 508 "aquery.y"
    { put_sym(env, (yyvsp[(1) - (3)].str), UNKNOWN_TYPE, 0, 0);    (yyval.namedexpr) = make_NamedExprNode((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 134:
#line 512 "aquery.y"
    { (yyval.exprnode) = make_int((yyvsp[(1) - (1)].intval));    ;}
    break;

  case 135:
#line 513 "aquery.y"
    { (yyval.exprnode) = make_float((yyvsp[(1) - (1)].floatval));  ;}
    break;

  case 136:
#line 514 "aquery.y"
    { (yyval.exprnode) = make_date((yyvsp[(1) - (1)].str));   ;}
    break;

  case 137:
#line 515 "aquery.y"
    { (yyval.exprnode) = make_string((yyvsp[(1) - (1)].str)); ;}
    break;

  case 138:
#line 516 "aquery.y"
    { (yyval.exprnode) = make_hex((yyvsp[(1) - (1)].str));    ;}
    break;

  case 139:
#line 517 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);              ;}
    break;

  case 140:
#line 520 "aquery.y"
    { (yyval.exprnode) = make_rowId();                                              ;}
    break;

  case 141:
#line 521 "aquery.y"
    { (yyval.exprnode) = make_colDotAccessNode(make_id(env, (yyvsp[(1) - (3)].str)), make_id(env, (yyvsp[(3) - (3)].str))); ;}
    break;

  case 142:
#line 522 "aquery.y"
    { (yyval.exprnode) = make_allColsNode();                                        ;}
    break;

  case 143:
#line 526 "aquery.y"
    { (yyval.exprnode) = make_caseNode((yyvsp[(2) - (5)].exprnode), (yyvsp[(3) - (5)].exprnode), (yyvsp[(4) - (5)].exprnode)); ;}
    break;

  case 144:
#line 529 "aquery.y"
    { (yyval.exprnode) = make_caseClauseNode((yyvsp[(1) - (1)].exprnode));   ;}
    break;

  case 145:
#line 530 "aquery.y"
    { (yyval.exprnode) = make_caseClauseNode(NULL); ;}
    break;

  case 146:
#line 533 "aquery.y"
    { (yyval.exprnode) = make_whenClausesNode((yyvsp[(1) - (2)].exprnode), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 147:
#line 536 "aquery.y"
    { (yyval.exprnode) = make_whenClausesNode((yyvsp[(1) - (2)].exprnode), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 148:
#line 537 "aquery.y"
    { (yyval.exprnode) = NULL; ;}
    break;

  case 149:
#line 540 "aquery.y"
    { (yyval.exprnode) = make_caseWhenNode((yyvsp[(2) - (4)].exprnode), (yyvsp[(4) - (4)].exprnode)); ;}
    break;

  case 150:
#line 543 "aquery.y"
    { (yyval.exprnode) = make_elseClauseNode((yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 151:
#line 546 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 152:
#line 547 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 153:
#line 548 "aquery.y"
    { (yyval.exprnode) = make_id(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 154:
#line 549 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 155:
#line 550 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 156:
#line 553 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                         ;}
    break;

  case 157:
#line 554 "aquery.y"
    { (yyval.exprnode) = make_indexNode((yyvsp[(1) - (4)].exprnode), (yyvsp[(3) - (4)].exprnode));                     ;}
    break;

  case 158:
#line 555 "aquery.y"
    { (yyval.exprnode) = make_callNode((yyvsp[(1) - (4)].exprnode), (yyvsp[(3) - (4)].exprnode));                      ;}
    break;

  case 159:
#line 556 "aquery.y"
    { (yyval.exprnode) = make_callNode((yyvsp[(1) - (3)].exprnode), NULL);                    ;}
    break;

  case 160:
#line 557 "aquery.y"
    { (yyval.exprnode) = make_callNode(make_udfNode(env, (yyvsp[(1) - (4)].str)), (yyvsp[(3) - (4)].exprnode));   ;}
    break;

  case 161:
#line 558 "aquery.y"
    { (yyval.exprnode) = make_callNode(make_udfNode(env, (yyvsp[(1) - (3)].str)), NULL); ;}
    break;

  case 162:
#line 562 "aquery.y"
    { (yyval.exprnode) = make_oddix();      ;}
    break;

  case 163:
#line 563 "aquery.y"
    { (yyval.exprnode) = make_evenix();     ;}
    break;

  case 164:
#line 564 "aquery.y"
    { (yyval.exprnode) = make_everynix((yyvsp[(2) - (2)].intval)); ;}
    break;

  case 165:
#line 567 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 166:
#line 568 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 167:
#line 569 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 168:
#line 570 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 169:
#line 571 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 170:
#line 572 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 171:
#line 573 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 172:
#line 574 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 173:
#line 575 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 174:
#line 576 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 175:
#line 577 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 176:
#line 578 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 177:
#line 579 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 178:
#line 580 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 179:
#line 581 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 180:
#line 582 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 181:
#line 583 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 182:
#line 584 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 183:
#line 585 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 184:
#line 586 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 185:
#line 587 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 186:
#line 588 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 187:
#line 589 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 188:
#line 590 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 189:
#line 593 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                               ;}
    break;

  case 190:
#line 594 "aquery.y"
    { (yyval.exprnode) = make_arithNode(POW_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 191:
#line 597 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                ;}
    break;

  case 192:
#line 598 "aquery.y"
    { (yyval.exprnode) = make_arithNode(MULT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 193:
#line 599 "aquery.y"
    { (yyval.exprnode) = make_arithNode(DIV_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode));  ;}
    break;

  case 194:
#line 603 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                 ;}
    break;

  case 195:
#line 604 "aquery.y"
    { (yyval.exprnode) = make_arithNode(PLUS_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode));  ;}
    break;

  case 196:
#line 605 "aquery.y"
    { (yyval.exprnode) = make_arithNode(MINUS_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 197:
#line 608 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                             ;}
    break;

  case 198:
#line 609 "aquery.y"
    { (yyval.exprnode) = make_compNode(LT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 199:
#line 610 "aquery.y"
    { (yyval.exprnode) = make_compNode(GT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 200:
#line 611 "aquery.y"
    { (yyval.exprnode) = make_compNode(LE_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 201:
#line 612 "aquery.y"
    { (yyval.exprnode) = make_compNode(GE_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 202:
#line 615 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                              ;}
    break;

  case 203:
#line 616 "aquery.y"
    { (yyval.exprnode) = make_compNode(EQ_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode));  ;}
    break;

  case 204:
#line 617 "aquery.y"
    { (yyval.exprnode) = make_compNode(NEQ_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 205:
#line 620 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                  ;}
    break;

  case 206:
#line 621 "aquery.y"
    { (yyval.exprnode) = make_logicOpNode(LAND_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 207:
#line 624 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                 ;}
    break;

  case 208:
#line 625 "aquery.y"
    { (yyval.exprnode) = make_logicOpNode(LOR_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 209:
#line 628 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 210:
#line 632 "aquery.y"
    { (yyvsp[(1) - (2)].exprnode)->next_sibling = (yyvsp[(2) - (2)].exprnode); (yyval.exprnode) = make_exprListNode((yyvsp[(1) - (2)].exprnode)); ;}
    break;

  case 211:
#line 635 "aquery.y"
    { (yyvsp[(2) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 212:
#line 636 "aquery.y"
    { (yyval.exprnode) = NULL; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3102 "aquery.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 642 "aquery.y"


void yyerror(const char *s) 
{
	//TODO: rewrite with more robust fgets wrapper
	//rewind file and find error
	rewind(yyin);
	int lines = line_num, cols = col_num;
	int max_size = 500;
	
	char *line = malloc(sizeof(char) * (max_size - 1));
	char *marker = malloc(sizeof(char) * (col_num + 2));
	memset(marker, ' ', col_num + 1);
	marker[col_num - yyleng] = '^';
	marker[col_num + 1] = '\0';
	
	while(lines-- > 0) 
	{ //find line with error
		fgets(line, max_size, yyin);
	}
	
	printf("%s at line %d, column %d\n%s" ERRORCOLOR "%s\n", s, line_num, col_num - yyleng, line, marker);
	fclose(yyin);
	free(line); free(marker);
	exit(1);
}

void help()
{
	printf("Usage: ./a2q [-p][-a <#>] aquery_file\n");
	printf("-p  print dot file AST to stdout\n");
	printf("-a  optimization level [0-1]\n");
    printf("-s  silence warnings\n");
}

void warning_Cross()
{
    if(!silence_warnings)
    {
         printf("The use of , at line:%d can result in reduced performance if no join-key is provided\n", line_num);
         printf("Run compiler with -s option to silence these warnings\n");
    }
}


int main(int argc, char *argv[]) {
	yydebug = 0;
	
	/* Aquery compiler flags */
	int print_ast_flag = 0;
	optim_level = 0;
	int max_optim_level = 1;
	
	/* getopt values */
	int op;
	
	
	while((op = getopt(argc, argv, "spha:")) != -1)
	{
		switch(op)
		{
            case 's':
                silence_warnings = 1;
                break;
			case 'p':
				print_ast_flag = 1;
				break;
			case 'h':
				help();
				exit(0);
				break;
			case 'a':
				if(!isdigit(optarg[0]))
				{
					printf("-%c requires numeric arg\n", optopt);
					help();
					exit(1);
				}
				
				optim_level = atoi(optarg);
				
				if(optim_level > max_optim_level)
				{
					printf("Defaulting to highest optimizing level:%d\n", max_optim_level);
					optim_level = max_optim_level;
				}
				break;
			case '?':
				if(optopt == 'a')
				{
					printf("Option -%c requires an option\n", optopt);
					exit(1);
				}
				break;
			default:
 				exit(1);
		}
	}
	
	
	
	if(1 > argc - optind) 
	{ //Did we get a file to analyze?
		help();
		exit(1);
	}
	
	FILE *to_parse = fopen(argv[optind], "r");
	
	if(to_parse == NULL)
	{
		printf("Unable to open %s for reading\n", argv[optind]);
		exit(1);
	}
	else
	{
		yyin = to_parse;
	}
	
	env = init_symtable(); //create the global environment
	
	do 
	{
		yyparse();
	} 
	while(!feof(yyin));
	
	if(print_ast_flag)
	{
		print_ast(ast);
	}		
		
}


