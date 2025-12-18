%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int yylex();
void yyerror(const char *s);
extern int yylineno; // Ссылка на счетчик строк из Lex

/* --- ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ --- */
char *FINAL_CODE = NULL;

/* Функция для склеивания строк */
char* concat(int count, ...) {
    va_list ap;
    int len = 0;
    
    va_start(ap, count);
    for(int i=0; i<count; i++) {
        char* s = va_arg(ap, char*);
        if(s) len += strlen(s);
    }
    va_end(ap);
    
    char* res = (char*)calloc(len + 1, 1);
    if(!res) return NULL;
    
    va_start(ap, count);
    for(int i=0; i<count; i++) {
        char* s = va_arg(ap, char*);
        if(s) strcat(res, s);
    }
    va_end(ap);
    return res;
}

const char* LIB_CODE = 
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"#include <time.h>\n"
"void print_int(int x) { printf(\"%d\\n\", x); }\n"
"void print_double(double x) { printf(\"%.2f\\n\", x); }\n"
"void print_string(char* x) { printf(\"%s\\n\", x); }\n"
"#define print_any(x) _Generic((x), int: print_int, double: print_double, char*: print_string)(x)\n"
"void fill_fibonacci_range(int *arr, int start_idx, int end_idx) {\n"
"    int f[1000]; f[0] = 0; f[1] = 1;\n"
"    for(int i=2; i<=end_idx; i++) f[i] = f[i-1] + f[i-2];\n"
"    int arr_i = 0;\n"
"    for(int i=start_idx; i<=end_idx; i++) arr[arr_i++] = f[i];\n"
"}\n"
"void file_write(char* filename, char* text) {\n"
"    FILE *f = fopen(filename, \"w\");\n"
"    if (f) { fprintf(f, \"%s\\n\", text); fclose(f); printf(\"[LOG] File created: %s\\n\", filename); }\n"
"    else { printf(\"[ERROR] Write failed: %s\\n\", filename); }\n"
"}\n"
"void file_append(char* filename, char* text) {\n"
"    FILE *f = fopen(filename, \"a\");\n"
"    if (f) { fprintf(f, \"%s\\n\", text); fclose(f); printf(\"[LOG] Data appended: %s\\n\", filename); }\n"
"    else { printf(\"[ERROR] Append failed: %s\\n\", filename); }\n"
"}\n"
"int random_int(int min, int max) { return min + rand() % (max - min + 1); }\n"
"int get_int() { char buf[100]; printf(\"> \"); fflush(stdout); if (!fgets(buf, 100, stdin)) exit(0); return atoi(buf); }\n"
"double get_float() { char buf[100]; printf(\"> \"); fflush(stdout); if (!fgets(buf, 100, stdin)) exit(0); return strtod(buf, NULL); }\n"
"char* get_str() { char buf[256]; printf(\"> \"); fflush(stdout); if (!fgets(buf, 256, stdin)) exit(0); buf[strcspn(buf, \"\\n\")] = 0; return strdup(buf); }\n"
"void get_list(int *arr, int max_size) {\n"
"    char buf[1024]; printf(\"> \"); fflush(stdout);\n"
"    if (!fgets(buf, 1024, stdin)) exit(1); buf[strcspn(buf, \"\\n\")] = 0;\n"
"    char *token = strtok(buf, \" \"); int i = 0;\n"
"    while (token != NULL && i < max_size) { arr[i++] = atoi(token); token = strtok(NULL, \" \"); }\n"
"}\n\n";

%}

%union {
    char* str_val;
}

%token T_TYPE_INT T_TYPE_FLOAT T_TYPE_STR T_TYPE_LIST
%token T_IF T_ELSE T_LOOP T_WHILE T_BLOCK_END
%token T_FUNC T_RETURN T_ENTRY
%token T_PRINT_OP T_INPUT_OP 
%token T_ASSIGN T_EQ T_NEQ T_GT T_LT T_PLUS T_MINUS T_MUL T_DIV
%token T_LBRACKET T_RBRACKET T_LPAREN T_RPAREN T_COMMA
%token T_NEWLINE

%token <str_val> T_ID T_VAL_INT T_VAL_FLOAT T_VAL_STR

%left T_PLUS T_MINUS
%left T_MUL T_DIV

