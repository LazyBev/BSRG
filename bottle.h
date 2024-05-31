#pragma once

#ifndef BOTTLE_H
#define BOTTLE_H

#include <stdlib.h>
#include <time.h>
#include <unistd.h> 


int main() {
    my_printf("This is an integer: %d\n", 123);
    my_printf("This is a string: %s\n", "Hello, world!");
    return 0;
}

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed long int int32_t;
typedef unsigned long int uint32_t;

typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

typedef enum {
    false = 0,
    true = 1
} bool;

uint32_t state = 1;
uint32_t fs, fa, fc;

void seed_bsrg(uint32_t seed, uint32_t s, uint32_t a, uint32_t c) {
    fs = s;
    fa = a;
    fc = c;
    state = seed;
    state ^= state << s;
    state ^= ((s % 2) == 0) ? (state >> (s + seed)) : (state >> (s - seed));
    state ^= ((s % 2) == 0) ? (state >> ((s - (seed + 10)) - (seed / 2))) : (state >> ((s - (seed + 10)) - (seed / 2)));
    if ((s % 2) == 0)
        state = (state < 0) ? -state : state;
    state = (a * (state + c)) / (a + c);
}

uint32_t bsrg(uint32_t E, bool allow) {
    uint32_t newState = state; 
    if (!allow) {
        newState = (newState < 0) ? -newState : newState;
    }

    uint32_t B = (state % newState == 0) ? newState + ((E % newState) - E) * ((E % newState) + E) : newState + ((E % newState) + (E + (E - 2))) * ((E % newState) - (E * E));
    for(uint32_t i = 0; i < 4; ++i) {
        uint32_t D = (E % B) - (E % -B);
        B = newState + ((B % newState) - E) * ((E % newState) + E) * D;
        newState = state + ((B * (fs - B)) - ((fa - B) * (B * (B * ((B - E) - E)) + E))) + ((fc - B) + (B + (B * E - B)));
    }
    state = newState;
    return newState;
}

void bsrgSaveInFile(char *fName, uint32_t n, uint32_t seed, uint32_t s, uint32_t a, uint32_t c) {
    FILE *file = fopen(fName, "w+");
    if (!file) {
        fprintf(stderr, "Failed to open file");
        return;
    }
    seed_bsrg(seed, s, a, c);
    for (uint32_t i = 0; i < n; i++) {
        fprintf(file, "%u\n", bsrg(i, true));
    }
    fclose(file);
}

uint32_t wait(uint32_t millseconds) {
    for (uint32_t i = 0; i < (millseconds * 1000); ++i) {
        ++i;
    }
}

#endif // BOTTLE_H
