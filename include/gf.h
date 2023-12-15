#ifndef GF_H
#define GF_H

#include <cstdint>

extern uint8_t gf_exp[];
extern uint8_t gf_log[];

// Initialize Galois field logarithm and anti-log (exponents) tables, used for
// gf_mult and gf_div
void init_lookup_tables(int primitive_element = 0x11d);

// GF(2^8) Addition
uint8_t gf_add(uint8_t x, uint8_t y);

// GF(2^8) Subtraction
uint8_t gf_sub(uint8_t x, uint8_t y);

// Carry-Less Multiplication
uint8_t cl_mul(uint8_t x, uint8_t y);

// GF(2^8) Multiplication
uint8_t gf_mul(uint8_t x, uint8_t y);

uint8_t gf_div(uint8_t x, uint8_t y);

uint8_t gf_pow(uint8_t x, uint8_t power);
uint8_t gf_inverse(uint8_t x);

#endif
