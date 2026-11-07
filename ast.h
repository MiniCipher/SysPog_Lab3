/* ast.h — вузли абстрактного синтаксичного дерева (AST) */
#ifndef AST_H
#define AST_H
#include <stdio.h>

typedef enum {
    N_PROGRAM, N_FUNC, N_PARAMS, N_PARAM, N_BLOCK, N_DECL, N_VARINIT,
    N_IF, N_WHILE, N_FOR, N_RETURN, N_BREAK, N_EXPR, N_EMPTY,
    N_ASSIGN, N_BINOP, N_UNOP, N_INCDEC, N_INT, N_FLOAT, N_STR, N_VAR, N_CALL
} Kind;

typedef enum { T_INT, T_DOUBLE, T_VOID } Type;

typedef struct Node {
    Kind kind;
    char *op;            /* оператор: "+", "==", "+=", "++" ...      */
    char *name;          /* ім'я змінної / функції, текст рядка      */
    long ival;           /* цілий літерал; для INCDEC: 1 = префікс   */
    double fval;         /* дійсний літерал                          */
    Type type;           /* оголошений або виведений (sema) тип      */
    int line;            /* рядок у вихідному файлі                  */
    int n, cap;          /* кількість дітей                          */
    struct Node **c;     /* діти (можуть бути NULL — "відсутні")     */
} Node;

Node *mk(Kind k, int line);
Node *add(Node *parent, Node *child);
Node *mk_op(Kind k, const char *op, Node *a, Node *b, int line);
const char *type_name(Type t);
void ast_print(Node *n, int depth);
void ast_json(Node *n, FILE *f);
void json_str(FILE *f, const char *s);

extern Node *root;
#endif
