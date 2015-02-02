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
     ORDER = 263,
     WHERE = 264,
     GROUP = 265,
     BY = 266,
     HAVING = 267,
     LC_AS = 268,
     ROWID = 269,
     ODD = 270,
     EVEN = 271,
     EVERY = 272,
     FLATTEN = 273,
     CROSS = 274,
     JOIN = 275,
     NATURAL = 276,
     INNER = 277,
     OUTER = 278,
     LEFT = 279,
     RIGHT = 280,
     FULL = 281,
     ON = 282,
     USING = 283,
     CREATE = 284,
     TABLE = 285,
     VIEW = 286,
     UPDATE = 287,
     SET = 288,
     INSERT = 289,
     INTO = 290,
     VALUES = 291,
     DELETE = 292,
     AND = 293,
     OR = 294,
     IS = 295,
     NOT = 296,
     BETWEEN = 297,
     IN = 298,
     LIKE = 299,
     NULL_KEYWORD = 300,
     OVERLAPS = 301,
     CASE = 302,
     END = 303,
     WHEN = 304,
     THEN = 305,
     ELSE = 306,
     TYPE_INT = 307,
     TYPE_FLOAT = 308,
     TYPE_STRING = 309,
     TYPE_DATE = 310,
     TYPE_BOOLEAN = 311,
     TYPE_BIT = 312,
     TYPE_HEX = 313,
     FUNCTION = 314,
     ASSIGN = 315,
     ABS = 316,
     AVG = 317,
     COUNT = 318,
     DISTINCT = 319,
     DROP = 320,
     FIRST = 321,
     LAST = 322,
     MAX = 323,
     MIN = 324,
     MOD = 325,
     NEXT = 326,
     PREV = 327,
     PRD = 328,
     REV = 329,
     SUM = 330,
     STDDEV = 331,
     AVGS = 332,
     DELTAS = 333,
     MAXS = 334,
     MINS = 335,
     PRDS = 336,
     SUMS = 337,
     INT = 338,
     FLOAT = 339,
     STRING = 340,
     DATE = 341,
     TRUE = 342,
     FALSE = 343,
     BIT = 344,
     HEX = 345,
     NULL_VAL = 346,
     ID = 347,
     TIMES_OP = 348,
     DIV_OP = 349,
     PLUS_OP = 350,
     MINUS_OP = 351,
     LE_OP = 352,
     GE_OP = 353,
     L_OP = 354,
     G_OP = 355,
     EQ_OP = 356,
     NEQ_OP = 357,
     AND_OP = 358,
     OR_OP = 359
   };
#endif
/* Tokens.  */
#define WITH 258
#define UC_AS 259
#define SELECT 260
#define FROM 261
#define ASSUMING 262
#define ORDER 263
#define WHERE 264
#define GROUP 265
#define BY 266
#define HAVING 267
#define LC_AS 268
#define ROWID 269
#define ODD 270
#define EVEN 271
#define EVERY 272
#define FLATTEN 273
#define CROSS 274
#define JOIN 275
#define NATURAL 276
#define INNER 277
#define OUTER 278
#define LEFT 279
#define RIGHT 280
#define FULL 281
#define ON 282
#define USING 283
#define CREATE 284
#define TABLE 285
#define VIEW 286
#define UPDATE 287
#define SET 288
#define INSERT 289
#define INTO 290
#define VALUES 291
#define DELETE 292
#define AND 293
#define OR 294
#define IS 295
#define NOT 296
#define BETWEEN 297
#define IN 298
#define LIKE 299
#define NULL_KEYWORD 300
#define OVERLAPS 301
#define CASE 302
#define END 303
#define WHEN 304
#define THEN 305
#define ELSE 306
#define TYPE_INT 307
#define TYPE_FLOAT 308
#define TYPE_STRING 309
#define TYPE_DATE 310
#define TYPE_BOOLEAN 311
#define TYPE_BIT 312
#define TYPE_HEX 313
#define FUNCTION 314
#define ASSIGN 315
#define ABS 316
#define AVG 317
#define COUNT 318
#define DISTINCT 319
#define DROP 320
#define FIRST 321
#define LAST 322
#define MAX 323
#define MIN 324
#define MOD 325
#define NEXT 326
#define PREV 327
#define PRD 328
#define REV 329
#define SUM 330
#define STDDEV 331
#define AVGS 332
#define DELTAS 333
#define MAXS 334
#define MINS 335
#define PRDS 336
#define SUMS 337
#define INT 338
#define FLOAT 339
#define STRING 340
#define DATE 341
#define TRUE 342
#define FALSE 343
#define BIT 344
#define HEX 345
#define NULL_VAL 346
#define ID 347
#define TIMES_OP 348
#define DIV_OP 349
#define PLUS_OP 350
#define MINUS_OP 351
#define LE_OP 352
#define GE_OP 353
#define L_OP 354
#define G_OP 355
#define EQ_OP 356
#define NEQ_OP 357
#define AND_OP 358
#define OR_OP 359




