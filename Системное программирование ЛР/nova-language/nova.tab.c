/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "nova.y"

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


#line 147 "nova.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "nova.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_TYPE_INT = 3,                 /* T_TYPE_INT  */
  YYSYMBOL_T_TYPE_FLOAT = 4,               /* T_TYPE_FLOAT  */
  YYSYMBOL_T_TYPE_STR = 5,                 /* T_TYPE_STR  */
  YYSYMBOL_T_TYPE_LIST = 6,                /* T_TYPE_LIST  */
  YYSYMBOL_T_IF = 7,                       /* T_IF  */
  YYSYMBOL_T_ELSE = 8,                     /* T_ELSE  */
  YYSYMBOL_T_LOOP = 9,                     /* T_LOOP  */
  YYSYMBOL_T_WHILE = 10,                   /* T_WHILE  */
  YYSYMBOL_T_BLOCK_END = 11,               /* T_BLOCK_END  */
  YYSYMBOL_T_FUNC = 12,                    /* T_FUNC  */
  YYSYMBOL_T_RETURN = 13,                  /* T_RETURN  */
  YYSYMBOL_T_ENTRY = 14,                   /* T_ENTRY  */
  YYSYMBOL_T_PRINT_OP = 15,                /* T_PRINT_OP  */
  YYSYMBOL_T_INPUT_OP = 16,                /* T_INPUT_OP  */
  YYSYMBOL_T_ASSIGN = 17,                  /* T_ASSIGN  */
  YYSYMBOL_T_EQ = 18,                      /* T_EQ  */
  YYSYMBOL_T_NEQ = 19,                     /* T_NEQ  */
  YYSYMBOL_T_GT = 20,                      /* T_GT  */
  YYSYMBOL_T_LT = 21,                      /* T_LT  */
  YYSYMBOL_T_PLUS = 22,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 23,                   /* T_MINUS  */
  YYSYMBOL_T_MUL = 24,                     /* T_MUL  */
  YYSYMBOL_T_DIV = 25,                     /* T_DIV  */
  YYSYMBOL_T_LBRACKET = 26,                /* T_LBRACKET  */
  YYSYMBOL_T_RBRACKET = 27,                /* T_RBRACKET  */
  YYSYMBOL_T_LPAREN = 28,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 29,                  /* T_RPAREN  */
  YYSYMBOL_T_COMMA = 30,                   /* T_COMMA  */
  YYSYMBOL_T_NEWLINE = 31,                 /* T_NEWLINE  */
  YYSYMBOL_T_ID = 32,                      /* T_ID  */
  YYSYMBOL_T_VAL_INT = 33,                 /* T_VAL_INT  */
  YYSYMBOL_T_VAL_FLOAT = 34,               /* T_VAL_FLOAT  */
  YYSYMBOL_T_VAL_STR = 35,                 /* T_VAL_STR  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_footer_opt = 38,                /* footer_opt  */
  YYSYMBOL_functions = 39,                 /* functions  */
  YYSYMBOL_function_def = 40,              /* function_def  */
  YYSYMBOL_func_args = 41,                 /* func_args  */
  YYSYMBOL_entry_point = 42,               /* entry_point  */
  YYSYMBOL_end_block_opt = 43,             /* end_block_opt  */
  YYSYMBOL_statements = 44,                /* statements  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_declaration = 46,               /* declaration  */
  YYSYMBOL_assignment = 47,                /* assignment  */
  YYSYMBOL_print_stmt = 48,                /* print_stmt  */
  YYSYMBOL_if_head = 49,                   /* if_head  */
  YYSYMBOL_if_block = 50,                  /* if_block  */
  YYSYMBOL_while_block = 51,               /* while_block  */
  YYSYMBOL_loop_block = 52,                /* loop_block  */
  YYSYMBOL_return_stmt = 53,               /* return_stmt  */
  YYSYMBOL_void_func_call = 54,            /* void_func_call  */
  YYSYMBOL_expression = 55,                /* expression  */
  YYSYMBOL_call_args = 56,                 /* call_args  */
  YYSYMBOL_call_arg_list = 57,             /* call_arg_list  */
  YYSYMBOL_cmp_op = 58,                    /* cmp_op  */
  YYSYMBOL_value = 59                      /* value  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   103,   103,   111,   113,   118,   119,   127,   131,   141,
     142,   145,   152,   162,   163,   167,   168,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   188,   191,   194,   197,
     207,   210,   213,   216,   221,   226,   231,   239,   244,   252,
     262,   272,   277,   282,   283,   284,   285,   286,   288,   297,
     298,   302,   303,   310,   311,   312,   313,   317,   318,   319,
     320,   321
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_TYPE_INT",
  "T_TYPE_FLOAT", "T_TYPE_STR", "T_TYPE_LIST", "T_IF", "T_ELSE", "T_LOOP",
  "T_WHILE", "T_BLOCK_END", "T_FUNC", "T_RETURN", "T_ENTRY", "T_PRINT_OP",
  "T_INPUT_OP", "T_ASSIGN", "T_EQ", "T_NEQ", "T_GT", "T_LT", "T_PLUS",
  "T_MINUS", "T_MUL", "T_DIV", "T_LBRACKET", "T_RBRACKET", "T_LPAREN",
  "T_RPAREN", "T_COMMA", "T_NEWLINE", "T_ID", "T_VAL_INT", "T_VAL_FLOAT",
  "T_VAL_STR", "$accept", "program", "footer_opt", "functions",
  "function_def", "func_args", "entry_point", "end_block_opt",
  "statements", "statement", "declaration", "assignment", "print_stmt",
  "if_head", "if_block", "while_block", "loop_block", "return_stmt",
  "void_func_call", "expression", "call_args", "call_arg_list", "cmp_op",
  "value", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -32,    31,     7,   -32,   -25,    12,   -32,   -32,   -32,    27,
     -32,    35,    30,    54,   -32,    38,    41,    48,    50,    52,
      55,   213,   213,   213,   -32,   213,   213,   -32,    11,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
      56,    58,    79,    80,    84,    94,     6,   -32,   -32,   -32,
     212,   -32,   110,   212,   136,   140,   213,   213,     5,   -32,
     -32,   -10,    14,   104,     1,   213,   213,   -32,   -32,   -32,
     -32,   213,   213,   213,   213,   213,   -32,   213,   -32,   -32,
     153,   195,    95,   -32,    82,   -32,    68,    97,   157,    98,
     167,   109,   171,   111,   122,   216,   125,     2,     2,   -32,
     -32,   181,    99,   185,   -32,   213,   135,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   213,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   112,   199,   142,   -32,   213,   -32,
      69,   137,   -32
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     7,     6,     3,     0,
      15,     2,     9,    14,     4,    10,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     0,    17,     0,    12,
      16,    18,    19,    20,    15,    21,    23,    22,    24,    25,
       0,     0,     0,     0,     0,     0,    57,    58,    59,    60,
       0,    43,     0,     0,     0,     0,     0,    49,     0,    11,
      15,     0,     0,     0,     0,     0,    49,    55,    56,    53,
      54,     0,     0,     0,     0,     0,    15,     0,    41,    35,
       0,    51,     0,    50,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,    45,    46,
      47,     0,     0,     0,    34,     0,     0,    15,     8,    30,
      26,    31,    27,    32,    28,    33,     0,    61,    48,    36,
      40,    15,    52,    42,     0,     0,     0,    38,     0,    39,
       0,     0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -31,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -21,
      60,    51,   116,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    11,     2,     7,    16,     8,    29,    13,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    81,
      82,    83,    75,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    52,    53,    58,    54,    55,    87,     9,    17,    18,
      19,    20,    21,    84,    22,    23,    85,    93,    25,     4,
      26,     5,    46,    47,    48,    49,    73,    74,    56,    86,
      89,     3,    65,    94,    66,    80,    27,    28,     6,    57,
      88,    90,    92,    10,    95,   102,    46,    47,    48,    49,
      97,    98,    99,   100,   101,    12,   103,    17,    18,    19,
      20,    21,    15,    22,    23,    24,    14,    25,    40,    26,
      41,    17,    18,    19,    20,    21,   124,    22,    23,   108,
      42,    25,    43,    26,    44,    27,    28,    45,    59,    60,
     126,    71,    72,    73,    74,   125,    61,    62,   131,    27,
      28,    63,    17,    18,    19,    20,    21,   130,    22,    23,
     120,    64,    25,   107,    26,    17,    18,    19,    20,    21,
      91,    22,    23,   127,   106,    25,    96,    26,   109,   111,
      27,    28,    71,    72,    73,    74,    46,    47,    48,    49,
     113,    76,   115,    27,    28,    17,    18,    19,    20,    21,
     116,    22,    23,   129,   118,    25,   122,    26,    71,    72,
      73,    74,    71,    72,    73,    74,   123,    78,   132,    77,
       0,    79,     0,    27,    28,    71,    72,    73,    74,    71,
      72,    73,    74,     0,   104,     0,     0,     0,   110,    71,
      72,    73,    74,    71,    72,    73,    74,     0,   112,     0,
       0,     0,   114,    71,    72,    73,    74,    71,    72,    73,
      74,     0,   119,     0,     0,     0,   121,    71,    72,    73,
      74,    71,    72,    73,    74,   105,     0,     0,     0,   128,
      67,    68,    69,    70,    71,    72,    73,    74,    71,    72,
      73,    74,     0,   117,     0,    46,    47,    48,    49
};

static const yytype_int16 yycheck[] =
{
      21,    22,    23,    34,    25,    26,    16,    32,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    16,    13,    12,
      15,    14,    32,    33,    34,    35,    24,    25,    17,    60,
      16,     0,    26,    32,    28,    56,    31,    32,    31,    28,
      61,    62,    63,    31,    65,    76,    32,    33,    34,    35,
      71,    72,    73,    74,    75,    28,    77,     3,     4,     5,
       6,     7,    32,     9,    10,    11,    31,    13,    30,    15,
      29,     3,     4,     5,     6,     7,   107,     9,    10,    11,
      32,    13,    32,    15,    32,    31,    32,    32,    32,    31,
     121,    22,    23,    24,    25,   116,    17,    17,    29,    31,
      32,    17,     3,     4,     5,     6,     7,   128,     9,    10,
      11,    17,    13,    31,    15,     3,     4,     5,     6,     7,
      16,     9,    10,    11,    29,    13,    66,    15,    31,    31,
      31,    32,    22,    23,    24,    25,    32,    33,    34,    35,
      31,    31,    31,    31,    32,     3,     4,     5,     6,     7,
      28,     9,    10,    11,    29,    13,   105,    15,    22,    23,
      24,    25,    22,    23,    24,    25,    31,    31,    31,    53,
      -1,    31,    -1,    31,    32,    22,    23,    24,    25,    22,
      23,    24,    25,    -1,    31,    -1,    -1,    -1,    31,    22,
      23,    24,    25,    22,    23,    24,    25,    -1,    31,    -1,
      -1,    -1,    31,    22,    23,    24,    25,    22,    23,    24,
      25,    -1,    31,    -1,    -1,    -1,    31,    22,    23,    24,
      25,    22,    23,    24,    25,    30,    -1,    -1,    -1,    30,
      18,    19,    20,    21,    22,    23,    24,    25,    22,    23,
      24,    25,    -1,    27,    -1,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    37,    39,     0,    12,    14,    31,    40,    42,    32,
      31,    38,    28,    44,    31,    32,    41,     3,     4,     5,
       6,     7,     9,    10,    11,    13,    15,    31,    32,    43,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      30,    29,    32,    32,    32,    32,    32,    33,    34,    35,
      55,    59,    55,    55,    55,    55,    17,    28,    44,    32,
      31,    17,    17,    17,    17,    26,    28,    18,    19,    20,
      21,    22,    23,    24,    25,    58,    31,    58,    31,    31,
      55,    55,    56,    57,     8,    11,    44,    16,    55,    16,
      55,    16,    55,    16,    32,    55,    56,    55,    55,    55,
      55,    55,    44,    55,    31,    30,    29,    31,    11,    31,
      31,    31,    31,    31,    31,    31,    28,    27,    29,    31,
      11,    31,    57,    31,    44,    55,    44,    11,    30,    11,
      55,    29,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    39,    40,    41,
      41,    41,    42,    43,    43,    44,    44,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    48,    49,    50,    50,    51,
      52,    53,    54,    55,    55,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    59,    59,    59,
      59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     2,     0,     2,     2,     8,     0,
       1,     3,     4,     1,     0,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     5,    10,
       5,     5,     5,     5,     4,     3,     5,     3,     6,     7,
       5,     3,     5,     1,     3,     3,     3,     3,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: functions entry_point footer_opt  */
