#include <stddef.h>
#include <stdint.h>
#include "descriptors.h" 
#include "screen.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
 
void kmain(void) {
	/* initialize terminal interface */
	terminal_initialize();
 
	/* initialize the gdt */
	gdt_init();

	terminal_writestring("better than windows already\nand this is in new line\nand another line!\nHACKER SIBER OS!!!");
}
