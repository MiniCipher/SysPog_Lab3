/* interp.c — інтерпретатор AST (обчислення): обхід дерева з
   стеком кадрів викликів, лексичними областями видимості та типами.  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sema.h"

typedef struct { Type t; long i; double f; } Val;
typedef struct Var { char *name; Val v; struct Var *next; } Var;
typedef enum { F_NORMAL, F_BREAK, F_RETURN } Flow;
typedef struct { Var *vars; Val ret; } Frame;

static Frame *fr;                     /* поточний кадр виклику */
static int depth = 0;

static void die(Node *n, const char *msg, const char *x) {
    fflush(stdout);
    fprintf(stderr, "\nПомилка виконання (рядок %d): %s %s\n", n->line, msg, x ? x : "");
    exit(2);
}

static Val vi(long i)   { Val v = { T_INT, i, (double)i }; return v; }
static Val vd(double f) { Val v = { T_DOUBLE, (long)f, f }; return v; }
static double D(Val v)  { return v.t == T_DOUBLE ? v.f : (double)v.i; }
static long   I(Val v)  { return v.t == T_DOUBLE ? (long)v.f : v.i; }
static Val conv(Val v, Type t) { return t == T_DOUBLE ? vd(D(v)) : vi(I(v)); }  /* як у C */

static Var *find(Node *n) {
    for (Var *v = fr->vars; v; v = v->next)
        if (!strcmp(v->name, n->name)) return v;
    die(n, "невідома змінна", n->name);
    return NULL;
}
static void define(const char *name, Val v) {
    Var *x = malloc(sizeof *x);
    x->name = (char *)name; x->v = v; x->next = fr->vars; fr->vars = x;
}
static void pop_scope(Var *saved) {   /* вихід з блоку: знищуємо локальні змінні */
    while (fr->vars != saved) { Var *x = fr->vars; fr->vars = x->next; free(x); }
}

static Val eval(Node *n);
static Flow exec(Node *n);

/* арифметика над двома значеннями з урахуванням типу результату */
static Val arith(Node *n, const char *op, Val a, Val b) {
    int dbl = a.t == T_DOUBLE || b.t == T_DOUBLE;
    if (dbl) {
        double x = D(a), y = D(b);
        switch (op[0]) {
        case '+': return vd(x + y);
        case '-': return vd(x - y);
        case '*': return vd(x * y);
        case '/': return vd(x / y);
        }
    } else {
        long x = a.i, y = b.i;
        switch (op[0]) {
        case '+': return vi(x + y);
        case '-': return vi(x - y);
        case '*': return vi(x * y);
        case '/': if (!y) die(n, "ділення на нуль", NULL); return vi(x / y);
        case '%': if (!y) die(n, "ділення на нуль", NULL); return vi(x % y);
        }
    }
    die(n, "невідомий оператор", op);
    return vi(0);
}

static Val compare(const char *op, Val a, Val b) {
    double x = D(a), y = D(b);
    if (!strcmp(op, "==")) return vi(x == y);
    if (!strcmp(op, "!=")) return vi(x != y);
    if (!strcmp(op, "<="))  return vi(x <= y);
    if (!strcmp(op, ">="))  return vi(x >= y);
    if (!strcmp(op, "<"))   return vi(x < y);
    return vi(x > y);
}

/* "\n" у вихідному рядку -> справжній символ переводу рядка */
static char *unescape(const char *s) {
    char *r = malloc(strlen(s) + 1), *p = r;
    for (s++; *s && *s != '"'; s++) {
        if (*s != '\\') { *p++ = *s; continue; }
        switch (*++s) {
        case 'n': *p++ = '\n'; break;  case 't': *p++ = '\t'; break;
        case 'r': *p++ = '\r'; break;  case '0': *p++ = '\0'; break;
        default:  *p++ = *s;
        }
    }
    *p = 0;
    return r;
}

static Val builtin_printf(Node *n) {
    char *fmt = unescape(n->c[0]->name), spec[32];
    int arg = 1, count = 0;
    for (char *p = fmt; *p; p++) {
        if (*p != '%') { putchar(*p); count++; continue; }
        if (p[1] == '%') { putchar('%'); p++; count++; continue; }
        int k = 0;
        spec[k++] = *p++;
        while (*p && !strchr("diouxXcfFeEgGs", *p) && k < 28) {
            if (*p != 'l' && *p != 'h') spec[k++] = *p;   /* модифікатори довжини відкидаємо */
            p++;
        }
        if (!*p) break;
        if (arg >= n->n) die(n, "printf: замало аргументів", NULL);
        Node *a = n->c[arg++];
        char cv = *p;
        if (cv == 's') {
            spec[k++] = 's'; spec[k] = 0;
            if (a->kind != N_STR) die(n, "printf: %s очікує рядковий літерал", NULL);
            char *s = unescape(a->name);
            count += printf(spec, s);
            free(s);
        } else if (strchr("fFeEgG", cv)) {
            spec[k++] = cv; spec[k] = 0;
            count += printf(spec, D(eval(a)));
        } else if (cv == 'c') {
            spec[k++] = 'c'; spec[k] = 0;
            count += printf(spec, (int)I(eval(a)));
        } else {
            spec[k++] = 'l'; spec[k++] = cv; spec[k] = 0;
            count += printf(spec, I(eval(a)));
        }
    }
    free(fmt);
    return vi(count);
}

