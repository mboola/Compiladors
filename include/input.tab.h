/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INPUT_TAB_H_INCLUDED
# define YY_YY_INPUT_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 15 "bison/input.y"

	/* Les definicions que s'utilitzen al %union han d'estar aqui */
	#include "data_types.h"

#line 54 "input.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INTEGER_TKN = 258,             /* INTEGER_TKN  */
    FLOAT_TKN = 259,               /* FLOAT_TKN  */
    ID_TKN = 260,                  /* ID_TKN  */
    NEWLINE_TKN = 261,             /* NEWLINE_TKN  */
    ASSIGN = 262,                  /* ASSIGN  */
    OPENPAR = 263,                 /* OPENPAR  */
    CLOSEDPAR = 264,               /* CLOSEDPAR  */
    ADDITION = 265,                /* ADDITION  */
    SUBSTRACTION = 266,            /* SUBSTRACTION  */
    POWER = 267,                   /* POWER  */
    MULTIPLICATION = 268,          /* MULTIPLICATION  */
    DIVISION = 269,                /* DIVISION  */
    MOD = 270,                     /* MOD  */
    SIN = 271,                     /* SIN  */
    COS = 272,                     /* COS  */
    TAN = 273,                     /* TAN  */
    OCT = 274,                     /* OCT  */
    BIN = 275,                     /* BIN  */
    HEX = 276,                     /* HEX  */
    DEC = 277,                     /* DEC  */
    RIC = 278,                     /* RIC  */
    REPEAT = 279,                  /* REPEAT  */
    DONE = 280,                    /* DONE  */
    DO = 281                       /* DO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "bison/input.y"

    int *integer;
    float *real;
    t_id id;
    t_expression expression_type;
    t_assignment assignment_type;
    t_repeat repeat_type;
    void *no_value;

#line 107 "input.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INPUT_TAB_H_INCLUDED  */
