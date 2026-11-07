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
#line 3 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);
extern int yylineno;
extern char *yytext;
int parse_errors = 0;

/* x += e  ->  Assign(x, "+=", e) */
static Node *assign(char *name, const char *op, Node *e) {
    Node *n = mk_op(N_ASSIGN, op, e, NULL, yylineno);
    n->name = name;
    return n;
}
static Node *incdec(char *name, const char *op, int prefix) {
    Node *n = mk(N_INCDEC, yylineno);
    n->name = name; n->op = strdup(op); n->ival = prefix;
    return n;
}

#line 96 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FNUM = 4,                       /* FNUM  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_DOUBLE = 8,                     /* DOUBLE  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_NE = 17,                        /* NE  */
  YYSYMBOL_LE = 18,                        /* LE  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_INC = 22,                       /* INC  */
  YYSYMBOL_DEC = 23,                       /* DEC  */
  YYSYMBOL_ADD_ASSIGN = 24,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 25,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 26,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 27,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 28,                /* MOD_ASSIGN  */
  YYSYMBOL_LOWER_THAN_ELSE = 29,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '<'  */
  YYSYMBOL_32_ = 32,                       /* '>'  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_UMINUS = 38,                    /* UMINUS  */
  YYSYMBOL_39_ = 39,                       /* '!'  */
  YYSYMBOL_40_ = 40,                       /* '('  */
  YYSYMBOL_41_ = 41,                       /* ')'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* '{'  */
  YYSYMBOL_44_ = 44,                       /* '}'  */
  YYSYMBOL_45_ = 45,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_func = 48,                      /* func  */
  YYSYMBOL_type = 49,                      /* type  */
  YYSYMBOL_params = 50,                    /* params  */
  YYSYMBOL_param_list = 51,                /* param_list  */
  YYSYMBOL_param = 52,                     /* param  */
  YYSYMBOL_block = 53,                     /* block  */
  YYSYMBOL_stmt_list = 54,                 /* stmt_list  */
  YYSYMBOL_stmt = 55,                      /* stmt  */
  YYSYMBOL_for_init = 56,                  /* for_init  */
  YYSYMBOL_decl = 57,                      /* decl  */
  YYSYMBOL_init_list = 58,                 /* init_list  */
  YYSYMBOL_init = 59,                      /* init  */
  YYSYMBOL_expr_opt = 60,                  /* expr_opt  */
  YYSYMBOL_expr = 61,                      /* expr  */
  YYSYMBOL_args = 62,                      /* args  */
  YYSYMBOL_arg_list = 63                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

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


#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif


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

#if 1


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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};


# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   315

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130


#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,    37,     2,     2,
      40,    41,    35,    33,    42,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
      31,    30,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    38
};

#if YYDEBUG

static const yytype_uint8 yyrline[] =
{
       0,    68,    68,    69,    73,    79,    80,    81,    85,    86,
      87,    91,    92,    96,   100,   104,   105,   109,   110,   111,
     112,   113,   115,   117,   119,   122,   123,   127,   128,   132,
     136,   137,   141,   142,   146,   147,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   185,   186,   190,
     191
};
#endif


#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "FNUM", "ID",
  "STRING", "INT", "DOUBLE", "VOID", "IF", "ELSE", "WHILE", "FOR",
  "RETURN", "BREAK", "EQ", "NE", "LE", "GE", "AND", "OR", "INC", "DEC",
  "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "LOWER_THAN_ELSE", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "UMINUS", "'!'", "'('", "')'", "','", "'{'", "'}'", "';'",
  "$accept", "program", "func", "type", "params", "param_list", "param",
  "block", "stmt_list", "stmt", "for_init", "decl", "init_list", "init",
  "expr_opt", "expr", "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-55)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-10)

#define yytable_value_is_error(Yyn) \
  0

