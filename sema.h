#ifndef SEMA_H
#define SEMA_H
#include "ast.h"
int sema(Node *prog);                 /* повертає кількість помилок */
Node *find_func(const char *name);
void interpret(Node *prog);           /* interp.c  */
void gen_python(Node *prog, FILE *f); /* codegen.c */
#endif
