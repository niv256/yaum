#include <ctype.h>

int isspace(char c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' ||
          c == '\r');
}