static const yytype_int16 yypact[] =
{
       0,   -55,   -55,   -55,   122,   -55,    -2,   -55,   -55,   -38,
      58,   -31,    32,    10,    19,   -55,   -55,    29,     0,   -55,
     -55,   -55,    93,   -55,   -55,    53,   -55,    22,    42,    46,
      30,    43,    84,    87,    30,    30,    30,   -55,   -55,    89,
     -55,   -55,    59,   166,   -55,   -55,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    51,    64,   251,   -55,   -55,
     -55,   -55,   -55,   173,    81,    92,   -55,   -55,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,   -55,   251,   251,   251,   251,   251,   251,   251,    83,
     105,   199,   225,    78,   -55,   -55,   -55,   -55,    30,    89,
     278,   278,   119,   119,   258,    -5,   119,   119,    82,    82,
     -55,   -55,   -55,   -55,    30,   136,   136,    30,   251,   -55,
     251,   115,   -55,    90,   136,    30,   -55,   116,   136,   -55
};

static const yytype_int8 yydefact[] =
{
       0,     5,     6,     7,     0,     2,     0,     1,     3,     0,
       8,     7,     0,     0,    10,    11,    13,     0,     0,    15,
       4,    12,     0,    62,    63,    65,    64,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,    14,    20,     0,
      17,    16,     0,     0,    59,    60,     0,     0,     0,     0,
       0,     0,    67,     0,     0,    34,     0,    35,    26,    57,
      58,    55,    56,     0,    32,    29,    30,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    37,    38,    39,    40,    41,    36,    69,     0,
      68,     0,     0,     0,    28,    27,    25,    61,     0,     0,
      44,    45,    48,    49,    43,    42,    46,    47,    50,    51,
      52,    53,    54,    66,     0,     0,     0,    34,    33,    31,
      70,    21,    23,     0,     0,    34,    22,     0,     0,    24
};


static const yytype_int16 yypgoto[] =
{
     -55,   -55,   156,   110,   -55,   -55,   143,   145,   -55,    -3,
     -55,   108,   -55,    65,   -54,   -30,   -55,   -55
};


static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,    39,    13,    14,    15,    40,    22,    41,
      93,    42,    65,    66,    56,    43,    89,    90
};

static const yytype_int16 yytable[] =
{
      57,    95,    10,     9,    61,    62,    63,     1,     2,     3,
      -9,    68,    69,    70,    71,    72,    82,    83,    84,    85,
      86,    87,    88,    91,    92,    57,    74,    75,    76,    77,
      78,    79,    80,    23,    24,    25,    26,    16,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    17,    32,    33,    23,    24,    25,    26,     1,     2,
       3,    18,    53,   123,    34,     1,     2,    11,   118,    35,
      36,   127,    19,    32,    33,    44,    45,    46,    47,    48,
      49,    50,    54,    51,   120,    34,    55,    57,    58,    59,
      35,    36,    60,    52,    64,    57,    23,    24,    25,    26,
       1,     2,     3,    27,    67,    28,    29,    30,    31,    96,
       6,    98,   121,   122,     6,    32,    33,    78,    79,    80,
      12,   126,     7,   117,   113,   129,   124,    34,    12,     1,
       2,     3,    35,    36,    99,   125,    19,    37,    38,    23,
      24,    25,    26,     1,     2,     3,    27,   114,    28,    29,
      30,    31,    76,    77,    78,    79,    80,   128,    32,    33,
       8,    21,    20,    94,   119,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,    35,    36,     0,     0,    19,
       0,    38,    68,    69,    70,    71,    72,    73,     0,    68,
      69,    70,    71,    72,    73,     0,     0,    74,    75,    76,
      77,    78,    79,    80,    74,    75,    76,    77,    78,    79,
      80,    81,     0,     0,    97,    68,    69,    70,    71,    72,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      74,    75,    76,    77,    78,    79,    80,     0,     0,     0,
     115,    68,    69,    70,    71,    72,    73,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    74,    75,    76,    77,
      78,    79,    80,     0,     0,     0,   116,    68,    69,    70,
      71,    72,    73,     0,    68,    69,    70,    71,     0,     0,
       0,     0,    74,    75,    76,    77,    78,    79,    80,    74,
      75,    76,    77,    78,    79,    80,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      75,    76,    77,    78,    79,    80
};

