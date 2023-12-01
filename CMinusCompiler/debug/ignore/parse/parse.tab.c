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
#line 1 "parse.y"

  #define YYPARSER
  #include "./parser/syntax_tree.h"
  #define YYSTYPE syntax_tree *
  
  #include "./parse.tab.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "./lexical_analyzer/get_token.h"

  /*
    Variaveis Globais
  */

  int lineno = 0;
  char lex[40];
  int last_token = -1;
  int tok_num = END;


  syntax_tree* tree;            /* raiz da syntax_tree */
  syntax_tree* R_mst_decl_node; /* (utilizado para as regras 2 e 3 da CFG) mantem um ponteiro pro nó declaracao
                                   mais a esquerda corrente na arvore 
                                */
  syntax_tree* R_mst_param;     /* (utilizado para as regras 8 e 9 da CFG) mantem um ponteiro pro nó param
                                   mais a esquerda corrente na arvore que se origina de param-list 
                                */
  syntax_tree* L_var_decl;                                
  syntax_tree* L_mst_expr;

  /*
    Funcoes
  */

  static int yylex(void);
  TokenNode* next_token();
  int tok_to_num(char *);
  char* deepCopy(char *);
  void yyerror(char *);

#line 113 "parse.tab.c"

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

#include "parse.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
  YYSYMBOL_ID = 10,                        /* ID  */
  YYSYMBOL_ASS = 11,                       /* ASS  */
  YYSYMBOL_EQL = 12,                       /* EQL  */
  YYSYMBOL_NEQL = 13,                      /* NEQL  */
  YYSYMBOL_LT = 14,                        /* LT  */
  YYSYMBOL_GT = 15,                        /* GT  */
  YYSYMBOL_LET = 16,                       /* LET  */
  YYSYMBOL_GET = 17,                       /* GET  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MINUS = 19,                     /* MINUS  */
  YYSYMBOL_TIMES = 20,                     /* TIMES  */
  YYSYMBOL_DIV = 21,                       /* DIV  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LBRA = 24,                      /* LBRA  */
  YYSYMBOL_RBRA = 25,                      /* RBRA  */
  YYSYMBOL_LKEY = 26,                      /* LKEY  */
  YYSYMBOL_RKEY = 27,                      /* RKEY  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 29,                 /* SEMICOLON  */
  YYSYMBOL_ERR = 30,                       /* ERR  */
  YYSYMBOL_END = 31,                       /* END  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_programa = 33,                  /* programa  */
  YYSYMBOL_34_decl_lista = 34,             /* decl-lista  */
  YYSYMBOL_decl = 35,                      /* decl  */
  YYSYMBOL_36_var_decl = 36,               /* var-decl  */
  YYSYMBOL_37_fun_decl = 37,               /* fun-decl  */
  YYSYMBOL_params = 38,                    /* params  */
  YYSYMBOL_39_param_lista = 39,            /* param-lista  */
  YYSYMBOL_param = 40,                     /* param  */
  YYSYMBOL_41_composto_decl = 41,          /* composto-decl  */
  YYSYMBOL_42_local_decls = 42,            /* local-decls  */
  YYSYMBOL_43_statement_lista = 43,        /* statement-lista  */
  YYSYMBOL_statement = 44,                 /* statement  */
  YYSYMBOL_45_expr_decl = 45,              /* expr-decl  */
  YYSYMBOL_46_selec_decl = 46,             /* selec-decl  */
  YYSYMBOL_47_iter_decl = 47,              /* iter-decl  */
  YYSYMBOL_48_retorno_decl = 48,           /* retorno-decl  */
  YYSYMBOL_expr = 49,                      /* expr  */
  YYSYMBOL_var = 50,                       /* var  */
  YYSYMBOL_51_simples_expr = 51,           /* simples-expr  */
  YYSYMBOL_relacional = 52,                /* relacional  */
  YYSYMBOL_53_soma_expr = 53,              /* soma-expr  */
  YYSYMBOL_soma = 54,                      /* soma  */
  YYSYMBOL_termo = 55,                     /* termo  */
  YYSYMBOL_mult = 56,                      /* mult  */
  YYSYMBOL_fator = 57,                     /* fator  */
  YYSYMBOL_ativacao = 58,                  /* ativacao  */
  YYSYMBOL_args = 59,                      /* args  */
  YYSYMBOL_60_arg_list = 60,               /* arg-list  */
  YYSYMBOL_id = 61,                        /* id  */
  YYSYMBOL_num = 62                        /* num  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   133

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    51,    51,    54,    59,    65,    66,    69,    78,    91,
     105,   119,   122,   129,   134,   140,   150,   163,   176,   177,
     178,   181,   186,   192,   207,   210,   213,   216,   219,   222,
     227,   230,   235,   242,   252,   261,   267,   275,   282,   287,
     288,   297,   303,   308,   313,   318,   323,   328,   333,   340,
     346,   351,   356,   363,   369,   374,   379,   386,   387,   388,
     389,   392,   399,   402,   405,   410,   416,   424
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "INT", "VOID", "RETURN", "NUMBER", "ID", "ASS", "EQL", "NEQL", "LT",
  "GT", "LET", "GET", "PLUS", "MINUS", "TIMES", "DIV", "LPAREN", "RPAREN",
  "LBRA", "RBRA", "LKEY", "RKEY", "COMMA", "SEMICOLON", "ERR", "END",
  "$accept", "programa", "decl-lista", "decl", "var-decl", "fun-decl",
  "params", "param-lista", "param", "composto-decl", "local-decls",
  "statement-lista", "statement", "expr-decl", "selec-decl", "iter-decl",
  "retorno-decl", "expr", "var", "simples-expr", "relacional", "soma-expr",
  "soma", "termo", "mult", "fator", "ativacao", "args", "arg-list", "id",
  "num", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-45)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      64,    15,    15,    30,    64,   -45,   -45,   -45,   -45,    18,
      29,   -45,   -45,    90,    28,   -45,    90,    15,   -45,    31,
      33,   -45,   -45,    34,    41,    48,    67,    78,    71,    67,
      79,     6,   -45,   -45,   -45,   -45,   -45,    81,    83,    15,
      -2,     9,   -45,   -45,   -45,   -45,    47,    72,   -45,   -45,
     -45,   -45,   -45,    89,    97,   -45,    98,    58,   -45,   -45,
      14,   -45,     9,     9,     0,   -45,    91,    96,   -45,   -45,
      80,   -45,   -45,   -45,     9,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,     9,     9,   -45,   -45,     9,     9,     9,
      99,   100,   -45,   -45,   -45,   -45,   -45,    68,    58,   -45,
     -45,   101,    93,   102,    36,    36,   -45,     9,   -45,   121,
      36,   -45,    36,   -45
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     5,     6,    66,     0,
       0,     1,     3,     0,     0,     7,     0,     0,    12,     0,
      11,    14,    67,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     9,    13,     8,    10,    16,     0,     0,     0,
       0,     0,    20,    31,    22,    26,     0,     0,    24,    25,
      27,    28,    29,     0,    58,    38,    42,    50,    54,    59,
      39,    60,     0,     0,     0,    35,     0,     0,    18,    21,
       0,    19,    23,    30,     0,    47,    48,    44,    45,    43,
      46,    51,    52,     0,     0,    55,    56,     0,    63,     0,
       0,     0,    36,    57,    17,    37,    58,    41,    49,    53,
      65,     0,    62,     0,     0,     0,    61,     0,    40,    32,
      34,    64,     0,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   -45,   122,   -29,   -45,   112,   -45,   103,   -16,
     -45,   -42,   -44,   -45,   -45,   -45,   -45,   -40,     8,   -45,
     -45,    46,   -45,    49,   -45,    44,   -45,   -45,   -45,     4,
     118
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,    19,    20,    21,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      83,    56,    84,    57,    87,    58,    59,   101,   102,    60,
      61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      66,    67,    44,    72,    70,     9,    10,    22,     8,    37,
      32,    38,    39,    35,    40,    22,     8,    69,    22,     8,
      41,    25,    90,    91,    14,     8,    72,    65,    41,    15,
      11,    41,    31,    42,    95,    43,    88,    22,    89,    37,
      13,    38,    14,    64,    40,    22,     8,    15,   100,   103,
      37,    16,    38,    39,    26,    40,    22,     8,    41,    28,
     109,    27,    31,   110,    29,    43,    72,   111,   113,    41,
       1,     2,    30,    31,    68,    37,    43,    38,    85,    86,
      40,    22,     8,    37,    17,    38,    81,    82,    40,    22,
       8,    96,    96,    31,    41,    96,    17,    18,    31,    71,
      34,    43,    41,    62,    36,    63,    31,    94,    74,    43,
      75,    76,    77,    78,    79,    80,    81,    82,    73,    93,
      92,   107,   104,   105,   106,   112,    12,   108,    24,    97,
      33,    99,    23,    98
};

static const yytype_int8 yycheck[] =
{
      40,    41,    31,    47,    46,     1,     2,     9,    10,     3,
      26,     5,     6,    29,     8,     9,    10,    46,     9,    10,
      22,    17,    62,    63,    24,    10,    70,    29,    22,    29,
       0,    22,    26,    27,    74,    29,    22,     9,    24,     3,
      22,     5,    24,    39,     8,     9,    10,    29,    88,    89,
       3,    22,     5,     6,    23,     8,     9,    10,    22,    25,
     104,    28,    26,   105,    23,    29,   110,   107,   112,    22,
       6,     7,    24,    26,    27,     3,    29,     5,    20,    21,
       8,     9,    10,     3,     6,     5,    18,    19,     8,     9,
      10,    83,    84,    26,    22,    87,     6,     7,    26,    27,
      29,    29,    22,    22,    25,    22,    26,    27,    11,    29,
      12,    13,    14,    15,    16,    17,    18,    19,    29,    23,
      29,    28,    23,    23,    23,     4,     4,    25,    16,    83,
      27,    87,    14,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,    33,    34,    35,    36,    37,    10,    61,
      61,     0,    35,    22,    24,    29,    22,     6,     7,    38,
      39,    40,     9,    62,    38,    61,    23,    28,    25,    23,
      24,    26,    41,    40,    29,    41,    25,     3,     5,     6,
       8,    22,    27,    29,    36,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    53,    55,    57,    58,
      61,    62,    22,    22,    61,    29,    49,    49,    27,    36,
      43,    27,    44,    29,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    52,    54,    20,    21,    56,    22,    24,
      49,    49,    29,    23,    27,    49,    50,    53,    55,    57,
      49,    59,    60,    49,    23,    23,    23,    28,    25,    44,
      43,    49,     4,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    36,    36,    37,
      37,    38,    38,    39,    39,    40,    40,    41,    41,    41,
      41,    42,    42,    43,    43,    44,    44,    44,    44,    44,
      45,    45,    46,    46,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    58,    59,    59,    60,    60,    61,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     6,
       6,     1,     1,     3,     1,     2,     4,     4,     3,     3,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     5,     7,     5,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     4,     1,     0,     3,     1,     1,     1
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
  case 2: /* programa: decl-lista  */
