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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

