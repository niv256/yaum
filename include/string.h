#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);
int strcmp(const char *str1, const char *str2);
void *memcpy(void *dest, const void *src, size_t size);

#endif
