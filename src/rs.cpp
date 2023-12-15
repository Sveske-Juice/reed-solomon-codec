#include "rs.h"
#include "gf.h"
#include "gf_poly.h"

#include <iostream>

std::vector<uint8_t> generator_poly(uint8_t nsym) {
    std::vector<uint8_t> gpoly = {1};
    for (uint8_t i = 0; i < nsym; i++) {
        std::vector<uint8_t> tmp = {1};
        tmp.push_back(gf_pow(2, i));
        gpoly = gf_poly_mul(gpoly, tmp);
    }
    return gpoly;
}

std::vector<uint8_t> rs_encode(std::vector<uint8_t>& data, uint8_t nsym) {
    std::vector<uint8_t> gpoly = generator_poly(nsym);
    size_t redundancy = gpoly.size() - 1;
    size_t data_size = data.size();

    // Add redundancy padding
    for (int i = 0; i < redundancy; i++) {
        data.push_back(0);
    }
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>>
        quotientRemainderPair = gf_poly_div(data, gpoly);

    std::vector<uint8_t> encoded;
    encoded.reserve(data_size + std::get<1>(quotientRemainderPair).size());

    // Add data and remainder to encoded codeword
    for (int i = 0; i < data_size; i++) {
        encoded.push_back(data[i]);
    }
    for (auto r : std::get<1>(quotientRemainderPair)) {
        encoded.push_back(r);
    }

    return encoded;
}
