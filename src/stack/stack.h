#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define STACK_CAPACITY 2048

typedef struct Stack
{
    int top;
    int data[STACK_CAPACITY];
} Stack;

Stack stack_create(void);

void stack_push(Stack *s, int value, bool *error_occured);

int stack_pop(Stack *s, bool *error_occured);

int stack_peek(Stack *s, bool *error_occured);

bool stack_is_empty(Stack *s);

#endif /* ! STACK_H */
