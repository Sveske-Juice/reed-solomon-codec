#ifndef RS_H
#define RS_H

#include <cstdint>
#include <vector>

std::vector<uint8_t> generator_poly(uint8_t nsym);
std::vector<uint8_t> rs_encode(std::vector<uint8_t>& data, uint8_t nsym);;

#endif
