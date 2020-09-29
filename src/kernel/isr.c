#include "isr.h"
#include "panic.h"
#include "screen.h"
#include "tools.h"

#define NUMBER_CALLBACKS 256

isr_t callbacks[NUMBER_CALLBACKS];

void isr_handler(registers_t regs) {
  if (regs.int_num >= IRQ0 && regs.int_num <= IRQ15) {
    panic("invalid interrupt number in isr");
  }

  if (callbacks[regs.int_num]) {
    (*callbacks[regs.int_num])(regs);
  } else {
    terminal_writestring("got interrupt: 0x");
    terminal_writeint((uint64_t)regs.int_num, 16);
    terminal_putchar('\n');
  }
}

void irq_handler(registers_t regs) {
  if (regs.int_num < IRQ0 || regs.int_num > IRQ15) {
    panic("invalid interrupt number in irq");
  }

  // ack the irq
  outb(0x20, 0x20);
  // if the interrupt was from slave PIC
  if (regs.int_num >= IRQ8) {
    outb(0xa0, 0x20);
  }

  if (callbacks[regs.int_num]) {
    (*callbacks[regs.int_num])(regs);
  } else {
    terminal_writestring("got IRQ: 0x");
    terminal_writeint(regs.int_num, 16);
    terminal_putchar('\n');
  }
}

void setup_isr_callback(int isr, isr_t callback) {
  if (!callback) {
    panic("callback function passed is 0");
  }
  callbacks[isr] = callback;
}
