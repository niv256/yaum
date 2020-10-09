#include <io/screen.h>
#include <stdarg.h>

int vprintf(const char *format, va_list ap) {
  int total = 0;
  for (const char *i = format; *i; i++) {
    if (*i == '%') {
      switch (*(++i)) {
        case 'd': {
          terminal_writedec(va_arg(ap, int));
          break;
        }
        case 'x': {
          terminal_writehex(va_arg(ap, uint32_t));
          break;
        }
        case 's': {
          terminal_writestring(va_arg(ap, char *));
          break;
        }
        case 'c': {
          /* since we can only push a minimum of 4 bytes on the stack, char
           * automatically gets promoted to an int */
          terminal_writechar(va_arg(ap, int));
          break;
        }
        case '%': {
          terminal_writechar('%');
          break;
        }
        default: {
          terminal_writechar('%');
          terminal_writechar(*i);
          break;
        }
      }
    } else {
      terminal_writechar(*i);
    }
  }

  // TODO: implement counting for real
  return total;
}
