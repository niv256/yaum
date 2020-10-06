#include <string.h>

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
