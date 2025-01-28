#define _POSIX_C_SOURCE 200809L

#include "infix.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "queue/queue.h"
#include "rpn/rpn.h"
#include "stack/stack.h"

typedef struct InfixArgs
{
    Stack *s;
    Queue *q;
    bool *error_occured;
} InfixArgs;

static int __infix_operator_precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

static void __infix_handle_digits(const char *input, int *i, InfixArgs *args)
{
    char number[32] = { 0 };
    int num_idx = 0;

    while (isdigit(input[*i]))
    {
        number[num_idx++] = input[*i];
        (*i)++;
    }

    for (int j = 0; j < num_idx; j++)
    {
        queue_enqueue(args->q, number[j], args->error_occured);
    }

    queue_enqueue(args->q, ' ', args->error_occured);
}

static void __infix_handle_parenthesis(InfixArgs *args)
{
    while (!stack_is_empty(args->s)
           && stack_peek(args->s, args->error_occured) != '(')
    {
        char op = stack_pop(args->s, args->error_occured);
        queue_enqueue(args->q, op, args->error_occured);
        queue_enqueue(args->q, ' ', args->error_occured);
    }

    if (stack_is_empty(args->s))
    {
        *args->error_occured = true;
        return;
    }

    // Pop the '('
    stack_pop(args->s, args->error_occured);
}

static char *__infix_queue_to_string(InfixArgs *args)
{
    char *result = calloc(QUEUE_CAPACITY + 1, sizeof(char));
    if (!result)
    {
        *args->error_occured = true;
        return NULL;
    }

    int i = 0;
    while (!queue_is_empty(args->q))
    {
        result[i++] = queue_dequeue(args->q, args->error_occured);
    }

    result[i] = '\0';
    return result;
}

static char *__infix_get_rpn_string(InfixArgs *args)
{
    while (!stack_is_empty(args->s))
    {
        char op = stack_peek(args->s, args->error_occured);
        if (op == '(')
        {
            *args->error_occured = true;
            break;
        }

        op = stack_pop(args->s, args->error_occured);
        queue_enqueue(args->q, op, args->error_occured);
        queue_enqueue(args->q, ' ', args->error_occured);
    }

    return __infix_queue_to_string(args);
}

static bool __infix_stack_higher_precedence(InfixArgs *args, char op)
{
    if (stack_is_empty(args->s))
    {
        return false;
    }

    char stack_top = stack_peek(args->s, args->error_occured);
    if (stack_top == '(')
    {
        return false;
    }

    int stack_precedence = __infix_operator_precedence(stack_top);
    int op_precedence = __infix_operator_precedence(op);

    if (op == '^')
    {
        return stack_precedence > op_precedence;
    }
    return stack_precedence >= op_precedence;
}

static void __infix_handle_op(char op, char prev_token, InfixArgs *args)
{
    if ((op == '+' || op == '-')
        && (prev_token == 0 || prev_token == '('
            || strchr("+-*/^%", prev_token)))
    {
        if (op == '-')
        {
            queue_enqueue(args->q, '0', args->error_occured);
            queue_enqueue(args->q, ' ', args->error_occured);
            stack_push(args->s, op, args->error_occured);
        }

        return;
    }

    while (__infix_stack_higher_precedence(args, op))
    {
        char stack_op = stack_pop(args->s, args->error_occured);
        queue_enqueue(args->q, stack_op, args->error_occured);
        queue_enqueue(args->q, ' ', args->error_occured);
    }

    stack_push(args->s, op, args->error_occured);
}

static char *shunting_yard(const char *input, bool *error_occured)
{
    if (!input || !*input)
    {
        *error_occured = true;
        return NULL;
    }

    Stack s = stack_create();
    Queue q = queue_create();
    InfixArgs args = { .s = &s, .q = &q, .error_occured = error_occured };

    int i = 0;
    char prev_token = 0;

    while (input[i] && !*error_occured)
    {
        if (isspace(input[i]))
        {
            ++i;
            continue;
        }

        if (isdigit(input[i]))
        {
            __infix_handle_digits(input, &i, &args);
            prev_token = 'd';
        }
        else if (input[i] == '(')
        {
            stack_push(&s, input[i], error_occured);
            prev_token = '(';
            ++i;
        }
        else if (input[i] == ')')
        {
            __infix_handle_parenthesis(&args);
            prev_token = ')';
            ++i;
        }
        else if (strchr("+-*/^%", input[i]))
        {
            __infix_handle_op(input[i], prev_token, &args);
            prev_token = input[i];
            ++i;
        }
        else
        {
            *error_occured = true;
            break;
        }
    }

    char *result = __infix_get_rpn_string(&args);
    return result;
}

int infix_evaluate(const char *input, bool *error_occured)
{
    char *rpn_notation = shunting_yard(input, error_occured);
    if (*error_occured || !rpn_notation)
    {
        free(rpn_notation);
        return 0;
    }

    int result = rpn_evaluate(rpn_notation, error_occured);
    free(rpn_notation);
    return result;
}
