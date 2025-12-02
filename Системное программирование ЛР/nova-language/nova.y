%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);
%}

%union {
    char* str_val;
}

%token T_TYPE_INT T_TYPE_FLOAT T_TYPE_STR T_TYPE_LIST
%token T_IF T_ELSE T_LOOP T_WHILE T_BLOCK_END
%token T_PRINT_OP T_INPUT_OP T_ASSIGN T_EQ T_NEQ T_GT T_LT T_PLUS T_MINUS T_MUL T_DIV
%token T_LBRACKET T_RBRACKET
%token T_NEWLINE

%token <str_val> T_ID T_VAL_INT T_VAL_FLOAT T_VAL_STR

%left T_PLUS T_MINUS
%left T_MUL T_DIV

%type <str_val> expression value cmp_op

%%

program: 
    { 
        printf("#include <stdio.h>\n");
        printf("#include <stdlib.h>\n");
        printf("#include <string.h>\n");
        printf("#include <ctype.h>\n");

        printf("#define print_any(x) _Generic((x), \\\n");
        printf("    int: printf(\"%%d\\n\", x), \\\n");
        printf("    double: printf(\"%%.2f\\n\", x), \\\n");
        printf("    char*: printf(\"%%s\\n\", x) \\\n");
        printf(")\n\n");

        /* --- ФУНКЦИИ ВВОДА (MINIMAL STYLE) --- */

        printf("int get_int() {\n");
        printf("    char buf[100];\n");
        printf("    printf(\"> \");\n"); /* Просто стрелочка */
        printf("    fflush(stdout);\n");
        printf("    if (!fgets(buf, 100, stdin)) exit(1);\n");
        printf("    char *end;\n");
        printf("    long val = strtol(buf, &end, 10);\n");
        printf("    if (end == buf || (*end != '\\n' && *end != 0)) { printf(\"Ошибка: Ожидалось целое число!\\n\"); exit(1); }\n");
        printf("    return (int)val;\n");
        printf("}\n\n");

        printf("double get_float() {\n");
        printf("    char buf[100];\n");
        printf("    printf(\"> \");\n");
        printf("    fflush(stdout);\n");
        printf("    if (!fgets(buf, 100, stdin)) exit(1);\n");
        printf("    char *end;\n");
        printf("    double val = strtod(buf, &end);\n");
        printf("    if (end == buf || (*end != '\\n' && *end != 0)) { printf(\"Ошибка: Ожидалось дробное число!\\n\"); exit(1); }\n");
        printf("    return val;\n");
        printf("}\n\n");

        printf("char* get_str() {\n");
        printf("    char buf[256];\n");
        printf("    printf(\"> \");\n");
        printf("    fflush(stdout);\n");
        printf("    if (!fgets(buf, 256, stdin)) exit(1);\n");
        printf("    buf[strcspn(buf, \"\\n\")] = 0;\n");
        printf("    return strdup(buf);\n");
        printf("}\n\n");

        printf("void get_list(int *arr, int max_size) {\n");
        printf("    char buf[1024];\n");
        printf("    printf(\"> \");\n");
        printf("    fflush(stdout);\n");
        printf("    if (!fgets(buf, 1024, stdin)) exit(1);\n");
        printf("    buf[strcspn(buf, \"\\n\")] = 0;\n");
        printf("    char *token = strtok(buf, \" \");\n");
        printf("    int i = 0;\n");
        printf("    while (token != NULL && i < max_size) {\n");
        printf("        arr[i++] = atoi(token);\n");
        printf("        token = strtok(NULL, \" \");\n");
        printf("    }\n");
        printf("}\n\n");

        printf("int main() {\n"); 
    }
    statements
    ;

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
    ;

declaration:
      T_TYPE_INT T_ID T_ASSIGN expression T_NEWLINE
      { printf("\tint %s = %s;\n", $2, $4); }
    | T_TYPE_FLOAT T_ID T_ASSIGN expression T_NEWLINE
      { printf("\tdouble %s = %s;\n", $2, $4); }
    | T_TYPE_STR T_ID T_ASSIGN T_VAL_STR T_NEWLINE
      { printf("\tchar *%s = %s;\n", $2, $4); }
    | T_TYPE_LIST T_ID T_ASSIGN expression T_NEWLINE
      { printf("\tint %s[%s];\n", $2, $4); }

    | T_TYPE_INT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { printf("\tint %s = get_int();\n", $2); }
    | T_TYPE_FLOAT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { printf("\tdouble %s = get_float();\n", $2); }
    | T_TYPE_STR T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { printf("\tchar *%s = get_str();\n", $2); }
    | T_TYPE_LIST T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { 
          printf("\tint %s[100] = {0};\n", $2); 
          printf("\tget_list(%s, 100);\n", $2);
      }
    ;

assignment:
      T_ID T_ASSIGN expression T_NEWLINE
      { printf("\t%s = %s;\n", $1, $3); }
    | T_ID T_ASSIGN T_INPUT_OP T_NEWLINE
      { printf("\t%s = get_int();\n", $1); }
    ;

print_stmt:
      T_PRINT_OP expression T_NEWLINE
      { printf("\tprint_any(%s);\n", $2); }
    | T_PRINT_OP T_VAL_STR T_NEWLINE
      { printf("\tprintf(\"%%s\\n\", %s);\n", $2); }
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

expression:
      value { $$ = $1; }
    | expression T_PLUS expression  { 
        char buf[100]; sprintf(buf, "%s + %s", $1, $3); $$ = strdup(buf); 
      }
    | expression T_MINUS expression { 
        char buf[100]; sprintf(buf, "%s - %s", $1, $3); $$ = strdup(buf); 
      }
    | expression T_MUL expression   { 
        char buf[100]; sprintf(buf, "%s * %s", $1, $3); $$ = strdup(buf); 
      }
    | expression T_DIV expression   { 
        char buf[100]; sprintf(buf, "%s / %s", $1, $3); $$ = strdup(buf); 
      }
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
    | T_ID T_LBRACKET expression T_RBRACKET {
        char buf[100];
        sprintf(buf, "%s[%s]", $1, $3);
        $$ = strdup(buf);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        extern FILE *yyin;
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }
    yyparse();
    printf("\n\treturn 0;\n}\n");
    return 0;
}