#line 51 "parse.y"
                       {tree = yyvsp[0];}
#line 1242 "parse.tab.c"
    break;

  case 3: /* decl-lista: decl-lista decl  */
#line 54 "parse.y"
                              {
                yyval = yyvsp[-1];
                R_mst_decl_node->sibling = yyvsp[0];
                R_mst_decl_node = yyvsp[0];               
              }
#line 1252 "parse.tab.c"
    break;

  case 4: /* decl-lista: decl  */
#line 59 "parse.y"
                   {
                yyval = yyvsp[0];
                R_mst_decl_node = yyvsp[0];
              }
#line 1261 "parse.tab.c"
    break;

  case 5: /* decl: var-decl  */
#line 65 "parse.y"
                 {yyval = yyvsp[0];}
#line 1267 "parse.tab.c"
    break;

  case 6: /* decl: fun-decl  */
#line 66 "parse.y"
                 {yyval = yyvsp[0];}
#line 1273 "parse.tab.c"
    break;

  case 7: /* var-decl: INT id SEMICOLON  */
#line 69 "parse.y"
                             {
              yyval = syntax_tree_alloc_node(1);
              yyval->node_data->token = "INT";
              yyval->node_data->lexem = "int";
              yyval->n_child = 1;
              yyval->child[0] = yyvsp[-1];
              yyvsp[-1]->node_data->nodetype = VARIAVEL;
              yyvsp[-1]->node_data->datatype = INTEGER_T;
            }
