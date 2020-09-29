#include "math.h"

double ceil(double x) {
  int n = (int)x;
  if (n == x) {
    return x;
  }
  return (double)n + 1;
}
