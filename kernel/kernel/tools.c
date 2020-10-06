#include "tools.h"
#include "screen.h"

void outb(uint16_t port, uint8_t val) {
  asm volatile("outb %1, %0" : : "dN"(port), "a"(val));
}

void outw(uint16_t port, uint16_t val) {
  asm volatile("outw %1, %0" : : "dN"(port), "a"(val));
}

uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/*uint8_t inw(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inw %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

uint8_t inl(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inl %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
*/

char switch_case(char c) {
  if (c >= 0x41 && c <= 0x5a) {
    return c + 'a' - 'A';
  }

  if (c >= 0x61 && c <= 0x7a) {
    return c - 'a' + 'A';
  }

  return c;
}

/* 8 bits + '\0' = 9 bytes at least*/
char *binrep(char *dst, uint8_t num) {
  char *end;
  dst[8] = '\0';

  end = dst + 7;
  while (end > dst + 1) {
    *end-- = num & 1 ? '1' : '0';
    num >>= 1;
  }
  return dst;
}
