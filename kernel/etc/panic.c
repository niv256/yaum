#include <etc/panic.h>
#include <io/screen.h>

static void print_info(void);

void panic(char *panic_msg, char *file, int line) {
  terminal_newline();
  terminal_writestring("PANIC: \"");
  terminal_writestring(panic_msg);
  terminal_writestring("\" (");
  terminal_writestring(file);
  terminal_writestring(":");
  terminal_writedec(line);
  terminal_writestring(")\n");

  print_info();

  __asm__("cli");
  for (;;) {
    __asm__("hlt");
  }
}

static void print_info(void) {
}
