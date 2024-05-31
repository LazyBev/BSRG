#include "ranu.h"

// Seeds Random Number Generator
void sera(int e) { srand(e * (time(NULL) * getpid())); }

// Generates Random Number
int ranu(int u, bool allow) {
  sera(7);
  float B = rand() * u;
  int A = B + floor((B / 10000000) / getpid());

  if (!allow)
    A = (A < 0) ? -A : A;

  return A;
}
