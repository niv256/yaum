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


int kmain(void *mbd,unsigned int magic) {
	/* initialize terminal interface */
	terminal_initialize();
	if (magic != 0x2BADB002){
		terminal_writestring("Invalid multiboot header.");
		return -1;
	}
	terminal_writestring("this is big siber os.\n");

	/* initialize the gdt */
	terminal_writestring("initializing gdt.\n");
	gdt_init();
	terminal_writestring("gdt initialized.\n");

	/* initialize the idt */
	terminal_writestring("initializing idt.\n");
	idt_init();
	terminal_writestring("idt initialized.\n");

	__asm__("int $0x80");
	/*terminal_writestring("interrupt 1\n");
	terminal_clearscreen();
	__asm__("int $0x80");*/
	return 0;
}
