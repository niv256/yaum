#ifndef STRING_H
#define STRING_H

#include <stdint.h>

uint32_t strlen(const char *str);
int strcmp(const char *str1, const char *str2);
uint32_t trim(char *out, uint32_t len, const char *str);

#endif
