#ifndef GF_POLY_H
#define GF_POLY_H

#include <cstdint>
#include <vector>

void gf_poly_scale(std::vector<uint8_t>& poly, uint8_t scalor);

std::vector<uint8_t> gf_poly_add(std::vector<uint8_t>& x, std::vector<uint8_t>& y);
std::vector<uint8_t> gf_poly_mul(std::vector<uint8_t>& x, std::vector<uint8_t>& y);
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> gf_poly_div(std::vector<uint8_t>& dividend, std::vector<uint8_t>& divisor);

uint8_t gf_poly_eval(std::vector<uint8_t>& poly, uint8_t x);

#endif
