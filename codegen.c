/* codegen.c — трансляція AST у програму мовою Python 3.
   Використовує типи, виведені в sema.c, щоб зберегти семантику C:
   цілочисельне ділення, перетворення int<->double, 0/1 для логіки.     */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sema.h"

static FILE *out;

static const char *PRELUDE =
    "# Згенеровано транслятором c2py з підмножини мови C\n"
    "import sys, math\n\n"
    "def _div(a, b):  # цілочисельне ділення C (усічення до нуля)\n"
    "    q = abs(a) // abs(b)\n"
    "    return q if (a >= 0) == (b >= 0) else -q\n\n"
    "def _mod(a, b):  # остача C (знак як у діленого)\n"
    "    return a - b * _div(a, b)\n\n"
    "def printf(fmt, *args):\n"
    "    s = fmt % args\n"
    "    sys.stdout.write(s)\n"
    "    return len(s)\n\n";

static const char *PY_KW[] = { "and", "as", "assert", "async", "await", "class", "def", "del",
    "elif", "except", "finally", "from", "global", "import", "in", "is", "lambda", "None",
    "nonlocal", "not", "or", "pass", "raise", "True", "False", "try", "with", "yield",
    "sys", "math", "_div", "_mod", NULL };

/* ім'я C -> безпечне ім'я Python */
static const char *id(const char *s) {
    for (int i = 0; PY_KW[i]; i++)
        if (!strcmp(s, PY_KW[i])) {
            static char buf[8][128]; static int k;
            k = (k + 1) % 8;
            snprintf(buf[k], sizeof buf[k], "%s_", s);
            return buf[k];
        }
    return s;
}

/* Області видимості C -> Python (у Python область — уся функція):
   змінна, що перекриває зовнішню, отримує нове ім'я x_1, x_2 ...     */
typedef struct Map { const char *c; char *py; struct Map *next; } Map;
static Map *env = NULL;
static int uniq = 0;

static const char *pyname(const char *c) {
    for (Map *m = env; m; m = m->next)
        if (!strcmp(m->c, c)) return m->py;
    return id(c);
}
static char *fresh(const char *c) {          /* ім'я для нового оголошення */
    char buf[160];
    for (Map *m = env; m; m = m->next)
        if (!strcmp(m->c, c)) { snprintf(buf, sizeof buf, "%s_%d", id(c), ++uniq); return strdup(buf); }
    return strdup(id(c));
}
static void bind(const char *c, char *py) {
    Map *m = malloc(sizeof *m);
    m->c = c; m->py = py; m->next = env; env = m;
}

static void expr(Node *n);

/* вираз, приведений до потрібного типу (як присвоєння в C) */
static void expr_as(Node *e, Type t) {
    if (t == T_INT && e->type == T_DOUBLE) { fputs("int(", out); expr(e); fputc(')', out); }
    else if (t == T_DOUBLE && e->type == T_INT) { fputs("float(", out); expr(e); fputc(')', out); }
    else expr(e);
}

/* права частина присвоєння: x op= e  ->  x op e  з урахуванням типів */
static void assign_rhs(Node *n) {
    if (n->op[0] == '=') { expr_as(n->c[0], n->type); return; }
    char op = n->op[0];
    int ints = n->type == T_INT && n->c[0]->type == T_INT;
    int conv = n->type == T_INT && !ints;
    if (conv) fputs("int(", out);
    if (op == '/' && ints)      { fprintf(out, "_div(%s, ", pyname(n->name)); expr(n->c[0]); fputc(')', out); }
    else if (op == '%')         { fprintf(out, "_mod(%s, ", pyname(n->name)); expr(n->c[0]); fputc(')', out); }
    else { fprintf(out, "%s %c ", pyname(n->name), op); expr(n->c[0]); }
    if (conv) fputc(')', out);
}

static void expr(Node *n) {
    switch (n->kind) {
    case N_INT:   fprintf(out, "%ld", n->ival); break;
    case N_FLOAT: {
        char b[64];
        snprintf(b, sizeof b, "%.15g", n->fval);
        if (atof(b) != n->fval) snprintf(b, sizeof b, "%.17g", n->fval);
        fprintf(out, strpbrk(b, ".einf") ? "%s" : "%s.0", b);   /* щоб Python бачив float */
        break;
    }
    case N_STR:   fputs(n->name, out); break;       /* C-літерал сумісний з Python */
    case N_VAR:   fputs(pyname(n->name), out); break;
    case N_ASSIGN:                                   /* присвоєння всередині виразу */
        fprintf(out, "(%s := ", pyname(n->name)); assign_rhs(n); fputc(')', out); break;
    case N_INCDEC: {
        char op = n->op[0];
        const char *v = pyname(n->name);
        if (n->ival) fprintf(out, "(%s := %s %c 1)", v, v, op);
        else fprintf(out, "((%s := %s %c 1) %c 1)", v, v, op,
                     op == '+' ? '-' : '+');
        break;
    }
    case N_UNOP:
        if (n->op[0] == '!') { fputs("int(not ", out); expr(n->c[0]); fputc(')', out); }
        else { fputs("(-", out); expr(n->c[0]); fputc(')', out); }
        break;
    case N_BINOP: {
        const char *op = n->op;
        Node *a = n->c[0], *b = n->c[1];
        int ints = a->type == T_INT && b->type == T_INT;
        if (!strcmp(op, "&&") || !strcmp(op, "||")) {
            fputs("int(bool(", out); expr(a);
            fputs(!strcmp(op, "&&") ? ") and bool(" : ") or bool(", out);
            expr(b); fputs("))", out);
        } else if (!strcmp(op, "/") && ints) {
            fputs("_div(", out); expr(a); fputs(", ", out); expr(b); fputc(')', out);
        } else if (!strcmp(op, "%")) {
            fputs("_mod(", out); expr(a); fputs(", ", out); expr(b); fputc(')', out);
        } else if (strchr("<>=!", op[0])) {
            fputs("int(", out); expr(a); fprintf(out, " %s ", op); expr(b); fputc(')', out);
        } else {
            fputc('(', out); expr(a); fprintf(out, " %s ", op); expr(b); fputc(')', out);
        }
        break;
    }
    case N_CALL: {
        Node *f = strcmp(n->name, "printf") ? find_func(n->name) : NULL;
        fprintf(out, "%s(", id(n->name));
        for (int i = 0; i < n->n; i++) {
            if (i) fputs(", ", out);
            if (f) expr_as(n->c[i], f->c[0]->c[i]->type);   /* приведення до типу параметра */
            else expr(n->c[i]);
        }
        fputc(')', out);
        break;
    }
    default: fputs("None", out);
    }
}

