#include <math.h>
#include <stdlib.h>
#include <string.h>

uint8_t get_decimal_places(float number);

char *ftoa(float number, uint8_t ndigit, char *buf) {
  ndigit = fmin(ndigit, get_decimal_places(number));

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

uint8_t get_decimal_places(float number) {
  uint8_t count = 0;

  while ((number = number * 10 - (int)number * 10)) {
    count++;
  }

  return count;
}
