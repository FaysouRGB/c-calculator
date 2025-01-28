#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "infix/infix.h"
#include "rpn/rpn.h"

#define BUFFER_SIZE 2048

bool validate_arguments(int argc, char *argv[])
{
    return !(argc > 2 || (argc == 2 && strcmp(argv[1], "-rpn")));
}

bool read_input(char *input)
{
    // Read stdin.
    if (!fgets(input, BUFFER_SIZE, stdin))
    {
        return false;
    }

    // Check if input is too large.
    if (strlen(input) == BUFFER_SIZE - 1 && input[BUFFER_SIZE - 2] != '\n')
    {
        fprintf(stderr, "Input is too large.\n");
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (!validate_arguments(argc, argv))
    {
        fprintf(stderr, "Usage: %s <expression> [-rpn]\n", argv[0]);
        return 1;
    }

    bool is_rpn = argc == 2;

    char input[BUFFER_SIZE];
    if (!read_input(input))
    {
        return 1;
    }

    bool error_occured = false;
    int result = is_rpn ? rpn_evaluate(input, &error_occured)
                        : infix_evaluate(input, &error_occured);

    if (error_occured)
    {
        return 1;
    }

    printf("%d\n", result);
}
