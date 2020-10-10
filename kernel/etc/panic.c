#include <etc/panic.h>
#include <stdio.h>

static void print_info(void);

void panic(char *panic_msg, char *file, int line) {
  printf("\nPANIC: \"%s\" (%s:%d)\n", panic_msg, file, line);

  print_info();

  __asm__("cli");
  for (;;) {
    __asm__("hlt");
  }
}

static void print_info(void) {
}