#line 104 "nova.y"
    {
        FINAL_CODE = concat(3, LIB_CODE, ((yyvsp[-2].str_val) ? (yyvsp[-2].str_val) : ""), ((yyvsp[-1].str_val) ? (yyvsp[-1].str_val) : ""));
        if ((yyvsp[-2].str_val)) free((yyvsp[-2].str_val));
        if ((yyvsp[-1].str_val)) free((yyvsp[-1].str_val));
    }
#line 1306 "nova.tab.c"
    break;

  case 5: /* functions: %empty  */
#line 118 "nova.y"
                       { (yyval.str_val) = NULL; }
#line 1312 "nova.tab.c"
    break;

  case 6: /* functions: functions function_def  */
#line 119 "nova.y"
                             { 
        if ((yyvsp[-1].str_val)) {
            (yyval.str_val) = concat(2, (yyvsp[-1].str_val), (yyvsp[0].str_val));
            free((yyvsp[-1].str_val)); free((yyvsp[0].str_val));
        } else {
            (yyval.str_val) = (yyvsp[0].str_val);
        }
    }
#line 1325 "nova.tab.c"
    break;

  case 7: /* functions: functions T_NEWLINE  */
#line 127 "nova.y"
                          { (yyval.str_val) = (yyvsp[-1].str_val); }
