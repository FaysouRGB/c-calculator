#include "utilities.h"

#include <ctype.h>
#include <stddef.h>

bool utilities_is_string_empty(const char *input)
{
    if (!input)
    {
        return true;
    }

    for (size_t i = 0; input[i]; ++i)
    {
        if (!isspace(input[i]))
        {
            return false;
        }
    }

    return true;
}
