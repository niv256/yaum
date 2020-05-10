#include "string.h"
#include "stdlib.h"
#include "ctype.h"

size_t strlen(const char *str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int strcmp(const char *str1, const char *str2) {
	if (strlen(str1) != strlen(str2)) {
		return 0;
	}

	for (int i = 0; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}

	return 1;
}

size_t trim(char *out, size_t len, const char *str) {
  if(len == 0)
    return 0;

  const char *end;
  size_t out_size;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
  {
    *out = 0;
    return 1;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;
  end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len-1 ? (end - str) : len-1;

  // Copy trimmed string and add null terminator
  memcpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}
