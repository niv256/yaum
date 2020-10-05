#include "math.h"

double ceil(double x) {
  int n = (int)x;
  if (n == x) {
    return x;
  }
  return (double)n + 1;
}

int abs(int x) {
  if (x >= 0) {
    return x;
  }

  return -x;
}

double fabs(double x) {
  if (x >= 0) {
    return x;
  }

  return -x;
}
