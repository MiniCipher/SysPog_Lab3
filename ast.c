// ast.c — створення, друк та експорт AST у JSON
#include <stdlib.h>
#include <string.h>
#include "ast.h"

Node *root = NULL;

static const char *KN[] = {
    "Program", "Function", "Params", "Param", "Block", "Decl", "VarInit",
    "If", "While", "For", "Return", "Break", "ExprStmt", "Empty",
    "Assign", "BinOp", "UnOp", "IncDec", "Int", "Float", "String", "Var", "Call"
};

Node *mk(Kind k, int line) {
    Node *n = calloc(1, sizeof(Node));
    n->kind = k;
    n->line = line;
    return n;
}

Node *add(Node *p, Node *child) {
    if (p->n == p->cap) {
        p->cap = p->cap ? p->cap * 2 : 4;
        p->c = realloc(p->c, p->cap * sizeof(Node *));
    }
    p->c[p->n++] = child;
    return p;
}

Node *mk_op(Kind k, const char *op, Node *a, Node *b, int line) {
    Node *n = mk(k, line);
    n->op = strdup(op);
    add(n, a);
    if (b) add(n, b);
    return n;
}

const char *type_name(Type t) {
    return t == T_INT ? "int" : t == T_DOUBLE ? "double" : "void";
}

/* Підпис вузла для текстового дерева та для веб-візуалізації */
static void label(Node *n, char *buf, size_t sz) {
    switch (n->kind) {
    case N_FUNC:    snprintf(buf, sz, "Function %s : %s", n->name, type_name(n->type)); break;
    case N_PARAM:   snprintf(buf, sz, "Param %s %s", type_name(n->type), n->name); break;
    case N_DECL:    snprintf(buf, sz, "Decl %s", type_name(n->type)); break;
    case N_VARINIT: snprintf(buf, sz, "%s", n->name); break;
    case N_ASSIGN:  snprintf(buf, sz, "Assign %s %s", n->name, n->op); break;
    case N_BINOP:
    case N_UNOP:    snprintf(buf, sz, "%s %s", KN[n->kind], n->op); break;
    case N_INCDEC:  if (n->ival) snprintf(buf, sz, "IncDec %s%s", n->op, n->name);
                    else         snprintf(buf, sz, "IncDec %s%s", n->name, n->op);
                    break;
    case N_INT:     snprintf(buf, sz, "Int %ld", n->ival); break;
    case N_FLOAT:   snprintf(buf, sz, "Float %g", n->fval); break;
    case N_STR:     snprintf(buf, sz, "String %s", n->name); break;
    case N_VAR:     snprintf(buf, sz, "Var %s", n->name); break;
    case N_CALL:    snprintf(buf, sz, "Call %s()", n->name); break;
    default:        snprintf(buf, sz, "%s", KN[n->kind]);
    }
}

void ast_print(Node *n, int depth) {
    char buf[512];
    if (!n) return;
    label(n, buf, sizeof buf);
    printf("%*s%s\n", depth * 2, "", buf);
    for (int i = 0; i < n->n; i++) ast_print(n->c[i], depth + 1);
}

void json_str(FILE *f, const char *s) {
    fputc('"', f);
    for (; *s; s++) {
        if (*s == '"' || *s == '\\') fprintf(f, "\\%c", *s);
        else if (*s == '\n') fputs("\\n", f);
        else if (*s == '\t') fputs("\\t", f);
        else if ((unsigned char)*s < 32) fprintf(f, "\\u%04x", *s);
        else fputc(*s, f);
    }
    fputc('"', f);
}

void ast_json(Node *n, FILE *f) {
    char buf[512];
    label(n, buf, sizeof buf);
    fprintf(f, "{\"kind\":\"%s\",\"line\":%d,\"label\":", KN[n->kind], n->line);
    json_str(f, buf);
    fputs(",\"children\":[", f);
    int first = 1;
    for (int i = 0; i < n->n; i++) {
        if (!n->c[i]) continue;
        if (!first) fputc(',', f);
        ast_json(n->c[i], f);
        first = 0;
    }
    fputs("]}", f);
}
