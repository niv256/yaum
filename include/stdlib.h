#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

char *itoa(int num, char *str, int base);
char *ftoa(float number, int ndigit, char *buf);
char *utoa(uint32_t num, char *str, int base);
int abs(int x);

#endif
