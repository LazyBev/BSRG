#include "xRan.h"

uint32_t state = 1;

uint32_t seed_bsrg(uint32_t seed, uint32_t s, uint32_t a, uint32_t c) {
    state = seed;
    state ^= state << s;
    state ^= ((s % 2) == 0) ? (state >> (s + 4)) : (state >> (s - 4));
    state ^= (((state - s) % 2) == 0) ? (state >> ((s / 2) + s)) : (state >> ((s - 10) - 2));
    state = (a * (state + c)) / (a + c);
    return state;
}

uint32_t bsrg(int E, bool allow) {
    uint32_t newState = state; 
    if (!allow) {
        newState = (newState < 0) ? -newState : newState;
    }
    int B = newState * E;
    newState = (B - (B / (B * ((B + E) - E) / E))) + (B / (B * E - B));
    state = newState;
    return newState;
}
