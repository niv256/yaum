#include <string.h>

void *memcpy(void *dest, const void *src, uint32_t size) {
  for (uint32_t i = 0; i < size; i++)
    ((char *)dest)[i] = ((char *)src)[i];
  return dest;
}
