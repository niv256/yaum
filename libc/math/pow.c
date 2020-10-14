#include <math.h>

float pow(float x, int n) {
  if (n < 0) {
    n = 0;
  }

  float ret = 1;

  for (int i = 0; i < n; i++) {
    ret *= x;
  }

  return ret;
}
