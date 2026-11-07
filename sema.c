/* sema.c — семантичний аналіз: області видимості, оголошення,
   перевірка викликів, виведення типів виразів (node->type).        */
#include <stdlib.h>
#include <string.h>
#include "sema.h"

typedef struct Sym { char *name; Type t; struct Sym *next; } Sym;

static Sym *scope = NULL;      /* стек імен: голова = найвнутрішніша область */
static Node *cur_func = NULL;
static int errors = 0;

#define ERR(n, ...) do { fprintf(stderr, "Семантична помилка (рядок %d): ", (n)->line); \
                         fprintf(stderr, __VA_ARGS__); fputc('\n', stderr); errors++; } while (0)

Node *find_func(const char *name) {
    for (int i = 0; i < root->n; i++)
        if (!strcmp(root->c[i]->name, name)) return root->c[i];
    return NULL;
}

static void declare(const char *name, Type t) {
    Sym *s = malloc(sizeof *s);
    s->name = (char *)name; s->t = t; s->next = scope; scope = s;
}

static Sym *lookup(const char *name) {
    for (Sym *s = scope; s; s = s->next)
        if (!strcmp(s->name, name)) return s;
    return NULL;
}

static Type var_type(Node *n) {
    Sym *s = lookup(n->name);
    if (!s) { ERR(n, "змінну '%s' не оголошено", n->name); return T_INT; }
    return s->t;
}

static int is_cmp(const char *op) {
    return !strcmp(op, "==") || !strcmp(op, "!=") || !strcmp(op, "<") || !strcmp(op, ">") ||
           !strcmp(op, "<=") || !strcmp(op, ">=") || !strcmp(op, "&&") || !strcmp(op, "||");
}

static void check(Node *n) {
    if (!n) return;
    Sym *saved = scope;
    switch (n->kind) {
    case N_FUNC:
        cur_func = n;
        for (int i = 0; i < n->c[0]->n; i++) declare(n->c[0]->c[i]->name, n->c[0]->c[i]->type);
        check(n->c[1]);
        scope = saved;
        return;
    case N_BLOCK:
    case N_FOR:                      /* нова область видимості */
        for (int i = 0; i < n->n; i++) check(n->c[i]);
        scope = saved;
        return;
    case N_DECL:
        if (n->type == T_VOID) ERR(n, "змінна не може мати тип void");
        for (int i = 0; i < n->n; i++) {
            n->c[i]->type = n->type;
            if (n->c[i]->n) check(n->c[i]->c[0]);
            declare(n->c[i]->name, n->type);   /* ім'я видно після ініціалізатора */
        }
        return;
    case N_RETURN:
        if (n->c[0]) check(n->c[0]);
        if (cur_func->type == T_VOID && n->c[0]) ERR(n, "void-функція повертає значення");
        if (cur_func->type != T_VOID && !n->c[0]) ERR(n, "return без значення");
        return;
    case N_INT:   n->type = T_INT; return;
    case N_FLOAT: n->type = T_DOUBLE; return;
    case N_STR:   n->type = T_INT; return;
    case N_VAR:   n->type = var_type(n); return;
    case N_ASSIGN:
        check(n->c[0]);
        n->type = var_type(n);
        if (!strcmp(n->op, "%=") && (n->type == T_DOUBLE || n->c[0]->type == T_DOUBLE))
            ERR(n, "оператор %% застосовано до double");
        return;
    case N_INCDEC: n->type = var_type(n); return;
    case N_UNOP:
        check(n->c[0]);
        n->type = !strcmp(n->op, "!") ? T_INT : n->c[0]->type;
        return;
    case N_BINOP:
        check(n->c[0]); check(n->c[1]);
        if (is_cmp(n->op)) n->type = T_INT;
        else n->type = (n->c[0]->type == T_DOUBLE || n->c[1]->type == T_DOUBLE) ? T_DOUBLE : T_INT;
        if (!strcmp(n->op, "%") && n->type == T_DOUBLE) ERR(n, "оператор %% застосовано до double");
        return;
    case N_CALL: {
        for (int i = 0; i < n->n; i++) check(n->c[i]);
        if (!strcmp(n->name, "printf")) {
            if (n->n == 0 || n->c[0]->kind != N_STR) ERR(n, "printf: першим аргументом має бути рядок");
            n->type = T_INT;
            return;
        }
        Node *f = find_func(n->name);
        if (!f) { ERR(n, "функцію '%s' не оголошено", n->name); n->type = T_INT; return; }
        if (f->c[0]->n != n->n)
            ERR(n, "'%s' очікує %d аргумент(ів), передано %d", n->name, f->c[0]->n, n->n);
        n->type = f->type;
        return;
    }
    default:
        for (int i = 0; i < n->n; i++) check(n->c[i]);
    }
}

int sema(Node *prog) {
    for (int i = 0; i < prog->n; i++)
        for (int j = 0; j < i; j++)
            if (!strcmp(prog->c[i]->name, prog->c[j]->name))
                ERR(prog->c[i], "функцію '%s' визначено двічі", prog->c[i]->name);
    if (!find_func("main")) { fprintf(stderr, "Семантична помилка: немає функції main\n"); errors++; }
    for (int i = 0; i < prog->n; i++) check(prog->c[i]);
    return errors;
}
