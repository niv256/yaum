#include "isr.h"
#include "screen.h"
#include "tools.h"
#include "panic.h"

#define NUMBER_CALLBACKS 16

void (*callbacks[NUMBER_CALLBACKS])();

void isr_handler(struct registers registers) {
	terminal_writestring("got interrupt: 0x");
	terminal_writeint((uint64_t)registers.int_num, 16);
	terminal_putchar('\n');
}

void irq_handler(struct registers registers) {
	// ack the irq
	outb(0x20, 0x20);
	// if the interrupt was from slave PIC
	if (registers.int_num >= IRQ8) {
		outb(0xa0, 0x20);
	}
	if (callbacks[registers.int_num-IRQ0] != 0) {
		(*callbacks[registers.int_num-IRQ0])();
	} else {
		terminal_writestring("got IRQ: 0x");
		terminal_writeint(registers.int_num, 16);
		terminal_putchar('\n');
	}

}

void setup_isr_callback(int irq, void (*callback)()) {
	if (!callback) {
		panic("callback function passed is 0");
	}
	callbacks[irq-IRQ0] = callback;
}
