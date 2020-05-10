#ifndef STRING_H
#define STRING_H

#include <stddef.h>
size_t strlen(const char *str);
int strcmp(const char *str1, const char *str2);
size_t trim(char *out, size_t len, const char *str);

#endif
