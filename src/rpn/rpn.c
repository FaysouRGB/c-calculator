#define _POSIX_C_SOURCE 200809L

#include "rpn.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack/stack.h"
#include "utilities/utilities.h"

static int __rpn_perform_operation(char op, int left, int right,
                                   bool *error_occured)
{
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
    case '%':
        if (!right)
        {
            goto error;
        }
        return op == '/' ? left / right : left % right;
    case '^':
        if (right < 0)
        {
            goto error;
        }
        int result = 1;
        for (int i = 0; i < right; ++i)
        {
            result *= left;
        }
        return result;
    default:
        goto error;
    }

error:
    *error_occured = true;
    return 0;
}

int rpn_evaluate(const char *input, bool *error_occured)
{
    // Check if the string is empty.
    if (utilities_is_string_empty(input))
    {
        return 0;
    }

    // Create operand stack.
    Stack s = stack_create();

    // Tokenize the input string.
    char *input_copy = strdup(input);
    if (!input_copy)
    {
        *error_occured = true;
        return 0;
    }

    char *token = strtok(input_copy, " \n");
    while (token)
    {
        // Check if it is a number.
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            stack_push(&s, atoi(token), error_occured);
            if (*error_occured)
            {
                break;
            }
        }
        // Check if it is an operator.
        else if (strchr("+-*/%^", token[0]) && token[1] == '\0')
        {
            int right = stack_pop(&s, error_occured);
            if (*error_occured)
            {
                break;
            }

            int left = stack_pop(&s, error_occured);
            if (*error_occured)
            {
                break;
            }

            stack_push(
                &s,
                __rpn_perform_operation(token[0], left, right, error_occured),
                error_occured);
            if (*error_occured)
            {
                break;
            }
        }
        // Invalid token encountered
        else
        {
            *error_occured = true;
            break;
        }

        // Move to next token.
        token = strtok(NULL, " \n");
    }

    free(input_copy);

    // Check if there is only one element in the stack.
    if (s.top != 0)
    {
        *error_occured = true;
    }

    return *error_occured ? 0 : stack_pop(&s, error_occured);
}
