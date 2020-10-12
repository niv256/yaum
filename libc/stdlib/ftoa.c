#include <string.h>
#include <stdlib.h>
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
    
    // the decimal part of a negative number is the same as its opposite
    if(number < 0)
    {
        number = -number;
        int_part = -int_part;
    }
    
    // after the end of the integer part will be the decimal part
    char *fraction = buf + strlen(buf);
    *fraction++ = '.'; // decimal point divides both parts

    number = (number - int_part) * BASE; // get the first decimal digit
    for(; ndigit > 0 && number; ndigit--, number = (number - (int)(number)) * BASE)
        *fraction++ = '0' + (int)(number);

    // if there's no decimal part, we'll delete the decimal point
    if(*(fraction - 1) == '.')
        fraction--;

    *fraction = '\0'; // end of string

    return buf;
}
