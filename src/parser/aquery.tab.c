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
#include "symtable.h"	
#include "ast.h"
#include "ast_print.h"

	
#define YYDEBUG 1
#define ERRORCOLOR  "\x1B[32m"

extern int yyleng;
extern FILE *yyin;
extern int yylex();
extern int yyparse();

//for debugging purposes, defined in flex
extern int line_num; 
extern int col_num;

//Symbol table
Symtable *env;	


void yyerror(const char *);





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
#line 136 "aquery.y"
{
  int   intval;
  float floatval;
  char* str;
  struct ExprNode *exprnode;
  //UDF related
  struct UDFDefNode *udfdef;
  struct IDListNode *idlist;
  struct LocalVarDefNode *localvardef;
  struct UDFBodyNode *udfbody;
  struct FullQueryNode *fullquery; 
  struct LogicalQueryNode *plan;
  struct OrderNode *order;
  struct NamedExprNode *namedexpr;
  struct InsertNode *insert;
}
/* Line 193 of yacc.c.  */
#line 346 "aquery.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 359 "aquery.tab.c"

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
#define YYLAST   806

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  111
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  94
/* YYNRULES -- Number of rules.  */
#define YYNRULES  214
/* YYNRULES -- Number of states.  */
#define YYNSTATES  375

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
      24,    26,    27,    28,    33,    37,    38,    41,    42,    43,
      51,    55,    56,    59,    63,    64,    70,    74,    78,    80,
      84,    85,    88,    91,    92,    95,    98,   101,   103,   107,
     111,   112,   115,   116,   121,   122,   125,   126,   128,   132,
     134,   138,   140,   143,   145,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   171,   178,   182,   187,   191,   193,
     197,   202,   207,   211,   215,   220,   222,   224,   228,   234,
     236,   242,   248,   255,   262,   265,   270,   272,   277,   280,
     284,   286,   290,   293,   297,   298,   303,   308,   311,   315,
     318,   321,   325,   326,   328,   330,   332,   334,   336,   338,
     346,   349,   353,   354,   358,   365,   369,   370,   372,   377,
     383,   388,   389,   390,   401,   404,   405,   409,   410,   413,
     414,   418,   419,   421,   423,   425,   429,   431,   433,   435,
     437,   439,   441,   443,   447,   449,   455,   457,   458,   461,
     464,   465,   470,   473,   475,   477,   479,   483,   485,   487,
     492,   497,   501,   506,   510,   512,   514,   517,   519,   521,
     523,   525,   527,   529,   531,   533,   535,   537,   539,   541,
     543,   545,   547,   549,   551,   553,   555,   557,   559,   561,
     563,   565,   567,   571,   573,   577,   581,   583,   587,   591,
     593,   597,   601,   605,   609,   611,   615,   619,   621,   625,
     627,   631,   633,   636,   640
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     112,     0,    -1,   113,    -1,   114,   113,    -1,   160,   113,
      -1,   170,   113,    -1,   166,   113,    -1,   173,   113,    -1,
     174,   113,    -1,    -1,   115,    -1,    -1,    -1,   116,   118,
     125,   117,    -1,     3,   120,   119,    -1,    -1,   120,   119,
      -1,    -1,    -1,    87,   121,   122,     4,   102,   125,   103,
      -1,   102,   123,   103,    -1,    -1,    87,   124,    -1,   104,
      87,   124,    -1,    -1,   126,   129,   130,   135,   136,    -1,
       5,   127,   128,    -1,   202,    14,    87,    -1,   202,    -1,
     104,   127,   128,    -1,    -1,     6,   158,    -1,     7,   131,
      -1,    -1,   132,   134,    -1,     8,   133,    -1,     9,   133,
      -1,    87,    -1,    87,   105,    87,    -1,   104,   132,   134,
      -1,    -1,    10,   138,    -1,    -1,    11,    12,   203,   137,
      -1,    -1,    13,   138,    -1,    -1,   139,    -1,   138,    36,
     139,    -1,   140,    -1,   139,    35,   140,    -1,   141,    -1,
      38,   141,    -1,   142,    -1,   102,   138,   103,    -1,   202,
      -1,   143,    -1,   151,    -1,   144,    -1,   145,    -1,   148,
      -1,   147,    -1,   149,    -1,   202,    39,   202,    35,   202,
      -1,   202,    38,    39,   202,    35,   202,    -1,   202,    40,
     146,    -1,   202,    38,    40,   146,    -1,   102,   203,   103,
      -1,   202,    -1,   202,    41,   202,    -1,   202,    38,    41,
     202,    -1,   202,    37,    38,    42,    -1,   202,    37,    42,
      -1,   202,    37,   150,    -1,   202,    37,    38,   150,    -1,
      83,    -1,    84,    -1,   152,    43,   152,    -1,   102,   202,
     104,   202,   103,    -1,   156,    -1,   156,    21,    20,   153,
     154,    -1,   156,    21,    20,   153,   155,    -1,   156,    23,
      22,    20,   153,   154,    -1,   156,    23,    22,    20,   153,
     155,    -1,    24,   138,    -1,    25,   102,   123,   103,    -1,
     157,    -1,    19,   102,   157,   103,    -1,    87,    87,    -1,
      87,     4,    87,    -1,    87,    -1,   102,   153,   103,    -1,
     153,   159,    -1,   104,   153,   159,    -1,    -1,    26,    27,
      87,   161,    -1,    26,    28,    87,   161,    -1,     4,   115,
      -1,   102,   162,   103,    -1,   163,   164,    -1,    87,   165,
      -1,   104,   163,   164,    -1,    -1,    49,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    29,    87,
      30,   167,   130,   135,   136,    -1,   169,   168,    -1,   104,
     169,   168,    -1,    -1,    87,    98,   202,    -1,    31,    32,
      87,   130,   171,   172,    -1,   102,   123,   103,    -1,    -1,
     115,    -1,    33,   102,   203,   103,    -1,    34,     6,    87,
     130,   135,    -1,    34,   123,     6,    87,    -1,    -1,    -1,
      55,    87,   175,   102,   177,   103,   106,   179,   176,   107,
      -1,    87,   178,    -1,    -1,   104,    87,   178,    -1,    -1,
     181,   180,    -1,    -1,   108,   181,   180,    -1,    -1,   202,
      -1,   182,    -1,   115,    -1,    87,    56,   202,    -1,    82,
      -1,    81,    -1,    85,    -1,    88,    -1,    86,    -1,   150,
      -1,    15,    -1,    87,   105,    87,    -1,    90,    -1,    44,
     186,   187,   190,    45,    -1,   202,    -1,    -1,   189,   188,
      -1,   189,   188,    -1,    -1,    46,   138,    47,   202,    -1,
      48,   202,    -1,   183,    -1,   184,    -1,    87,    -1,   102,
     202,   103,    -1,   185,    -1,   191,    -1,   191,   109,   193,
     110,    -1,   194,   102,   203,   103,    -1,   194,   102,   103,
      -1,    87,   102,   203,   103,    -1,    87,   102,   103,    -1,
      16,    -1,    17,    -1,    18,    82,    -1,    57,    -1,    58,
      -1,    74,    -1,    59,    -1,    75,    -1,    60,    -1,    61,
      -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,    76,
      -1,    66,    -1,    77,    -1,    67,    -1,    68,    -1,    69,
      -1,    70,    -1,    78,    -1,    71,    -1,    72,    -1,    79,
      -1,    73,    -1,    80,    -1,   192,    -1,   192,    89,   195,
      -1,   195,    -1,   196,    90,   195,    -1,   196,    91,   195,
      -1,   196,    -1,   197,    92,   196,    -1,   197,    93,   196,
      -1,   197,    -1,   198,    96,   197,    -1,   198,    97,   197,
      -1,   198,    94,   197,    -1,   198,    95,   197,    -1,   198,
      -1,   199,    98,   198,    -1,   199,    99,   198,    -1,   199,
      -1,   200,   100,   199,    -1,   200,    -1,   201,   101,   200,
      -1,   201,    -1,   202,   204,    -1,   104,   202,   204,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   170,   171,   172,   173,   174,   175,   176,
     181,   183,   185,   183,   190,   191,   194,   195,   198,   198,
     202,   203,   206,   209,   210,   215,   218,   221,   222,   225,
     226,   229,   232,   233,   236,   239,   240,   243,   244,   247,
     248,   251,   252,   255,   256,   259,   260,   265,   266,   269,
     270,   273,   274,   277,   278,   282,   283,   284,   288,   289,
     290,   291,   292,   296,   297,   300,   301,   304,   305,   308,
     309,   312,   313,   316,   317,   320,   321,   324,   327,   334,
     335,   336,   337,   338,   342,   345,   348,   349,   352,   353,
     354,   355,   360,   363,   364,   368,   369,   372,   373,   376,
     378,   380,   381,   384,   384,   384,   384,   384,   384,   388,
     391,   394,   395,   398,   401,   404,   405,   408,   409,   412,
     413,   417,   422,   417,   426,   427,   430,   431,   435,   436,
     439,   440,   443,   444,   445,   448,   452,   453,   454,   455,
     456,   457,   460,   461,   462,   466,   469,   470,   473,   476,
     477,   480,   483,   486,   487,   488,   489,   490,   493,   494,
     495,   496,   497,   498,   502,   503,   504,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   533,   534,   537,   538,   539,   543,   544,   545,   548,
     549,   550,   551,   552,   555,   556,   557,   560,   561,   564,
     565,   568,   572,   575,   576
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
  "global_query", "full_query", "@1", "@2", "local_queries",
  "local_queries_tail", "local_query", "@3", "col_aliases",
  "comma_identifier_list", "comma_identifier_list_tail", "base_query",
  "select_clause", "select_elem", "select_clause_tail", "from_clause",
  "order_clause", "order_specs", "order_spec", "column_name",
  "order_specs_tail", "where_clause", "groupby_clause", "having_clause",
  "search_condition", "boolean_term", "boolean_factor", "boolean_primary",
  "predicate", "postfix_predicate", "between_predicate", "in_predicate",
  "in_pred_spec", "like_predicate", "null_predicate", "is_predicate",
  "truth_value", "overlaps_predicate", "range_value_expression",
  "joined_table", "on_clause", "using_clause", "table_expression",
  "table_expression_main", "table_expressions", "table_expressions_tail",
  "create_table_or_view", "create_spec", "schema", "schema_element",
  "schema_tail", "type_name", "update_statement", "set_clauses",
  "set_clauses_tail", "set_clause", "insert_statement", "insert_modifier",
  "insert_source", "delete_statement", "user_function_definition", "@4",
  "@5", "def_arg_list", "def_arg_list_tail", "function_body",
  "function_body_tail", "function_body_elem", "function_local_var_def",
  "constant", "table_constant", "case_expression", "case_clause",
  "when_clauses", "when_clauses_tail", "when_clause", "else_clause",
  "main_expression", "call", "indexing", "built_in_fun", "exp_expression",
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
     355,   356,    40,    41,    44,    46,   123,   125,    59,    91,
      93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   111,   112,   113,   113,   113,   113,   113,   113,   113,
     114,   116,   117,   115,   118,   118,   119,   119,   121,   120,
     122,   122,   123,   124,   124,   125,   126,   127,   127,   128,
     128,   129,   130,   130,   131,   132,   132,   133,   133,   134,
     134,   135,   135,   136,   136,   137,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   142,   142,   143,   143,
     143,   143,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   152,   153,
     153,   153,   153,   153,   154,   155,   156,   156,   157,   157,
     157,   157,   158,   159,   159,   160,   160,   161,   161,   162,
     163,   164,   164,   165,   165,   165,   165,   165,   165,   166,
     167,   168,   168,   169,   170,   171,   171,   172,   172,   173,
     173,   175,   176,   174,   177,   177,   178,   178,   179,   179,
     180,   180,   181,   181,   181,   182,   183,   183,   183,   183,
     183,   183,   184,   184,   184,   185,   186,   186,   187,   188,
     188,   189,   190,   191,   191,   191,   191,   191,   192,   192,
     192,   192,   192,   192,   193,   193,   193,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   195,   195,   196,   196,   196,   197,   197,   197,   198,
     198,   198,   198,   198,   199,   199,   199,   200,   200,   201,
     201,   202,   203,   204,   204
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     0,
       1,     0,     0,     4,     3,     0,     2,     0,     0,     7,
       3,     0,     2,     3,     0,     5,     3,     3,     1,     3,
       0,     2,     2,     0,     2,     2,     2,     1,     3,     3,
       0,     2,     0,     4,     0,     2,     0,     1,     3,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     6,     3,     4,     3,     1,     3,
       4,     4,     3,     3,     4,     1,     1,     3,     5,     1,
       5,     5,     6,     6,     2,     4,     1,     4,     2,     3,
       1,     3,     2,     3,     0,     4,     4,     2,     3,     2,
       2,     3,     0,     1,     1,     1,     1,     1,     1,     7,
       2,     3,     0,     3,     6,     3,     0,     1,     4,     5,
       4,     0,     0,    10,     2,     0,     3,     0,     2,     0,
       3,     0,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     5,     1,     0,     2,     2,
       0,     4,     2,     1,     1,     1,     3,     1,     1,     4,
       4,     3,     4,     3,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     2,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     0,     0,     0,     0,     0,     2,    11,    10,
      15,    11,    11,    11,    11,    11,     0,     0,     0,     0,
       0,    24,     0,   121,     1,     3,     0,     0,     4,     6,
       5,     7,     8,     0,     0,     0,    33,    33,     0,    22,
       0,     0,    18,    17,     0,    12,     0,    11,     0,    95,
      96,     0,    33,   112,     0,   116,    42,    24,   120,   125,
      21,    14,    17,   142,   147,   167,   168,   170,   172,   173,
     174,   175,   176,   177,   179,   181,   182,   183,   184,   186,
     187,   189,   169,   171,   178,   180,   185,   188,   190,   137,
     136,    75,    76,   138,   140,   155,   139,   144,     0,    30,
     141,   153,   154,   157,   158,   191,     0,   193,   196,   199,
     204,   207,   209,   211,    28,    13,     0,    33,    97,     0,
       0,   102,     0,    42,     0,   110,     0,     0,    32,    40,
       0,    11,     0,   119,    23,   127,     0,     0,     0,    16,
       0,   146,     0,     0,     0,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,     0,    94,    79,    86,    31,
      42,   103,   104,   105,   106,   107,   108,   100,    98,     0,
      99,   113,    44,   112,    37,    35,    36,     0,    34,     0,
       0,   117,   114,     0,     0,    41,    47,    49,    51,    53,
      56,    58,    59,    61,    60,    62,    57,     0,    55,     0,
     124,     0,     0,     0,     0,     0,   150,   163,   214,     0,
     143,   156,    30,   164,   165,     0,     0,   192,   161,     0,
     194,   195,   197,   198,   202,   203,   200,   201,   205,   206,
     208,   210,    27,     0,     0,    88,     0,     0,    92,     0,
       0,    44,   102,     0,   109,   111,     0,    40,   115,     0,
      52,     0,    55,     0,     0,     0,     0,     0,     0,     0,
       0,   127,    11,    20,     0,     0,     0,     0,   148,   150,
       0,   212,   162,    29,   166,   159,   160,     0,    89,    91,
      94,     0,     0,    25,   101,     0,    38,    39,     0,    54,
       0,    48,    50,     0,    77,     0,    72,    73,     0,     0,
       0,     0,     0,    65,    68,    69,   126,   155,   134,   122,
     131,   133,   132,     0,     0,   152,   145,   149,   214,    87,
      93,     0,     0,    46,   118,     0,     0,    71,    74,     0,
      66,    70,     0,     0,     0,     0,     0,    11,   128,    19,
     151,   213,     0,     0,    80,    81,     0,     0,    43,    78,
       0,    63,    67,   135,   123,   131,    84,     0,    82,    83,
      45,    64,   130,     0,    85
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,   115,    27,    61,    62,
      60,   138,    22,    39,    45,    46,    99,   146,   117,    55,
     128,   129,   185,   188,   133,   254,   358,   195,   196,   197,
     198,   199,   200,   201,   202,   313,   203,   204,   205,   100,
     206,   207,   166,   354,   355,   167,   168,   169,   248,    11,
      49,   120,   121,   180,   177,    12,    52,   125,    53,    13,
     131,   192,    14,    15,    41,   346,   136,   210,   319,   348,
     320,   321,   101,   102,   103,   140,   215,   278,   279,   277,
     104,   105,   226,   106,   107,   108,   109,   110,   111,   112,
     113,   208,   219,   281
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -244
static const yytype_int16 yypact[] =
{
      11,    33,   -43,    47,     4,     0,   116,  -244,    11,  -244,
      86,    11,    11,    11,    11,    11,    34,    37,    95,    39,
      40,    24,   125,  -244,  -244,  -244,    45,   128,  -244,  -244,
    -244,  -244,  -244,     2,     2,    48,   127,   127,    49,  -244,
      50,    36,  -244,    45,   482,  -244,   133,  -244,    53,  -244,
    -244,    43,   127,    38,    64,    41,   134,    24,  -244,    58,
      44,  -244,    45,  -244,   482,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,   -66,  -244,  -244,   482,    51,
    -244,  -244,  -244,  -244,    52,    59,    54,  -244,     9,    10,
     -39,    13,    57,    62,   135,  -244,   -12,   127,  -244,   -19,
      55,    56,   482,   134,    48,  -244,    60,    60,  -244,    61,
      65,   120,   408,  -244,  -244,    67,    63,    65,   150,  -244,
     118,  -244,   260,    82,   101,   482,  -244,    66,   482,   334,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   119,   105,     5,   -12,   104,    46,  -244,  -244,
     134,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,    53,
    -244,  -244,   198,    38,   106,  -244,  -244,    64,  -244,   107,
     110,  -244,  -244,   556,   408,   177,   179,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,   173,    69,   131,
    -244,   113,   117,   121,   408,   181,   118,  -244,   126,   130,
    -244,  -244,    51,  -244,  -244,   139,   124,  -244,  -244,   132,
    -244,  -244,     9,     9,    10,    10,    10,    10,   -39,   -39,
      13,    57,  -244,   -61,   144,  -244,   136,   -12,  -244,   217,
     218,   198,    56,   229,  -244,  -244,   155,    61,  -244,   482,
    -244,   -15,   -23,   408,   408,   141,   -13,    12,   482,   630,
     482,    67,   115,  -244,   128,    -9,   482,   199,  -244,   118,
     482,  -244,  -244,  -244,  -244,  -244,  -244,   142,  -244,  -244,
     104,   -12,   226,  -244,  -244,   482,  -244,  -244,   145,  -244,
     482,   179,  -244,   482,  -244,   -20,  -244,  -244,   482,   630,
     482,   212,   482,  -244,  -244,  -244,  -244,   -37,  -244,  -244,
     146,  -244,  -244,   147,   482,  -244,  -244,  -244,   126,  -244,
    -244,    89,   -12,   236,  -244,   149,   151,  -244,  -244,   222,
    -244,  -244,   482,    14,   157,   482,   154,   704,  -244,  -244,
    -244,  -244,   408,   156,  -244,  -244,    89,   408,  -244,  -244,
     482,  -244,  -244,  -244,  -244,   146,   177,    65,  -244,  -244,
     177,  -244,  -244,   159,  -244
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -244,  -244,    35,  -244,   -45,  -244,  -244,  -244,   191,   237,
    -244,  -244,  -129,   210,    -5,  -244,   129,    68,  -244,   -24,
    -244,    83,   152,    15,  -111,    20,  -244,  -190,    18,    19,
      80,  -244,  -244,  -244,  -244,   -32,  -244,  -244,  -244,  -243,
    -244,    17,  -162,   -80,   -78,  -244,    42,  -244,    -6,  -244,
     252,  -244,   108,    99,  -244,  -244,  -244,   109,   164,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,    22,  -244,   -76,
     -56,  -244,  -244,  -244,  -244,  -244,  -244,    16,   160,  -244,
    -244,  -244,  -244,  -244,   -74,   -33,   -60,   -36,   137,   138,
    -244,   -44,  -144,   -34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -130
static const yytype_int16 yytable[] =
{
     114,   189,   118,   246,   261,   229,    47,   163,   212,   244,
      20,    -9,   182,    56,   266,   267,   268,   269,   270,   345,
     141,   263,   337,   307,   275,   305,   164,   263,   123,   306,
     171,   172,   173,   174,   175,   176,   142,     1,   324,   143,
       2,   165,     3,    25,    18,     4,    28,    29,    30,    31,
      32,   308,   309,   310,   144,   154,   155,   156,   157,   251,
      16,    17,   338,    91,    92,   142,     5,   249,   143,   250,
      91,    92,   126,   127,   227,   164,   230,   231,   181,    19,
     221,   300,   223,   224,   225,   290,   191,    23,   299,    26,
     165,    21,   245,   170,   234,   235,   236,   237,   218,   150,
     151,   114,   152,   153,    48,   218,   266,   267,   268,   269,
     270,   158,   159,   352,   353,   298,    24,   221,   280,   232,
     233,    33,   238,   239,    34,    35,    36,    37,    38,   331,
      63,    40,    42,    44,    54,    51,    57,    58,    59,   116,
     119,   122,   124,   130,   132,   135,   137,   184,   148,   162,
     262,   333,    21,   190,   213,   145,   149,   160,   178,    64,
     179,   147,   366,   161,   214,   187,   211,   370,   344,   220,
     356,   209,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,   317,    96,   221,    97,   242,   243,   247,   253,
     258,   256,   259,   263,   264,   218,   265,    98,   271,   272,
     273,   284,  -129,   274,   311,   314,   315,   318,   322,   276,
     280,   288,   325,   282,   285,   286,   328,   291,   373,   289,
     292,   295,   296,   303,   326,   329,   332,   342,   334,   357,
     349,   218,   359,   139,   347,   300,   335,   360,   367,   336,
     362,   364,   374,    43,   339,   314,   341,   134,   343,   323,
     257,   293,   297,   260,   222,    63,   368,   340,   369,   186,
     350,   301,   304,   302,   330,   287,    50,   252,   183,   372,
     283,   365,   255,   316,   351,   327,     0,   240,   361,   241,
     216,   363,   318,   322,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   371,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    63,
      97,   294,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,   217,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    63,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    98,   228,     0,     0,
       0,     0,     0,     0,     0,     0,   193,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    63,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     194,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    63,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    63,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   194,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    63,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   317,    96,     0,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    98
};

static const yytype_int16 yycheck[] =
{
      44,   130,    47,   165,   194,   149,     4,    19,   137,     4,
       6,     0,   123,    37,    37,    38,    39,    40,    41,    56,
      64,    36,    42,   266,   214,    38,    87,    36,    52,    42,
      49,    50,    51,    52,    53,    54,   102,    26,    47,   105,
      29,   102,    31,     8,    87,    34,    11,    12,    13,    14,
      15,    39,    40,    41,    98,    94,    95,    96,    97,   170,
      27,    28,   305,    83,    84,   102,    55,    21,   105,    23,
      83,    84,     8,     9,   148,    87,   150,   151,   122,    32,
     103,   104,    16,    17,    18,   247,   131,    87,   103,     3,
     102,    87,    87,   117,   154,   155,   156,   157,   142,    90,
      91,   145,    92,    93,   102,   149,    37,    38,    39,    40,
      41,    98,    99,    24,    25,   259,     0,   103,   104,   152,
     153,    87,   158,   159,    87,    30,    87,    87,   104,   291,
      15,     6,    87,     5,     7,    87,    87,    87,   102,     6,
      87,    98,   104,   102,    10,    87,   102,    87,    89,    14,
     194,   295,    87,    33,     4,   104,   102,   100,   103,    44,
     104,   109,   352,   101,    46,   104,   103,   357,   312,    87,
     332,   104,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   103,    90,    87,   102,   104,    11,
     103,   105,   102,    36,    35,   259,    43,   102,    87,   106,
     103,    82,   107,   102,   268,   269,   270,   272,   272,    48,
     104,    87,   276,   103,   110,   103,   280,    20,   367,   103,
      22,    12,    87,   102,    45,   103,    20,    35,   103,    13,
     103,   295,   103,    62,   108,   104,   300,    35,   102,   303,
     103,   107,   103,    26,   308,   309,   310,    57,   312,   274,
     187,   251,   257,   193,   145,    15,   356,   309,   356,   127,
     324,   263,   265,   264,   290,   243,    34,   179,   124,   365,
     222,   347,   183,   271,   328,   279,    -1,   160,   342,   161,
     140,   345,   347,   347,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   360,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    15,
      90,   252,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    15,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    15,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    15,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    15,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    15,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    29,    31,    34,    55,   112,   113,   114,   115,
     116,   160,   166,   170,   173,   174,    27,    28,    87,    32,
       6,    87,   123,    87,     0,   113,     3,   118,   113,   113,
     113,   113,   113,    87,    87,    30,    87,    87,   104,   124,
       6,   175,    87,   120,     5,   125,   126,     4,   102,   161,
     161,    87,   167,   169,     7,   130,   130,    87,    87,   102,
     121,   119,   120,    15,    44,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    90,   102,   127,
     150,   183,   184,   185,   191,   192,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   117,     6,   129,   115,    87,
     162,   163,    98,   130,   104,   168,     8,     9,   131,   132,
     102,   171,    10,   135,   124,    87,   177,   102,   122,   119,
     186,   202,   102,   105,   202,   104,   128,   109,    89,   102,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,    14,    19,    87,   102,   153,   156,   157,   158,
     130,    49,    50,    51,    52,    53,    54,   165,   103,   104,
     164,   202,   135,   169,    87,   133,   133,   104,   134,   123,
      33,   115,   172,    38,   102,   138,   139,   140,   141,   142,
     143,   144,   145,   147,   148,   149,   151,   152,   202,   104,
     178,   103,   123,     4,    46,   187,   189,   103,   202,   203,
      87,   103,   127,    16,    17,    18,   193,   195,   103,   203,
     195,   195,   196,   196,   197,   197,   197,   197,   198,   198,
     199,   200,    87,   102,     4,    87,   153,   104,   159,    21,
      23,   135,   163,    11,   136,   168,   105,   132,   103,   102,
     141,   138,   202,    36,    35,    43,    37,    38,    39,    40,
      41,    87,   106,   103,   102,   138,    48,   190,   188,   189,
     104,   204,   103,   128,    82,   110,   103,   157,    87,   103,
     153,    20,    22,   136,   164,    12,    87,   134,   203,   103,
     104,   139,   140,   102,   152,    38,    42,   150,    39,    40,
      41,   202,   102,   146,   202,   202,   178,    87,   115,   179,
     181,   182,   202,   125,    47,   202,    45,   188,   202,   103,
     159,   153,    20,   203,   103,   202,   202,    42,   150,   202,
     146,   202,    35,   202,   203,    56,   176,   108,   180,   103,
     202,   204,    24,    25,   154,   155,   153,    13,   137,   103,
      35,   202,   103,   202,   107,   181,   138,   102,   154,   155,
     138,   202,   180,   123,   103
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
        case 11:
#line 183 "aquery.y"
    { print_symtable(env);  env = push_env(env); /* create a new scope to handle local query names */ ;}
    break;

  case 12:
#line 185 "aquery.y"
    { print_symtable(env); env = pop_env(env); /* remove local queries from scope */ ;}
    break;

  case 13:
#line 186 "aquery.y"
    { (yyval.fullquery) = NULL; ;}
    break;

  case 18:
#line 198 "aquery.y"
    { put_sym(env, (yyvsp[(1) - (1)].str), TABLE_TYPE); /* add local query table name to symbol table */ ;}
    break;

  case 22:
#line 206 "aquery.y"
    {(yyval.idlist) = make_IDListNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].idlist)); ;}
    break;

  case 23:
