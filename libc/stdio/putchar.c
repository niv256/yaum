#include <io/screen.h>
#include <stdio.h>

int putchar(int c) {
  terminal_writechar(c);
  return c;
}
