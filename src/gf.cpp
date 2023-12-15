#include "gf.h"
#include <cstdint>
#include <stdexcept>

uint8_t gf_exp[512] = {};
uint8_t gf_log[256] = {};

uint8_t gf_add(uint8_t x, uint8_t y) {
    return x ^ y;
}

uint8_t gf_sub(uint8_t x, uint8_t y) {
    return x ^ y;
}

void init_lookup_tables(int primitive_element) {
    int x = 1;
    for (int i = 0; i < 255; i++) {
        gf_exp[i] = x;
        gf_log[x] = i;

        x <<= 1;
        if (x & 256) {
            x ^= primitive_element;
        }
    }

    // Repeat the contents for the exponent table, so we don't need
    // to mod 255 to stay inside the bounds
    for (int i = 255; i < 512; i++) {
        gf_exp[i] = gf_exp[i - 255];
    }
}

uint8_t gf_mult(uint8_t x, uint8_t y) {
    if (!x || !y) return 0;

    return gf_exp[gf_log[x] + gf_log[y]];
}

uint8_t gf_div(uint8_t x, uint8_t y) {
    if (!y) throw std::overflow_error("Divide by zero");
    else if (!x) return 0;

    return gf_exp[(gf_log[x] + 255 - gf_log[y]) % 255];
}

uint8_t gf_pow(uint8_t x, uint8_t power) {
    return gf_exp[(gf_log[x] * power) % 255];
}

uint8_t gf_inverse(uint8_t x) {
    return gf_exp[255 - gf_log[x]]; // gf_inverse(x) == gf_div(1, x)
}

