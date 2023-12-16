#ifndef RS_H
#define RS_H

#include <cstdint>
#include <vector>

void print_vec(std::vector<uint8_t>& vec, bool hex = true);

std::vector<uint8_t> generator_poly(uint8_t nsym);
std::vector<uint8_t> rs_encode(std::vector<uint8_t> &data, uint8_t nsym);
;

std::vector<uint8_t> rs_calc_syndrome(std::vector<uint8_t> &data, uint8_t nsym);
uint8_t rs_check_code(std::vector<uint8_t> &data, uint8_t nsym);

std::vector<uint8_t>
rs_find_errata_locator(std::vector<uint8_t> &err_positions);
std::vector<uint8_t>
rs_find_error_evaluator(std::vector<uint8_t> &syndrome,
                        std::vector<uint8_t> &err_locations, uint8_t nsym);

std::vector<uint8_t> rs_correct_errata(std::vector<uint8_t> &data,
                                       std::vector<uint8_t> &syndrome,
                                       std::vector<uint8_t> &err_pos);

#endif
