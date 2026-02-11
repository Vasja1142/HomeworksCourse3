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

#ifndef YY_YY_NOVA_TAB_H_INCLUDED
# define YY_YY_NOVA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_TYPE_INT = 258,              /* T_TYPE_INT  */
    T_TYPE_FLOAT = 259,            /* T_TYPE_FLOAT  */
    T_TYPE_STR = 260,              /* T_TYPE_STR  */
    T_TYPE_LIST = 261,             /* T_TYPE_LIST  */
    T_IF = 262,                    /* T_IF  */
    T_ELSE = 263,                  /* T_ELSE  */
    T_LOOP = 264,                  /* T_LOOP  */
    T_WHILE = 265,                 /* T_WHILE  */
    T_BLOCK_END = 266,             /* T_BLOCK_END  */
    T_FUNC = 267,                  /* T_FUNC  */
    T_RETURN = 268,                /* T_RETURN  */
    T_ENTRY = 269,                 /* T_ENTRY  */
    T_PRINT_OP = 270,              /* T_PRINT_OP  */
    T_INPUT_OP = 271,              /* T_INPUT_OP  */
    T_ASSIGN = 272,                /* T_ASSIGN  */
    T_EQ = 273,                    /* T_EQ  */
    T_NEQ = 274,                   /* T_NEQ  */
    T_GT = 275,                    /* T_GT  */
    T_LT = 276,                    /* T_LT  */
    T_PLUS = 277,                  /* T_PLUS  */
    T_MINUS = 278,                 /* T_MINUS  */
    T_MUL = 279,                   /* T_MUL  */
    T_DIV = 280,                   /* T_DIV  */
    T_LBRACKET = 281,              /* T_LBRACKET  */
    T_RBRACKET = 282,              /* T_RBRACKET  */
    T_LPAREN = 283,                /* T_LPAREN  */
    T_RPAREN = 284,                /* T_RPAREN  */
    T_COMMA = 285,                 /* T_COMMA  */
    T_NEWLINE = 286,               /* T_NEWLINE  */
    T_ID = 287,                    /* T_ID  */
    T_VAL_INT = 288,               /* T_VAL_INT  */
    T_VAL_FLOAT = 289,             /* T_VAL_FLOAT  */
    T_VAL_STR = 290                /* T_VAL_STR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 77 "nova.y"

    char* str_val;

#line 103 "nova.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_NOVA_TAB_H_INCLUDED  */
