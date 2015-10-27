#ifndef STACK_H
#define STACK_H
#include "setup_printchess.h"
typedef struct node {
        board b;
        struct node *next;
}node;
typedef struct stack {
        node *head;
        node *tail;
}stack;
void init(stack *s);
void push(stack *s, board b);
board pop(stack *s);
int empty(stack *s);
#endif