static const yytype_int16 yycheck[] =
{
      30,    55,    40,     5,    34,    35,    36,     7,     8,     9,
      41,    16,    17,    18,    19,    20,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    31,    32,    33,    34,
      35,    36,    37,     3,     4,     5,     6,     5,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    41,    22,    23,     3,     4,     5,     6,     7,     8,
       9,    42,    40,   117,    34,     7,     8,     9,    98,    39,
      40,   125,    43,    22,    23,    22,    23,    24,    25,    26,
      27,    28,    40,    30,   114,    34,    40,   117,    45,     5,
      39,    40,     5,    40,     5,   125,     3,     4,     5,     6,
       7,     8,     9,    10,    45,    12,    13,    14,    15,    45,
       0,    30,   115,   116,     4,    22,    23,    35,    36,    37,
      10,   124,     0,    45,    41,   128,    11,    34,    18,     7,
       8,     9,    39,    40,    42,    45,    43,    44,    45,     3,
       4,     5,     6,     7,     8,     9,    10,    42,    12,    13,
      14,    15,    33,    34,    35,    36,    37,    41,    22,    23,
       4,    18,    17,    55,    99,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    43,
      -1,    45,    16,    17,    18,    19,    20,    21,    -1,    16,
      17,    18,    19,    20,    21,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    31,    32,    33,    34,    35,    36,
      37,    45,    -1,    -1,    41,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      41,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    41,    16,    17,    18,
      19,    20,    21,    -1,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    31,
      32,    33,    34,    35,    36,    37,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37
};

static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    47,    48,    49,     0,    48,     5,
      40,     9,    49,    50,    51,    52,     5,    41,    42,    43,
      53,    52,    54,     3,     4,     5,     6,    10,    12,    13,
      14,    15,    22,    23,    34,    39,    40,    44,    45,    49,
      53,    55,    57,    61,    22,    23,    24,    25,    26,    27,
      28,    30,    40,    40,    40,    40,    60,    61,    45,     5,
       5,    61,    61,    61,     5,    58,    59,    45,    16,    17,
      18,    19,    20,    21,    31,    32,    33,    34,    35,    36,
      37,    45,    61,    61,    61,    61,    61,    61,    61,    62,
      63,    61,    61,    56,    57,    60,    45,    41,    30,    42,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    41,    42,    41,    41,    45,    61,    59,
      61,    55,    55,    60,    11,    45,    55,    60,    41,    55
};


static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    48,    49,    49,    49,    50,    50,
      50,    51,    51,    52,    53,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    56,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    62,    62,    63,
      63
};

static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     6,     1,     1,     1,     0,     1,
       1,     1,     3,     2,     3,     0,     2,     1,     2,     2,
       1,     5,     7,     5,     9,     3,     2,     1,     1,     2,
       1,     3,     1,     3,     0,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
       2,     3,     1,     1,     1,     1,     4,     0,     1,     1,
       3
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

#define YYERRCODE YYUNDEF



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



static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}


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

int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */



#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{

  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      int yyxbegin = yyn < 0 ? -yyn : 0;

      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr

static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  int yycount = 0;

  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };

  const char *yyformat = YY_NULLPTR;
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;


  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }
    
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}



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


YYSTYPE yylval;

int yynerrs;




int
yyparse (void)
{
    yy_state_fast_t yystate = 0;

    int yyerrstatus = 0;
    YYPTRDIFF_T yystacksize = YYINITDEPTH;


    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;


    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;

  int yyresult;

  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;

  YYSTYPE yyval;


  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;

yynewstate:
  yyssp++;


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

      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else 
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


yybackup:
  
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

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
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }


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

  if (yyerrstatus)
    yyerrstatus--;


  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  yychar = YYEMPTY;
  goto yynewstate;


yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


yyreduce:

  yylen = yyr2[yyn];

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
  case 2: /* program: func  */
#line 68 "parser.y"
                            { root = add(mk(N_PROGRAM, 1), (yyvsp[0].node)); (yyval.node) = root; }
#line 1533 "parser.tab.c"
    break;

  case 3: /* program: program func  */
