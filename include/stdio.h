#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

int printf(const char *format, ...);
int putchar(int c);
int puts(const char *s);
int vprintf(const char *format, va_list ap);

#endif