#line 1331 "nova.tab.c"
    break;

  case 8: /* function_def: T_FUNC T_ID T_LPAREN func_args T_RPAREN T_NEWLINE statements T_BLOCK_END  */
#line 132 "nova.y"
    {
        char *header;
        asprintf(&header, "int %s(%s) {\n", (yyvsp[-6].str_val), (yyvsp[-4].str_val));
        (yyval.str_val) = concat(3, header, (yyvsp[-1].str_val), "}\n\n");
        free(header); free((yyvsp[-4].str_val)); free((yyvsp[-1].str_val));
    }
#line 1342 "nova.tab.c"
    break;

  case 9: /* func_args: %empty  */
#line 141 "nova.y"
                       { (yyval.str_val) = strdup(""); }
#line 1348 "nova.tab.c"
    break;

  case 10: /* func_args: T_ID  */
#line 142 "nova.y"
           { 
        asprintf(&(yyval.str_val), "int %s", (yyvsp[0].str_val)); 
      }
#line 1356 "nova.tab.c"
    break;

  case 11: /* func_args: T_ID T_COMMA T_ID  */
#line 145 "nova.y"
                        { 
        asprintf(&(yyval.str_val), "int %s, int %s", (yyvsp[-2].str_val), (yyvsp[0].str_val)); 
      }