#line 69 "parser.y"
                            { (yyval.node) = add((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1539 "parser.tab.c"
    break;

  case 4: /* func: type ID '(' params ')' block  */
#line 74 "parser.y"
                            { (yyval.node) = mk(N_FUNC, (yyvsp[0].node)->line); (yyval.node)->name = (yyvsp[-4].str); (yyval.node)->type = (yyvsp[-5].type);
                              add(add((yyval.node), (yyvsp[-2].node)), (yyvsp[0].node)); }
#line 1546 "parser.tab.c"
    break;

  case 5: /* type: INT  */
#line 79 "parser.y"
                            { (yyval.type) = T_INT; }
#line 1552 "parser.tab.c"
    break;

  case 6: /* type: DOUBLE  */
#line 80 "parser.y"
                            { (yyval.type) = T_DOUBLE; }
#line 1558 "parser.tab.c"
    break;

  case 7: /* type: VOID  */
#line 81 "parser.y"
                            { (yyval.type) = T_VOID; }
#line 1564 "parser.tab.c"
    break;

  case 8: /* params: %empty  */
#line 85 "parser.y"
                                    { (yyval.node) = mk(N_PARAMS, yylineno); }
#line 1570 "parser.tab.c"
    break;

  case 9: /* params: VOID  */
#line 86 "parser.y"
                            { (yyval.node) = mk(N_PARAMS, yylineno); }
#line 1576 "parser.tab.c"
    break;

  case 11: /* param_list: param  */
#line 91 "parser.y"
                            { (yyval.node) = add(mk(N_PARAMS, yylineno), (yyvsp[0].node)); }
#line 1582 "parser.tab.c"
    break;

  case 12: /* param_list: param_list ',' param  */
#line 92 "parser.y"
                            { (yyval.node) = add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1588 "parser.tab.c"
    break;

  case 13: /* param: type ID  */
#line 96 "parser.y"
                            { (yyval.node) = mk(N_PARAM, yylineno); (yyval.node)->type = (yyvsp[-1].type); (yyval.node)->name = (yyvsp[0].str); }
#line 1594 "parser.tab.c"
    break;

  case 14: /* block: '{' stmt_list '}'  */
#line 100 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1600 "parser.tab.c"
    break;

  case 15: /* stmt_list: %empty  */
#line 104 "parser.y"
                                    { (yyval.node) = mk(N_BLOCK, yylineno); }
#line 1606 "parser.tab.c"
    break;

  case 16: /* stmt_list: stmt_list stmt  */
#line 105 "parser.y"
                            { (yyval.node) = add((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1612 "parser.tab.c"
    break;

  case 19: /* stmt: expr ';'  */
#line 111 "parser.y"
                            { (yyval.node) = add(mk(N_EXPR, yylineno), (yyvsp[-1].node)); }
#line 1618 "parser.tab.c"
    break;

  case 20: /* stmt: ';'  */
#line 112 "parser.y"
                            { (yyval.node) = mk(N_EMPTY, yylineno); }
#line 1624 "parser.tab.c"
    break;

  case 21: /* stmt: IF '(' expr ')' stmt  */
#line 114 "parser.y"
                            { (yyval.node) = add(add(add(mk(N_IF, (yyvsp[-2].node)->line), (yyvsp[-2].node)), (yyvsp[0].node)), NULL); }
#line 1630 "parser.tab.c"
    break;

  case 22: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 116 "parser.y"
                            { (yyval.node) = add(add(add(mk(N_IF, (yyvsp[-4].node)->line), (yyvsp[-4].node)), (yyvsp[-2].node)), (yyvsp[0].node)); }
#line 1636 "parser.tab.c"
    break;

  case 23: /* stmt: WHILE '(' expr ')' stmt  */
#line 118 "parser.y"
                            { (yyval.node) = add(add(mk(N_WHILE, (yyvsp[-2].node)->line), (yyvsp[-2].node)), (yyvsp[0].node)); }
#line 1642 "parser.tab.c"
    break;

  case 24: /* stmt: FOR '(' for_init ';' expr_opt ';' expr_opt ')' stmt  */
#line 120 "parser.y"
                            { (yyval.node) = mk(N_FOR, yylineno);
                              add(add(add(add((yyval.node), (yyvsp[-6].node)), (yyvsp[-4].node)), (yyvsp[-2].node)), (yyvsp[0].node)); }
#line 1649 "parser.tab.c"
    break;

  case 25: /* stmt: RETURN expr_opt ';'  */
#line 122 "parser.y"
                            { (yyval.node) = add(mk(N_RETURN, yylineno), (yyvsp[-1].node)); }
#line 1655 "parser.tab.c"
    break;

  case 26: /* stmt: BREAK ';'  */
#line 123 "parser.y"
                            { (yyval.node) = mk(N_BREAK, yylineno); }
#line 1661 "parser.tab.c"
    break;

  case 27: /* for_init: expr_opt  */
#line 127 "parser.y"
                            { (yyval.node) = (yyvsp[0].node) ? add(mk(N_EXPR, yylineno), (yyvsp[0].node)) : NULL; }
#line 1667 "parser.tab.c"
    break;

  case 29: /* decl: type init_list  */
#line 132 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); (yyval.node)->type = (yyvsp[-1].type); }
#line 1673 "parser.tab.c"
    break;

  case 30: /* init_list: init  */
#line 136 "parser.y"
                            { (yyval.node) = add(mk(N_DECL, yylineno), (yyvsp[0].node)); }
#line 1679 "parser.tab.c"
    break;

  case 31: /* init_list: init_list ',' init  */
#line 137 "parser.y"
                            { (yyval.node) = add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1685 "parser.tab.c"
    break;

  case 32: /* init: ID  */
#line 141 "parser.y"
                            { (yyval.node) = mk(N_VARINIT, yylineno); (yyval.node)->name = (yyvsp[0].str); }
#line 1691 "parser.tab.c"
    break;

  case 33: /* init: ID '=' expr  */
#line 142 "parser.y"
                            { (yyval.node) = add(mk(N_VARINIT, yylineno), (yyvsp[0].node)); (yyval.node)->name = (yyvsp[-2].str); }
#line 1697 "parser.tab.c"
    break;

  case 34: /* expr_opt: %empty  */
#line 146 "parser.y"
                                    { (yyval.node) = NULL; }
#line 1703 "parser.tab.c"
    break;

  case 36: /* expr: ID '=' expr  */
#line 151 "parser.y"
                            { (yyval.node) = assign((yyvsp[-2].str), "=",  (yyvsp[0].node)); }
#line 1709 "parser.tab.c"
    break;

  case 37: /* expr: ID ADD_ASSIGN expr  */
#line 152 "parser.y"
                            { (yyval.node) = assign((yyvsp[-2].str), "+=", (yyvsp[0].node)); }
#line 1715 "parser.tab.c"
    break;

  case 38: /* expr: ID SUB_ASSIGN expr  */
#line 153 "parser.y"
                            { (yyval.node) = assign((yyvsp[-2].str), "-=", (yyvsp[0].node)); }
#line 1721 "parser.tab.c"
    break;

  case 39: /* expr: ID MUL_ASSIGN expr  */
#line 154 "parser.y"
                            { (yyval.node) = assign((yyvsp[-2].str), "*=", (yyvsp[0].node)); }
#line 1727 "parser.tab.c"
    break;

  case 40: /* expr: ID DIV_ASSIGN expr  */
#line 155 "parser.y"
                            { (yyval.node) = assign((yyvsp[-2].str), "/=", (yyvsp[0].node)); }
#line 1733 "parser.tab.c"
    break;

  case 41: /* expr: ID MOD_ASSIGN expr  */
#line 156 "parser.y"
                            { (yyval.node) = assign((yyvsp[-2].str), "%=", (yyvsp[0].node)); }
#line 1739 "parser.tab.c"
    break;

  case 42: /* expr: expr OR expr  */
#line 157 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "||", (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1745 "parser.tab.c"
    break;

  case 43: /* expr: expr AND expr  */
#line 158 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "&&", (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1751 "parser.tab.c"
    break;

  case 44: /* expr: expr EQ expr  */
#line 159 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "==", (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1757 "parser.tab.c"
    break;

  case 45: /* expr: expr NE expr  */
#line 160 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "!=", (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1763 "parser.tab.c"
    break;

  case 46: /* expr: expr '<' expr  */
#line 161 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "<",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1769 "parser.tab.c"
    break;

  case 47: /* expr: expr '>' expr  */
#line 162 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, ">",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1775 "parser.tab.c"
    break;

  case 48: /* expr: expr LE expr  */
#line 163 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "<=", (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1781 "parser.tab.c"
    break;

  case 49: /* expr: expr GE expr  */
#line 164 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, ">=", (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1787 "parser.tab.c"
    break;

  case 50: /* expr: expr '+' expr  */
#line 165 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "+",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1793 "parser.tab.c"
    break;

  case 51: /* expr: expr '-' expr  */
#line 166 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "-",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1799 "parser.tab.c"
    break;

  case 52: /* expr: expr '*' expr  */
#line 167 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "*",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1805 "parser.tab.c"
    break;

  case 53: /* expr: expr '/' expr  */
#line 168 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "/",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1811 "parser.tab.c"
    break;

  case 54: /* expr: expr '%' expr  */
#line 169 "parser.y"
                            { (yyval.node) = mk_op(N_BINOP, "%",  (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1817 "parser.tab.c"
    break;

  case 55: /* expr: '-' expr  */
#line 170 "parser.y"
                            { (yyval.node) = mk_op(N_UNOP, "-", (yyvsp[0].node), NULL, yylineno); }
#line 1823 "parser.tab.c"
    break;

  case 56: /* expr: '!' expr  */
#line 171 "parser.y"
                            { (yyval.node) = mk_op(N_UNOP, "!", (yyvsp[0].node), NULL, yylineno); }
#line 1829 "parser.tab.c"
    break;

  case 57: /* expr: INC ID  */
#line 172 "parser.y"
                            { (yyval.node) = incdec((yyvsp[0].str), "++", 1); }
#line 1835 "parser.tab.c"
    break;

  case 58: /* expr: DEC ID  */
#line 173 "parser.y"
                            { (yyval.node) = incdec((yyvsp[0].str), "--", 1); }
#line 1841 "parser.tab.c"
    break;

  case 59: /* expr: ID INC  */
#line 174 "parser.y"
                            { (yyval.node) = incdec((yyvsp[-1].str), "++", 0); }
#line 1847 "parser.tab.c"
    break;

  case 60: /* expr: ID DEC  */
#line 175 "parser.y"
                            { (yyval.node) = incdec((yyvsp[-1].str), "--", 0); }
#line 1853 "parser.tab.c"
    break;

  case 61: /* expr: '(' expr ')'  */
#line 176 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1859 "parser.tab.c"
    break;

  case 62: /* expr: NUM  */
#line 177 "parser.y"
                            { (yyval.node) = mk(N_INT, yylineno);   (yyval.node)->ival = (yyvsp[0].ival); }
#line 1865 "parser.tab.c"
    break;

  case 63: /* expr: FNUM  */
#line 178 "parser.y"
                            { (yyval.node) = mk(N_FLOAT, yylineno); (yyval.node)->fval = (yyvsp[0].fval); }
#line 1871 "parser.tab.c"
    break;

  case 64: /* expr: STRING  */
#line 179 "parser.y"
                            { (yyval.node) = mk(N_STR, yylineno);   (yyval.node)->name = (yyvsp[0].str); }
#line 1877 "parser.tab.c"
    break;

  case 65: /* expr: ID  */
#line 180 "parser.y"
                            { (yyval.node) = mk(N_VAR, yylineno);   (yyval.node)->name = (yyvsp[0].str); }
#line 1883 "parser.tab.c"
    break;

  case 66: /* expr: ID '(' args ')'  */
#line 181 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); (yyval.node)->name = (yyvsp[-3].str); }
#line 1889 "parser.tab.c"
    break;

  case 67: /* args: %empty  */
#line 185 "parser.y"
                                    { (yyval.node) = mk(N_CALL, yylineno); }
#line 1895 "parser.tab.c"
    break;

  case 69: /* arg_list: expr  */
#line 190 "parser.y"
                            { (yyval.node) = add(mk(N_CALL, yylineno), (yyvsp[0].node)); }
#line 1901 "parser.tab.c"
    break;

  case 70: /* arg_list: arg_list ',' expr  */
#line 191 "parser.y"
                            { (yyval.node) = add((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1907 "parser.tab.c"
    break;


#line 1911 "parser.tab.c"

      default: break;
    }

  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


yyerrlab:
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);

  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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

  goto yyerrlab1;


yyerrorlab:
  if (0)
    YYERROR;
  ++yynerrs;

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


yyerrlab1:
  yyerrstatus = 3;   

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

yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


yyreturnlab:
  if (yychar != YYEMPTY)
    {
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 194 "parser.y"


void yyerror(const char *s) {
    parse_errors++;
    fprintf(stderr, "Помилка (рядок %d, біля '%s'): %s\n", yylineno, yytext, s);
}
