#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

bool str_to_int(char *str, int *converted_int);
void remove_spaces(char *str_trimmed, const char *str_untrimmed);
char *strstrip(char *s);
#endif