#line 1287 "parse.tab.c"
    break;

  case 8: /* var-decl: INT id LBRA num RBRA SEMICOLON  */
#line 78 "parse.y"
                                             {
              yyval = syntax_tree_alloc_node(2);
              yyval->node_data->token = "INT";
              yyval->node_data->lexem = "int";
              yyval->n_child = 2;
              yyval->child[0] = yyvsp[-4];
              yyval->child[1] = yyvsp[-2];
              yyvsp[-4]->node_data->nodetype = VARIAVEL;
              yyvsp[-4]->node_data->datatype = INTEGER_T;
              yyvsp[-4]->node_data->len = yyvsp[-2]->node_data->lexem;
            }
#line 1303 "parse.tab.c"
    break;

  case 9: /* fun-decl: INT id LPAREN params RPAREN composto-decl  */
#line 91 "parse.y"
                                                      {
              yyval = syntax_tree_alloc_node(1);
              yyval->node_data->token = "INT";
              yyval->node_data->lexem = "int";
              yyval->node_data->datatype = INTEGER_T;
              yyval->n_child = 1;
              yyval->child[0] = yyvsp[-4];
              yyvsp[-4]->child[0] = yyvsp[-2];
              yyvsp[-4]->child[1] = yyvsp[0];
              yyvsp[-4]->child[0]->node_data->scope = yyvsp[-4]->node_data->lexem;
              yyvsp[-4]->child[1]->node_data->scope = yyvsp[-4]->node_data->lexem;
              yyvsp[-4]->n_child = 2;
              yyvsp[-4]->node_data->nodetype = FUNCAO;
            }
