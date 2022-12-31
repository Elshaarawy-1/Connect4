#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"

bool str_to_int(char *str, int *converted_int)
{
    char *endptr;
    errno = 0; // reset error number
    long long_var = strtol(str, &endptr, 10);
    if (errno == ERANGE)
    {
        // out of range for a long
        return false;
    }
    if (endptr == str)
    {
        // no character was read
        return false;
    }
    if (*endptr && *endptr != '\n')
    {
        // *endptr is neither end of string nor newline,
        // so we didn't convert the *whole* input
        return false;
    }
    if (long_var > INT_MAX || long_var < INT_MIN)
    {
        // result will not fit in an int
        return false;
    }

    // write result through the pointer passed
    *converted_int = (int)long_var;
    return true;
}

void remove_spaces(char *str_trimmed, const char *str_untrimmed)
{
    while (*str_untrimmed != '\0')
    {
        if (!isspace(*str_untrimmed))
        {
            *str_trimmed = *str_untrimmed;
            str_trimmed++;
        }
        str_untrimmed++;
    }
    *str_trimmed = '\0';
}

char *strstrip(char *s)
{
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}