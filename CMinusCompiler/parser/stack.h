#ifndef STACK_H
#define STACK_H
#include "syntax_tree.h"

typedef struct stack_node stack_node;
struct stack {
    stack_node* top;
};
typedef struct stack stack;

struct stack_node {
    stack_node* prev;
    syntax_tree* ptr;
    int* x;
};

stack* stack_alloc();
stack_node* stack_pop(stack* s);
void stack_push(stack* s, stack_node* nod);
stack_node* stack_alloc_node(void);

#endif