static int lines = 0;                       /* лічильник згенерованих рядків */
/* вираз у позиції умови (if/while): 0/1 не потрібні -> чистий Python */
static void cond(Node *n) {
    if (n->kind == N_BINOP && (!strcmp(n->op, "&&") || !strcmp(n->op, "||"))) {
        fputc('(', out); cond(n->c[0]);
        fputs(n->op[0] == '&' ? " and " : " or ", out);
        cond(n->c[1]); fputc(')', out);
    } else if (n->kind == N_BINOP && strchr("<>=!", n->op[0])) {
        expr(n->c[0]); fprintf(out, " %s ", n->op); expr(n->c[1]);
    } else if (n->kind == N_UNOP && n->op[0] == '!') {
        fputs("not (", out); cond(n->c[0]); fputc(')', out);
    } else expr(n);
}

static void ind(int d) { fprintf(out, "%*s", d * 4, ""); lines++; }

static Node *cur_func;
static void stmt(Node *n, int d);

static void body(Node *n, int d) {           /* тіло складеної інструкції */
    int before = lines;
    Map *saved = env;
    if (n && n->kind == N_BLOCK) for (int i = 0; i < n->n; i++) stmt(n->c[i], d);
    else stmt(n, d);
    env = saved;
    if (lines == before) { ind(d); fputs("pass\n", out); }
}

/* інструкція-вираз: присвоєння та ++/-- без моржового оператора */
static void expr_stmt(Node *e, int d) {
    ind(d);
    if (e->kind == N_ASSIGN) { fprintf(out, "%s = ", pyname(e->name)); assign_rhs(e); }
    else if (e->kind == N_INCDEC) fprintf(out, "%s %c= 1", pyname(e->name), e->op[0]);
    else expr(e);
    fputc('\n', out);
}

static void stmt(Node *n, int d) {
    if (!n) return;
    switch (n->kind) {
    case N_BLOCK: {
        Map *saved = env;
        for (int i = 0; i < n->n; i++) stmt(n->c[i], d);
        env = saved;
        break;
    }
    case N_DECL:
        for (int i = 0; i < n->n; i++) {
            Node *v = n->c[i];
            char *py = fresh(v->name);
            ind(d); fprintf(out, "%s = ", py);
            if (v->n) expr_as(v->c[0], n->type);    /* ініціалізатор бачить старе ім'я */
            else fputs(n->type == T_DOUBLE ? "0.0" : "0", out);
            fputc('\n', out);
            bind(v->name, py);
        }
        break;
    case N_EXPR:  expr_stmt(n->c[0], d); break;
    case N_EMPTY: break;
    case N_IF:
        ind(d); fputs("if ", out); cond(n->c[0]); fputs(":\n", out);
        body(n->c[1], d + 1);
        while (n->c[2] && n->c[2]->kind == N_IF) {          /* else if -> elif */
            n = n->c[2];
            ind(d); fputs("elif ", out); cond(n->c[0]); fputs(":\n", out);
            body(n->c[1], d + 1);
        }
        if (n->c[2]) { ind(d); fputs("else:\n", out); body(n->c[2], d + 1); }
        break;
    case N_WHILE:
        ind(d); fputs("while ", out); cond(n->c[0]); fputs(":\n", out);
        body(n->c[1], d + 1);
        break;
    case N_FOR: { /* for(init; cond; step) body  ->  init; while cond: body; step */
        Map *saved = env;
        stmt(n->c[0], d);
        ind(d); fputs("while ", out);
        if (n->c[1]) cond(n->c[1]); else fputs("True", out);
        fputs(":\n", out);
        body(n->c[3], d + 1);
        if (n->c[2]) expr_stmt(n->c[2], d + 1);
        env = saved;
        break;
    }
    case N_RETURN:
        ind(d); fputs("return", out);
        if (n->c[0]) { fputc(' ', out); expr_as(n->c[0], cur_func->type); }
        fputc('\n', out);
        break;
    case N_BREAK: ind(d); fputs("break\n", out); break;
    default: break;
    }
}

void gen_python(Node *prog, FILE *f) {
    out = f;
    fputs(PRELUDE, out);
    for (int i = 0; i < prog->n; i++) {
        Node *fn = prog->c[i];
        cur_func = fn;
        env = NULL;
        fprintf(out, "def %s(", id(fn->name));
        for (int j = 0; j < fn->c[0]->n; j++) {
            fprintf(out, "%s%s", j ? ", " : "", id(fn->c[0]->c[j]->name));
            bind(fn->c[0]->c[j]->name, strdup(id(fn->c[0]->c[j]->name)));
        }
        fputs("):\n", out);
        body(fn->c[1], 1);
        fputc('\n', out);
    }
    fputs("if __name__ == \"__main__\":\n    sys.exit(main())\n", out);
}
