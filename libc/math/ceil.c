#include <math.h>

float ceil(float x) {
  int n = (int)x;
  if (n == x) {
    return x;
  }
  return (float)n + 1;
}
