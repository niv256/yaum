#include <etc/tools.h>
#include <io/uart.h>
#include <stdbool.h>

#define COM1                    0x3f8
#define TICKS_PER_SECOND        115200
#define BAUD_RATE               9600
#define BAUD_DEVISOR            (TICKS_PER_SECOND / BAUD_RATE)
#define BITS_8_NO_PARITY_1_STOP 3

#define LSR_BUF_EMPTY 3

static bool is_transmit_empty(void);

void init_uart(void) {
  // disable interrupts
  outb(COM1 + 1, 0x00);

  // set devisor
  outb(COM1 + 3, 1 << 7);              // enable DLAB
  outb(COM1 + 0, BAUD_DEVISOR & 0xff); // least significant byte of divisor
  outb(COM1 + 1, BAUD_DEVISOR >> 8);   // most significant byte of divisor
  outb(COM1 + 3, 0);                   // disable DLAB

  // 8 bits, no parity, one stop bit
  outb(COM1 + 3, BITS_8_NO_PARITY_1_STOP);

  outb(COM1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

static bool is_transmit_empty(void) {
  uint8_t line_status_register = inb(COM1 + 5);
  return (line_status_register & (1 << LSR_BUF_EMPTY)) != 0;
}

void uart_writechar(char c) {
  while (is_transmit_empty())
    ;
  outb(COM1 + 0, c);
}

void uart_deletechar(void) {
  uart_writechar('\b');
}
