#pragma once

#ifndef LIBBEV_H
#define LIBBEV_H

#define true 1
#define false 0

// Extra data types
typedef char* string_t;
typedef unsigned usig_t;
typedef signed sig_t;
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


// Logic gates
uint64_t NOT(uint64_t in) {
    return (in == true) ? false : true;
}

uint64_t NAND(uint64_t in1, uint64_t in2) {
    return NOT(in1 & in2);
}

uint64_t NOR(uint64_t in1, uint64_t in2) {
    return NOT(in1 | in2);
}

uint64_t XNOR(uint64_t in1, uint64_t in2) {
    return NOT(in1 ^ in2);
}

uint64_t AND(uint64_t in1, uint64_t in2) {
    return in1 & in2;
}

uint64_t OR(uint64_t in1, uint64_t in2) {
    return in1 | in2;
}

uint64_t XOR(uint64_t in1, uint64_t in2) {
    return in1 ^ in2;
}

void halfAdder(int x, int y, int *sum, int *car) {
    *sum = XOR(x, y);
    *car = AND(x, y);
}

void fullAdder(int c, int x, int y, int *sum, int *car) {
    *sum = XOR(XOR(c, x),y);
    *car = OR(AND(c, x), AND(XOR(c, x), y));
}

int byteAdder(int in1, int in2) {
    int bsum[8], tcar, result;

    halfAdder((in1 & 1), (in2 & 1), &bsum[0], &tcar);

    fullAdder(tcar, ((in1 >> 1) & 1), ((in2 >> 1) & 1), &bsum[1], &tcar);
    fullAdder(tcar, ((in1 >> 2) & 1), ((in2 >> 2) & 1), &bsum[2], &tcar);
    fullAdder(tcar, ((in1 >> 3) & 1), ((in2 >> 3) & 1), &bsum[3], &tcar);
    fullAdder(tcar, ((in1 >> 4) & 1), ((in2 >> 4) & 1), &bsum[4], &tcar);
    fullAdder(tcar, ((in1 >> 5) & 1), ((in2 >> 5) & 1), &bsum[5], &tcar);
    fullAdder(tcar, ((in1 >> 6) & 1), ((in2 >> 6) & 1), &bsum[6], &tcar);
    fullAdder(tcar, ((in1 >> 7) & 1), ((in2 >> 7) & 1), &bsum[7], &tcar);

    for (int i = 0; i < 8; i++) {
        result |= (bsum[i] << i);
    }

    return result;
}

// Math functions
double expo(double x, double e) {
    double result = 1.0;
    e = e >= 0 ? e : -e;

    for (int i = 0; i < e; ++i) {
        result *= x;
    }

    if (e < 0) {
        result = 1.0 / result;
    }

    return result;
}

double squ(double x){
    return x * x;
}

double squrot(double t) {
    long double r = t/2;
    for (int i = 0; i < 2000; i++) {
        r = (r+t/r)/2;
    }
    return r;
}

int abso(double x) {
    return (x < 0) ? (int)-x : (int)x;
}

// Radomizer
uint64_t Bsrg(uint64_t seed, uint64_t s, uint64_t a, uint64_t c, uint64_t E, bool allow) {
    uint64_t state = seed;
    uint64_t newState = state;
    uint64_t fs, fa, fc;

    // Seed
    fs = s;
    fa = a;
    fc = c;
    state ^= state << s;
    state ^= (s % 2 == 0) ? (state >> (s + seed)) : (state >> (s - seed));
    state ^= (s % 2 == 0) ? (state >> ((s - (seed + 10)) - (seed / 2))) : (state >> ((s - (seed + 10)) - (seed / 2)));
    state = (a * (state + c)) / (a + c);

    // Randomize
    newState = state;
    if (!allow) {
        newState = (newState < 0) ? -newState : newState;
    }

    uint64_t B = (state % newState == 0) ? newState + ((E % newState) - E) * ((E % newState) + E) 
                                          : newState + ((E % newState) + (E + (E - 2))) * ((E % newState) - (E * E));
    for (uint64_t i = 0; i < 4; ++i) {
        uint64_t D = (E % B) - (E % -B);
        B = newState + ((B % newState) - E) * ((E % newState) + E) * D;
        newState = state + ((B * (fs - B)) - ((fa - B) * (B * (B * ((B - E) - E)) + E))) + ((fc - B) + (B + (B * E - B)));
    }
    state = newState;

    newState = (newState <= 999999999999999999) ? (newState * (newState / 10000000000000000) * 10) : newState;
    newState = (newState >= 99999999999999999) ? (newState / (newState / 10000000000000000)) : newState;

    return newState;
}

// Approximation of a wait
uint64_t wait(uint64_t clockSpeed, uint64_t milliseconds) {
    clockSpeed *= 1000000000;
    for (uint64_t i = 0; i < (milliseconds * clockSpeed * 1000); ++i) {
    }
    return 0;
}

#endif // LIBBEV_H