#line 1322 "parse.tab.c"
    break;

  case 10: /* fun-decl: VOID id LPAREN params RPAREN composto-decl  */
#line 105 "parse.y"
                                                       {
              yyval = syntax_tree_alloc_node(1);
              yyval->node_data->token = "VOID";
              yyval->node_data->lexem = "void";
              yyval->node_data->datatype = VOID_T;
              yyval->n_child = 1;
              yyval->child[0] = yyvsp[-4];
              yyvsp[-4]->child[0] = yyvsp[-2];
              yyvsp[-4]->child[1] = yyvsp[0];
              yyvsp[-4]->n_child = 2;
              yyvsp[-4]->node_data->nodetype = FUNCAO;
            }
#line 1339 "parse.tab.c"
    break;

  case 11: /* params: param-lista  */
#line 119 "parse.y"
                      {
            yyval = yyvsp[0];
          }
#line 1347 "parse.tab.c"
    break;

  case 12: /* params: VOID  */
#line 122 "parse.y"
                 {
            yyval = syntax_tree_alloc_node(0);
            yyval->node_data->token = "VOID";
            yyval->node_data->lexem = "void";
          }
#line 1357 "parse.tab.c"
    break;

  case 13: /* param-lista: param-lista COMMA param  */
#line 129 "parse.y"
                                        {
                  yyval = yyvsp[-2];
                  R_mst_param->sibling = yyvsp[0];
                  R_mst_param = yyvsp[0];         
                }
#line 1367 "parse.tab.c"
    break;

  case 14: /* param-lista: param  */
#line 134 "parse.y"
                    {
                yyval = yyvsp[0];
                R_mst_param = yyvsp[0];
              }
#line 1376 "parse.tab.c"
    break;

  case 15: /* param: INT id  */
#line 140 "parse.y"
                 {
            yyval = syntax_tree_alloc_node(1);
            yyval->node_data->token = "INT";
            yyval->node_data->lexem = "int";
            yyval->node_data->datatype = INTEGER_T;
            yyval->n_child = 1;
            yyval->child[0] = yyvsp[0];
            yyvsp[0]->node_data->nodetype = VARIAVEL;
            yyvsp[0]->node_data->datatype = INTEGER_T;
          }
#line 1391 "parse.tab.c"
    break;

  case 16: /* param: INT id LBRA RBRA  */
#line 151 "parse.y"
          {
            yyval = syntax_tree_alloc_node(1);
            yyval->node_data->token = "INT";
            yyval->node_data->lexem = "int";
            yyval->node_data->datatype = INTEGER_T;
            yyval->n_child = 1;
            yyval->child[0] = yyvsp[-2];
            yyvsp[-2]->node_data->nodetype = VARIAVEL;
            yyvsp[-2]->node_data->datatype = INTEGER_T;
          }
