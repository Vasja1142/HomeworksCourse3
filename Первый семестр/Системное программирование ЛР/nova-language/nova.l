%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nova.tab.h"
%}

%option noyywrap
%option yylineno

DIGIT       [0-9]
LETTER      [a-zA-Z_]
INT_NUM     {DIGIT}+
FLOAT_NUM   {DIGIT}+"."{DIGIT}+
STRING      \"([^\\\"]|\\.)*\"
ID          {LETTER}({LETTER}|{DIGIT})*

%%

"#".*       { /* Игнорируем комментарии */ }

"---"       { return T_BLOCK_END; }

"int"       { return T_TYPE_INT; }
"float"     { return T_TYPE_FLOAT; }
"str"       { return T_TYPE_STR; }
"list"      { return T_TYPE_LIST; }

"if"        { return T_IF; }
"else"      { return T_ELSE; }
"loop"      { return T_LOOP; }
"while"     { return T_WHILE; }

"func"      { return T_FUNC; }
"return"    { return T_RETURN; }
"entry"     { return T_ENTRY; }

">>>"       { return T_PRINT_OP; }
"^"         { return T_INPUT_OP; }

"["         { return T_LBRACKET; }
"]"         { return T_RBRACKET; }
"("         { return T_LPAREN; }
")"         { return T_RPAREN; }
","         { return T_COMMA; }

"="         { return T_ASSIGN; }
"=="        { return T_EQ; }
"!="        { return T_NEQ; }
">"         { return T_GT; }
"<"         { return T_LT; }
"+"         { return T_PLUS; }
"-"         { return T_MINUS; }
"*"         { return T_MUL; }
"/"         { return T_DIV; }

{FLOAT_NUM} { yylval.str_val = strdup(yytext); return T_VAL_FLOAT; }
{INT_NUM}   { yylval.str_val = strdup(yytext); return T_VAL_INT; }
{STRING}    { yylval.str_val = strdup(yytext); return T_VAL_STR; }
{ID}        { yylval.str_val = strdup(yytext); return T_ID; }

[\n]        { return T_NEWLINE; }
[ \t\r]+    { /* Игнорируем пробелы */ }

.           { fprintf(stderr, "Lexer Error: Unknown char '%s' at line %d\n", yytext, yylineno); exit(1); }

%%