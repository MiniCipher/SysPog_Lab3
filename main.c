/* main.c — драйвер: розбір -> семантика -> AST (json/web) -> Python -> виконання */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sema.h"

extern FILE *yyin;
extern int parse_errors;
int yyparse(void);

static char *slurp(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    rewind(f);
    char *s = malloc(n + 1);
    s[fread(s, 1, n, f)] = 0;
    fclose(f);
    return s;
}

int main(int argc, char **argv) {
    const char *src = NULL;
    int tree = 0, run = 1;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-t")) tree = 1;
        else if (!strcmp(argv[i], "-n")) run = 0;
        else src = argv[i];
    }
    if (!src) { fprintf(stderr, "Використання: %s program.c [-t] [-n]\n", argv[0]); return 1; }
    if (!(yyin = fopen(src, "r"))) { perror(src); return 1; }


    if (yyparse() != 0 || parse_errors || !root) return 1;
    if (sema(root)) return 1;
    fprintf(stderr, "[OK] Розбір і семантичний аналіз успішні\n");
    if (tree) ast_print(root, 0);

    FILE *f = fopen("ast.json", "w");
    ast_json(root, f);
    fclose(f);

    f = fopen("out.py", "w");
    gen_python(root, f);
    fclose(f);
    fprintf(stderr, "[OK] Створено ast.json, out.py\n");

    if ((f = fopen("web/ast_data.js", "w"))) {
        char *c = slurp(src), *py = slurp("out.py");
        fputs("const AST = ", f); ast_json(root, f);
        fputs(";\nconst SRC = ", f); json_str(f, c ? c : "");
        fputs(";\nconst PY = ", f);  json_str(f, py ? py : "");
        fputs(";\n", f);
        fclose(f);
        fprintf(stderr, "[OK] Створено web/ast_data.js — відкрийте web/index.html\n");
    }

    if (run) {
        fprintf(stderr, "===== Виконання (інтерпретатор AST) =====\n");
        interpret(root);
    }
    return 0;
}
