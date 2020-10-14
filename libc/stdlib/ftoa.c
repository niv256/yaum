#include <math.h>
#include <stdlib.h>
#include <string.h>

int get_decimal_places(float number);

char *ftoa(float number, int ndigit, char *buf) {
  ndigit = fmin((uint32_t)ndigit, get_decimal_places(number));

  if (number < 0) {
    *buf++ = '-';
    number = fabs(number);
  }

  utoa((uint32_t)(number), buf, 10);
  buf += strlen(buf);

  // keep only the digits after the decimal point
  number -= (uint32_t)number;

  // number's fraction part as an integer
  uint32_t fraction = (uint32_t)(number * pow(10, ndigit));

  if (ndigit) {
    *buf++ = '.';
    utoa(fraction, buf, 10);
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
