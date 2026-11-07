/* parser.y — синтаксичний аналізатор (bison/yacc) для підмножини мови C.
   Будує AST; обчислення та генерація коду — в окремих модулях.          */
%{
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
%}

%code requires { #include "ast.h" }

%define parse.error verbose

%union {
    long   ival;
    double fval;
    char  *str;
    Node  *node;
    int    type;
}

%token <ival> NUM
%token <fval> FNUM
%token <str>  ID STRING
%token INT DOUBLE VOID IF ELSE WHILE FOR RETURN BREAK
%token EQ NE LE GE AND OR INC DEC
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN

// Пріоритети: від найнижчого до найвищого
%nonassoc LOWER_THAN_ELSE          // розв'язання "dangling else"
%nonassoc ELSE
%right '=' ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '!'                  /* унарні оператори */

%type <type> type
%type <node> program func params param_list param block stmt_list stmt
%type <node> decl init_list init for_init expr_opt expr args arg_list

%start program

%%

program
    : func                  { root = add(mk(N_PROGRAM, 1), $1); $$ = root; }
    | program func          { $$ = add($1, $2); }
    ;

func
    : type ID '(' params ')' block
                            { $$ = mk(N_FUNC, $6->line); $$->name = $2; $$->type = $1;
                              add(add($$, $4), $6); }
    ;

type
    : INT                   { $$ = T_INT; }
    | DOUBLE                { $$ = T_DOUBLE; }
    | VOID                  { $$ = T_VOID; }
    ;

params
    : /* порожньо */        { $$ = mk(N_PARAMS, yylineno); }
    | VOID                  { $$ = mk(N_PARAMS, yylineno); }
    | param_list
    ;

param_list
    : param                 { $$ = add(mk(N_PARAMS, yylineno), $1); }
    | param_list ',' param  { $$ = add($1, $3); }
    ;

param
    : type ID               { $$ = mk(N_PARAM, yylineno); $$->type = $1; $$->name = $2; }
    ;

block
    : '{' stmt_list '}'     { $$ = $2; }
    ;

stmt_list
    : /* порожньо */        { $$ = mk(N_BLOCK, yylineno); }
    | stmt_list stmt        { $$ = add($1, $2); }
    ;

stmt
    : block
    | decl ';'
    | expr ';'              { $$ = add(mk(N_EXPR, yylineno), $1); }
    | ';'                   { $$ = mk(N_EMPTY, yylineno); }
    | IF '(' expr ')' stmt %prec LOWER_THAN_ELSE
                            { $$ = add(add(add(mk(N_IF, $3->line), $3), $5), NULL); }
    | IF '(' expr ')' stmt ELSE stmt
                            { $$ = add(add(add(mk(N_IF, $3->line), $3), $5), $7); }
    | WHILE '(' expr ')' stmt
                            { $$ = add(add(mk(N_WHILE, $3->line), $3), $5); }
    | FOR '(' for_init ';' expr_opt ';' expr_opt ')' stmt
                            { $$ = mk(N_FOR, yylineno);
                              add(add(add(add($$, $3), $5), $7), $9); }
    | RETURN expr_opt ';'   { $$ = add(mk(N_RETURN, yylineno), $2); }
    | BREAK ';'             { $$ = mk(N_BREAK, yylineno); }
    ;

for_init
    : expr_opt              { $$ = $1 ? add(mk(N_EXPR, yylineno), $1) : NULL; }
    | decl
    ;

decl
    : type init_list        { $$ = $2; $$->type = $1; }
    ;

init_list
    : init                  { $$ = add(mk(N_DECL, yylineno), $1); }
    | init_list ',' init    { $$ = add($1, $3); }
    ;

init
    : ID                    { $$ = mk(N_VARINIT, yylineno); $$->name = $1; }
    | ID '=' expr           { $$ = add(mk(N_VARINIT, yylineno), $3); $$->name = $1; }
    ;

expr_opt
    : /* порожньо */        { $$ = NULL; }
    | expr
    ;

expr
    : ID '=' expr           { $$ = assign($1, "=",  $3); }
    | ID ADD_ASSIGN expr    { $$ = assign($1, "+=", $3); }
    | ID SUB_ASSIGN expr    { $$ = assign($1, "-=", $3); }
    | ID MUL_ASSIGN expr    { $$ = assign($1, "*=", $3); }
    | ID DIV_ASSIGN expr    { $$ = assign($1, "/=", $3); }
    | ID MOD_ASSIGN expr    { $$ = assign($1, "%=", $3); }
    | expr OR  expr         { $$ = mk_op(N_BINOP, "||", $1, $3, yylineno); }
    | expr AND expr         { $$ = mk_op(N_BINOP, "&&", $1, $3, yylineno); }
    | expr EQ  expr         { $$ = mk_op(N_BINOP, "==", $1, $3, yylineno); }
    | expr NE  expr         { $$ = mk_op(N_BINOP, "!=", $1, $3, yylineno); }
    | expr '<' expr         { $$ = mk_op(N_BINOP, "<",  $1, $3, yylineno); }
    | expr '>' expr         { $$ = mk_op(N_BINOP, ">",  $1, $3, yylineno); }
    | expr LE  expr         { $$ = mk_op(N_BINOP, "<=", $1, $3, yylineno); }
    | expr GE  expr         { $$ = mk_op(N_BINOP, ">=", $1, $3, yylineno); }
    | expr '+' expr         { $$ = mk_op(N_BINOP, "+",  $1, $3, yylineno); }
    | expr '-' expr         { $$ = mk_op(N_BINOP, "-",  $1, $3, yylineno); }
    | expr '*' expr         { $$ = mk_op(N_BINOP, "*",  $1, $3, yylineno); }
    | expr '/' expr         { $$ = mk_op(N_BINOP, "/",  $1, $3, yylineno); }
    | expr '%' expr         { $$ = mk_op(N_BINOP, "%",  $1, $3, yylineno); }
    | '-' expr %prec UMINUS { $$ = mk_op(N_UNOP, "-", $2, NULL, yylineno); }
    | '!' expr              { $$ = mk_op(N_UNOP, "!", $2, NULL, yylineno); }
    | INC ID                { $$ = incdec($2, "++", 1); }
    | DEC ID                { $$ = incdec($2, "--", 1); }
    | ID INC                { $$ = incdec($1, "++", 0); }
    | ID DEC                { $$ = incdec($1, "--", 0); }
    | '(' expr ')'          { $$ = $2; }
    | NUM                   { $$ = mk(N_INT, yylineno);   $$->ival = $1; }
    | FNUM                  { $$ = mk(N_FLOAT, yylineno); $$->fval = $1; }
    | STRING                { $$ = mk(N_STR, yylineno);   $$->name = $1; }
    | ID                    { $$ = mk(N_VAR, yylineno);   $$->name = $1; }
    | ID '(' args ')'       { $$ = $3; $$->name = $1; }
    ;

args
    : /* порожньо */        { $$ = mk(N_CALL, yylineno); }
    | arg_list
    ;

arg_list
    : expr                  { $$ = add(mk(N_CALL, yylineno), $1); }
    | arg_list ',' expr     { $$ = add($1, $3); }
    ;

%%

void yyerror(const char *s) {
    parse_errors++;
    fprintf(stderr, "Помилка (рядок %d, біля '%s'): %s\n", yylineno, yytext, s);
}
