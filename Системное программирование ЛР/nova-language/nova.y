%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int yylex();
void yyerror(const char *s);
%}

%union {
    char* str_val;
}

/* Типы и ключевые слова */
%token T_TYPE_INT T_TYPE_FLOAT T_TYPE_STR T_TYPE_LIST
%token T_IF T_ELSE T_LOOP T_WHILE T_BLOCK_END
%token T_FUNC T_RETURN T_ENTRY
%token T_PRINT_OP T_INPUT_OP 
%token T_ASSIGN T_EQ T_NEQ T_GT T_LT T_PLUS T_MINUS T_MUL T_DIV
%token T_LBRACKET T_RBRACKET T_LPAREN T_RPAREN T_COMMA
%token T_NEWLINE

/* Значения */
%token <str_val> T_ID T_VAL_INT T_VAL_FLOAT T_VAL_STR

/* Приоритеты */
%left T_PLUS T_MINUS
%left T_MUL T_DIV

/* Типы нетерминалов */
%type <str_val> expression value cmp_op call_args call_arg_list func_args

%%

/* --- ГЛАВНАЯ СТРУКТУРА ПРОГРАММЫ --- */

program:
    header functions entry_point
    ;

header:
    {
        /* ГЕНЕРАЦИЯ БИБЛИОТЕКИ C */
        printf("#include <stdio.h>\n");
        printf("#include <stdlib.h>\n");
        printf("#include <string.h>\n");
        printf("#include <time.h>\n");

        printf("#define print_any(x) _Generic((x), \\\n");
        printf("    int: printf(\"%%d\\n\", x), \\\n");
        printf("    double: printf(\"%%.2f\\n\", x), \\\n");
        printf("    char*: printf(\"%%s\\n\", x) \\\n");
        printf(")\n\n");

        /* 1. ФИБОНАЧЧИ */
        printf("void fill_fibonacci_range(int *arr, int start_idx, int end_idx) {\n");
        printf("    int f[1000];\n");
        printf("    f[0] = 0; f[1] = 1;\n");
        printf("    for(int i=2; i<=end_idx; i++) f[i] = f[i-1] + f[i-2];\n");
        printf("    int arr_i = 0;\n");
        printf("    for(int i=start_idx; i<=end_idx; i++) {\n");
        printf("        arr[arr_i++] = f[i];\n");
        printf("    }\n");
        printf("}\n\n");

        /* 2. ФАЙЛЫ: ЗАПИСЬ (ПЕРЕЗАПИСЬ) */
        printf("void file_write(char* filename, char* text) {\n");
        printf("    FILE *f = fopen(filename, \"w\");\n");
        printf("    if (f) {\n");
        printf("        fprintf(f, \"%%s\\n\", text);\n");
        printf("        fclose(f);\n");
        printf("        printf(\"[LOG] File created: %%s\\n\", filename);\n");
        printf("    } else { printf(\"[ERROR] Cannot open file %%s\\n\", filename); }\n");
        printf("}\n\n");

        /* 3. ФАЙЛЫ: ДОБАВЛЕНИЕ (APPEND) - НОВОЕ! */
        printf("void file_append(char* filename, char* text) {\n");
        printf("    FILE *f = fopen(filename, \"a\");\n"); /* "a" значит append */
        printf("    if (f) {\n");
        printf("        fprintf(f, \"%%s\\n\", text);\n");
        printf("        fclose(f);\n");
        printf("        printf(\"[LOG] Data appended to: %%s\\n\", filename);\n");
        printf("    } else { printf(\"[ERROR] Cannot open file %%s\\n\", filename); }\n");
        printf("}\n\n");

        /* 4. RANDOM */
        printf("int random_int(int min, int max) {\n");
        printf("    return min + rand() %% (max - min + 1);\n");
        printf("}\n\n");

        /* 5. ВВОД */
        printf("int get_int() {\n");
        printf("    char buf[100]; printf(\"> \"); fflush(stdout);\n");
        printf("    if (!fgets(buf, 100, stdin)) exit(0);\n");
        printf("    return atoi(buf);\n");
        printf("}\n");

        printf("char* get_str() {\n");
        printf("    char buf[256]; printf(\"> \"); fflush(stdout);\n");
        printf("    if (!fgets(buf, 256, stdin)) exit(0);\n");
        printf("    buf[strcspn(buf, \"\\n\")] = 0;\n");
        printf("    return strdup(buf);\n");
        printf("}\n\n");
        
        printf("/* --- КОНЕЦ БИБЛИОТЕКИ --- */\n\n");
    }
    ;

functions:
    | functions function_def
    | functions T_NEWLINE 
    ;

function_def:
    T_FUNC T_ID T_LPAREN func_args T_RPAREN T_NEWLINE
    {
        printf("int %s(%s) {\n", $2, $4); 
    }
    statements T_BLOCK_END
    { printf("}\n\n"); }
    ;

func_args:
      /* пусто */ { $$ = ""; }
    | T_ID { 
        char b[100]; sprintf(b, "int %s", $1); $$ = strdup(b); 
      }
    | T_ID T_COMMA T_ID { 
        char b[200]; sprintf(b, "int %s, int %s", $1, $3); $$ = strdup(b); 
      }
    ;
    
