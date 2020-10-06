#include <string.h>

void *memcpy(char *dest, const char *src, uint32_t size) {
  for (uint32_t i = 0; i < size; i++)
    dest[i] = src[i];
  return dest;
}
