/* A Bison parser, made by GNU Bison 3.8.2.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 28 "parser.y"
 #include "ast.h" 

#line 52 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    FNUM = 259,                    /* FNUM  */
    ID = 260,                      /* ID  */
    STRING = 261,                  /* STRING  */
    INT = 262,                     /* INT  */
    DOUBLE = 263,                  /* DOUBLE  */
    VOID = 264,                    /* VOID  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    WHILE = 267,                   /* WHILE  */
    FOR = 268,                     /* FOR  */
    RETURN = 269,                  /* RETURN  */
    BREAK = 270,                   /* BREAK  */
    EQ = 271,                      /* EQ  */
    NE = 272,                      /* NE  */
    LE = 273,                      /* LE  */
    GE = 274,                      /* GE  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    INC = 277,                     /* INC  */
    DEC = 278,                     /* DEC  */
    ADD_ASSIGN = 279,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 280,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 281,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 282,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 283,              /* MOD_ASSIGN  */
    LOWER_THAN_ELSE = 284,         /* LOWER_THAN_ELSE  */
    UMINUS = 285                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "parser.y"

    long   ival;
    double fval;
    char  *str;
    Node  *node;
    int    type;

#line 107 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