#line 1406 "parse.tab.c"
    break;

  case 17: /* composto-decl: LKEY local-decls statement-lista RKEY  */
#line 163 "parse.y"
                                                        {
                  yyval = yyvsp[-2];
                  /* 
                  Neste caso, precisamos percorrer a lista, por
                  nao termos um "caso base".
                  */
                  if(yyval != NULL){
                    while(yyval->sibling != NULL) yyval = yyval->sibling;
                    yyval->sibling = yyvsp[-1];
                    yyval = yyvsp[-2];
                  }
                  else yyval = yyvsp[-1];
                }
#line 1424 "parse.tab.c"
    break;

  case 18: /* composto-decl: LKEY local-decls RKEY  */
#line 176 "parse.y"
                                        { yyval = yyvsp[-1]; }
#line 1430 "parse.tab.c"
    break;

  case 19: /* composto-decl: LKEY statement-lista RKEY  */
#line 177 "parse.y"
                                            { yyval = yyvsp[-1]; }
#line 1436 "parse.tab.c"
    break;

  case 20: /* composto-decl: LKEY RKEY  */
#line 178 "parse.y"
                            { yyval = NULL; }
#line 1442 "parse.tab.c"
    break;

  case 21: /* local-decls: local-decls var-decl  */
#line 181 "parse.y"
                                     {
                  yyval = yyvsp[-1];
                  L_var_decl->sibling = yyvsp[0];
                  L_var_decl = yyvsp[0]; 
                }
#line 1452 "parse.tab.c"
    break;

  case 22: /* local-decls: var-decl  */
#line 186 "parse.y"
                         { 
                yyval = yyvsp[0];
                L_var_decl = yyvsp[0]; 
              }
#line 1461 "parse.tab.c"
    break;

  case 23: /* statement-lista: statement-lista statement  */
#line 192 "parse.y"
                                              {
                    yyval = yyvsp[-1];      
                    /*
                      Neste caso, tambem nao podemos usar o ponteiro
                      pois statements podem conter outros statements.
                      Ou seja, precisariamos de N niveis de statement
                      para nao ter conflito na variavel global.
                    */
                    if(yyval != NULL){
                      while(yyval->sibling != NULL) yyval = yyval->sibling;
                      yyval->sibling = yyvsp[0];
                      yyval = yyvsp[-1];
                    }   
                    else yyval = yyvsp[0];     
                 }
#line 1481 "parse.tab.c"
    break;

  case 24: /* statement-lista: statement  */
#line 207 "parse.y"
                            { yyval = yyvsp[0]; }
#line 1487 "parse.tab.c"
    break;

  case 25: /* statement: expr-decl  */
#line 210 "parse.y"
                        {
                yyval = yyvsp[0];
              }
#line 1495 "parse.tab.c"
    break;

  case 26: /* statement: composto-decl  */
#line 213 "parse.y"
                            {
                yyval = yyvsp[0];
              }
#line 1503 "parse.tab.c"
    break;

  case 27: /* statement: selec-decl  */
#line 216 "parse.y"
                         {
                yyval = yyvsp[0];
              }
#line 1511 "parse.tab.c"
    break;

  case 28: /* statement: iter-decl  */
#line 219 "parse.y"
                        {
                yyval = yyvsp[0];
              }
#line 1519 "parse.tab.c"
    break;

  case 29: /* statement: retorno-decl  */
#line 222 "parse.y"
                           {
                yyval = yyvsp[0];
              }
#line 1527 "parse.tab.c"
    break;

  case 30: /* expr-decl: expr SEMICOLON  */
#line 227 "parse.y"
                             {
                yyval = yyvsp[-1];
              }
#line 1535 "parse.tab.c"
    break;

  case 31: /* expr-decl: SEMICOLON  */
#line 230 "parse.y"
                        {
                yyval = NULL;
              }
#line 1543 "parse.tab.c"
    break;

  case 32: /* selec-decl: IF LPAREN expr RPAREN statement  */
#line 235 "parse.y"
                                              { 
                yyval = syntax_tree_alloc_node(2);
                yyval->node_data->token = "IF";
                yyval->n_child = 2;
                yyval->child[0] = yyvsp[-2];
                yyval->child[1] = yyvsp[0];
              }
