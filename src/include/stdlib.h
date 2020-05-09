#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

char* itoa(int num, char* str, int base);
void* memcpy(char* dest, char* src, size_t size);

#endif
