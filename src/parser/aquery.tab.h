/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 274 "parser/aquery.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