#line 1364 "nova.tab.c"
    break;

  case 12: /* entry_point: T_ENTRY T_NEWLINE statements end_block_opt  */
#line 153 "nova.y"
    {
        char *main_header = "int main() {\n\tsrand(time(NULL));\n";
        char *main_footer = "\n\treturn 0;\n}\n";
        (yyval.str_val) = concat(3, main_header, (yyvsp[-1].str_val), main_footer);
        free((yyvsp[-1].str_val));
    }
#line 1375 "nova.tab.c"
    break;

  case 15: /* statements: %empty  */
#line 167 "nova.y"
                       { (yyval.str_val) = strdup(""); }
#line 1381 "nova.tab.c"
    break;

  case 16: /* statements: statements statement  */
#line 168 "nova.y"
                           { 
        char *temp = concat(2, (yyvsp[-1].str_val), (yyvsp[0].str_val));
        free((yyvsp[-1].str_val)); free((yyvsp[0].str_val));
        (yyval.str_val) = temp;
    }
#line 1391 "nova.tab.c"
    break;

  case 17: /* statement: T_NEWLINE  */
#line 176 "nova.y"
                { (yyval.str_val) = strdup(""); }
#line 1397 "nova.tab.c"
    break;

  case 26: /* declaration: T_TYPE_INT T_ID T_ASSIGN expression T_NEWLINE  */
