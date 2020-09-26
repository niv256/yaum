#include "../include/stdint.h"
#include "descriptors.h"
#include "keyboard.h"
#include "screen.h"
#include <stddef.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

int kmain(void) {
  /* initialize terminal interface */
  terminal_initialize();
  terminal_writestring("this is big siber os.\n");

  /* initialize the gdt */
  gdt_init();
  terminal_writestring("gdt initialized.\n");

  /* initialize the idt */
  idt_init();
  terminal_writestring("idt initialized.\n");

  /* initialize the keyboard */
  keyboard_init();
  terminal_writestring("keyboard initialized.\n");

  terminal_writestring("> ");

  for (;;)
    ;
  return 0;
}