%type <str_val> program functions function_def func_args entry_point 
%type <str_val> statements statement declaration assignment print_stmt 
%type <str_val> if_block while_block loop_block return_stmt void_func_call
%type <str_val> expression value cmp_op call_args call_arg_list if_head

%%

/* ГЛАВНОЕ ПРАВИЛО */
program:
    functions entry_point footer_opt
    {
        FINAL_CODE = concat(3, LIB_CODE, ($1 ? $1 : ""), ($2 ? $2 : ""));
        if ($1) free($1);
        if ($2) free($2);
    }
    ;

footer_opt:
      /* пусто */
    | footer_opt T_NEWLINE
    ;

/* Функции + пустые строки между ними */
functions:
      /* пусто */ { $$ = NULL; }
    | functions function_def { 
        if ($1) {
            $$ = concat(2, $1, $2);
            free($1); free($2);
        } else {
            $$ = $2;
        }
    }
    | functions T_NEWLINE { $$ = $1; }
    ;

function_def:
    T_FUNC T_ID T_LPAREN func_args T_RPAREN T_NEWLINE statements T_BLOCK_END
    {
        char *header;
        asprintf(&header, "int %s(%s) {\n", $2, $4);
        $$ = concat(3, header, $7, "}\n\n");
        free(header); free($4); free($7);
    }
    ;

func_args:
      /* пусто */ { $$ = strdup(""); }
    | T_ID { 
        asprintf(&$$, "int %s", $1); 
      }
    | T_ID T_COMMA T_ID { 
        asprintf(&$$, "int %s, int %s", $1, $3); 
      }
    ;

/* Правило entry_point: допускает отсутствие '---' в конце */
entry_point:
    T_ENTRY T_NEWLINE statements end_block_opt
    {
        char *main_header = "int main() {\n\tsrand(time(NULL));\n";
        char *main_footer = "\n\treturn 0;\n}\n";
        $$ = concat(3, main_header, $3, main_footer);
        free($3);
    }
    ;

end_block_opt:
      T_BLOCK_END
    | /* пусто (для случая конца файла) */
    ;

statements:
      /* пусто */ { $$ = strdup(""); }
    | statements statement { 
        char *temp = concat(2, $1, $2);
        free($1); free($2);
        $$ = temp;
    }
    ;

statement:
      T_NEWLINE { $$ = strdup(""); }
    | declaration
    | assignment
    | print_stmt
    | if_block
    | loop_block
    | while_block
    | return_stmt
    | void_func_call 
    ;

declaration:
      T_TYPE_INT T_ID T_ASSIGN expression T_NEWLINE
      { asprintf(&$$, "\tint %s = %s;\n", $2, $4); free($2); free($4); }
      
    | T_TYPE_FLOAT T_ID T_ASSIGN expression T_NEWLINE
      { asprintf(&$$, "\tdouble %s = %s;\n", $2, $4); free($2); free($4); }
      
    | T_TYPE_STR T_ID T_ASSIGN expression T_NEWLINE
      { asprintf(&$$, "\tchar *%s = %s;\n", $2, $4); free($2); free($4); }
    
    | T_TYPE_LIST T_ID T_ASSIGN T_ID T_LPAREN expression T_COMMA expression T_RPAREN T_NEWLINE
      {
         if (strcmp($4, "fibonacci") == 0) {
             asprintf(&$$, "\tint %s[100];\n\tfill_fibonacci_range(%s, %s, %s);\n", $2, $2, $6, $8);
         } else {
             $$ = strdup("\t/* Unknown list func */\n");
         }
         free($2); free($4); free($6); free($8);
      }
      
    | T_TYPE_INT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { asprintf(&$$, "\tint %s = get_int();\n", $2); free($2); }
      
    | T_TYPE_FLOAT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { asprintf(&$$, "\tdouble %s = get_float();\n", $2); free($2); }
      
    | T_TYPE_STR T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { asprintf(&$$, "\tchar *%s = get_str();\n", $2); free($2); }
      
    | T_TYPE_LIST T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { asprintf(&$$, "\tint %s[100] = {0};\n\tget_list(%s, 100);\n", $2, $2); free($2); }
    ;

assignment:
      T_ID T_ASSIGN expression T_NEWLINE
      { asprintf(&$$, "\t%s = %s;\n", $1, $3); free($1); free($3); }
    ;

