#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BASE 10

char *ftoa(double number, int ndigit, char *buf)
{
  if(ndigit < 0) // no support for negative digits after the decimal point
    ndigit = 0;

  // percision
  double percision = 0.5;
  for(int i = ndigit; i; i--)
    percision /= 10;
  number += (number > 0) ? percision : -percision;

  int int_part = (int)(number);
  itoa(int_part, buf, BASE); // getting integer part using itoa
    
  // getting the decimal part's digits as an integer, in order to use atoi again
  number -= int_part;
  for(; ndigit; ndigit--) // we nedd only $ndigits digits of the decimal part
    number *= BASE;
  int_part = abs((int) number); // the decimal part is non-negative

  if(!int_part) // if the decimal part is 0, we are done with converting the number
    return buf;

  char *fraction = buf + strlen(buf);
  *fraction++ = '.'; // decimal point divides both parts

  itoa(int_part, fraction, BASE); // converting the decimal digits into a string
  return buf;
}
