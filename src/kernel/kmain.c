#include "descriptors.h"
#include "keyboard.h"
#include "paging.h"
#include "screen.h"
#include "timer.h"

#if defined(__linux__) || !defined(__i686__)
#error "Either not using a cross-compiler or not an x86 elf compiler"
#endif


int kmain(void) {
  terminal_initialize();
  terminal_writestring("yaum: big siber os.\n");

  gdt_init();
  terminal_writestring("gdt initialized.\n");

  enter_pmode();
  terminal_writestring("entered protected mode.\n");

  init_paging();
  terminal_writestring("paging initialized.\n");

  idt_init();
  terminal_writestring("idt initialized.\n");

  timer_init();
  terminal_writestring("timer initialized.\n");

  keyboard_init();
  terminal_writestring("keyboard initialized.\n");

  terminal_writestring("\nshell:\n> ");

  for (;;)
    ;

  return 0;
}