print_stmt:
      T_PRINT_OP expression T_NEWLINE
      { asprintf(&$$, "\tprint_any(%s);\n", $2); free($2); }
    ;

if_head:
      T_IF expression cmp_op expression T_NEWLINE 
      { 
          asprintf(&$$, "\tif (%s %s %s) {\n", $2, $3, $4); 
          free($2); free($3); free($4);
      }
    ;

if_block:
      if_head statements T_BLOCK_END
      { 
          $$ = concat(3, $1, $2, "\t}\n"); 
          free($1); free($2);
      }
    | if_head statements T_ELSE T_NEWLINE statements T_BLOCK_END
      { 
          $$ = concat(5, $1, $2, "\t} else {\n", $5, "\t}\n");
          free($1); free($2); free($5);
      }
    ;

while_block:
      T_WHILE expression cmp_op expression T_NEWLINE statements T_BLOCK_END
      {
          char *head;
          asprintf(&head, "\twhile (%s %s %s) {\n", $2, $3, $4);
          $$ = concat(3, head, $6, "\t}\n");
          free(head); free($2); free($3); free($4); free($6);
      }
    ;

loop_block:
      T_LOOP expression T_NEWLINE statements T_BLOCK_END
      {
          char *head;
          asprintf(&head, "\tfor(int _i=0; _i < (int)(%s); _i++) {\n", $2);
          $$ = concat(3, head, $4, "\t}\n");
          free(head); free($2); free($4);
      }
    ;

return_stmt:
      T_RETURN expression T_NEWLINE
      { asprintf(&$$, "\treturn %s;\n", $2); free($2); }
    ;

void_func_call:
      T_ID T_LPAREN call_args T_RPAREN T_NEWLINE
      { asprintf(&$$, "\t%s(%s);\n", $1, $3); free($1); free($3); }
    ;

expression:
      value { $$ = $1; }
    | expression T_PLUS expression  { asprintf(&$$, "%s + %s", $1, $3); free($1); free($3); }
    | expression T_MINUS expression { asprintf(&$$, "%s - %s", $1, $3); free($1); free($3); }
    | expression T_MUL expression   { asprintf(&$$, "%s * %s", $1, $3); free($1); free($3); }
    | expression T_DIV expression   { asprintf(&$$, "%s / %s", $1, $3); free($1); free($3); }
    
    | T_ID T_LPAREN call_args T_RPAREN
      { 
        if (strcmp($1, "random") == 0) asprintf(&$$, "random_int(%s)", $3);
        else asprintf(&$$, "%s(%s)", $1, $3);
        free($1); free($3);
      }
    ;

call_args:
      /* пусто */ { $$ = strdup(""); }
    | call_arg_list { $$ = $1; }
    ;

call_arg_list:
      expression { $$ = $1; }
    | expression T_COMMA call_arg_list { 
        asprintf(&$$, "%s, %s", $1, $3); 
        free($1); free($3);
    }
    ;

cmp_op:
      T_GT { $$ = strdup(">"); }
    | T_LT { $$ = strdup("<"); }
    | T_EQ { $$ = strdup("=="); }
    | T_NEQ { $$ = strdup("!="); }
    ;

value:
      T_ID { $$ = strdup($1); }
    | T_VAL_INT { $$ = strdup($1); }
    | T_VAL_FLOAT { $$ = strdup($1); }
    | T_VAL_STR { $$ = strdup($1); }
    | T_ID T_LBRACKET expression T_RBRACKET {
        asprintf(&$$, "%s[%s]", $1, $3);
        free($1); free($3);
    }
    ;

%%

void yyerror(const char *s) { 
    fprintf(stderr, "Parsing Error at line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        extern FILE *yyin;
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror(argv[1]); return 1; }
    }
    
    /* Парсинг */
    if (yyparse() == 0 && FINAL_CODE != NULL) {
        /* Успешный парсинг */
        printf("%s", FINAL_CODE);
        free(FINAL_CODE);
    } else {
        /* Ошибка парсинга */
        printf("%s", LIB_CODE);
        printf("int main() { printf(\"FATAL ERROR: Parsing failed! Check line %d.\\n\"); return 1; }\n", yylineno);
    }
    
    return 0;
}