entry_point:
    T_ENTRY T_NEWLINE
    {
        printf("int main() {\n");
        printf("    srand(time(NULL));\n");
    }
    statements T_BLOCK_END
    {
        /* main закрывается внизу */
    }
    ;

/* --- ОПЕРАТОРЫ --- */

statements:
    | statements statement
    ;

statement:
      T_NEWLINE 
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
      { printf("\tint %s = %s;\n", $2, $4); }
    | T_TYPE_FLOAT T_ID T_ASSIGN expression T_NEWLINE
      { printf("\tdouble %s = %s;\n", $2, $4); }
    | T_TYPE_STR T_ID T_ASSIGN expression T_NEWLINE
      { printf("\tchar *%s = %s;\n", $2, $4); }
    
    /* FIBONACCI */
    | T_TYPE_LIST T_ID T_ASSIGN T_ID T_LPAREN expression T_COMMA expression T_RPAREN T_NEWLINE
      {
         if (strcmp($4, "fibonacci") == 0) {
             printf("\tint %s[100];\n", $2);
             printf("\tfill_fibonacci_range(%s, %s, %s);\n", $2, $6, $8);
         } else {
             printf("\t/* Unknown list func */\n");
         }
      }
      
    | T_TYPE_INT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { printf("\tint %s = get_int();\n", $2); }
    | T_TYPE_STR T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { printf("\tchar *%s = get_str();\n", $2); }
    ;

assignment:
      T_ID T_ASSIGN expression T_NEWLINE
      { printf("\t%s = %s;\n", $1, $3); }
    ;

print_stmt:
      T_PRINT_OP expression T_NEWLINE
      { printf("\tprint_any(%s);\n", $2); }
    ;

if_head:
      T_IF expression cmp_op expression T_NEWLINE 
      { printf("\tif (%s %s %s) {\n", $2, $3, $4); }
    ;

if_block:
      if_head statements T_BLOCK_END
      { printf("\t}\n"); }
    | if_head statements T_ELSE T_NEWLINE 
      { printf("\t} else {\n"); } 
      statements T_BLOCK_END
      { printf("\t}\n"); }
    ;

while_block:
      T_WHILE expression cmp_op expression T_NEWLINE
      { printf("\twhile (%s %s %s) {\n", $2, $3, $4); }
      statements T_BLOCK_END
      { printf("\t}\n"); }
    ;

loop_block:
      T_LOOP expression T_NEWLINE
      { printf("\tfor(int _i=0; _i < (int)(%s); _i++) {\n", $2); }
      statements T_BLOCK_END
      { printf("\t}\n"); }
    ;

return_stmt:
      T_RETURN expression T_NEWLINE
      { printf("\treturn %s;\n", $2); }
    ;

void_func_call:
      T_ID T_LPAREN call_args T_RPAREN T_NEWLINE
      { printf("\t%s(%s);\n", $1, $3); }
    ;

/* --- ВЫРАЖЕНИЯ --- */

expression:
      value { $$ = $1; }
    | expression T_PLUS expression  { char b[100]; sprintf(b, "%s + %s", $1, $3); $$ = strdup(b); }
    | expression T_MINUS expression { char b[100]; sprintf(b, "%s - %s", $1, $3); $$ = strdup(b); }
    | expression T_MUL expression   { char b[100]; sprintf(b, "%s * %s", $1, $3); $$ = strdup(b); }
    | expression T_DIV expression   { char b[100]; sprintf(b, "%s / %s", $1, $3); $$ = strdup(b); }
    
    | T_ID T_LPAREN call_args T_RPAREN
      { 
        char b[100]; 
        if (strcmp($1, "random") == 0) sprintf(b, "random_int(%s)", $3);
        else sprintf(b, "%s(%s)", $1, $3); 
        $$ = strdup(b);
      }
    ;

call_args:
      /* пусто */ { $$ = "0, 0"; } 
    | call_arg_list { $$ = $1; }
    ;

call_arg_list:
      expression { $$ = $1; }
    | expression T_COMMA call_arg_list { char b[200]; sprintf(b, "%s, %s", $1, $3); $$ = strdup(b); }
    ;

cmp_op:
      T_GT { $$ = ">"; }
    | T_LT { $$ = "<"; }
    | T_EQ { $$ = "=="; }
    | T_NEQ { $$ = "!="; }
    ;

value:
      T_ID { $$ = $1; }
    | T_VAL_INT { $$ = $1; }
    | T_VAL_FLOAT { $$ = $1; }
    | T_VAL_STR { $$ = $1; }
    | T_ID T_LBRACKET expression T_RBRACKET {
        char buf[100]; sprintf(buf, "%s[%s]", $1, $3); $$ = strdup(buf);
    }
    ;

%%

void yyerror(const char *s) { fprintf(stderr, "Error: %s\n", s); }

int main(int argc, char **argv) {
    if (argc > 1) {
        extern FILE *yyin;
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror(argv[1]); return 1; }
    }
    yyparse();
    printf("\n    return 0;\n}\n");
    return 0;
}