/* Copy the first part of user declarations.  */
#line 1 "aquery.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYDEBUG 1
#define ERRORCOLOR  "\x1B[32m"

extern int yyleng;
extern FILE *yyin;
extern int yylex();
extern int yyparse();

//for debugging purposes, defined in flex
extern int line_num; 
extern int col_num;

	
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
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 337 "aquery.tab.c"

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
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   849

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  85
/* YYNRULES -- Number of rules.  */
#define YYNRULES  206
/* YYNRULES -- Number of states.  */
#define YYNSTATES  355

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   359

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     105,   106,     2,     2,   107,     2,   111,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   110,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   112,     2,   113,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   108,     2,   109,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      24,    27,    31,    32,    35,    36,    43,    47,    48,    51,
      55,    56,    62,    66,    70,    72,    76,    77,    80,    84,
      85,    88,    89,    94,    95,    98,    99,   101,   105,   107,
     111,   113,   116,   118,   122,   127,   129,   131,   133,   137,
     139,   141,   143,   145,   147,   149,   151,   157,   164,   168,
     173,   177,   182,   187,   191,   195,   201,   203,   208,   210,
     216,   222,   224,   229,   232,   236,   238,   242,   244,   247,
     251,   252,   254,   257,   259,   261,   263,   265,   268,   270,
     272,   275,   280,   285,   290,   293,   297,   300,   303,   307,
     308,   310,   312,   314,   316,   318,   320,   322,   328,   331,
     335,   336,   340,   346,   350,   351,   353,   358,   362,   366,
     375,   378,   379,   383,   384,   386,   388,   391,   395,   397,
     399,   401,   403,   405,   407,   409,   411,   413,   415,   417,
     421,   427,   429,   430,   433,   436,   437,   442,   445,   446,
     448,   450,   452,   456,   458,   460,   465,   470,   474,   479,
     483,   485,   487,   490,   492,   494,   496,   498,   500,   502,
     504,   506,   508,   510,   512,   514,   516,   518,   520,   522,
     524,   526,   528,   530,   532,   534,   536,   540,   544,   546,
     550,   554,   556,   560,   564,   568,   572,   574,   578,   582,
     584,   588,   590,   594,   596,   599,   603
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     115,     0,    -1,   116,    -1,   117,   116,    -1,   158,   116,
      -1,   168,   116,    -1,   164,   116,    -1,   171,   116,    -1,
     172,   116,    -1,    -1,   118,   124,    -1,     3,   120,   119,
      -1,    -1,   120,   119,    -1,    -1,    92,   121,     4,   105,
     124,   106,    -1,   105,   122,   106,    -1,    -1,    92,   123,
      -1,   107,    92,   123,    -1,    -1,   125,   128,   129,   130,
     131,    -1,     5,   126,   127,    -1,   196,    13,    92,    -1,
     196,    -1,   107,   126,   127,    -1,    -1,     6,   152,    -1,
       7,     8,   122,    -1,    -1,     9,   133,    -1,    -1,    10,
      11,   197,   132,    -1,    -1,    12,   133,    -1,    -1,   134,
      -1,   133,    39,   134,    -1,   135,    -1,   134,    38,   135,
      -1,   136,    -1,    41,   136,    -1,   138,    -1,   138,    40,
     137,    -1,   138,    40,    41,   137,    -1,    87,    -1,    88,
      -1,   139,    -1,   105,   133,   106,    -1,   140,    -1,   196,
      -1,   141,    -1,   142,    -1,   144,    -1,   143,    -1,   145,
      -1,   196,    42,   196,    38,   196,    -1,   196,    41,    42,
     196,    38,   196,    -1,   196,    43,   196,    -1,   196,    41,
      43,   196,    -1,   196,    44,   196,    -1,   196,    41,    44,
     196,    -1,   196,    40,    41,    45,    -1,   196,    40,    45,
      -1,   146,    46,   146,    -1,   105,   196,   107,   196,   106,
      -1,   148,    -1,   148,    19,    20,   147,    -1,   149,    -1,
     149,    21,   154,    20,   148,    -1,   149,   154,    20,   148,
     155,    -1,   150,    -1,   151,   105,   150,   106,    -1,    92,
      92,    -1,    92,    13,    92,    -1,    92,    -1,   105,   147,
     106,    -1,    18,    -1,   147,   153,    -1,   107,   147,   153,
      -1,    -1,    22,    -1,    24,    23,    -1,    24,    -1,    25,
      -1,    23,    -1,    26,    -1,    26,    23,    -1,   156,    -1,
     157,    -1,    27,   133,    -1,    28,   105,   122,   106,    -1,
      29,    30,    92,   159,    -1,    29,    31,    92,   159,    -1,
       4,   117,    -1,   105,   160,   106,    -1,   161,   162,    -1,
      92,   163,    -1,   107,   161,   162,    -1,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      58,    -1,    32,    92,    33,   165,   130,    -1,   167,   166,
      -1,   107,   167,   166,    -1,    -1,    92,   101,   196,    -1,
      34,    35,    92,   169,   170,    -1,   105,   122,   106,    -1,
      -1,   117,    -1,    36,   105,   197,   106,    -1,    37,   128,
     130,    -1,    37,   122,   128,    -1,    59,    92,   105,   122,
     106,   108,   173,   109,    -1,   175,   174,    -1,    -1,   110,
     175,   174,    -1,    -1,   196,    -1,   176,    -1,   118,   124,
      -1,    92,    60,   196,    -1,    83,    -1,    84,    -1,    86,
      -1,    85,    -1,    90,    -1,   137,    -1,    89,    -1,    91,
      -1,    14,    -1,   179,    -1,    93,    -1,    92,   111,    92,
      -1,    47,   181,   182,   185,    48,    -1,   196,    -1,    -1,
     184,   183,    -1,   184,   183,    -1,    -1,    49,   133,    50,
     196,    -1,    51,   196,    -1,    -1,   177,    -1,   178,    -1,
      92,    -1,   105,   196,   106,    -1,   180,    -1,   186,    -1,
     186,   112,   188,   113,    -1,   189,   105,   197,   106,    -1,
     189,   105,   106,    -1,    92,   105,   197,   106,    -1,    92,
     105,   106,    -1,    15,    -1,    16,    -1,    17,    83,    -1,
      61,    -1,    62,    -1,    77,    -1,    63,    -1,    78,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      79,    -1,    69,    -1,    80,    -1,    70,    -1,    71,    -1,
      72,    -1,    73,    -1,    81,    -1,    74,    -1,    75,    -1,
      82,    -1,    76,    -1,   187,    -1,   190,    93,   187,    -1,
     190,    94,   187,    -1,   190,    -1,   191,    95,   190,    -1,
     191,    96,   190,    -1,   191,    -1,   192,    99,   191,    -1,
     192,   100,   191,    -1,   192,    97,   191,    -1,   192,    98,
     191,    -1,   192,    -1,   193,   101,   192,    -1,   193,   102,
     192,    -1,   193,    -1,   194,   103,   193,    -1,   194,    -1,
     195,   104,   194,    -1,   195,    -1,   196,   198,    -1,   107,
     196,   198,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    90,    90,    92,    93,    94,    95,    96,    97,    98,
     103,   105,   106,   109,   110,   113,   115,   116,   119,   121,
     122,   127,   129,   131,   132,   135,   136,   139,   141,   142,
     145,   146,   149,   150,   153,   154,   159,   160,   163,   164,
     167,   168,   171,   172,   173,   176,   176,   178,   178,   180,
     180,   182,   183,   184,   185,   186,   189,   190,   193,   194,
     197,   198,   201,   202,   205,   207,   243,   244,   247,   248,
     249,   252,   253,   256,   257,   258,   259,   262,   264,   266,
     267,   270,   270,   270,   270,   270,   270,   270,   272,   272,
     274,   276,   280,   281,   284,   285,   288,   290,   292,   293,
     296,   296,   296,   296,   296,   296,   296,   300,   302,   304,
     305,   308,   310,   312,   313,   316,   317,   320,   321,   325,
     327,   328,   331,   332,   335,   336,   337,   340,   344,   344,
     344,   344,   344,   344,   344,   344,   346,   346,   346,   348,
     350,   352,   353,   356,   358,   359,   362,   364,   365,   368,
     368,   368,   368,   368,   370,   371,   372,   373,   374,   375,
     378,   378,   378,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   381,   381,   381,   381,   381,
     381,   381,   381,   381,   381,   384,   385,   386,   390,   391,
     392,   395,   396,   397,   398,   399,   402,   403,   404,   407,
     408,   411,   412,   415,   418,   420,   421
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WITH", "UC_AS", "SELECT", "FROM",
  "ASSUMING", "ORDER", "WHERE", "GROUP", "BY", "HAVING", "LC_AS", "ROWID",
  "ODD", "EVEN", "EVERY", "FLATTEN", "CROSS", "JOIN", "NATURAL", "INNER",
  "OUTER", "LEFT", "RIGHT", "FULL", "ON", "USING", "CREATE", "TABLE",
  "VIEW", "UPDATE", "SET", "INSERT", "INTO", "VALUES", "DELETE", "AND",
  "OR", "IS", "NOT", "BETWEEN", "IN", "LIKE", "NULL_KEYWORD", "OVERLAPS",
  "CASE", "END", "WHEN", "THEN", "ELSE", "TYPE_INT", "TYPE_FLOAT",
  "TYPE_STRING", "TYPE_DATE", "TYPE_BOOLEAN", "TYPE_BIT", "TYPE_HEX",
  "FUNCTION", "ASSIGN", "ABS", "AVG", "COUNT", "DISTINCT", "DROP", "FIRST",
  "LAST", "MAX", "MIN", "MOD", "NEXT", "PREV", "PRD", "REV", "SUM",
  "STDDEV", "AVGS", "DELTAS", "MAXS", "MINS", "PRDS", "SUMS", "INT",
  "FLOAT", "STRING", "DATE", "TRUE", "FALSE", "BIT", "HEX", "NULL_VAL",
  "ID", "TIMES_OP", "DIV_OP", "PLUS_OP", "MINUS_OP", "LE_OP", "GE_OP",
  "L_OP", "G_OP", "EQ_OP", "NEQ_OP", "AND_OP", "OR_OP", "'('", "')'",
  "','", "'{'", "'}'", "';'", "'.'", "'['", "']'", "$accept", "program",
  "top_level", "global_query", "local_queries", "local_queries_tail",
  "local_query", "col_aliases", "comma_identifier_list",
  "comma_identifier_list_tail", "base_query", "select_clause",
  "select_elem", "select_clause_tail", "from_clause", "order_clause",
  "where_clause", "groupby_clause", "having_clause", "search_condition",
  "boolean_term", "boolean_factor", "boolean_test", "truth_value",
  "boolean_primary", "predicate", "built_in_pred_expression",
  "between_predicate", "in_predicate", "like_predicate", "null_predicate",
  "overlaps_predicate", "range_value_expression", "joined_table",
  "qualified_join", "table_expression", "table_expression_main",
  "built_in_table_fun", "table_expressions", "table_expressions_tail",
  "join_type", "join_spec", "on_clause", "using_clause",
  "create_table_or_view", "create_spec", "schema", "schema_element",
  "schema_tail", "type_name", "update_statement", "set_clauses",
  "set_clauses_tail", "set_clause", "insert_statement", "insert_modifier",
  "insert_source", "delete_statement", "user_function_definition",
  "function_body", "function_body_tail", "function_body_elem",
  "function_local_var_def", "constant", "table_constant", "column_access",
  "case_expression", "case_clause", "when_clauses", "when_clauses_tail",
  "when_clause", "else_clause", "main_expression", "call", "indexing",
  "built_in_fun", "mult_expression", "add_expression", "rel_expression",
  "eq_expression", "and_expression", "or_expression", "value_expression",
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
     355,   356,   357,   358,   359,    40,    41,    44,   123,   125,
      59,    46,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     117,   118,   118,   119,   119,   120,   121,   121,   122,   123,
     123,   124,   125,   126,   126,   127,   127,   128,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   136,   137,   137,   138,   138,   139,
     139,   140,   140,   140,   140,   140,   141,   141,   142,   142,
     143,   143,   144,   144,   145,   146,   147,   147,   148,   148,
     148,   149,   149,   150,   150,   150,   150,   151,   152,   153,
     153,   154,   154,   154,   154,   154,   154,   154,   155,   155,
     156,   157,   158,   158,   159,   159,   160,   161,   162,   162,
     163,   163,   163,   163,   163,   163,   163,   164,   165,   166,
     166,   167,   168,   169,   169,   170,   170,   171,   171,   172,
     173,   173,   174,   174,   175,   175,   175,   176,   177,   177,
     177,   177,   177,   177,   177,   177,   178,   178,   178,   179,
     180,   181,   181,   182,   183,   183,   184,   185,   185,   186,
     186,   186,   186,   186,   187,   187,   187,   187,   187,   187,
     188,   188,   188,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   190,   190,   190,   191,   191,
     191,   192,   192,   192,   192,   192,   193,   193,   193,   194,
     194,   195,   195,   196,   197,   198,   198
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     0,
       2,     3,     0,     2,     0,     6,     3,     0,     2,     3,
       0,     5,     3,     3,     1,     3,     0,     2,     3,     0,
       2,     0,     4,     0,     2,     0,     1,     3,     1,     3,
       1,     2,     1,     3,     4,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     5,     6,     3,     4,
       3,     4,     4,     3,     3,     5,     1,     4,     1,     5,
       5,     1,     4,     2,     3,     1,     3,     1,     2,     3,
       0,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       2,     4,     4,     4,     2,     3,     2,     2,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     5,     2,     3,
       0,     3,     5,     3,     0,     1,     4,     3,     3,     8,
       2,     0,     3,     0,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       5,     1,     0,     2,     2,     0,     4,     2,     0,     1,
       1,     1,     3,     1,     1,     4,     4,     3,     4,     3,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     2,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     0,     0,     0,     0,     0,     0,     0,     2,     9,
       0,     9,     9,     9,     9,     9,    17,    14,     0,     0,
       0,     0,     0,    20,     0,    31,     0,     1,     3,     0,
      10,     0,     4,     6,     5,     7,     8,     0,     0,    11,
      14,     0,     0,     0,   114,    77,    75,     0,    80,    66,
      68,    71,     0,    27,     0,    18,   118,     0,   117,     0,
     136,   142,   163,   164,   166,   168,   169,   170,   171,   172,
     174,   176,   177,   178,   179,   181,   182,   184,   165,   167,
     173,   175,   180,   183,   128,   129,   131,   130,    45,    46,
     134,   132,   135,   151,   138,     0,    26,   133,   149,   150,
     137,   153,   154,   185,     0,   188,   191,   196,   199,   201,
     203,    24,    29,     0,     0,    13,    12,     0,    92,    93,
       0,    31,   110,     0,    12,     0,    73,     0,     0,    78,
       0,     0,    81,    85,    83,    84,    86,     0,     0,    20,
       0,     0,    30,    36,    38,    40,    42,    47,    49,    51,
      52,    54,    53,    55,     0,    50,     0,     0,   141,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    16,     0,    94,     0,     0,    99,     0,   107,     0,
     108,     0,     0,   115,   112,    74,    76,    80,     0,     0,
      82,    87,     0,     0,    19,    41,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148,
     145,   159,   206,     0,   139,   152,    26,   160,   161,     0,
       0,   157,     0,   186,   187,   189,   190,   194,   195,   192,
     193,   197,   198,   200,   202,    23,     0,    33,     0,   100,
     101,   102,   103,   104,   105,   106,    97,    95,     0,    96,
     111,   110,   113,     0,    79,    67,     0,     0,    72,    48,
       0,    37,    39,     0,    43,     0,    64,     0,    63,     0,
       0,     0,     0,    58,    60,    12,     0,     0,     0,   143,
     145,     0,   204,   158,    25,   162,   155,   156,    28,     0,
      21,    15,    99,   109,     0,    69,     0,     0,    70,    88,
      89,     0,    44,     0,    62,     0,    59,    61,     0,   151,
       0,     0,   123,   125,   124,     0,   147,   140,   144,   206,
       0,    98,   116,    90,     0,    65,     0,    56,     0,   126,
     119,    12,   120,   146,   205,    35,     0,    57,   127,   123,
       0,    32,    91,   122,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    39,    40,    38,    24,    55,
      30,    31,    96,   163,    25,   180,    58,   300,   351,   142,
     143,   144,   145,    97,   146,   147,   148,   149,   150,   151,
     152,   153,   154,    48,    49,    50,    51,    52,    53,   129,
     137,   308,   309,   310,    11,   118,   185,   186,   259,   256,
      12,   121,   190,   122,    13,   124,   194,    14,    15,   321,
     342,   322,   323,    98,    99,   100,   101,   157,   219,   289,
     290,   288,   102,   103,   230,   104,   105,   106,   107,   108,
     109,   110,   155,   223,   292
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -272
static const yytype_int16 yypact[] =
{
      19,   -61,    78,   -59,     1,     3,   -45,    49,  -272,    19,
      50,    19,    19,    19,    19,    19,   -53,   -61,   -19,   -12,
      51,    -6,   -11,    33,    82,   128,    41,  -272,  -272,   664,
    -272,    82,  -272,  -272,  -272,  -272,  -272,    55,   144,  -272,
     -61,     2,     2,    57,    45,  -272,    -3,   -11,    44,   133,
      99,  -272,    52,  -272,    64,  -272,  -272,   584,  -272,    55,
    -272,   664,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,  -272,   -77,  -272,   664,    46,  -272,  -272,  -272,
    -272,  -272,    42,  -272,    54,    17,    31,   -40,    27,    58,
      56,   149,   156,    59,    65,  -272,   161,    77,  -272,  -272,
      70,   128,    66,    55,    18,    80,  -272,    60,   -11,  -272,
     154,    74,  -272,  -272,   152,  -272,   153,   157,   -67,    33,
     744,   584,   139,   141,  -272,  -272,   140,  -272,  -272,  -272,
    -272,  -272,  -272,  -272,   135,    62,    76,   134,  -272,   424,
      92,    83,   664,  -272,    48,   504,   664,   664,   664,   664,
     664,   664,   664,   664,   664,   664,   664,   664,    96,   182,
     128,  -272,    50,  -272,    61,    85,    86,   664,  -272,    57,
    -272,    88,    87,  -272,  -272,  -272,  -272,    44,   -11,   175,
    -272,  -272,   -11,    90,  -272,  -272,   -31,   -24,   584,   584,
     -26,    93,     5,    25,   664,   664,   664,    89,   584,   148,
     134,  -272,    94,    97,  -272,  -272,    46,  -272,  -272,   117,
      91,  -272,   100,  -272,  -272,    17,    17,    31,    31,    31,
      31,   -40,   -40,    27,    58,  -272,    55,   192,   101,  -272,
    -272,  -272,  -272,  -272,  -272,  -272,  -272,  -272,    77,  -272,
    -272,    66,  -272,   664,  -272,  -272,   -11,   104,  -272,  -272,
     664,   141,  -272,    47,  -272,   664,  -272,   160,  -272,   664,
     664,   664,   170,  -272,  -272,   252,   -10,   664,   164,  -272,
     134,   664,  -272,  -272,  -272,  -272,  -272,  -272,  -272,   198,
    -272,  -272,    86,  -272,   107,  -272,   584,   109,  -272,  -272,
    -272,   110,  -272,   108,  -272,   179,  -272,  -272,   664,   -34,
      50,   111,   112,  -272,  -272,   664,  -272,  -272,  -272,    94,
     664,  -272,  -272,   139,    55,  -272,   664,  -272,   664,  -272,
    -272,   344,  -272,  -272,  -272,   206,   113,  -272,  -272,   112,
     584,  -272,  -272,  -272,   139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -272,  -272,    30,   -89,  -271,   181,   222,  -272,   -36,    98,
    -177,  -272,    63,    -2,     6,  -272,  -108,  -272,  -272,  -139,
      20,    21,    95,  -199,  -272,  -272,  -272,  -272,  -272,  -272,
    -272,  -272,    15,   -43,  -190,  -272,   102,  -272,  -272,    32,
     105,  -272,  -272,  -272,  -272,   185,  -272,   -25,   -71,  -272,
    -272,  -272,   -23,    43,  -272,  -272,  -272,  -272,  -272,  -272,
    -110,   -99,  -272,  -272,  -272,  -272,  -272,  -272,  -272,   -47,
     103,  -272,  -272,   -28,  -272,  -272,   -27,   -80,   -30,    68,
      71,  -272,   -29,  -162,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -122
static const yytype_int16 yytable[] =
{
     111,   113,   206,   232,   127,   248,   116,    45,   208,    22,
     125,   274,   267,   188,   320,   273,   212,   213,   214,   215,
     216,     1,     1,   156,   -12,    46,   338,   183,   159,   208,
      56,    16,   158,    20,   160,   193,    21,   112,    47,    28,
     325,    32,    33,    34,    35,    36,   277,    26,     2,    27,
     278,     3,    37,     4,   192,    29,     5,   170,   171,   172,
     173,    88,    89,   227,   228,   229,   161,   279,   280,   281,
     320,   159,   247,    41,   312,   269,   305,   160,     6,   286,
      42,    46,   225,   270,    43,   197,    44,   191,    22,   126,
     237,   238,   239,   240,    47,    23,   132,   133,   134,   135,
     136,   304,   212,   213,   214,   215,   216,   117,    18,    19,
     166,   167,   207,   249,   250,   251,   252,   253,   254,   255,
     131,   132,   133,   134,   135,   136,   168,   169,   174,   175,
     222,   306,   307,   111,    88,    89,   222,    57,   233,   234,
      54,   235,   236,   339,   241,   242,    59,    23,   114,   120,
     123,   128,   130,   162,   164,   265,   139,   138,   260,   165,
     177,   176,   178,   179,     1,   181,   196,   333,   345,   184,
     182,   187,   195,   189,   198,   200,   201,   202,   208,   209,
     210,   211,   217,   218,   224,   282,   283,   284,   245,   225,
     246,   257,   263,   258,   262,   266,   268,   285,   275,   287,
     295,   291,   299,   293,   296,   314,   297,   301,   318,   330,
     298,   354,   327,   332,   334,   270,   335,   336,   350,   352,
     340,   115,   341,    17,   294,   226,   276,   119,   271,   264,
     272,   331,   261,   302,   222,   205,   199,   204,   303,   353,
     203,   311,   349,   328,   243,   344,   313,     0,   244,     0,
     315,   316,   317,     0,     0,     1,   324,     0,   326,     0,
     220,     0,   329,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   337,
       0,     0,     0,     0,     0,     0,   343,     0,   346,    61,
       0,   222,     0,     0,     0,     0,     0,   347,     0,   348,
       0,     0,   324,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,   319,    94,     0,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    60,     0,
       0,  -121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,   319,    94,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
     231,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   140,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141
};

static const yytype_int16 yycheck[] =
{
      29,    37,   141,   165,    47,   182,     4,    18,    39,     6,
      13,   210,   202,   121,   285,    41,    40,    41,    42,    43,
      44,     3,     3,    59,     5,    92,    60,   116,   105,    39,
      24,    92,    61,    92,   111,   124,    35,    31,   105,     9,
      50,    11,    12,    13,    14,    15,    41,    92,    29,     0,
      45,    32,   105,    34,    36,     5,    37,    97,    98,    99,
     100,    87,    88,    15,    16,    17,    95,    42,    43,    44,
     341,   105,   180,    92,   273,   106,   266,   111,    59,   218,
      92,    92,   106,   107,    33,   128,    92,   123,     6,    92,
     170,   171,   172,   173,   105,    92,    22,    23,    24,    25,
      26,   263,    40,    41,    42,    43,    44,   105,    30,    31,
      93,    94,   141,    52,    53,    54,    55,    56,    57,    58,
      21,    22,    23,    24,    25,    26,    95,    96,   101,   102,
     159,    27,    28,   162,    87,    88,   165,     9,   166,   167,
     107,   168,   169,   320,   174,   175,   105,    92,     4,    92,
     105,   107,    19,   107,   112,   198,    92,   105,   187,   105,
     104,   103,    13,     7,     3,   106,   106,   306,   330,    92,
     105,   101,    92,   107,    20,    23,    23,    20,    39,    38,
      40,    46,   106,    49,    92,   214,   215,   216,    92,   106,
       8,   106,   105,   107,   106,    20,   106,   108,   105,    51,
      83,   107,    10,   106,   113,    45,   106,   106,    38,    11,
     246,   350,    48,   106,   105,   107,   106,    38,    12,   106,
     109,    40,   110,     1,   226,   162,   211,    42,   208,   197,
     209,   302,   189,   258,   263,   140,   131,   139,   261,   349,
     138,   270,   341,   290,   176,   329,   275,    -1,   177,    -1,
     279,   280,   281,    -1,    -1,     3,   285,    -1,   287,    -1,
     157,    -1,   291,    -1,    -1,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   318,
      -1,    -1,    -1,    -1,    -1,    -1,   325,    -1,   334,    47,
      -1,   330,    -1,    -1,    -1,    -1,    -1,   336,    -1,   338,
      -1,    -1,   341,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    14,    -1,
      -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    29,    32,    34,    37,    59,   115,   116,   117,
     118,   158,   164,   168,   171,   172,    92,   120,    30,    31,
      92,    35,     6,    92,   122,   128,    92,     0,   116,     5,
     124,   125,   116,   116,   116,   116,   116,   105,   121,   119,
     120,    92,    92,    33,    92,    18,    92,   105,   147,   148,
     149,   150,   151,   152,   107,   123,   128,     9,   130,   105,
      14,    47,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,   105,   126,   137,   177,   178,
     179,   180,   186,   187,   189,   190,   191,   192,   193,   194,
     195,   196,   128,   122,     4,   119,     4,   105,   159,   159,
      92,   165,   167,   105,   169,    13,    92,   147,   107,   153,
      19,    21,    22,    23,    24,    25,    26,   154,   105,    92,
      41,   105,   133,   134,   135,   136,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   196,   122,   181,   196,   105,
     111,   196,   107,   127,   112,   105,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    13,     7,
     129,   106,   105,   117,    92,   160,   161,   101,   130,   107,
     166,   122,    36,   117,   170,    92,   106,   147,    20,   154,
      23,    23,    20,   150,   123,   136,   133,   196,    39,    38,
      40,    46,    40,    41,    42,    43,    44,   106,    49,   182,
     184,   106,   196,   197,    92,   106,   126,    15,    16,    17,
     188,   106,   197,   187,   187,   190,   190,   191,   191,   191,
     191,   192,   192,   193,   194,    92,     8,   130,   124,    52,
      53,    54,    55,    56,    57,    58,   163,   106,   107,   162,
     196,   167,   106,   105,   153,   147,    20,   148,   106,   106,
     107,   134,   135,    41,   137,   105,   146,    41,    45,    42,
      43,    44,   196,   196,   196,   108,   133,    51,   185,   183,
     184,   107,   198,   106,   127,    83,   113,   106,   122,    10,
     131,   106,   161,   166,   197,   148,    27,    28,   155,   156,
     157,   196,   137,   196,    45,   196,   196,   196,    38,    92,
     118,   173,   175,   176,   196,    50,   196,    48,   183,   196,
      11,   162,   106,   133,   105,   106,    38,   196,    60,   124,
     109,   110,   174,   196,   198,   197,   122,   196,   196,   175,
      12,   132,   106,   174,   133
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
      
/* Line 1267 of yacc.c.  */
#line 2002 "aquery.tab.c"
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


#line 427 "aquery.y"


void yyerror(const char *s) 
{
	//TODO: handle end of file errors
	//rewind file and find error
	rewind(yyin);
	int lines = line_num, cols = col_num;
	size_t max_size = 256;
	
	char *line = NULL;
	char *marker = malloc(sizeof(char) * (col_num + 2));
	memset(marker, ' ', col_num + 1);
	marker[col_num - yyleng] = '^';
	marker[col_num + 1] = '\0';
	
	while(lines-- > 0) 
	{ //find line with error
		getline(&line, &max_size, yyin);
	}
	
	printf("%s at line %d, column %d\n%s" ERRORCOLOR "%s\n", s, line_num, col_num, line,marker);
	fclose(yyin);
	exit(1);
}

int main(int argc, char *argv[]) {
	
	yydebug = 1;
	
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
	
	do 
	{
		yyparse();
	} 
	while(!feof(yyin));
	
	printf("File conforms to Aquery grammar... now on to building AST\n");
}