#line 1555 "parse.tab.c"
    break;

  case 33: /* selec-decl: IF LPAREN expr RPAREN statement ELSE statement  */
#line 242 "parse.y"
                                                             {
                yyval = syntax_tree_alloc_node(3);
                yyval->node_data->token = "IF-ELSE";
                yyval->n_child = 3;
                yyval->child[0] = yyvsp[-4];
                yyval->child[1] = yyvsp[-2];
                yyval->child[2] = yyvsp[0];
              }
#line 1568 "parse.tab.c"
    break;

  case 34: /* iter-decl: WHILE LPAREN expr RPAREN statement-lista  */
#line 252 "parse.y"
                                                       {
                yyval = syntax_tree_alloc_node(2);
                yyval->node_data->token = "WHILE";
                yyval->n_child = 2;
                yyval->child[0] = yyvsp[-2];
                yyval->child[1] = yyvsp[0];
              }
#line 1580 "parse.tab.c"
    break;

  case 35: /* retorno-decl: RETURN SEMICOLON  */
#line 261 "parse.y"
                                 {
                 yyval = syntax_tree_alloc_node(0);
                 yyval->node_data->token = "RETURN";
                 yyval->n_child = 0;
                 yyval->node_data->datatype = VOID_T;
              }
#line 1591 "parse.tab.c"
    break;

  case 36: /* retorno-decl: RETURN expr SEMICOLON  */
#line 267 "parse.y"
                                      {
                yyval = syntax_tree_alloc_node(1);
                yyval->node_data->token = "RETURN";
                yyval->n_child = 1;
                yyval->child[0] = yyvsp[-1];
              }
#line 1602 "parse.tab.c"
    break;

  case 37: /* expr: var ASS expr  */
#line 275 "parse.y"
                     {
          yyval = syntax_tree_alloc_node(2);
          yyval->node_data->token = "ASSIGN";
          yyval->child[0] = yyvsp[-2];
          yyval->child[1] = yyvsp[0];
          yyval->n_child = 2;
        }
#line 1614 "parse.tab.c"
    break;

  case 38: /* expr: simples-expr  */
#line 282 "parse.y"
                     {
          yyval = yyvsp[0];
        }
#line 1622 "parse.tab.c"
    break;

  case 39: /* var: id  */
#line 287 "parse.y"
           { yyval = yyvsp[0]; }
#line 1628 "parse.tab.c"
    break;

  case 40: /* var: id LBRA expr RBRA  */
#line 288 "parse.y"
                          {
          yyval = yyvsp[-3];
          yyval->n_child = 1;
          yyval->node_data->datatype = VARIAVEL;
          yyval->node_data->datatype = INTEGER_T;
          yyval->child[0] = yyvsp[-1];
        }
#line 1640 "parse.tab.c"
    break;

  case 41: /* simples-expr: soma-expr relacional soma-expr  */
#line 297 "parse.y"
                                               {
                  yyval = yyvsp[-1];
                  yyval->n_child = 2;
                  yyvsp[-1]->child[0] = yyvsp[-2];
                  yyvsp[-1]->child[1] = yyvsp[0];
              }
#line 1651 "parse.tab.c"
    break;

  case 42: /* simples-expr: soma-expr  */
#line 303 "parse.y"
                          {
                  yyval = yyvsp[0];
              }
#line 1659 "parse.tab.c"
    break;

  case 43: /* relacional: LET  */
#line 308 "parse.y"
                  {
                yyval=syntax_tree_alloc_node(0);
                yyval->node_data->token = "<=";
                yyval->node_data->lexem = "<=";
              }
#line 1669 "parse.tab.c"
    break;

  case 44: /* relacional: LT  */
#line 313 "parse.y"
                 {
                yyval=syntax_tree_alloc_node(0);
                yyval->node_data->token = "<";
                yyval->node_data->lexem = "<";
              }
#line 1679 "parse.tab.c"
    break;

  case 45: /* relacional: GT  */
#line 318 "parse.y"
                 {
                yyval=syntax_tree_alloc_node(0);
                yyval->node_data->token = ">";
                yyval->node_data->lexem = ">";
              }
#line 1689 "parse.tab.c"
    break;

  case 46: /* relacional: GET  */
