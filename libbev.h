#ifndef LIBBEV_H
#define LIBBEV_H

#include <stdlib.h>

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

// Function declarations
uint64_t NOT(uint64_t in);
uint64_t NAND(uint64_t in1, uint64_t in2);
uint64_t NOR(uint64_t in1, uint64_t in2);
uint64_t XNOR(uint64_t in1, uint64_t in2);
uint64_t AND(uint64_t in1, uint64_t in2);
uint64_t OR(uint64_t in1, uint64_t in2);
uint64_t XOR(uint64_t in1, uint64_t in2);

void halfAdder(int x, int y, int *sum, int *car);
void fullAdder(int c, int x, int y, int *sum, int *car);
int byteAdder(int in1, int in2);

double add(double x, double y);
double sub(double x, double y);
double div(double x, double y);
double mul(double x, double y);
double expo(double x, double e);
double squ(double x);
double squrt(double t);
int abso(double x);

uint64_t Bsrg(uint64_t seed, uint64_t s, uint64_t a, uint64_t c, uint64_t E, char* allow);
void wait(uint64_t clockSpeed, uint64_t milliseconds);

uint64_t* map(uint64_t (*fn)(uint64_t), uint64_t* x, uint64_t size);

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
    *sum = XOR(XOR(c, x), y);
    *car = OR(AND(c, x), AND(XOR(c, x), y));
}

int byteAdder(int in1, int in2) {
    int bsum[8] = {0}, tcar = 0;
    int result = 0;

    halfAdder((in1 & 1), (in2 & 1), &bsum[0], &tcar);

    for (int i = 1; i < 8; i++) {
        fullAdder(tcar, ((in1 >> i) & 1), ((in2 >> i) & 1), &bsum[i], &tcar);
    }

    for (int i = 0; i < 8; i++) {
        result |= (bsum[i] << i);
    }

    return result;
}

// Math functions
double add(double x, double y) { return x + y; }

double sub(double x, double y) { return x - y; }

double div(double x, double y) { return x / y; }

double mul(double x, double y) { return x * y; }

double expo(double x, double e) {
    double result = 1.0;
    int positive_exponent = (int)(e >= 0 ? e : -e);

    for (int i = 0; i < positive_exponent; ++i) {
        result *= x;
    }

    if (e < 0) {
        result = 1.0 / result;
    }

    return result;
}

double squ(double x) {
    return x * x;
}

double squrt(double t) {
    double r = t / 2;
    for (int i = 0; i < 2000; i++) {
        r = (r + t / r) / 2;
    }
    return r;
}

int abso(double x) {
    return (x < 0) ? (int)-x : (int)x;
}

// Randomizer
uint64_t Bsrg(uint64_t seed, uint64_t s, uint64_t a, uint64_t c, uint64_t E, char* allow) {
    uint64_t state = seed;
    uint64_t newState = state;
    uint64_t fs = s, fa = a, fc = c;

    state ^= state << s;
    state ^= (s % 2 == 0) ? (state >> (s + seed)) : (state >> (s - seed));
    state ^= state >> ((s - (seed + 10)) - (seed / 2));
    state = (a * (state + c)) / (a + c);

    if (allow && newState < 0) {
        newState = -newState;
    }

    uint64_t B = (state % newState == 0)
                 ? newState + ((E % newState) - E) * ((E % newState) + E)
                 : newState + ((E % newState) + (E + (E - 2))) * ((E % newState) - (E * E));

    for (uint64_t i = 0; i < 4; ++i) {
        uint64_t D = (E % B) - (E % -B);
        B = newState + ((B % newState) - E) * ((E % newState) + E) * D;
        newState = state + ((B * (fs - B)) - ((fa - B) * (B * (B * ((B - E) - E)) + E)))
                          + ((fc - B) + (B + (B * E - B)));
    }

    state = newState;

    if (newState <= 999999999999999999) {
        newState = newState * (newState / 10000000000000000) * 10;
    } else if (newState >= 99999999999999999) {
        newState = newState / (newState / 10000000000000000);
    }

    return newState;
}

// Approximation of a wait
void wait(uint64_t clockSpeed, uint64_t milliseconds) {
    uint64_t ns_per_tick = 1000000000 * clockSpeed;
    uint64_t ticks = (milliseconds * 1000000) / ns_per_tick;

    for (uint64_t i = 0; i < ticks; ++i) {
        // Busy wait
    }
}

// Map function
uint64_t* map(uint64_t (*fn)(uint64_t), uint64_t* x, uint64_t size) {
    uint64_t* results = (uint64_t*)malloc(size * sizeof(uint64_t));
    for (uint64_t i = 0; i < size; ++i) {
        results[i] = fn(x[i]);
    }
    return results;
}

#endif // LIBBEV_H
