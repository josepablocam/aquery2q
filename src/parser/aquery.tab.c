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
     SQRT = 328,
     STDDEV = 329,
     AVGS = 330,
     DELTAS = 331,
     MAXS = 332,
     MINS = 333,
     PRDS = 334,
     SUMS = 335,
     MAKENULL = 336,
     FLOAT = 337,
     INT = 338,
     TRUE = 339,
     FALSE = 340,
     DATE = 341,
     HEX = 342,
     ID = 343,
     STRING = 344,
     EXP_OP = 345,
     TIMES_OP = 346,
     DIV_OP = 347,
     PLUS_OP = 348,
     MINUS_OP = 349,
     LE_OP = 350,
     GE_OP = 351,
     L_OP = 352,
     G_OP = 353,
     EQ_OP = 354,
     NEQ_OP = 355,
     AND_OP = 356,
     OR_OP = 357
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
#define SQRT 328
#define STDDEV 329
#define AVGS 330
#define DELTAS 331
#define MAXS 332
#define MINS 333
#define PRDS 334
#define SUMS 335
#define MAKENULL 336
#define FLOAT 337
#define INT 338
#define TRUE 339
#define FALSE 340
#define DATE 341
#define HEX 342
#define ID 343
#define STRING 344
#define EXP_OP 345
#define TIMES_OP 346
#define DIV_OP 347
#define PLUS_OP 348
#define MINUS_OP 349
#define LE_OP 350
#define GE_OP 351
#define L_OP 352
#define G_OP 353
#define EQ_OP 354
#define NEQ_OP 355
#define AND_OP 356
#define OR_OP 357




/* Copy the first part of user declarations.  */
#line 1 "parser/aquery.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "symtable.h"  /* manages the symbol table, to enable meta data lookup */	
#include "../ast/ast.h"       /* builds ast for parser */
#include "../ast/ast_print.h" /* provides dot printing of ast */
#include "../optimizer/optimizer.h" /* optimizing for query plans */
#include "../codegen/codegen.h" /* generates q code */
	
#define YYDEBUG 1
#define ERRORCOLOR  "\x1B[32m"
#define SAFE_ORDER_DEP(x) ((x) != NULL && (x)->order_dep);

extern int yyleng;
extern FILE *yyin;
extern int yylex();
extern int yyparse();


//for debugging purposes, defined in flex
extern int line_num; 
extern int col_num;

//For reporting query issues
int query_line_num;
int query_col_num;

//Symbol table
Symtable *env;	/* global symbol table: stack of hash tables */
Symentry *entry; /* place holder for entry pointers to perform modifications ad-hoc */

//AST
TopLevelNode* ast; /* holds any asts created during compilation */
LogicalQueryNode *curr_order;

//Code generation
FILE *DEST_FILE;
int GEN_CODE = 0;


void yyerror(const char *);

