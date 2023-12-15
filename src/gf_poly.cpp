#include "gf_poly.h"

#include "gf.h"

void gf_poly_scale(std::vector<uint8_t>& poly, uint8_t scalor) {
    for (int i = 0; i < poly.size(); i++) {
        poly[i] = gf_mul(poly[i], scalor);
    }
}

std::vector<uint8_t> gf_poly_add(std::vector<uint8_t>& x, std::vector<uint8_t>& y) {
    std::vector<uint8_t> res;
    res.resize(std::max(x.size(), y.size()));

    for (int i = 0; i < x.size(); i++) {
        res[i + res.size() - x.size()] = x[i];
    }
    for (int i = 0; i < y.size(); i++) {
        res[i + res.size() - y.size()] ^= y[i];
    }
    return res;
}

std::vector<uint8_t> gf_poly_mult(std::vector<uint8_t>& x, std::vector<uint8_t>& y) {
    std::vector<uint8_t> res;
    res.resize(x.size() + y.size() - 1);

    for (int j = 0; j < y.size(); j++) {
        for (int i = 0; i < x.size(); i++) {
            res[i + j] ^= gf_mul(x[i], y[j]);
        }
    }
    return res;
}

uint8_t gf_poly_eval(std::vector<uint8_t>& poly, uint8_t x) {
    uint8_t y = poly[0];
    for (int i = 1; i < poly.size(); i++) {
        y = gf_mul(y, x) ^ poly[i];
    }
    return y;
}