#line 323 "parse.y"
                  {
                yyval=syntax_tree_alloc_node(0);
                yyval->node_data->token = ">=";
                yyval->node_data->lexem = ">=";
              }
#line 1699 "parse.tab.c"
    break;

  case 47: /* relacional: EQL  */
#line 328 "parse.y"
                  {
                yyval=syntax_tree_alloc_node(0);
                yyval->node_data->token = "==";
                yyval->node_data->lexem = "==";
              }
#line 1709 "parse.tab.c"
    break;

  case 48: /* relacional: NEQL  */
#line 333 "parse.y"
                   {
                yyval=syntax_tree_alloc_node(0);
                yyval->node_data->token = "!=";
                yyval->node_data->lexem = "!=";
              }
#line 1719 "parse.tab.c"
    break;

  case 49: /* soma-expr: soma-expr soma termo  */
#line 340 "parse.y"
                                  {
                yyval = yyvsp[-1];
                yyval->n_child = 2;
                yyvsp[-1]->child[0] = yyvsp[-2];
                yyvsp[-1]->child[1] = yyvsp[0];
              }
#line 1730 "parse.tab.c"
    break;

  case 50: /* soma-expr: termo  */
#line 346 "parse.y"
                    {
                yyval = yyvsp[0];
              }
#line 1738 "parse.tab.c"
    break;

  case 51: /* soma: PLUS  */
#line 351 "parse.y"
             {
          yyval = syntax_tree_alloc_node(0);
          yyval->node_data->token = "+";
          yyval->node_data->lexem = "+";
        }
#line 1748 "parse.tab.c"
    break;

  case 52: /* soma: MINUS  */
#line 356 "parse.y"
              {
          yyval = syntax_tree_alloc_node(0);
          yyval->node_data->token = "-";
          yyval->node_data->lexem = "-";
      }
#line 1758 "parse.tab.c"
    break;

  case 53: /* termo: termo mult fator  */
#line 363 "parse.y"
                           {
            yyval = yyvsp[-1];
            yyval->n_child = 2;
            yyvsp[-1]->child[0] = yyvsp[-2];
            yyvsp[-1]->child[1] = yyvsp[0];
  }
#line 1769 "parse.tab.c"
    break;

  case 54: /* termo: fator  */
#line 369 "parse.y"
                 {
          yyval = yyvsp[0];
       }
#line 1777 "parse.tab.c"
    break;

  case 55: /* mult: TIMES  */
#line 374 "parse.y"
              {
          yyval = syntax_tree_alloc_node(0);
          yyval->node_data->token = "*";
          yyval->node_data->lexem = "*";
        }
#line 1787 "parse.tab.c"
    break;

  case 56: /* mult: DIV  */
#line 379 "parse.y"
            {
          yyval = syntax_tree_alloc_node(0);
          yyval->node_data->token = "/";
          yyval->node_data->lexem = "/";
      }
#line 1797 "parse.tab.c"
    break;

  case 57: /* fator: LPAREN expr RPAREN  */
#line 386 "parse.y"
                             {yyval = yyvsp[-1];}
#line 1803 "parse.tab.c"
    break;

  case 58: /* fator: var  */
#line 387 "parse.y"
              {yyval = yyvsp[0];}
#line 1809 "parse.tab.c"
    break;

  case 59: /* fator: ativacao  */
#line 388 "parse.y"
                   {yyval = yyvsp[0];}
#line 1815 "parse.tab.c"
    break;

  case 60: /* fator: num  */
#line 389 "parse.y"
              {yyval = yyvsp[0]; }
#line 1821 "parse.tab.c"
    break;

  case 61: /* ativacao: id LPAREN args RPAREN  */
#line 392 "parse.y"
                                  {
            yyval = yyvsp[-3];
            yyval->n_child = 1;
            yyval->child[0] = yyvsp[-1];
          }
#line 1831 "parse.tab.c"
    break;

  case 62: /* args: arg-list  */
#line 399 "parse.y"
                 {
          yyval = yyvsp[0];
        }
#line 1839 "parse.tab.c"
    break;

  case 63: /* args: %empty  */
#line 402 "parse.y"
        { yyval = NULL; }
#line 1845 "parse.tab.c"
    break;

  case 64: /* arg-list: arg-list COMMA expr  */
