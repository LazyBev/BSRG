#pragma once

#ifndef XRAN_H
#define XRAN_H

#define DEFAULT_MODULUS 7
#define DEFAULT_MULTIPLIER 4
#define DEFAULT_INCREMENT 5
#define DEFAULT_SEED 1

typedef unsigned int uint32_t;

typedef enum {
    false = 0,
    true = 1
} bool;

extern uint32_t state;

uint32_t seed_bsrg(uint32_t seed, uint32_t s, uint32_t a, uint32_t c);
uint32_t bsrg(int E, bool allow);

#endif // XRAN_H