static Val call(Node *n) {
    if (!strcmp(n->name, "printf")) return builtin_printf(n);
    Node *f = find_func(n->name);
    Node *params = f->c[0];
    Val args[64];
    if (n->n > 64) die(n, "забагато аргументів", NULL);
    for (int i = 0; i < n->n; i++) args[i] = eval(n->c[i]);   /* обчислюємо в кадрі викликача */
    if (++depth > 100000) die(n, "переповнення стеку", NULL);

    Frame frame = { NULL, vi(0) }, *saved = fr;
    fr = &frame;
    for (int i = 0; i < params->n; i++)
        define(params->c[i]->name, conv(args[i], params->c[i]->type));
    exec(f->c[1]);
    Val r = f->type == T_VOID ? vi(0) : conv(frame.ret, f->type);
    pop_scope(NULL);
    fr = saved;
    depth--;
    return r;
}

static Val eval(Node *n) {
    switch (n->kind) {
    case N_INT:   return vi(n->ival);
    case N_FLOAT: return vd(n->fval);
    case N_STR:   return vi(0);
    case N_VAR:   return find(n)->v;
    case N_CALL:  return call(n);
    case N_ASSIGN: {
        Val r = eval(n->c[0]);
        Var *v = find(n);
        if (n->op[0] != '=') {                  /* x += e  ==  x = x + e */
            char op[2] = { n->op[0], 0 };
            r = arith(n, op, v->v, r);
        }
        return v->v = conv(r, v->v.t);
    }
    case N_INCDEC: {
        Var *v = find(n);
        Val old = v->v;
        v->v = conv(arith(n, n->op[0] == '+' ? "+" : "-", old, vi(1)), old.t);
        return n->ival ? v->v : old;           /* префікс / постфікс */
    }
    case N_UNOP: {
        Val a = eval(n->c[0]);
        if (n->op[0] == '!') return vi(!D(a));
        return a.t == T_DOUBLE ? vd(-a.f) : vi(-a.i);
    }
    case N_BINOP: {
        const char *op = n->op;
        if (!strcmp(op, "&&")) return vi(D(eval(n->c[0])) && D(eval(n->c[1])));  /* ліниве */
        if (!strcmp(op, "||")) return vi(D(eval(n->c[0])) || D(eval(n->c[1])));
        Val a = eval(n->c[0]), b = eval(n->c[1]);
        if (strchr("+-*/%", op[0]) && !op[1]) return arith(n, op, a, b);
        return compare(op, a, b);
    }
    default:
        die(n, "не вираз", NULL);
        return vi(0);
    }
}

static int truthy(Node *e) { return D(eval(e)) != 0; }

static Flow exec(Node *n) {
    if (!n) return F_NORMAL;
    Var *saved = fr->vars;
    Flow fl = F_NORMAL;
    switch (n->kind) {
    case N_BLOCK:
        for (int i = 0; i < n->n && fl == F_NORMAL; i++) fl = exec(n->c[i]);
        pop_scope(saved);
        return fl;
    case N_DECL:
        for (int i = 0; i < n->n; i++) {
            Node *v = n->c[i];
            define(v->name, conv(v->n ? eval(v->c[0]) : vi(0), n->type));
        }
        return F_NORMAL;
    case N_EXPR:  eval(n->c[0]); return F_NORMAL;
    case N_EMPTY: return F_NORMAL;
    case N_IF:
        return truthy(n->c[0]) ? exec(n->c[1]) : exec(n->c[2]);
    case N_WHILE:
        while (truthy(n->c[0])) {
            fl = exec(n->c[1]);
            if (fl == F_BREAK) { fl = F_NORMAL; break; }
            if (fl == F_RETURN) break;
        }
        return fl;
    case N_FOR:   /* c[0]=init c[1]=cond c[2]=step c[3]=body */
        for (exec(n->c[0]); !n->c[1] || truthy(n->c[1]); n->c[2] ? (void)eval(n->c[2]) : (void)0) {
            fl = exec(n->c[3]);
            if (fl == F_BREAK) { fl = F_NORMAL; break; }
            if (fl == F_RETURN) break;
        }
        pop_scope(saved);
        return fl;
    case N_RETURN:
        if (n->c[0]) fr->ret = eval(n->c[0]);
        return F_RETURN;
    case N_BREAK:
        return F_BREAK;
    default:
        die(n, "невідома інструкція", NULL);
        return F_NORMAL;
    }
}

void interpret(Node *prog) {
    (void)prog;
    Frame top = { NULL, vi(0) };
    fr = &top;
    Node c = { .kind = N_CALL, .name = "main", .line = 0 };
    Val r = call(&c);
    fflush(stdout);
    fprintf(stderr, "\n[main повернула %ld]\n", I(r));
}
