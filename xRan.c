#include "xRan.h"

uint32_t state = 1;
int fs, fa, fc;

int mod(int a, int b) {
    return (a % b - b) % b;
}

void saveInFile(char *fName, int n, uint32_t seed,uint32_t s, uint32_t a, uint32_t c) {
    FILE *file = fopen(fName, "w+");
    seed_bsrg(seed, s, a, c);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", bsrg(i, true));
    }
    fclose(file);
}

uint32_t seed_bsrg(uint32_t seed, uint32_t s, uint32_t a, uint32_t c) {
    fs, fa, fc = s, a, c;
    state = seed;
    state ^= state << s;
    state ^= ((s % 2) == 0) ? (state >> (s + seed)) : (state >> (s - seed));
    state ^= ((s % 2) == 0) ? (state >> ((s - (seed + 10)) - (seed / 2))) : (state >> ((s - (seed + 10)) - (seed / 2)));
    if ((s % 2) == 0)
        state = (state < 0) ? -state : state;
    state = (a * (state + c)) / (a + c);
    return state;
}

uint32_t bsrg(int E, bool allow) {
    uint32_t newState = state; 
    if (!allow) {
        newState = (newState < 0) ? -newState : newState;
    }

    int B = newState + (mod(E, newState) - E) * (mod(E, newState) + E);
    for(int i = 0; i < 4; ++i) {
        int C = -B;
        int D = mod(E, B) * mod(E, C);
        B = newState + (mod(E, newState) - E) * (mod(E, newState) + E) * D;
        newState = state + ((B * fs) - (fa *(B * (B * ((B - E) - E)) + E))) + (fc + (B + (B * E - B)));
    }
    state = newState;
    return newState;
}
