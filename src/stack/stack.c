#include "stack.h"

#include "utilities/utilities.h"

Stack stack_create(void)
{
    Stack s = { .top = -1 };
    return s;
}

void stack_push(Stack *s, int value, bool *error_occured)
{
    if (s->top < STACK_CAPACITY - 1)
    {
        s->data[++s->top] = value;
    }
    else
    {
        *error_occured = true;
    }
}

int stack_pop(Stack *s, bool *error_occured)
{
    if (s->top < 0)
    {
        *error_occured = true;
        return 0;
    }

    return s->data[s->top--];
}

int stack_peek(Stack *s, bool *error_occured)
{
    if (s->top < 0)
    {
        *error_occured = true;
        return 0;
    }

    return s->data[s->top];
}

bool stack_is_empty(Stack *s)
{
    return s->top == -1;
}
