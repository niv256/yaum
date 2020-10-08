#ifndef STRING_H
#define STRING_H

#include <stdint.h>

uint32_t strlen(const char *str);
int strcmp(const char *str1, const char *str2);
void *memcpy(void *dest, const void *src, uint32_t size);

#endif
