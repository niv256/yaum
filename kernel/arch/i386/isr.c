#include <arch/i386/isr.h>
#include <etc/panic.h>
#include <etc/tools.h>
#include <stdio.h>

#define NUMBER_CALLBACKS 256

static char is_irq(uint32_t int_num);

isr_t callbacks[NUMBER_CALLBACKS];

void isr_handler(registers_t regs) {
  if (is_irq(regs.int_num)) {
    // ack the irq
    outb(0x20, 0x20);
    // if the interrupt was from slave PIC
    if (regs.int_num >= IRQ8) {
      outb(0xa0, 0x20);
    }
  }

  if (callbacks[regs.int_num]) {
    (*callbacks[regs.int_num])(regs);
  } else {
    printf("got interrupt: 0x%x\n", regs.int_num);
  }
}

static char is_irq(uint32_t int_num) {
  return (int_num >= IRQ0 && int_num <= IRQ15);
}

void setup_isr_callback(int isr, isr_t callback) {
  if (!callback) {
    PANIC("callback function passed is 0");
  }
  callbacks[isr] = callback;
}
