/* lexer.l — лексичний аналізатор (flex) для підмножини мови C */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
void yyerror(const char *s);

static long char_value(const char *t) {
    if (t[1] != '\\') return (unsigned char)t[1];
    switch (t[2]) {
    case 'n': return '\n'; case 't': return '\t'; case 'r': return '\r';
    case '0': return 0;    default:  return (unsigned char)t[2];
    }
}
%}

%option noyywrap yylineno nounput noinput

D   [0-9]
L   [a-zA-Z_]
E   [eE][+-]?{D}+

%%

"//".*                          { /* однорядковий коментар */ }
"/*"([^*]|\*+[^*/])*\*+"/"      { /* багаторядковий коментар */ }
^[ \t]*"#".*                    { /* #include, #define — ігноруємо */ }

"int"|"char"|"long"             { return INT; }
"double"|"float"                { return DOUBLE; }
"void"                          { return VOID; }
"if"                            { return IF; }
"else"                          { return ELSE; }
"while"                         { return WHILE; }
"for"                           { return FOR; }
"return"                        { return RETURN; }
"break"                         { return BREAK; }

{L}({L}|{D})*                   { yylval.str = strdup(yytext); return ID; }

({D}+"."{D}*|"."{D}+){E}?|{D}+{E}  { yylval.fval = atof(yytext); return FNUM; }
{D}+                            { yylval.ival = atol(yytext); return NUM; }
"'"(\\.|[^\\'\n])"'"            { yylval.ival = char_value(yytext); return NUM; }
\"(\\.|[^\\"\n])*\"             { yylval.str = strdup(yytext); return STRING; }

"=="    { return EQ; }
"!="    { return NE; }
"<="    { return LE; }
">="    { return GE; }
"&&"    { return AND; }
"||"    { return OR; }
"++"    { return INC; }
"--"    { return DEC; }
"+="    { return ADD_ASSIGN; }
"-="    { return SUB_ASSIGN; }
"*="    { return MUL_ASSIGN; }
"/="    { return DIV_ASSIGN; }
"%="    { return MOD_ASSIGN; }

[-+*/%<>=!(){};,]               { return yytext[0]; }

[ \t\r\n]+                      { /* пробіли */ }
.                               { yyerror("unknown character"); }

%%