#line 189 "nova.y"
      { asprintf(&(yyval.str_val), "\tint %s = %s;\n", (yyvsp[-3].str_val), (yyvsp[-1].str_val)); free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val)); }
#line 1403 "nova.tab.c"
    break;

  case 27: /* declaration: T_TYPE_FLOAT T_ID T_ASSIGN expression T_NEWLINE  */
#line 192 "nova.y"
      { asprintf(&(yyval.str_val), "\tdouble %s = %s;\n", (yyvsp[-3].str_val), (yyvsp[-1].str_val)); free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val)); }
#line 1409 "nova.tab.c"
    break;

  case 28: /* declaration: T_TYPE_STR T_ID T_ASSIGN expression T_NEWLINE  */
#line 195 "nova.y"
      { asprintf(&(yyval.str_val), "\tchar *%s = %s;\n", (yyvsp[-3].str_val), (yyvsp[-1].str_val)); free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val)); }
#line 1415 "nova.tab.c"
    break;

  case 29: /* declaration: T_TYPE_LIST T_ID T_ASSIGN T_ID T_LPAREN expression T_COMMA expression T_RPAREN T_NEWLINE  */
#line 198 "nova.y"
      {
         if (strcmp((yyvsp[-6].str_val), "fibonacci") == 0) {
             asprintf(&(yyval.str_val), "\tint %s[100];\n\tfill_fibonacci_range(%s, %s, %s);\n", (yyvsp[-8].str_val), (yyvsp[-8].str_val), (yyvsp[-4].str_val), (yyvsp[-2].str_val));
         } else {
             (yyval.str_val) = strdup("\t/* Unknown list func */\n");
         }
         free((yyvsp[-8].str_val)); free((yyvsp[-6].str_val)); free((yyvsp[-4].str_val)); free((yyvsp[-2].str_val));
      }
#line 1428 "nova.tab.c"
    break;

  case 30: /* declaration: T_TYPE_INT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE  */
#line 208 "nova.y"
      { asprintf(&(yyval.str_val), "\tint %s = get_int();\n", (yyvsp[-3].str_val)); free((yyvsp[-3].str_val)); }
#line 1434 "nova.tab.c"
    break;

  case 31: /* declaration: T_TYPE_FLOAT T_ID T_ASSIGN T_INPUT_OP T_NEWLINE  */
#line 211 "nova.y"
      { asprintf(&(yyval.str_val), "\tdouble %s = get_float();\n", (yyvsp[-3].str_val)); free((yyvsp[-3].str_val)); }
#line 1440 "nova.tab.c"
    break;

  case 32: /* declaration: T_TYPE_STR T_ID T_ASSIGN T_INPUT_OP T_NEWLINE  */
#line 214 "nova.y"
      { asprintf(&(yyval.str_val), "\tchar *%s = get_str();\n", (yyvsp[-3].str_val)); free((yyvsp[-3].str_val)); }
#line 1446 "nova.tab.c"
    break;

  case 33: /* declaration: T_TYPE_LIST T_ID T_ASSIGN T_INPUT_OP T_NEWLINE  */
#line 217 "nova.y"
      { asprintf(&(yyval.str_val), "\tint %s[100] = {0};\n\tget_list(%s, 100);\n", (yyvsp[-3].str_val), (yyvsp[-3].str_val)); free((yyvsp[-3].str_val)); }
#line 1452 "nova.tab.c"
    break;

  case 34: /* assignment: T_ID T_ASSIGN expression T_NEWLINE  */
#line 222 "nova.y"
      { asprintf(&(yyval.str_val), "\t%s = %s;\n", (yyvsp[-3].str_val), (yyvsp[-1].str_val)); free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val)); }
#line 1458 "nova.tab.c"
    break;

  case 35: /* print_stmt: T_PRINT_OP expression T_NEWLINE  */
#line 227 "nova.y"
      { asprintf(&(yyval.str_val), "\tprint_any(%s);\n", (yyvsp[-1].str_val)); free((yyvsp[-1].str_val)); }
