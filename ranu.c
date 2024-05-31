#include "ranu.h"

// Seeds Random Number Generator
// "int e" is a modifer to add more entropy to the generation of the number 
void sera(int e) { srand(e * (time(NULL) * getpid())); }

// Generates Random Number
// "int u" is a modifer to add more entropy to the generation of the number 
// "bool allow" is a boolean that decides if negative numbers can be produced or not (true = possiblity of negatives) 
int ranu(int u, bool allow) {
  sera(7);
  float B = rand() * u;
  int A = B + floor((B - (B / 10000000)) / (B / getpid()));

  if (!allow)
    A = (A < 0) ? -A : A;

  return A;
}
