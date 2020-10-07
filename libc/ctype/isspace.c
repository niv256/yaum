#include <ctype.h>

int isspace(int c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' ||
          c == '\r');
}