//Command line options
int optim_level = 0; //level of optimization in ast
int silence_warnings = 0;



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
#line 173 "parser/aquery.y"
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
#line 372 "parser/aquery.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 385 "parser/aquery.tab.c"

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
#define YYLAST   891

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  217
/* YYNRULES -- Number of states.  */
#define YYNSTATES  380

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     103,   104,     2,     2,   105,     2,   106,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   109,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   110,     2,   111,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   107,     2,   108,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      24,    26,    27,    31,    35,    36,    39,    40,    47,    51,
      52,    55,    59,    60,    66,    70,    74,    76,    80,    81,
      82,    86,    89,    90,    93,    96,    99,   101,   105,   109,
     110,   113,   114,   119,   120,   123,   124,   127,   131,   132,
     134,   138,   140,   143,   145,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   171,   178,   182,   187,   191,   193,
     197,   202,   207,   211,   215,   220,   222,   224,   228,   234,
     236,   242,   248,   255,   262,   265,   270,   273,   275,   280,
     283,   287,   289,   293,   296,   300,   301,   306,   311,   314,
     318,   321,   324,   328,   329,   331,   333,   335,   337,   339,
     341,   349,   352,   356,   357,   361,   368,   372,   373,   375,
     380,   386,   391,   392,   402,   405,   406,   410,   411,   414,
     415,   419,   420,   422,   424,   426,   430,   432,   434,   436,
     438,   440,   442,   444,   448,   450,   456,   458,   459,   462,
     465,   466,   471,   474,   476,   478,   480,   484,   486,   488,
     493,   498,   502,   507,   511,   513,   515,   518,   520,   522,
     524,   526,   528,   530,   532,   534,   536,   538,   540,   542,
     544,   546,   548,   550,   552,   554,   556,   558,   560,   562,
     564,   566,   568,   570,   573,   575,   579,   581,   585,   589,
     591,   595,   599,   601,   605,   609,   613,   617,   619,   623,
     627,   629,   633,   635,   639,   641,   644,   648
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     113,     0,    -1,   114,    -1,   115,   114,    -1,   161,   114,
      -1,   171,   114,    -1,   167,   114,    -1,   174,   114,    -1,
     175,   114,    -1,    -1,   116,    -1,    -1,   117,   118,   124,
      -1,     3,   120,   119,    -1,    -1,   120,   119,    -1,    -1,
      88,   121,     4,   103,   124,   104,    -1,   103,   122,   104,
      -1,    -1,    88,   123,    -1,   105,    88,   123,    -1,    -1,
     125,   128,   130,   135,   136,    -1,     5,   126,   127,    -1,
     203,    14,    88,    -1,   203,    -1,   105,   126,   127,    -1,
      -1,    -1,     6,   129,   159,    -1,     7,   131,    -1,    -1,
     132,   134,    -1,     8,   133,    -1,     9,   133,    -1,    88,
      -1,    88,   106,    88,    -1,   105,   132,   134,    -1,    -1,
      10,   138,    -1,    -1,    11,    12,   204,   137,    -1,    -1,
      13,   138,    -1,    -1,   140,   139,    -1,    35,   140,   139,
      -1,    -1,   141,    -1,   140,    36,   141,    -1,   142,    -1,
      38,   142,    -1,   143,    -1,   103,   140,   104,    -1,   203,
      -1,   144,    -1,   152,    -1,   145,    -1,   146,    -1,   149,
      -1,   148,    -1,   150,    -1,   203,    39,   203,    35,   203,
      -1,   203,    38,    39,   203,    35,   203,    -1,   203,    40,
     147,    -1,   203,    38,    40,   147,    -1,   103,   204,   104,
      -1,   203,    -1,   203,    41,   203,    -1,   203,    38,    41,
     203,    -1,   203,    37,    38,    42,    -1,   203,    37,    42,
      -1,   203,    37,   151,    -1,   203,    37,    38,   151,    -1,
      84,    -1,    85,    -1,   153,    43,   153,    -1,   103,   203,
     105,   203,   104,    -1,   157,    -1,   157,    21,    20,   154,
     155,    -1,   157,    21,    20,   154,   156,    -1,   157,    23,
      22,    20,   154,   155,    -1,   157,    23,    22,    20,   154,
     156,    -1,    24,   138,    -1,    25,   103,   122,   104,    -1,
      25,    88,    -1,   158,    -1,    19,   103,   158,   104,    -1,
      88,    88,    -1,    88,     4,    88,    -1,    88,    -1,   103,
     154,   104,    -1,   154,   160,    -1,   105,   154,   160,    -1,
      -1,    26,    27,    88,   162,    -1,    26,    28,    88,   162,
      -1,     4,   116,    -1,   103,   163,   104,    -1,   164,   165,
      -1,    88,   166,    -1,   105,   164,   165,    -1,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    29,    88,    30,   168,   130,   135,   136,    -1,   170,
     169,    -1,   105,   170,   169,    -1,    -1,    88,    99,   203,
      -1,    31,    32,    88,   130,   172,   173,    -1,   103,   122,
     104,    -1,    -1,   116,    -1,    33,   103,   204,   104,    -1,
      34,     6,    88,   130,   135,    -1,    34,   122,     6,    88,
      -1,    -1,    55,    88,   176,   103,   177,   104,   107,   179,
     108,    -1,    88,   178,    -1,    -1,   105,    88,   178,    -1,
      -1,   181,   180,    -1,    -1,   109,   181,   180,    -1,    -1,
     203,    -1,   182,    -1,   116,    -1,    88,    56,   203,    -1,
      83,    -1,    82,    -1,    86,    -1,    89,    -1,    87,    -1,
     151,    -1,    15,    -1,    88,   106,    88,    -1,    91,    -1,
      44,   186,   187,   190,    45,    -1,   203,    -1,    -1,   189,
     188,    -1,   189,   188,    -1,    -1,    46,   140,    47,   203,
      -1,    48,   203,    -1,   183,    -1,   184,    -1,    88,    -1,
     103,   203,   104,    -1,   185,    -1,   191,    -1,   191,   110,
     193,   111,    -1,   194,   103,   204,   104,    -1,   194,   103,
     104,    -1,    88,   103,   204,   104,    -1,    88,   103,   104,
      -1,    16,    -1,    17,    -1,    18,    83,    -1,    57,    -1,
      58,    -1,    75,    -1,    59,    -1,    76,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      77,    -1,    66,    -1,    78,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,    79,    -1,    71,    -1,    72,    -1,
      80,    -1,    73,    -1,    74,    -1,    81,    -1,   192,    -1,
      94,   192,    -1,   195,    -1,   195,    90,   196,    -1,   196,
      -1,   197,    91,   196,    -1,   197,    92,   196,    -1,   197,
      -1,   198,    93,   197,    -1,   198,    94,   197,    -1,   198,
      -1,   199,    97,   198,    -1,   199,    98,   198,    -1,   199,
      95,   198,    -1,   199,    96,   198,    -1,   199,    -1,   200,
      99,   199,    -1,   200,   100,   199,    -1,   200,    -1,   201,
     101,   200,    -1,   201,    -1,   202,   102,   201,    -1,   202,
      -1,   203,   205,    -1,   105,   203,   205,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   210,   210,   213,   214,   215,   216,   217,   218,   219,
     225,   228,   228,   235,   236,   239,   240,   243,   248,   249,
     252,   255,   256,   263,   266,   269,   270,   273,   274,   277,
     277,   280,   281,   284,   287,   288,   291,   292,   295,   296,
     299,   300,   303,   304,   307,   308,   323,   326,   327,   330,
     331,   334,   335,   338,   339,   343,   344,   345,   349,   350,
     351,   352,   353,   359,   360,   363,   364,   367,   368,   371,
     372,   375,   376,   379,   380,   383,   384,   387,   390,   397,
     398,   399,   400,   401,   405,   408,   409,   412,   413,   416,
     417,   418,   419,   424,   427,   428,   432,   433,   436,   437,
     440,   443,   446,   447,   450,   451,   452,   453,   454,   455,
     460,   463,   466,   467,   470,   473,   476,   477,   480,   481,
     484,   485,   490,   490,   499,   500,   503,   504,   508,   509,
     512,   513,   516,   517,   518,   521,   525,   526,   527,   528,
     529,   530,   533,   534,   535,   539,   542,   543,   546,   549,
     550,   553,   556,   559,   560,   561,   562,   563,   566,   567,
     568,   569,   570,   571,   575,   576,   577,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   596,   597,   598,   599,   600,   601,   602,
     603,   604,   607,   608,   611,   612,   615,   616,   617,   621,
     622,   623,   626,   627,   628,   629,   630,   633,   634,   635,
     638,   639,   642,   643,   646,   650,   653,   654
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
  "MAX", "MIN", "MOD", "NEXT", "PREV", "PRD", "REV", "SUM", "SQRT",
  "STDDEV", "AVGS", "DELTAS", "MAXS", "MINS", "PRDS", "SUMS", "MAKENULL",
  "FLOAT", "INT", "TRUE", "FALSE", "DATE", "HEX", "ID", "STRING", "EXP_OP",
  "TIMES_OP", "DIV_OP", "PLUS_OP", "MINUS_OP", "LE_OP", "GE_OP", "L_OP",
  "G_OP", "EQ_OP", "NEQ_OP", "AND_OP", "OR_OP", "'('", "')'", "','", "'.'",
  "'{'", "'}'", "';'", "'['", "']'", "$accept", "program", "top_level",
  "global_query", "full_query", "@1", "local_queries",
  "local_queries_tail", "local_query", "col_aliases",
  "comma_identifier_list", "comma_identifier_list_tail", "base_query",
  "select_clause", "select_elem", "select_clause_tail", "from_clause",
  "@2", "order_clause", "order_specs", "order_spec", "column_name",
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
  "delete_statement", "user_function_definition", "@3", "def_arg_list",
  "def_arg_list_tail", "function_body", "function_body_tail",
  "function_body_elem", "function_local_var_def", "constant",
  "table_constant", "case_expression", "case_clause", "when_clauses",
  "when_clauses_tail", "when_clause", "else_clause", "main_expression",
  "call", "indexing", "built_in_fun", "unary_neg", "exp_expression",
  "mult_expression", "add_expression", "rel_expression", "eq_expression",
  "and_expression", "or_expression", "value_expression",
  "comma_value_expression_list", "comma_value_expression_list_tail", 0
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
     355,   356,   357,    40,    41,    44,    46,   123,   125,    59,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   114,   114,   114,   114,   114,   114,   114,
     115,   117,   116,   118,   118,   119,   119,   120,   121,   121,
     122,   123,   123,   124,   125,   126,   126,   127,   127,   129,
     128,   130,   130,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   138,   139,   139,   140,
     140,   141,   141,   142,   142,   143,   143,   143,   144,   144,
     144,   144,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   153,   154,
     154,   154,   154,   154,   155,   156,   156,   157,   157,   158,
     158,   158,   158,   159,   160,   160,   161,   161,   162,   162,
     163,   164,   165,   165,   166,   166,   166,   166,   166,   166,
     167,   168,   169,   169,   170,   171,   172,   172,   173,   173,
     174,   174,   176,   175,   177,   177,   178,   178,   179,   179,
     180,   180,   181,   181,   181,   182,   183,   183,   183,   183,
     183,   183,   184,   184,   184,   185,   186,   186,   187,   188,
     188,   189,   190,   191,   191,   191,   191,   191,   192,   192,
     192,   192,   192,   192,   193,   193,   193,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   195,   195,   196,   196,   197,   197,   197,   198,
     198,   198,   199,   199,   199,   199,   199,   200,   200,   200,
     201,   201,   202,   202,   203,   204,   205,   205
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     0,
       1,     0,     3,     3,     0,     2,     0,     6,     3,     0,
       2,     3,     0,     5,     3,     3,     1,     3,     0,     0,
       3,     2,     0,     2,     2,     2,     1,     3,     3,     0,
       2,     0,     4,     0,     2,     0,     2,     3,     0,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     6,     3,     4,     3,     1,     3,
       4,     4,     3,     3,     4,     1,     1,     3,     5,     1,
       5,     5,     6,     6,     2,     4,     2,     1,     4,     2,
       3,     1,     3,     2,     3,     0,     4,     4,     2,     3,
       2,     2,     3,     0,     1,     1,     1,     1,     1,     1,
       7,     2,     3,     0,     3,     6,     3,     0,     1,     4,
       5,     4,     0,     9,     2,     0,     3,     0,     2,     0,
       3,     0,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     5,     1,     0,     2,     2,
       0,     4,     2,     1,     1,     1,     3,     1,     1,     4,
       4,     3,     4,     3,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     2,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     0,     0,     0,     0,     0,     2,    11,    10,
      14,    11,    11,    11,    11,    11,     0,     0,     0,     0,
       0,    22,     0,   122,     1,     3,     0,     0,     4,     6,
       5,     7,     8,     0,     0,     0,    32,    32,     0,    20,
       0,     0,    19,    16,     0,    12,     0,    11,     0,    96,
      97,     0,    32,   113,     0,   117,    41,    22,   121,   125,
       0,     0,    13,    16,   142,   147,   167,   168,   170,   172,
     173,   174,   175,   176,   177,   179,   181,   182,   183,   184,
     186,   187,   189,   190,   169,   171,   178,   180,   185,   188,
     191,   137,   136,    75,    76,   138,   140,   155,   139,   144,
       0,     0,    28,   141,   153,   154,   157,   158,   192,     0,
     194,   196,   199,   202,   207,   210,   212,   214,    26,    29,
      32,    98,     0,     0,   103,     0,    41,     0,   111,     0,
       0,    31,    39,     0,    11,     0,   120,    21,   127,     0,
       0,     0,    15,     0,   146,     0,     0,   193,     0,     0,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,   104,
     105,   106,   107,   108,   109,   101,    99,     0,   100,   114,
      43,   113,    36,    34,    35,     0,    33,     0,     0,   118,
     115,     0,     0,    40,    48,    49,    51,    53,    56,    58,
      59,    61,    60,    62,    57,     0,    55,     0,   124,     0,
      18,     0,     0,     0,   150,   163,   217,     0,   143,   156,
      28,   164,   165,     0,     0,   161,     0,   195,   197,   198,
     200,   201,   205,   206,   203,   204,   208,   209,   211,   213,
      25,     0,    91,     0,    95,    79,    87,    30,    43,   103,
       0,   110,   112,     0,    39,   116,     0,    52,     0,    55,
       0,     0,    46,     0,     0,     0,     0,     0,     0,   127,
      11,     0,     0,     0,     0,   148,   150,     0,   215,   162,
      27,   166,   159,   160,     0,     0,    89,     0,     0,    93,
       0,     0,    23,   102,     0,    37,    38,     0,    54,     0,
      48,    50,     0,    77,     0,    72,    73,     0,     0,     0,
       0,     0,    65,    68,    69,   126,   155,   134,     0,   131,
     133,   132,    17,     0,   152,   145,   149,   217,     0,    90,
      92,    95,     0,     0,    45,   119,     0,    47,     0,    71,
      74,     0,    66,    70,     0,     0,     0,     0,   123,    11,
     128,   151,   216,    88,    94,     0,     0,     0,    42,    78,
       0,    63,    67,   135,   131,     0,     0,    80,    81,     0,
      44,    64,   130,    84,    86,     0,    82,    83,     0,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    27,    62,    63,    61,
      22,    39,    45,    46,   102,   150,   120,   167,    55,   131,
     132,   183,   186,   136,   251,   358,   193,   262,   194,   195,
     196,   197,   198,   199,   200,   312,   201,   202,   203,   103,
     204,   205,   244,   367,   368,   245,   246,   247,   289,    11,
      49,   123,   124,   178,   175,    12,    52,   128,    53,    13,
     134,   190,    14,    15,    41,   139,   208,   318,   350,   319,
     320,   104,   105,   106,   143,   213,   275,   276,   274,   107,
     108,   224,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   206,   217,   278
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -324
static const yytype_int16 yypact[] =
{
       7,    59,   -57,     3,     0,   -12,    64,  -324,     7,  -324,
      86,     7,     7,     7,     7,     7,    18,    27,    83,    49,
      50,    34,   124,  -324,  -324,  -324,    52,   136,  -324,  -324,
    -324,  -324,  -324,     1,     1,    54,   137,   137,    55,  -324,
      58,    44,    48,    52,   488,  -324,   143,  -324,    65,  -324,
    -324,    53,   137,    51,    94,    56,   144,    34,  -324,    67,
      69,   154,  -324,    52,  -324,   488,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,  -324,  -324,   -74,  -324,  -324,
     788,   488,    93,  -324,  -324,  -324,  -324,    89,  -324,    57,
      71,  -324,    28,    29,   -24,    25,    95,    99,   188,  -324,
     137,  -324,    46,   100,    98,   488,   144,    54,  -324,   117,
     117,  -324,   101,    69,   174,   413,  -324,  -324,   103,   109,
     111,   108,  -324,   164,  -324,   263,   128,  -324,   113,   488,
    -324,    42,   338,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   488,   130,   -11,   144,  -324,
    -324,  -324,  -324,  -324,  -324,  -324,  -324,    65,  -324,  -324,
     208,    51,   114,  -324,  -324,    94,  -324,   121,   118,  -324,
    -324,   563,   413,  -324,    91,  -324,  -324,  -324,  -324,  -324,
    -324,  -324,  -324,  -324,  -324,   185,    15,   142,  -324,   125,
    -324,   136,   413,   183,   164,  -324,   129,   131,  -324,  -324,
      93,  -324,  -324,   153,   126,  -324,   134,  -324,  -324,  -324,
      28,    28,    29,    29,    29,    29,   -24,   -24,    25,    95,
    -324,   138,     5,   -11,   135,    22,  -324,  -324,   208,    98,
     227,  -324,  -324,   155,   101,  -324,   488,  -324,   -19,   -25,
     413,   413,  -324,   139,   -18,    43,   488,   638,   488,   103,
     106,   140,    -8,   488,   200,  -324,   164,   488,  -324,  -324,
    -324,  -324,  -324,  -324,   -66,   158,  -324,   145,   -11,  -324,
     228,   225,  -324,  -324,   488,  -324,  -324,   147,  -324,   488,
      91,  -324,   488,  -324,   -15,  -324,  -324,   488,   638,   488,
     217,   488,  -324,  -324,  -324,  -324,   -38,  -324,   146,   148,
    -324,  -324,  -324,   488,  -324,  -324,  -324,   129,   149,  -324,
    -324,   135,   -11,   236,   246,  -324,   156,  -324,   157,  -324,
    -324,   226,  -324,  -324,   488,    24,   162,   488,  -324,   713,
    -324,  -324,  -324,  -324,  -324,   107,   -11,   413,  -324,  -324,
     488,  -324,  -324,  -324,   148,   413,   -63,  -324,  -324,   107,
    -324,  -324,  -324,  -324,  -324,    69,  -324,  -324,   165,  -324
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -324,  -324,    36,  -324,   -43,  -324,  -324,   205,   244,  -324,
     -58,   214,    61,  -324,   127,    60,  -324,  -324,   -26,  -324,
      88,   151,    20,  -107,    35,  -324,  -323,   -16,  -182,    14,
      96,  -324,  -324,  -324,  -324,   -31,  -324,  -324,  -324,  -241,
    -324,    19,  -242,   -84,   -83,  -324,     4,  -324,   -42,  -324,
     256,  -324,   115,    45,  -324,  -324,  -324,   110,   166,  -324,
    -324,  -324,  -324,  -324,  -324,  -324,    26,  -324,   -68,   -52,
    -324,  -324,  -324,  -324,  -324,  -324,    23,   159,  -324,  -324,
     198,  -324,  -324,  -324,   -37,   -23,   -49,   -27,   150,   190,
    -324,   -44,  -149,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -130
static const yytype_int16 yytable[] =
{
     118,   287,   140,   226,   121,    47,    20,    -9,   241,   285,
     258,    56,   264,   265,   266,   267,   268,   261,   347,   180,
     304,   144,   242,   306,   305,   374,   126,   339,   261,   145,
     272,    18,   146,     1,   370,    19,     2,   243,     3,   323,
     375,     4,   373,   290,    25,   291,   331,    28,    29,    30,
      31,    32,   264,   265,   266,   267,   268,   148,   221,   222,
     223,   248,     5,   340,    24,   145,    93,    94,   146,    93,
      94,   158,   159,   160,   161,   187,    23,   242,   300,   219,
     299,   179,   307,   308,   309,   298,    16,    17,    21,    26,
     355,   189,   243,   286,   168,   169,   170,   171,   172,   173,
     174,   216,   129,   130,    48,   118,    33,   297,   216,   232,
     233,   234,   235,    35,   369,    34,   227,   228,   229,   154,
     155,    64,   156,   157,   162,   163,   260,   261,   219,   277,
      40,   365,   366,   230,   231,   236,   237,    36,    37,    38,
      42,    44,    51,    57,    54,   334,    58,    59,   259,   119,
      65,    60,   125,   122,   135,   138,   127,    21,   141,   133,
     152,   153,   346,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,   316,    98,   164,    99,   149,   151,
     100,   165,   166,   177,   176,   182,   185,   188,   207,   101,
     212,   211,   216,   209,  -129,   210,   218,   219,   240,   250,
     253,   256,   310,   313,   314,   255,   321,   317,   263,   324,
     269,   273,   270,   327,   277,   279,   281,   282,   283,   294,
     288,   284,   302,   295,   322,   325,   329,   333,   332,   330,
     216,   335,   344,   353,   348,   336,   356,   349,   338,   357,
     359,   360,   299,   341,   313,   343,   362,   345,   142,   379,
      43,   137,   271,   254,   296,   301,   220,   342,    64,   351,
     280,   184,   303,   292,   337,   376,   377,   257,   328,   354,
      50,   252,   249,   181,   293,   315,   372,   364,   147,   326,
     361,     0,   214,   363,     0,   321,   317,    65,     0,     0,
     352,     0,     0,     0,   238,     0,   371,   378,     0,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    64,    99,   239,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   101,   215,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    64,    99,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,   101,   225,     0,     0,     0,     0,     0,     0,     0,
       0,   191,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    64,    99,     0,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    64,    99,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    64,    99,     0,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    64,    99,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,   311,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,   316,    98,    64,    99,     0,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101
};

static const yytype_int16 yycheck[] =
{
      44,   243,    60,   152,    47,     4,     6,     0,    19,     4,
     192,    37,    37,    38,    39,    40,    41,    36,    56,   126,
      38,    65,    88,   264,    42,    88,    52,    42,    36,   103,
     212,    88,   106,    26,   357,    32,    29,   103,    31,    47,
     103,    34,   365,    21,     8,    23,   288,    11,    12,    13,
      14,    15,    37,    38,    39,    40,    41,   101,    16,    17,
      18,   168,    55,   304,     0,   103,    84,    85,   106,    84,
      85,    95,    96,    97,    98,   133,    88,    88,   260,   104,
     105,   125,    39,    40,    41,   104,    27,    28,    88,     3,
     332,   134,   103,    88,   120,    49,    50,    51,    52,    53,
      54,   145,     8,     9,   103,   149,    88,   256,   152,   158,
     159,   160,   161,    30,   356,    88,   153,   154,   155,    91,
      92,    15,    93,    94,    99,   100,    35,    36,   104,   105,
       6,    24,    25,   156,   157,   162,   163,    88,    88,   105,
      88,     5,    88,    88,     7,   294,    88,   103,   192,     6,
      44,   103,    99,    88,    10,    88,   105,    88,     4,   103,
     103,    90,   311,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   101,    91,   105,   110,
      94,   102,    14,   105,   104,    88,   105,    33,   105,   103,
      46,   103,   256,   104,   108,   104,    88,   104,    88,    11,
     106,   103,   266,   267,   268,   104,   270,   270,    43,   273,
      88,    48,   107,   277,   105,   104,    83,   111,   104,    12,
     105,   103,   103,    88,   104,    45,    88,    22,    20,   104,
     294,   104,    35,   104,   108,   299,    20,   109,   302,    13,
     104,    35,   105,   307,   308,   309,   104,   311,    63,   104,
      26,    57,   211,   185,   254,   261,   149,   308,    15,   323,
     220,   130,   263,   248,   300,   369,   369,   191,   284,   331,
      34,   181,   177,   127,   249,   269,   364,   349,   100,   276,
     344,    -1,   143,   347,    -1,   349,   349,    44,    -1,    -1,
     327,    -1,    -1,    -1,   164,    -1,   360,   375,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    15,    91,   165,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    15,    91,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    15,    91,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    15,    91,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    15,    91,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    15,    91,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    15,    91,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    29,    31,    34,    55,   113,   114,   115,   116,
     117,   161,   167,   171,   174,   175,    27,    28,    88,    32,
       6,    88,   122,    88,     0,   114,     3,   118,   114,   114,
     114,   114,   114,    88,    88,    30,    88,    88,   105,   123,
       6,   176,    88,   120,     5,   124,   125,     4,   103,   162,
     162,    88,   168,   170,     7,   130,   130,    88,    88,   103,
     103,   121,   119,   120,    15,    44,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    91,
      94,   103,   126,   151,   183,   184,   185,   191,   192,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,     6,
     128,   116,    88,   163,   164,    99,   130,   105,   169,     8,
       9,   131,   132,   103,   172,    10,   135,   123,    88,   177,
     122,     4,   119,   186,   203,   103,   106,   192,   203,   105,
     127,   110,   103,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    14,   129,   130,    49,
      50,    51,    52,    53,    54,   166,   104,   105,   165,   203,
     135,   170,    88,   133,   133,   105,   134,   122,    33,   116,
     173,    38,   103,   138,   140,   141,   142,   143,   144,   145,
     146,   148,   149,   150,   152,   153,   203,   105,   178,   104,
     104,   103,    46,   187,   189,   104,   203,   204,    88,   104,
     126,    16,    17,    18,   193,   104,   204,   196,   196,   196,
     197,   197,   198,   198,   198,   198,   199,   199,   200,   201,
      88,    19,    88,   103,   154,   157,   158,   159,   135,   164,
      11,   136,   169,   106,   132,   104,   103,   142,   140,   203,
      35,    36,   139,    43,    37,    38,    39,    40,    41,    88,
     107,   124,   140,    48,   190,   188,   189,   105,   205,   104,
     127,    83,   111,   104,   103,     4,    88,   154,   105,   160,
      21,    23,   136,   165,    12,    88,   134,   204,   104,   105,
     140,   141,   103,   153,    38,    42,   151,    39,    40,    41,
     203,   103,   147,   203,   203,   178,    88,   116,   179,   181,
     182,   203,   104,    47,   203,    45,   188,   203,   158,    88,
     104,   154,    20,    22,   204,   104,   203,   139,   203,    42,
     151,   203,   147,   203,    35,   203,   204,    56,   108,   109,
     180,   203,   205,   104,   160,   154,    20,    13,   137,   104,
      35,   203,   104,   203,   181,    24,    25,   155,   156,   154,
     138,   203,   180,   138,    88,   103,   155,   156,   122,   104
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
#line 210 "parser/aquery.y"
    { (yyval.top) = (yyvsp[(1) - (1)].top); ast = (yyval.top); cg_AQUERY2Q(ast); ;}
    break;

  case 3:
#line 213 "parser/aquery.y"
    { (yyval.top) = make_Top_GlobalQuery((yyvsp[(1) - (2)].fullquery), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 4:
#line 214 "parser/aquery.y"
    { (yyval.top) = make_Top_Create((yyvsp[(1) - (2)].create), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 5:
#line 215 "parser/aquery.y"
    { (yyval.top) = make_Top_Insert((yyvsp[(1) - (2)].insert), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 6:
#line 216 "parser/aquery.y"
    { (yyval.top) = make_Top_UpdateDelete((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 7:
#line 217 "parser/aquery.y"
    { (yyval.top) = make_Top_UpdateDelete((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 8:
#line 218 "parser/aquery.y"
    { (yyval.top) = make_Top_UDF((yyvsp[(1) - (2)].udfdef), (yyvsp[(2) - (2)].top)); ;}
    break;

  case 9:
#line 219 "parser/aquery.y"
    { (yyval.top) = NULL; ;}
    break;

  case 10:
#line 225 "parser/aquery.y"
    { (yyval.fullquery) = (yyvsp[(1) - (1)].fullquery); ;}
    break;

  case 11:
#line 228 "parser/aquery.y"
    { env = push_env(env); ;}
    break;

  case 12:
#line 230 "parser/aquery.y"
    { env = pop_env(env); (yyval.fullquery) = make_FullQueryNode((yyvsp[(2) - (3)].localquery), (yyvsp[(3) - (3)].plan)); ;}
    break;

  case 13:
#line 235 "parser/aquery.y"
    { (yyvsp[(2) - (3)].localquery)->next_sibling = (yyvsp[(3) - (3)].localquery); (yyval.localquery) = (yyvsp[(2) - (3)].localquery); ;}
    break;

  case 14:
#line 236 "parser/aquery.y"
    { (yyval.localquery) = NULL; ;}
    break;

  case 15:
#line 239 "parser/aquery.y"
    { (yyvsp[(1) - (2)].localquery)->next_sibling = (yyvsp[(2) - (2)].localquery); (yyval.localquery) = (yyvsp[(1) - (2)].localquery); ;}
    break;

  case 16:
#line 240 "parser/aquery.y"
    { (yyval.localquery) = NULL; ;}
    break;

  case 17:
#line 245 "parser/aquery.y"
    { put_sym(env, (yyvsp[(1) - (6)].str), TABLE_TYPE, 0, 0); (yyval.localquery) = make_LocalQueryNode((yyvsp[(1) - (6)].str), (yyvsp[(2) - (6)].idlist), (yyvsp[(5) - (6)].plan)); add_order(env, (yyvsp[(1) - (6)].str), curr_order); ;}
    break;

  case 18:
#line 248 "parser/aquery.y"
    { (yyval.idlist) = (yyvsp[(2) - (3)].idlist); ;}
    break;

  case 19:
#line 249 "parser/aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 20:
#line 252 "parser/aquery.y"
    { (yyval.idlist) = make_IDListNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].idlist)); ;}
    break;

  case 21:
#line 255 "parser/aquery.y"
    { (yyval.idlist) = make_IDListNode((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].idlist));;}
    break;

  case 22:
#line 256 "parser/aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 23:
#line 263 "parser/aquery.y"
    { (yyval.plan) = assemble_plan((yyvsp[(1) - (5)].plan), (yyvsp[(2) - (5)].plan), (yyvsp[(3) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].plan)); curr_order = (yyvsp[(3) - (5)].plan); if((yyvsp[(5) - (5)].plan) != NULL) { annotate_groupedNamedExpr((yyvsp[(1) - (5)].plan)->params.namedexprs); } ;}
    break;

  case 24:
#line 266 "parser/aquery.y"
    { (yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.plan) = make_project(PROJECT_SELECT, NULL, (yyvsp[(2) - (3)].namedexpr)); ;}
    break;

  case 25:
#line 269 "parser/aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode((yyvsp[(3) - (3)].str), (yyvsp[(1) - (3)].exprnode)); ;}
    break;

  case 26:
#line 270 "parser/aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode(NULL, (yyvsp[(1) - (1)].exprnode)); ;}
    break;

  case 27:
#line 273 "parser/aquery.y"
    { (yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.namedexpr) = (yyvsp[(2) - (3)].namedexpr); ;}
    break;

  case 28:
#line 274 "parser/aquery.y"
    { (yyval.namedexpr) = NULL; ;}
    break;

  case 29:
#line 277 "parser/aquery.y"
    {query_line_num = line_num; query_col_num = col_num; ;}
    break;

  case 30:
#line 277 "parser/aquery.y"
    { (yyval.plan) = (yyvsp[(3) - (3)].plan); ;}
    break;

  case 31:
#line 280 "parser/aquery.y"
    { (yyval.plan) = make_sort(NULL, (yyvsp[(2) - (2)].order));;}
    break;

  case 32:
#line 281 "parser/aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 33:
#line 284 "parser/aquery.y"
    { (yyvsp[(1) - (2)].order)->next = (yyvsp[(2) - (2)].order); (yyval.order) = (yyvsp[(1) - (2)].order); ;}
    break;

  case 34:
#line 287 "parser/aquery.y"
    { (yyval.order) = make_OrderNode(ASC_SORT, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 35:
#line 288 "parser/aquery.y"
    { (yyval.order) = make_OrderNode(DESC_SORT, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 36:
#line 291 "parser/aquery.y"
    { (yyval.exprnode) = make_id(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 37:
#line 292 "parser/aquery.y"
    { (yyval.exprnode) = make_colDotAccessNode(make_id(env, (yyvsp[(1) - (3)].str)), make_id(env, (yyvsp[(3) - (3)].str))); ;}
    break;

  case 38:
#line 295 "parser/aquery.y"
    { (yyvsp[(2) - (3)].order)->next = (yyvsp[(3) - (3)].order); (yyval.order) = (yyvsp[(2) - (3)].order); ;}
    break;

  case 39:
#line 296 "parser/aquery.y"
    { (yyval.order) = NULL; ;}
    break;

  case 40:
#line 299 "parser/aquery.y"
    { (yyval.plan) = make_filterWhere(NULL, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 41:
#line 300 "parser/aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 42:
#line 303 "parser/aquery.y"
    { (yyval.plan) = pushdown_logical((yyvsp[(4) - (4)].plan), make_groupby(NULL, (yyvsp[(3) - (4)].exprnode)));   ;}
    break;

  case 43:
#line 304 "parser/aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 44:
#line 307 "parser/aquery.y"
    { annotate_groupedExpr((yyvsp[(2) - (2)].exprnode)); (yyval.plan) = make_filterHaving(NULL, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 45:
#line 308 "parser/aquery.y"
    { (yyval.plan) =  NULL; ;}
    break;

  case 46:
#line 323 "parser/aquery.y"
    { (yyvsp[(1) - (2)].exprnode)->next_sibling = (yyvsp[(2) - (2)].exprnode); (yyval.exprnode) = (yyvsp[(1) - (2)].exprnode); ;}
    break;

  case 47:
#line 326 "parser/aquery.y"
    { (yyvsp[(2) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 48:
#line 327 "parser/aquery.y"
    { (yyval.exprnode) = NULL;                      ;}
    break;

  case 49:
#line 330 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 50:
#line 331 "parser/aquery.y"
    { (yyval.exprnode) = make_logicOpNode(WHERE_OR_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 51:
#line 334 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 52:
#line 335 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 53:
#line 338 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 54:
#line 339 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 55:
#line 343 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 56:
#line 344 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 57:
#line 345 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 58:
#line 349 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 59:
#line 350 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 60:
#line 351 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 61:
#line 352 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 62:
#line 353 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 63:
#line 359 "parser/aquery.y"
    { (yyvsp[(3) - (5)].exprnode)->next_sibling = (yyvsp[(5) - (5)].exprnode); (yyvsp[(1) - (5)].exprnode)->next_sibling = make_exprListNode((yyvsp[(3) - (5)].exprnode)); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (5)].str)), make_exprListNode((yyvsp[(1) - (5)].exprnode))); ;}
    break;

  case 64:
#line 360 "parser/aquery.y"
    { (yyvsp[(4) - (6)].exprnode)->next_sibling = (yyvsp[(6) - (6)].exprnode); (yyvsp[(1) - (6)].exprnode)->next_sibling = make_exprListNode((yyvsp[(4) - (6)].exprnode)); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (6)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (6)].str)), make_exprListNode((yyvsp[(1) - (6)].exprnode))))); ;}
    break;

  case 65:
#line 363 "parser/aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 66:
#line 364 "parser/aquery.y"
    { (yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 67:
#line 367 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 68:
#line 368 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 69:
#line 371 "parser/aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 70:
#line 372 "parser/aquery.y"
    { (yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 71:
#line 375 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(4) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 72:
#line 376 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 73:
#line 379 "parser/aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 74:
#line 380 "parser/aquery.y"
    { (yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode);  (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (4)].str)),  make_exprListNode(make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 75:
#line 383 "parser/aquery.y"
    { (yyval.exprnode) = make_bool(1); ;}
    break;

  case 76:
#line 384 "parser/aquery.y"
    { (yyval.exprnode) = make_bool(0); ;}
    break;

  case 77:
#line 387 "parser/aquery.y"
    { (yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 78:
#line 390 "parser/aquery.y"
    { (yyvsp[(2) - (5)].exprnode)->next_sibling = (yyvsp[(4) - (5)].exprnode); (yyval.exprnode) = make_exprListNode((yyvsp[(2) - (5)].exprnode)); ;}
    break;

  case 79:
#line 397 "parser/aquery.y"
    { (yyval.plan) = (yyvsp[(1) - (1)].plan);                                                ;}
    break;

  case 80:
#line 398 "parser/aquery.y"
    { (yyval.plan) = make_joinOn(INNER_JOIN_ON, (yyvsp[(1) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].exprnode));            ;}
    break;

  case 81:
#line 399 "parser/aquery.y"
    { (yyval.plan) = make_joinUsing(INNER_JOIN_USING, (yyvsp[(1) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].idlist));      ;}
    break;

  case 82:
#line 400 "parser/aquery.y"
    { (yyval.plan) = make_joinOn(FULL_OUTER_JOIN_ON, (yyvsp[(1) - (6)].plan), (yyvsp[(5) - (6)].plan), (yyvsp[(6) - (6)].exprnode));       ;}
    break;

  case 83:
#line 401 "parser/aquery.y"
    { (yyval.plan) = make_joinUsing(FULL_OUTER_JOIN_USING, (yyvsp[(1) - (6)].plan), (yyvsp[(5) - (6)].plan), (yyvsp[(6) - (6)].idlist)); ;}
    break;

  case 84:
#line 405 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (2)].exprnode); ;}
    break;

  case 85:
#line 408 "parser/aquery.y"
    { (yyval.idlist) = (yyvsp[(3) - (4)].idlist); ;}
    break;

  case 86:
#line 409 "parser/aquery.y"
    { (yyval.idlist) = make_IDListNode((yyvsp[(2) - (2)].str), NULL); ;}
    break;

  case 87:
#line 412 "parser/aquery.y"
    { (yyval.plan) = (yyvsp[(1) - (1)].plan);               ;}
    break;

  case 88:
#line 413 "parser/aquery.y"
    { (yyval.plan) = make_flatten((yyvsp[(3) - (4)].plan)); ;}
    break;

  case 89:
#line 416 "parser/aquery.y"
    { (yyval.plan) = make_alias(make_table((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 90:
#line 417 "parser/aquery.y"
    { (yyval.plan) = make_alias(make_table((yyvsp[(1) - (3)].str)), (yyvsp[(3) - (3)].str)); ;}
    break;

  case 91:
#line 418 "parser/aquery.y"
    { (yyval.plan) = make_table((yyvsp[(1) - (1)].str));                 ;}
    break;

  case 92:
#line 419 "parser/aquery.y"
    { (yyval.plan) = (yyvsp[(2) - (3)].plan);                             ;}
    break;

  case 93:
#line 424 "parser/aquery.y"
    { if((yyvsp[(2) - (2)].plan) == NULL){ (yyval.plan) = (yyvsp[(1) - (2)].plan); } else { (yyval.plan) = make_cross((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].plan)); } ;}
    break;

  case 94:
#line 427 "parser/aquery.y"
    { if((yyvsp[(3) - (3)].plan) == NULL){ (yyval.plan) = (yyvsp[(2) - (3)].plan); } else { (yyval.plan) = make_cross((yyvsp[(2) - (3)].plan), (yyvsp[(3) - (3)].plan)); } ;}
    break;

  case 95:
#line 428 "parser/aquery.y"
    { (yyval.plan) = NULL;                                                   ;}
    break;

  case 96:
#line 432 "parser/aquery.y"
    { put_sym(env, (yyvsp[(3) - (4)].str), TABLE_TYPE, 0, 0); (yyval.create) = make_createNode(CREATE_TABLE, (yyvsp[(3) - (4)].str), (yyvsp[(4) - (4)].createsrc)); ;}
    break;

  case 97:
#line 433 "parser/aquery.y"
    { put_sym(env, (yyvsp[(3) - (4)].str), VIEW_TYPE, 0, 0);  (yyval.create) = make_createNode(CREATE_VIEW, (yyvsp[(3) - (4)].str), (yyvsp[(4) - (4)].createsrc));  ;}
    break;

  case 98:
#line 436 "parser/aquery.y"
    { (yyval.createsrc) = make_querySource((yyvsp[(2) - (2)].fullquery));  ;}
    break;

  case 99:
#line 437 "parser/aquery.y"
    { (yyval.createsrc) = make_schemaSource((yyvsp[(2) - (3)].schema)); ;}
    break;

  case 100:
#line 440 "parser/aquery.y"
    { (yyvsp[(1) - (2)].schema)->next_sibling = (yyvsp[(2) - (2)].schema); (yyval.schema) = (yyvsp[(1) - (2)].schema); ;}
    break;

  case 101:
#line 443 "parser/aquery.y"
    { (yyval.schema) = make_schemaNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 102:
#line 446 "parser/aquery.y"
    { (yyvsp[(2) - (3)].schema)->next_sibling = (yyvsp[(3) - (3)].schema); (yyval.schema) = (yyvsp[(2) - (3)].schema); ;}
    break;

  case 103:
#line 447 "parser/aquery.y"
    { (yyval.schema) = NULL;                      ;}
    break;

  case 104:
#line 450 "parser/aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 105:
#line 451 "parser/aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 106:
#line 452 "parser/aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 107:
#line 453 "parser/aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 108:
#line 454 "parser/aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 109:
#line 455 "parser/aquery.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 110:
#line 460 "parser/aquery.y"
    { if((yyvsp[(7) - (7)].plan) != NULL){ annotate_groupedNamedExpr((yyvsp[(4) - (7)].namedexpr)); } (yyval.plan)  = assemble_base(make_project(PROJECT_UPDATE, NULL, (yyvsp[(4) - (7)].namedexpr)), make_table((yyvsp[(2) - (7)].str)), (yyvsp[(5) - (7)].plan), (yyvsp[(6) - (7)].plan), (yyvsp[(7) - (7)].plan)); ;}
    break;

  case 111:
#line 463 "parser/aquery.y"
    { (yyvsp[(1) - (2)].namedexpr)->next_sibling = (yyvsp[(2) - (2)].namedexpr); (yyval.namedexpr) = (yyvsp[(1) - (2)].namedexpr); ;}
    break;

  case 112:
#line 466 "parser/aquery.y"
    { (yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.namedexpr) = (yyvsp[(2) - (3)].namedexpr); ;}
    break;

  case 113:
#line 467 "parser/aquery.y"
    { (yyval.namedexpr) = NULL; ;}
    break;

  case 114:
#line 470 "parser/aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 115:
#line 473 "parser/aquery.y"
    { (yyval.insert) = make_insert(assemble_base(NULL, make_table((yyvsp[(3) - (6)].str)), (yyvsp[(4) - (6)].plan), NULL, NULL), (yyvsp[(5) - (6)].idlist), (yyvsp[(6) - (6)].fullquery)); ;}
    break;

  case 116:
#line 476 "parser/aquery.y"
    {  (yyval.idlist) = (yyvsp[(2) - (3)].idlist); ;}
    break;

  case 117:
#line 477 "parser/aquery.y"
    {  (yyval.idlist) = NULL; ;}
    break;

  case 118:
#line 480 "parser/aquery.y"
    { (yyval.fullquery) = (yyvsp[(1) - (1)].fullquery); ;}
    break;

  case 119:
#line 481 "parser/aquery.y"
    { (yyval.fullquery) = make_FullQueryNode(NULL, make_values((yyvsp[(3) - (4)].exprnode))); ;}
    break;

  case 120:
#line 484 "parser/aquery.y"
    { (yyval.plan) = assemble_base(make_delete(NULL, NULL), make_table((yyvsp[(3) - (5)].str)), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].plan), NULL);   ;}
    break;

  case 121:
#line 485 "parser/aquery.y"
    { (yyval.plan) = assemble_base(make_delete(NULL, (yyvsp[(2) - (4)].idlist)), make_table((yyvsp[(4) - (4)].str)), NULL, NULL, NULL); ;}
    break;

  case 122:
#line 490 "parser/aquery.y"
    { put_sym(env, (yyvsp[(2) - (2)].str), FUNCTION_TYPE, 0, 0); env = push_env(env);  ;}
    break;

  case 123:
#line 496 "parser/aquery.y"
    { env = pop_env(env); (yyval.udfdef) =  make_UDFDefNode((yyvsp[(2) - (9)].str), (yyvsp[(5) - (9)].idlist), (yyvsp[(8) - (9)].udfbody)); entry = lookup_sym(env, (yyvsp[(2) - (9)].str)); entry->order_dep = (yyval.udfdef)->order_dep; entry->uses_agg = (yyval.udfdef)->uses_agg; ;}
    break;

  case 124:
#line 499 "parser/aquery.y"
    { put_sym(env, (yyvsp[(1) - (2)].str), UNKNOWN_TYPE, 0, 0); (yyval.idlist) = make_IDListNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].idlist)); ;}
    break;

  case 125:
#line 500 "parser/aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 126:
#line 503 "parser/aquery.y"
    { put_sym(env, (yyvsp[(2) - (3)].str), UNKNOWN_TYPE, 0, 0); (yyval.idlist) = make_IDListNode((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].idlist)); ;}
    break;

  case 127:
#line 504 "parser/aquery.y"
    {(yyval.idlist) = NULL; ;}
    break;

  case 128:
#line 508 "parser/aquery.y"
    { (yyvsp[(1) - (2)].udfbody)->next_sibling = (yyvsp[(2) - (2)].udfbody); (yyval.udfbody) = (yyvsp[(1) - (2)].udfbody);;}
    break;

  case 129:
#line 509 "parser/aquery.y"
    { (yyval.udfbody) = NULL; ;}
    break;

  case 130:
#line 512 "parser/aquery.y"
    { (yyvsp[(2) - (3)].udfbody)->next_sibling = (yyvsp[(3) - (3)].udfbody); (yyval.udfbody) = (yyvsp[(2) - (3)].udfbody); ;}
    break;

  case 131:
#line 513 "parser/aquery.y"
    { (yyval.udfbody)= NULL; ;}
    break;

  case 132:
#line 516 "parser/aquery.y"
    {(yyval.udfbody) = make_UDFExpr((yyvsp[(1) - (1)].exprnode));   ;}
    break;

  case 133:
#line 517 "parser/aquery.y"
    {(yyval.udfbody) = make_UDFVardef((yyvsp[(1) - (1)].namedexpr)); ;}
    break;

  case 134:
#line 518 "parser/aquery.y"
    {(yyval.udfbody) = make_UDFQuery((yyvsp[(1) - (1)].fullquery));  ;}
    break;

  case 135:
#line 521 "parser/aquery.y"
    { put_sym(env, (yyvsp[(1) - (3)].str), UNKNOWN_TYPE, 0, 0);    (yyval.namedexpr) = make_NamedExprNode((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 136:
#line 525 "parser/aquery.y"
    { (yyval.exprnode) = make_int((yyvsp[(1) - (1)].intval));    ;}
    break;

  case 137:
#line 526 "parser/aquery.y"
    { (yyval.exprnode) = make_float((yyvsp[(1) - (1)].floatval));  ;}
    break;

  case 138:
#line 527 "parser/aquery.y"
    { (yyval.exprnode) = make_date((yyvsp[(1) - (1)].str));   ;}
    break;

  case 139:
#line 528 "parser/aquery.y"
    { (yyval.exprnode) = make_string((yyvsp[(1) - (1)].str)); ;}
    break;

  case 140:
#line 529 "parser/aquery.y"
    { (yyval.exprnode) = make_hex((yyvsp[(1) - (1)].str));    ;}
    break;

  case 141:
#line 530 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);              ;}
    break;

  case 142:
#line 533 "parser/aquery.y"
    { (yyval.exprnode) = make_rowId();                                              ;}
    break;

  case 143:
#line 534 "parser/aquery.y"
    { (yyval.exprnode) = make_colDotAccessNode(make_id(env, (yyvsp[(1) - (3)].str)), make_id(env, (yyvsp[(3) - (3)].str))); ;}
    break;

  case 144:
#line 535 "parser/aquery.y"
    { (yyval.exprnode) = make_allColsNode();                                        ;}
    break;

  case 145:
#line 539 "parser/aquery.y"
    { (yyval.exprnode) = make_caseNode((yyvsp[(2) - (5)].exprnode), (yyvsp[(3) - (5)].exprnode), (yyvsp[(4) - (5)].exprnode)); ;}
    break;

  case 146:
#line 542 "parser/aquery.y"
    { (yyval.exprnode) = make_caseClauseNode((yyvsp[(1) - (1)].exprnode));   ;}
    break;

  case 147:
#line 543 "parser/aquery.y"
    { (yyval.exprnode) = make_caseClauseNode(NULL); ;}
    break;

  case 148:
#line 546 "parser/aquery.y"
    { (yyval.exprnode) = make_whenClausesNode((yyvsp[(1) - (2)].exprnode), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 149:
#line 549 "parser/aquery.y"
    { (yyvsp[(1) - (2)].exprnode)->next_sibling = (yyvsp[(2) - (2)].exprnode); (yyval.exprnode) = (yyvsp[(1) - (2)].exprnode); ;}
    break;

  case 150:
#line 550 "parser/aquery.y"
    { (yyval.exprnode) = NULL; ;}
    break;

  case 151:
#line 553 "parser/aquery.y"
    { (yyval.exprnode) = make_caseWhenNode((yyvsp[(2) - (4)].exprnode), (yyvsp[(4) - (4)].exprnode)); ;}
    break;

  case 152:
#line 556 "parser/aquery.y"
    { (yyval.exprnode) = make_elseClauseNode((yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 153:
#line 559 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 154:
#line 560 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 155:
#line 561 "parser/aquery.y"
    { (yyval.exprnode) = make_id(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 156:
#line 562 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 157:
#line 563 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 158:
#line 566 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                         ;}
    break;

  case 159:
#line 567 "parser/aquery.y"
    { (yyval.exprnode) = make_indexNode((yyvsp[(1) - (4)].exprnode), (yyvsp[(3) - (4)].exprnode));                     ;}
    break;

  case 160:
#line 568 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode((yyvsp[(1) - (4)].exprnode), (yyvsp[(3) - (4)].exprnode));                      ;}
    break;

  case 161:
#line 569 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode((yyvsp[(1) - (3)].exprnode), NULL);                    ;}
    break;

  case 162:
#line 570 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode(make_udfNode(env, (yyvsp[(1) - (4)].str)), (yyvsp[(3) - (4)].exprnode));   ;}
    break;

  case 163:
#line 571 "parser/aquery.y"
    { (yyval.exprnode) = make_callNode(make_udfNode(env, (yyvsp[(1) - (3)].str)), NULL); ;}
    break;

  case 164:
#line 575 "parser/aquery.y"
    { (yyval.exprnode) = make_oddix();      ;}
    break;

  case 165:
#line 576 "parser/aquery.y"
    { (yyval.exprnode) = make_evenix();     ;}
    break;

  case 166:
#line 577 "parser/aquery.y"
    { (yyval.exprnode) = make_everynix((yyvsp[(2) - (2)].intval)); ;}
    break;

  case 167:
#line 580 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 168:
#line 581 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 169:
#line 582 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 170:
#line 583 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 171:
#line 584 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 172:
#line 585 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 173:
#line 586 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 174:
#line 587 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 175:
#line 588 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 176:
#line 589 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 177:
#line 590 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 178:
#line 591 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 179:
#line 592 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 180:
#line 593 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 181:
#line 594 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 182:
#line 595 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 183:
#line 596 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 184:
#line 597 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 185:
#line 598 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 186:
#line 599 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 187:
#line 600 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 188:
#line 601 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 189:
#line 602 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 190:
#line 603 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 191:
#line 604 "parser/aquery.y"
    { (yyval.exprnode) = make_builtInFunNode(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 192:
#line 607 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 193:
#line 608 "parser/aquery.y"
    { (yyval.exprnode) = make_neg((yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 194:
#line 611 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                               ;}
    break;

  case 195:
#line 612 "parser/aquery.y"
    { (yyval.exprnode) = make_arithNode(POW_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 196:
#line 615 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                ;}
    break;

  case 197:
#line 616 "parser/aquery.y"
    { (yyval.exprnode) = make_arithNode(MULT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 198:
#line 617 "parser/aquery.y"
    { (yyval.exprnode) = make_arithNode(DIV_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode));  ;}
    break;

  case 199:
#line 621 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                 ;}
    break;

  case 200:
#line 622 "parser/aquery.y"
    { (yyval.exprnode) = make_arithNode(PLUS_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode));  ;}
    break;

  case 201:
#line 623 "parser/aquery.y"
    { (yyval.exprnode) = make_arithNode(MINUS_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 202:
#line 626 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                             ;}
    break;

  case 203:
#line 627 "parser/aquery.y"
    { (yyval.exprnode) = make_compNode(LT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 204:
#line 628 "parser/aquery.y"
    { (yyval.exprnode) = make_compNode(GT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 205:
#line 629 "parser/aquery.y"
    { (yyval.exprnode) = make_compNode(LE_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 206:
#line 630 "parser/aquery.y"
    { (yyval.exprnode) = make_compNode(GE_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 207:
#line 633 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                              ;}
    break;

  case 208:
#line 634 "parser/aquery.y"
    { (yyval.exprnode) = make_compNode(EQ_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode));  ;}
    break;

  case 209:
#line 635 "parser/aquery.y"
    { (yyval.exprnode) = make_compNode(NEQ_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 210:
#line 638 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                  ;}
    break;

  case 211:
#line 639 "parser/aquery.y"
    { (yyval.exprnode) = make_logicOpNode(LAND_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 212:
#line 642 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode);                                 ;}
    break;

  case 213:
#line 643 "parser/aquery.y"
    { (yyval.exprnode) = make_logicOpNode(LOR_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 214:
#line 646 "parser/aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 215:
#line 650 "parser/aquery.y"
    { (yyvsp[(1) - (2)].exprnode)->next_sibling = (yyvsp[(2) - (2)].exprnode); (yyval.exprnode) = make_exprListNode((yyvsp[(1) - (2)].exprnode)); ;}
    break;

  case 216:
#line 653 "parser/aquery.y"
    { (yyvsp[(2) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 217:
#line 654 "parser/aquery.y"
    { (yyval.exprnode) = NULL; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3158 "parser/aquery.tab.c"
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


#line 660 "parser/aquery.y"


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
    printf("-c  generate code\n");
}



int main(int argc, char *argv[]) {
	yydebug = 0;
	
	/* Aquery compiler flags */
	int print_ast_flag = 0;
	optim_level = 0;
	int max_optim_level = 1;
	
	/* getopt values */
	int op;
	
    /* where to save the code generated */
    DEST_FILE = stdout;
    
	
	while((op = getopt(argc, argv, "cspha:")) != -1)
	{
		switch(op)
		{
            case 's':
                silence_warnings = 1;
                break;
			case 'p':
				print_ast_flag = 1;
				break;
            case 'c':
                GEN_CODE = 1;
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
	
	
	FILE *to_parse;
    
	if(1 > argc - optind) 
	{ //Did we get a file to analyze?
		//help();
		//exit(1);
        to_parse = stdin;
	}
    else
    {
        to_parse = fopen(argv[optind], "r");
    }
	
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


