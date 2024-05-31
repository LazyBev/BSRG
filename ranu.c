#include "ranu.h"

// "int e" (e for entropy) adds entropy to the generation of the number 
void sera(int E) { srand(E * (time(NULL) * getpid())); }

// "int u" is a modifer to add more entropy to the generation of the number 
// "bool allow" is a boolean that decides if negative numbers can be produced or not (true = possiblity of negatives) 
int ranu(int E, bool allow) {
  sera(E);
  float B = rand() * E;
  int A = B + ((B - (B / (B * (E * E)))) / (B / getpid()));

  if (!allow)
    A = (A < 0) ? -A : A;

  return A;
}
