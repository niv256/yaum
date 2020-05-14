#include "panic.h"
#include "screen.h"

static void print_info(void);

void panic(char *panic_msg) {
	terminal_writestring("PANIC: ");
	terminal_writestring(panic_msg);
	terminal_putchar('\n');

	print_info();

	__asm__("cli");
	for (;;) {
		__asm__("hlt");
	}
}

static void print_info(void) {
}
