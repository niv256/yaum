#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BASE          10
#define MAX_PRECISION 10

char *ftoa(double number, int ndigit, char *buf) {
  // no support for negative digits after the decimal point
  ndigit = fmax(0, ndigit);

  uint32_t int_part = (int)(number);
  itoa(int_part, buf, BASE); // getting integer part using itoa

  // getting the decimal part's digits as an integer, in order to use atoi again
  number -= int_part;
  number = fabs(number); // and we continue with the absolute value

  // we need only $ndigits digits of the decimal part
  int_part =
      (uint32_t)(number * __builtin_powf(BASE, fmin(ndigit, MAX_PRECISION)));
  if (ndigit) { // if the decimal part is 0, we are done with converting the
                // number
    char *fraction = buf + strlen(buf);
    *fraction++    = '.'; // decimal point divides both parts

    utoa(int_part, fraction,
         BASE); // converting the decimal digits into a string
  }

  return buf;
}