#line 1464 "nova.tab.c"
    break;

  case 36: /* if_head: T_IF expression cmp_op expression T_NEWLINE  */
#line 232 "nova.y"
      { 
          asprintf(&(yyval.str_val), "\tif (%s %s %s) {\n", (yyvsp[-3].str_val), (yyvsp[-2].str_val), (yyvsp[-1].str_val)); 
          free((yyvsp[-3].str_val)); free((yyvsp[-2].str_val)); free((yyvsp[-1].str_val));
      }
#line 1473 "nova.tab.c"
    break;

  case 37: /* if_block: if_head statements T_BLOCK_END  */
#line 240 "nova.y"
      { 
          (yyval.str_val) = concat(3, (yyvsp[-2].str_val), (yyvsp[-1].str_val), "\t}\n"); 
          free((yyvsp[-2].str_val)); free((yyvsp[-1].str_val));
      }
#line 1482 "nova.tab.c"
    break;

  case 38: /* if_block: if_head statements T_ELSE T_NEWLINE statements T_BLOCK_END  */
#line 245 "nova.y"
      { 
          (yyval.str_val) = concat(5, (yyvsp[-5].str_val), (yyvsp[-4].str_val), "\t} else {\n", (yyvsp[-1].str_val), "\t}\n");
          free((yyvsp[-5].str_val)); free((yyvsp[-4].str_val)); free((yyvsp[-1].str_val));
      }
#line 1491 "nova.tab.c"
    break;

  case 39: /* while_block: T_WHILE expression cmp_op expression T_NEWLINE statements T_BLOCK_END  */
#line 253 "nova.y"
      {
          char *head;
          asprintf(&head, "\twhile (%s %s %s) {\n", (yyvsp[-5].str_val), (yyvsp[-4].str_val), (yyvsp[-3].str_val));
          (yyval.str_val) = concat(3, head, (yyvsp[-1].str_val), "\t}\n");
          free(head); free((yyvsp[-5].str_val)); free((yyvsp[-4].str_val)); free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val));
      }
#line 1502 "nova.tab.c"
    break;

  case 40: /* loop_block: T_LOOP expression T_NEWLINE statements T_BLOCK_END  */
#line 263 "nova.y"
      {
          char *head;
          asprintf(&head, "\tfor(int _i=0; _i < (int)(%s); _i++) {\n", (yyvsp[-3].str_val));
          (yyval.str_val) = concat(3, head, (yyvsp[-1].str_val), "\t}\n");
          free(head); free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val));
      }
#line 1513 "nova.tab.c"
    break;

  case 41: /* return_stmt: T_RETURN expression T_NEWLINE  */
#line 273 "nova.y"
      { asprintf(&(yyval.str_val), "\treturn %s;\n", (yyvsp[-1].str_val)); free((yyvsp[-1].str_val)); }
#line 1519 "nova.tab.c"
    break;

  case 42: /* void_func_call: T_ID T_LPAREN call_args T_RPAREN T_NEWLINE  */
#line 278 "nova.y"
      { asprintf(&(yyval.str_val), "\t%s(%s);\n", (yyvsp[-4].str_val), (yyvsp[-2].str_val)); free((yyvsp[-4].str_val)); free((yyvsp[-2].str_val)); }
#line 1525 "nova.tab.c"
    break;

  case 43: /* expression: value  */
#line 282 "nova.y"
            { (yyval.str_val) = (yyvsp[0].str_val); }
#line 1531 "nova.tab.c"
    break;

  case 44: /* expression: expression T_PLUS expression  */
#line 283 "nova.y"
                                    { asprintf(&(yyval.str_val), "%s + %s", (yyvsp[-2].str_val), (yyvsp[0].str_val)); free((yyvsp[-2].str_val)); free((yyvsp[0].str_val)); }
#line 1537 "nova.tab.c"
    break;

  case 45: /* expression: expression T_MINUS expression  */
#line 284 "nova.y"
                                    { asprintf(&(yyval.str_val), "%s - %s", (yyvsp[-2].str_val), (yyvsp[0].str_val)); free((yyvsp[-2].str_val)); free((yyvsp[0].str_val)); }
#line 1543 "nova.tab.c"
    break;

  case 46: /* expression: expression T_MUL expression  */
