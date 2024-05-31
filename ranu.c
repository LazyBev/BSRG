#include "ranu.h"

// "int e" is a modifer to add more entropy to the generation of the number 
void sera(int e) { srand(e * (time(NULL) * getpid())); }

// "int u" is a modifer to add more entropy to the generation of the number 
// "bool allow" is a boolean that decides if negative numbers can be produced or not (true = possiblity of negatives) 
int ranu(int U, bool allow) {
  sera(U);
  float B = rand() * U;
  int A = B + ((B - (B / (B * (U * U)))) / (B / getpid()));

  if (!allow)
    A = (A < 0) ? -A : A;

  printf("B = %f\n", B);
  return A;
}