#line 405 "parse.y"
                                {
                  yyval = yyvsp[-2];
                  L_mst_expr->sibling = yyvsp[0];
                  L_mst_expr = yyvsp[0]; 
                }
#line 1855 "parse.tab.c"
    break;

  case 65: /* arg-list: expr  */
#line 410 "parse.y"
                     { 
                yyval = yyvsp[0];
                L_mst_expr = yyvsp[0]; 
              }
#line 1864 "parse.tab.c"
    break;

  case 66: /* id: ID  */
#line 416 "parse.y"
         {
      yyval = syntax_tree_alloc_node(3);
      yyval->node_data->token = "ID";
      yyval->node_data->lexem = deepCopy(lex);
      yyval->node_data->line = lineno;
    }
#line 1875 "parse.tab.c"
    break;

  case 67: /* num: NUMBER  */
#line 424 "parse.y"
              {
    yyval = syntax_tree_alloc_node(3);
    yyval->node_data->token = "NUMBER";
    yyval->node_data->lexem = deepCopy(lex);
    yyval->node_data->datatype = INTEGER_T;
  }
#line 1886 "parse.tab.c"
    break;


#line 1890 "parse.tab.c"

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

#line 432 "parse.y"


static int yylex(){
  TokenNode* curr_token = next_token();
  last_token = tok_num;
  tok_num = END;
  char *tok;
  if(curr_token){
    lineno = curr_token->line;
    tok = curr_token->token;
    strcpy(lex, curr_token->lexem);
    tok_num = tok_to_num(tok);
  }else{
   //printf("Last token received!\n");
  }
  //if(lex) printf("Current Token: %d - %d Lexem: %s Num: %d\n", tok_num, last_token, lex, tok_num);
  //else printf("Current Token: %s\n", tok);

  if(last_token == SEMICOLON && tok_num == SEMICOLON){
    printf("ERRO SINTATICO: syntax error LINHA: %d\n", lineno);
    exit(1);
  }
   
  return tok_num;
}

int tok_to_num(char* tok){
  if(!strcmp(tok, "ID")) return ID;
  if(!strcmp(tok, "IF")) return IF;
  if(!strcmp(tok, "ELSE"))return ELSE;
  if(!strcmp(tok, "INT"))return INT;
  if(!strcmp(tok, "VOID"))return VOID;
  if(!strcmp(tok, "WHILE"))return WHILE;
  if(!strcmp(tok, "RETURN"))return RETURN;

  if(!strcmp(tok, "="))return ASS;
  if(!strcmp(tok, "=="))return EQL;
  if(!strcmp(tok, "!="))return NEQL;
  if(!strcmp(tok, ">")) return GT;
  if(!strcmp(tok, "<")) return LT;
  if(!strcmp(tok, "<="))return LET;
  if(!strcmp(tok, ">="))return GET;
  if(!strcmp(tok, "+"))return PLUS;
  if(!strcmp(tok, "-"))return MINUS;
  if(!strcmp(tok, "*"))return TIMES;
  if(!strcmp(tok, "/"))return DIV;
  if(!strcmp(tok, "["))return LBRA;
  if(!strcmp(tok, "]"))return RBRA;
  if(!strcmp(tok, "("))return LPAREN;
  if(!strcmp(tok, ")"))return RPAREN;
  if(!strcmp(tok, "{"))return LKEY;
  if(!strcmp(tok, "}")) return RKEY;
  if(!strcmp(tok, ","))return COMMA;
  if(!strcmp(tok, ";"))return SEMICOLON;

  if(!strcmp(tok, "NUMBER"))return NUMBER;
  
  if(!strcmp(tok, "END"))return END;
  //printf("Token not found: %s\n", tok);
  return ERR;
}

char * deepCopy(char * source){ 
    if (source==NULL) return NULL;
    int n = strlen(source)+1;
    char* target = malloc(sizeof(char) * n);
    if (target==NULL) printf("Out of Memory\n");
    else strcpy(target,source);

    return target;
}

syntax_tree parseTree(){
  yyparse();
  syntax_tree_display(tree);
  return tree;
}

void yyerror(char *c){
  if(yychar != ERR && yychar != END){
    printf("ERRO SINTATICO: %s LINHA: %d\n", c, lineno);
    exit(1);
  }
}
