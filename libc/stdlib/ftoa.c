#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int get_decimal_places(float number);

char *ftoa(float number, int ndigit, char *buf) {
  ndigit = fmin((uint32_t)ndigit, get_decimal_places(number));

  if (number < 0) {
    *buf++ = '-';
    number = fabs(number);
  }

  uint32_t int_part = (uint32_t)(number);
  itoa(int_part, buf, 10);

  number -= int_part;

  int_part = (uint32_t)(number * pow(10, ndigit));
  if (ndigit) {
    buf += strlen(buf);
    *buf++ = '.';
    utoa(int_part, buf, 10);
  }

  return buf;
}

int get_decimal_places(float number) {
  int count = 0;

  while ((number = number * 10 - (int)number * 10)) {
    count++;
  }

  return count;
}
