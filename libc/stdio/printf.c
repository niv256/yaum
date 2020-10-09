#include <stdio.h>

int printf(const char *format, ...) {
  int total;
  va_list args;

  va_start(args, format);
  total = vprintf(format, args);
  va_end(args);

  return total;
}