#line 285 "nova.y"
                                    { asprintf(&(yyval.str_val), "%s * %s", (yyvsp[-2].str_val), (yyvsp[0].str_val)); free((yyvsp[-2].str_val)); free((yyvsp[0].str_val)); }
#line 1549 "nova.tab.c"
    break;

  case 47: /* expression: expression T_DIV expression  */
#line 286 "nova.y"
                                    { asprintf(&(yyval.str_val), "%s / %s", (yyvsp[-2].str_val), (yyvsp[0].str_val)); free((yyvsp[-2].str_val)); free((yyvsp[0].str_val)); }
#line 1555 "nova.tab.c"
    break;

  case 48: /* expression: T_ID T_LPAREN call_args T_RPAREN  */
#line 289 "nova.y"
      { 
        if (strcmp((yyvsp[-3].str_val), "random") == 0) asprintf(&(yyval.str_val), "random_int(%s)", (yyvsp[-1].str_val));
        else asprintf(&(yyval.str_val), "%s(%s)", (yyvsp[-3].str_val), (yyvsp[-1].str_val));
        free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val));
      }
#line 1565 "nova.tab.c"
    break;

  case 49: /* call_args: %empty  */
#line 297 "nova.y"
                       { (yyval.str_val) = strdup(""); }
#line 1571 "nova.tab.c"
    break;

  case 50: /* call_args: call_arg_list  */
#line 298 "nova.y"
                    { (yyval.str_val) = (yyvsp[0].str_val); }
#line 1577 "nova.tab.c"
    break;

  case 51: /* call_arg_list: expression  */
#line 302 "nova.y"
                 { (yyval.str_val) = (yyvsp[0].str_val); }
#line 1583 "nova.tab.c"
    break;

  case 52: /* call_arg_list: expression T_COMMA call_arg_list  */
#line 303 "nova.y"
                                       { 
        asprintf(&(yyval.str_val), "%s, %s", (yyvsp[-2].str_val), (yyvsp[0].str_val)); 
        free((yyvsp[-2].str_val)); free((yyvsp[0].str_val));
    }
#line 1592 "nova.tab.c"
    break;

  case 53: /* cmp_op: T_GT  */
#line 310 "nova.y"
           { (yyval.str_val) = strdup(">"); }
#line 1598 "nova.tab.c"
    break;

  case 54: /* cmp_op: T_LT  */
#line 311 "nova.y"
           { (yyval.str_val) = strdup("<"); }
#line 1604 "nova.tab.c"
    break;

  case 55: /* cmp_op: T_EQ  */
#line 312 "nova.y"
           { (yyval.str_val) = strdup("=="); }
#line 1610 "nova.tab.c"
    break;

  case 56: /* cmp_op: T_NEQ  */
#line 313 "nova.y"
            { (yyval.str_val) = strdup("!="); }
#line 1616 "nova.tab.c"
    break;

  case 57: /* value: T_ID  */
#line 317 "nova.y"
           { (yyval.str_val) = strdup((yyvsp[0].str_val)); }
#line 1622 "nova.tab.c"
    break;

  case 58: /* value: T_VAL_INT  */
#line 318 "nova.y"
                { (yyval.str_val) = strdup((yyvsp[0].str_val)); }
#line 1628 "nova.tab.c"
    break;

  case 59: /* value: T_VAL_FLOAT  */
#line 319 "nova.y"
                  { (yyval.str_val) = strdup((yyvsp[0].str_val)); }
#line 1634 "nova.tab.c"
    break;

  case 60: /* value: T_VAL_STR  */
#line 320 "nova.y"
                { (yyval.str_val) = strdup((yyvsp[0].str_val)); }
#line 1640 "nova.tab.c"
    break;

  case 61: /* value: T_ID T_LBRACKET expression T_RBRACKET  */
#line 321 "nova.y"
                                            {
        asprintf(&(yyval.str_val), "%s[%s]", (yyvsp[-3].str_val), (yyvsp[-1].str_val));
        free((yyvsp[-3].str_val)); free((yyvsp[-1].str_val));
    }
#line 1649 "nova.tab.c"
    break;


#line 1653 "nova.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 327 "nova.y"


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