#line 209 "aquery.y"
    {(yyval.idlist) = make_IDListNode((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].idlist));;}
    break;

  case 24:
#line 210 "aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 25:
#line 215 "aquery.y"
    {(yyval.plan) = assemble_logical((yyvsp[(1) - (5)].plan), (yyvsp[(2) - (5)].plan), (yyvsp[(3) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].plan)); print_logical_query((yyval.plan));;}
    break;

  case 26:
#line 218 "aquery.y"
    {(yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.plan) = make_project(PROJECT_SELECT, NULL, (yyvsp[(2) - (3)].namedexpr)); ;}
    break;

  case 27:
#line 221 "aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode((yyvsp[(3) - (3)].str), (yyvsp[(1) - (3)].exprnode)); ;}
    break;

  case 28:
#line 222 "aquery.y"
    { (yyval.namedexpr) = make_NamedExprNode(NULL, (yyvsp[(1) - (1)].exprnode)); ;}
    break;

  case 29:
#line 225 "aquery.y"
    {(yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.namedexpr) = (yyvsp[(2) - (3)].namedexpr); ;}
    break;

  case 30:
#line 226 "aquery.y"
    {(yyval.namedexpr) = NULL; ;}
    break;

  case 31:
#line 229 "aquery.y"
    {(yyval.plan) = (yyvsp[(2) - (2)].plan); ;}
    break;

  case 32:
#line 232 "aquery.y"
    { (yyval.plan) = make_sort(NULL, (yyvsp[(2) - (2)].order)); ;}
    break;

  case 33:
#line 233 "aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 34:
#line 236 "aquery.y"
    {(yyvsp[(1) - (2)].order)->next = (yyvsp[(2) - (2)].order); (yyval.order) = (yyvsp[(1) - (2)].order); ;}
    break;

  case 35:
#line 239 "aquery.y"
    {(yyval.order) = make_OrderNode(ASC_SORT, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 36:
#line 240 "aquery.y"
    {(yyval.order) = make_OrderNode(DESC_SORT, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 37:
#line 243 "aquery.y"
    { (yyval.exprnode) = make_id(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 38:
#line 244 "aquery.y"
    {(yyval.exprnode) = make_colDotAccessNode(make_id(env, (yyvsp[(1) - (3)].str)), make_id(env, (yyvsp[(3) - (3)].str))); ;}
    break;

  case 39:
#line 247 "aquery.y"
    {(yyvsp[(2) - (3)].order)->next = (yyvsp[(3) - (3)].order); (yyval.order) = (yyvsp[(2) - (3)].order); ;}
    break;

  case 40:
#line 248 "aquery.y"
    {(yyval.order) = NULL; ;}
    break;

  case 41:
#line 251 "aquery.y"
    {(yyval.plan) = make_filterWhere(NULL, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 42:
#line 252 "aquery.y"
    {(yyval.plan) = NULL; ;}
    break;

  case 43:
#line 255 "aquery.y"
    {(yyval.plan) = pushdown_logical((yyvsp[(4) - (4)].plan), make_groupby(NULL, (yyvsp[(3) - (4)].exprnode)));   ;}
    break;

  case 44:
#line 256 "aquery.y"
    {(yyval.plan) = NULL; ;}
    break;

  case 45:
#line 259 "aquery.y"
    {(yyval.plan) = make_filterHaving(NULL, (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 46:
#line 260 "aquery.y"
    {(yyval.plan) =  NULL; ;}
    break;

  case 47:
#line 265 "aquery.y"
    {printf("---->search\n"); print_expr((yyvsp[(1) - (1)].exprnode), DUMMY, 0, 0); (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 48:
#line 266 "aquery.y"
    {(yyval.exprnode) = make_logicOpNode(WHERE_OR_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 49:
#line 269 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 50:
#line 270 "aquery.y"
    {(yyval.exprnode) = make_logicOpNode(WHERE_AND_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 51:
#line 273 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 52:
#line 274 "aquery.y"
    {(yyval.exprnode) = make_callNode(make_predNode((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 53:
#line 277 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 54:
#line 278 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 55:
#line 282 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 56:
#line 283 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 57:
#line 284 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 58:
#line 288 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 59:
#line 289 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 60:
#line 290 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 61:
#line 291 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 62:
#line 292 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 63:
#line 296 "aquery.y"
    {(yyvsp[(1) - (5)].exprnode)->next_sibling = (yyvsp[(3) - (5)].exprnode); (yyvsp[(3) - (5)].exprnode)->next_sibling = (yyvsp[(5) - (5)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (5)].str)), make_exprListNode((yyvsp[(1) - (5)].exprnode))); ;}
    break;

  case 64:
#line 297 "aquery.y"
    {(yyvsp[(1) - (6)].exprnode)->next_sibling = (yyvsp[(4) - (6)].exprnode); (yyvsp[(4) - (6)].exprnode)->next_sibling = (yyvsp[(6) - (6)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (6)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (6)].str)), make_exprListNode((yyvsp[(1) - (6)].exprnode))))); ;}
    break;

  case 65:
#line 300 "aquery.y"
    {(yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 66:
#line 301 "aquery.y"
    {(yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 67:
#line 304 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 68:
#line 305 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 69:
#line 308 "aquery.y"
    {(yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 70:
#line 309 "aquery.y"
    {(yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 71:
#line 312 "aquery.y"
    {(yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (4)].str)), make_exprListNode(make_callNode(make_predNode((yyvsp[(4) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 72:
#line 313 "aquery.y"
    {(yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 73:
#line 316 "aquery.y"
    {(yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 74:
#line 317 "aquery.y"
    {(yyvsp[(1) - (4)].exprnode)->next_sibling = (yyvsp[(4) - (4)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(3) - (4)].str)),  make_exprListNode(make_callNode(make_predNode((yyvsp[(2) - (4)].str)), make_exprListNode((yyvsp[(1) - (4)].exprnode))))); ;}
    break;

  case 75:
#line 320 "aquery.y"
    {(yyval.exprnode) = make_bool(1); ;}
    break;

  case 76:
#line 321 "aquery.y"
    {(yyval.exprnode) = make_bool(0); ;}
    break;

  case 77:
#line 324 "aquery.y"
    {(yyvsp[(1) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = make_callNode(make_predNode((yyvsp[(2) - (3)].str)), make_exprListNode((yyvsp[(1) - (3)].exprnode))); ;}
    break;

  case 78:
#line 327 "aquery.y"
    {(yyvsp[(2) - (5)].exprnode)->next_sibling = (yyvsp[(4) - (5)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (5)].exprnode); ;}
    break;

  case 79:
#line 334 "aquery.y"
    { (yyval.plan) = (yyvsp[(1) - (1)].plan); ;}
    break;

  case 80:
#line 335 "aquery.y"
    { (yyval.plan) = make_joinOn(INNER_JOIN_ON, (yyvsp[(1) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].exprnode)); ;}
    break;

  case 81:
#line 336 "aquery.y"
    { (yyval.plan) = make_joinUsing(INNER_JOIN_USING, (yyvsp[(1) - (5)].plan), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].idlist)); ;}
    break;

  case 82:
#line 337 "aquery.y"
    { (yyval.plan) = make_joinOn(FULL_OUTER_JOIN_ON, (yyvsp[(1) - (6)].plan), (yyvsp[(5) - (6)].plan), (yyvsp[(6) - (6)].exprnode)); ;}
    break;

  case 83:
#line 338 "aquery.y"
    { (yyval.plan) = make_joinUsing(FULL_OUTER_JOIN_USING, (yyvsp[(1) - (6)].plan), (yyvsp[(5) - (6)].plan), (yyvsp[(6) - (6)].idlist)); ;}
    break;

  case 84:
#line 342 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(2) - (2)].exprnode); ;}
    break;

  case 85:
#line 345 "aquery.y"
    { (yyval.idlist) = (yyvsp[(3) - (4)].idlist); ;}
    break;

  case 86:
#line 348 "aquery.y"
    { (yyval.plan) = (yyvsp[(1) - (1)].plan); ;}
    break;

  case 87:
#line 349 "aquery.y"
    { (yyval.plan) = make_flatten((yyvsp[(3) - (4)].plan)); ;}
    break;

  case 88:
#line 352 "aquery.y"
    { (yyval.plan) = make_alias(make_table((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 89:
#line 353 "aquery.y"
    { (yyval.plan) = make_alias(make_table((yyvsp[(1) - (3)].str)), (yyvsp[(3) - (3)].str)); ;}
    break;

  case 90:
#line 354 "aquery.y"
    { (yyval.plan) = make_table((yyvsp[(1) - (1)].str)); ;}
    break;

  case 91:
#line 355 "aquery.y"
    { (yyval.plan) = (yyvsp[(2) - (3)].plan); ;}
    break;

  case 92:
#line 360 "aquery.y"
    {if((yyvsp[(2) - (2)].plan) == NULL){ (yyval.plan) = (yyvsp[(1) - (2)].plan); }else { (yyval.plan) = make_cross((yyvsp[(1) - (2)].plan), (yyvsp[(2) - (2)].plan)); } print_logical_query((yyval.plan));;}
    break;

  case 93:
#line 363 "aquery.y"
    {if((yyvsp[(3) - (3)].plan) == NULL){ (yyval.plan) = (yyvsp[(2) - (3)].plan); }else { (yyval.plan) = make_cross((yyvsp[(2) - (3)].plan), (yyvsp[(3) - (3)].plan)); } ;}
    break;

  case 94:
#line 364 "aquery.y"
    { (yyval.plan) = NULL; ;}
    break;

  case 95:
#line 368 "aquery.y"
    { put_sym(env, (yyvsp[(3) - (4)].str), TABLE_TYPE); ;}
    break;

  case 96:
#line 369 "aquery.y"
    { put_sym(env, (yyvsp[(3) - (4)].str), VIEW_TYPE);  ;}
    break;

  case 109:
#line 388 "aquery.y"
    { (yyval.plan)  = assemble_logical(make_project(PROJECT_UPDATE, NULL, (yyvsp[(4) - (7)].namedexpr)), make_table((yyvsp[(2) - (7)].str)), (yyvsp[(5) - (7)].plan), (yyvsp[(6) - (7)].plan), (yyvsp[(7) - (7)].plan)); print_logical_query((yyval.plan));;}
    break;

  case 110:
#line 391 "aquery.y"
    {(yyvsp[(1) - (2)].namedexpr)->next_sibling = (yyvsp[(2) - (2)].namedexpr); (yyval.namedexpr) = (yyvsp[(1) - (2)].namedexpr); ;}
    break;

  case 111:
#line 394 "aquery.y"
    {(yyvsp[(2) - (3)].namedexpr)->next_sibling = (yyvsp[(3) - (3)].namedexpr); (yyval.namedexpr) = (yyvsp[(2) - (3)].namedexpr); ;}
    break;

  case 112:
#line 395 "aquery.y"
    { (yyval.namedexpr) = NULL; ;}
    break;

  case 113:
#line 398 "aquery.y"
    {(yyval.namedexpr) = make_NamedExprNode((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 114:
#line 401 "aquery.y"
    {(yyval.insert) = make_insert(assemble_logical(NULL, make_table((yyvsp[(3) - (6)].str)), (yyvsp[(4) - (6)].plan), NULL, NULL), (yyvsp[(5) - (6)].idlist), (yyvsp[(6) - (6)].fullquery)); ;}
    break;

  case 115:
#line 404 "aquery.y"
    {  (yyval.idlist) = (yyvsp[(2) - (3)].idlist); ;}
    break;

  case 116:
#line 405 "aquery.y"
    {  (yyval.idlist) = NULL; ;}
    break;

  case 117:
#line 408 "aquery.y"
    {(yyval.fullquery) = (yyvsp[(1) - (1)].fullquery); ;}
    break;

  case 118:
#line 409 "aquery.y"
    {(yyval.fullquery) = make_FullQueryNode(NULL, make_values((yyvsp[(3) - (4)].exprnode))); ;}
    break;

  case 119:
#line 412 "aquery.y"
    {(yyval.plan) = assemble_logical(make_delete(NULL, NULL),make_table((yyvsp[(3) - (5)].str)), (yyvsp[(4) - (5)].plan), (yyvsp[(5) - (5)].plan), NULL);  print_logical_query((yyval.plan));;}
    break;

  case 120:
#line 413 "aquery.y"
    {(yyval.plan) = assemble_logical(make_delete(NULL, (yyvsp[(2) - (4)].idlist)), make_table((yyvsp[(4) - (4)].str)), NULL, NULL, NULL); print_logical_query((yyval.plan));;}
    break;

  case 121:
#line 417 "aquery.y"
    { put_sym(env, (yyvsp[(2) - (2)].str), FUNCTION_TYPE); env = push_env(env);  /* define function, create new scope for args*/ ;}
    break;

  case 122:
#line 422 "aquery.y"
    { print_symtable(env); /* this is what is reachable during function body*/ ;}
    break;

  case 123:
#line 423 "aquery.y"
    { env = pop_env(env); (yyval.udfdef) =  make_UDFDefNode((yyvsp[(2) - (10)].str), (yyvsp[(5) - (10)].idlist), (yyvsp[(8) - (10)].udfbody)); print_udf_def((yyval.udfdef)); ;}
    break;

  case 124:
#line 426 "aquery.y"
    { put_sym(env, (yyvsp[(1) - (2)].str), UNKNOWN_TYPE); (yyval.idlist) = make_IDListNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].idlist)); ;}
    break;

  case 125:
#line 427 "aquery.y"
    { (yyval.idlist) = NULL; ;}
    break;

  case 126:
#line 430 "aquery.y"
    { put_sym(env, (yyvsp[(2) - (3)].str), UNKNOWN_TYPE ); (yyval.idlist) = make_IDListNode((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].idlist)); ;}
    break;

  case 127:
#line 431 "aquery.y"
    {(yyval.idlist) = NULL; ;}
    break;

  case 128:
#line 435 "aquery.y"
    {(yyvsp[(1) - (2)].udfbody)->next_sibling = (yyvsp[(2) - (2)].udfbody); (yyval.udfbody) = (yyvsp[(1) - (2)].udfbody);;}
    break;

  case 129:
#line 436 "aquery.y"
    {(yyval.udfbody) = NULL; ;}
    break;

  case 130:
#line 439 "aquery.y"
    {(yyvsp[(2) - (3)].udfbody)->next_sibling = (yyvsp[(3) - (3)].udfbody); (yyval.udfbody) = (yyvsp[(2) - (3)].udfbody); ;}
    break;

  case 131:
#line 440 "aquery.y"
    { (yyval.udfbody)= NULL; ;}
    break;

  case 132:
#line 443 "aquery.y"
    {(yyval.udfbody) = make_UDFExpr((yyvsp[(1) - (1)].exprnode));   ;}
    break;

  case 133:
#line 444 "aquery.y"
    {(yyval.udfbody) = make_UDFVardef((yyvsp[(1) - (1)].localvardef)); ;}
    break;

  case 134:
#line 445 "aquery.y"
    {(yyval.udfbody) = make_UDFQuery((yyvsp[(1) - (1)].fullquery));  ;}
    break;

  case 135:
#line 448 "aquery.y"
    { put_sym(env, (yyvsp[(1) - (3)].str), UNKNOWN_TYPE);    (yyval.localvardef) = make_LocalVarDefNode((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 136:
#line 452 "aquery.y"
    { (yyval.exprnode) = make_int((yyvsp[(1) - (1)].intval)); ;}
    break;

  case 137:
#line 453 "aquery.y"
    { (yyval.exprnode) = make_float((yyvsp[(1) - (1)].floatval)); ;}
    break;

  case 138:
#line 454 "aquery.y"
    { (yyval.exprnode) = make_date((yyvsp[(1) - (1)].str)); ;}
    break;

  case 139:
#line 455 "aquery.y"
    { (yyval.exprnode) = make_string((yyvsp[(1) - (1)].str)); ;}
    break;

  case 140:
#line 456 "aquery.y"
    { (yyval.exprnode) = make_hex((yyvsp[(1) - (1)].str)); ;}
    break;

  case 141:
#line 457 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 142:
#line 460 "aquery.y"
    { (yyval.exprnode) = make_rowId(); ;}
    break;

  case 143:
#line 461 "aquery.y"
    { (yyval.exprnode) = make_colDotAccessNode(make_id(env, (yyvsp[(1) - (3)].str)), make_id(env, (yyvsp[(3) - (3)].str))); ;}
    break;

  case 144:
#line 462 "aquery.y"
    { (yyval.exprnode) = make_allColsNode(); ;}
    break;

  case 145:
#line 466 "aquery.y"
    {(yyval.exprnode) = make_caseNode((yyvsp[(2) - (5)].exprnode), (yyvsp[(3) - (5)].exprnode), (yyvsp[(4) - (5)].exprnode)); ;}
    break;

  case 146:
#line 469 "aquery.y"
    { (yyval.exprnode) = make_caseClauseNode((yyvsp[(1) - (1)].exprnode));  ;}
    break;

  case 147:
#line 470 "aquery.y"
    { (yyval.exprnode) = make_caseClauseNode(NULL); ;}
    break;

  case 148:
#line 473 "aquery.y"
    {(yyval.exprnode) = make_whenClausesNode((yyvsp[(1) - (2)].exprnode), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 149:
#line 476 "aquery.y"
    {(yyval.exprnode) = make_whenClausesNode((yyvsp[(1) - (2)].exprnode), (yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 150:
#line 477 "aquery.y"
    {(yyval.exprnode) = NULL; ;}
    break;

  case 151:
#line 480 "aquery.y"
    {(yyval.exprnode) = make_caseWhenNode((yyvsp[(2) - (4)].exprnode), (yyvsp[(4) - (4)].exprnode)); ;}
    break;

  case 152:
#line 483 "aquery.y"
    { (yyval.exprnode) = make_elseClauseNode((yyvsp[(2) - (2)].exprnode)); ;}
    break;

  case 153:
#line 486 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 154:
#line 487 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 155:
#line 488 "aquery.y"
    { (yyval.exprnode) = make_id(env, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 156:
#line 489 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 157:
#line 490 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 158:
#line 493 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 159:
#line 494 "aquery.y"
    { (yyval.exprnode) = make_indexNode((yyvsp[(1) - (4)].exprnode), (yyvsp[(3) - (4)].exprnode)); ;}
    break;

  case 160:
#line 495 "aquery.y"
    {(yyval.exprnode) = make_callNode((yyvsp[(1) - (4)].exprnode), (yyvsp[(3) - (4)].exprnode)); ;}
    break;

  case 161:
#line 496 "aquery.y"
    {(yyval.exprnode) = make_callNode((yyvsp[(1) - (3)].exprnode), NULL); ;}
    break;

  case 162:
#line 497 "aquery.y"
    {(yyval.exprnode) = make_callNode(make_udfNode(env, (yyvsp[(1) - (4)].str)), (yyvsp[(3) - (4)].exprnode)); ;}
    break;

  case 163:
#line 498 "aquery.y"
    {(yyval.exprnode) = make_callNode(make_udfNode(env, (yyvsp[(1) - (3)].str)), NULL); ;}
    break;

  case 164:
#line 502 "aquery.y"
    {(yyval.exprnode) = make_oddix();     ;}
    break;

  case 165:
#line 503 "aquery.y"
    {(yyval.exprnode) = make_evenix();     ;}
    break;

  case 166:
#line 504 "aquery.y"
    {(yyval.exprnode) = make_everynix((yyvsp[(2) - (2)].intval)); ;}
    break;

  case 167:
#line 507 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 168:
#line 508 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 169:
#line 509 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 170:
#line 510 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 171:
#line 511 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 172:
#line 512 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 173:
#line 513 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 174:
#line 514 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 175:
#line 515 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 176:
#line 516 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 177:
#line 517 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 178:
#line 518 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 179:
#line 519 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 180:
#line 520 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 181:
#line 521 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 182:
#line 522 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 183:
#line 523 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 184:
#line 524 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 185:
#line 525 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 186:
#line 526 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 187:
#line 527 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 188:
#line 528 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 189:
#line 529 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 190:
#line 530 "aquery.y"
    { (yyval.exprnode) = make_builtInFunNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 191:
#line 533 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 192:
#line 534 "aquery.y"
    { (yyval.exprnode) = make_arithNode(POW_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 193:
#line 537 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 194:
#line 538 "aquery.y"
    { (yyval.exprnode) = make_arithNode(MULT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 195:
#line 539 "aquery.y"
    { (yyval.exprnode) = make_arithNode(DIV_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 196:
#line 543 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 197:
#line 544 "aquery.y"
    { (yyval.exprnode) = make_arithNode(PLUS_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 198:
#line 545 "aquery.y"
    { (yyval.exprnode) = make_arithNode(MINUS_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 199:
#line 548 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 200:
#line 549 "aquery.y"
    { (yyval.exprnode) = make_compNode(LT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 201:
#line 550 "aquery.y"
    { (yyval.exprnode) = make_compNode(GT_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 202:
#line 551 "aquery.y"
    { (yyval.exprnode) = make_compNode(LE_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 203:
#line 552 "aquery.y"
    { (yyval.exprnode) = make_compNode(GE_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 204:
#line 555 "aquery.y"
    {(yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 205:
#line 556 "aquery.y"
    { (yyval.exprnode) = make_compNode(EQ_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 206:
#line 557 "aquery.y"
    { (yyval.exprnode) = make_compNode(NEQ_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 207:
#line 560 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 208:
#line 561 "aquery.y"
    { (yyval.exprnode) = make_logicOpNode(LAND_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 209:
#line 564 "aquery.y"
    { (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 210:
#line 565 "aquery.y"
    { (yyval.exprnode) = make_logicOpNode(LOR_EXPR, (yyvsp[(1) - (3)].exprnode), (yyvsp[(3) - (3)].exprnode)); ;}
    break;

  case 211:
#line 568 "aquery.y"
    { print_expr((yyvsp[(1) - (1)].exprnode), DUMMY,0, 0); (yyval.exprnode) = (yyvsp[(1) - (1)].exprnode); ;}
    break;

  case 212:
#line 572 "aquery.y"
    { (yyvsp[(1) - (2)].exprnode)->next_sibling = (yyvsp[(2) - (2)].exprnode); (yyval.exprnode) = make_exprListNode((yyvsp[(1) - (2)].exprnode)); ;}
    break;

  case 213:
#line 575 "aquery.y"
    { (yyvsp[(2) - (3)].exprnode)->next_sibling = (yyvsp[(3) - (3)].exprnode); (yyval.exprnode) = (yyvsp[(2) - (3)].exprnode); ;}
    break;

  case 214:
#line 576 "aquery.y"
    { (yyval.exprnode) = NULL; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2958 "aquery.tab.c"
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


#line 582 "aquery.y"


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

int main(int argc, char *argv[]) {
	
	yydebug = 0;
	
	if(argc < 2) 
	{
		printf("Usage: aquery <file_name_to_parse>\n");
		exit(1);
	}
	
	FILE *to_parse = fopen(argv[1], "r");
	
	if(to_parse == NULL)
	{
		printf("Unable to open %s for reading\n", argv[1]);
		exit(1);
	}
	else
	{
		yyin = to_parse;
	}
	
	env = make_symtable(); //create the global environment
	
	do 
	{
		yyparse();
	} 
	while(!feof(yyin));
	
	print_symtable(env);
	
	printf("File conforms to Aquery grammar... now on to building AST\n");
}


