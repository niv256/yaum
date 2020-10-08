#include <ctype.h>
#include <etc/tools.h>
#include <io/screen.h>
#include <string.h>

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

size_t trim(char *out, size_t len, const char *str) {
  if (len == 0)
    return 0;

  const char *end;
  size_t out_size;

  // Trim leading space
  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0) // All spaces?
  {
    *out = 0;
    return 1;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;
  end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len - 1 ? (end - str) : len - 1;

  // Copy trimmed string and add null terminator
  memcpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}
