#include "ranNum.h"

void sera(int e) { srand(e * (time(NULL) * getpid())); }

int ranu(int u) {
  sera(7);
  float B = rand() * u;
  int A = B + floor((B / 10000000) / getpid());

  A = (A < 0) ? -A : A;

  return A;
}
