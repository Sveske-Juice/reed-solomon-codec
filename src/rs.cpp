#include "rs.h"
#include "gf.h"
#include "gf_poly.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sys/types.h>
#include <vector>

std::vector<uint8_t> generator_poly(uint8_t nsym) {
    std::vector<uint8_t> gpoly = {1};
    for (uint8_t i = 0; i < nsym; i++) {
        std::vector<uint8_t> tmp = {1};
        tmp.push_back(gf_pow(2, i));
        gpoly = gf_poly_mul(gpoly, tmp);
    }
    return gpoly;
}

std::vector<uint8_t> rs_encode(std::vector<uint8_t> &data, uint8_t nsym) {
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

std::vector<uint8_t> rs_calc_syndrome(std::vector<uint8_t> &data,
                                      uint8_t nsym) {
    std::vector<uint8_t> syndrome;
    syndrome.assign(nsym + 1, 0);

    for (uint8_t i = 1; i < nsym + 1; i++) {
        syndrome[i] = gf_poly_eval(data, gf_pow(2, i - 1));
    }
    return syndrome;
}

uint8_t rs_check_code(std::vector<uint8_t> &data, uint8_t nsym) {
    std::vector<uint8_t> syndrome = rs_calc_syndrome(data, nsym);
    return std::reduce(syndrome.begin(), syndrome.end());
}

std::vector<uint8_t>
rs_find_errata_locator(std::vector<uint8_t> &err_positions) {
    std::vector<uint8_t> err_locators = {1};

    for (int i = 0; i < err_positions.size(); i++) {
        std::vector<uint8_t> one = {1};
        std::vector<uint8_t> second = {gf_pow(2, err_positions[i]), 0};
        auto sum = gf_poly_add(one, second);

        err_locators = gf_poly_mul(err_locators, sum);
    }

    return err_locators;
}

std::vector<uint8_t> rs_find_error_evaluator(std::vector<uint8_t> &syndrome,
                                             std::vector<uint8_t> &err_locators,
                                             uint8_t nsym) {
    std::vector<uint8_t> truncator;
    truncator.assign(nsym + 2, 0);
    truncator[0] = 1;

    auto product = gf_poly_mul(syndrome, err_locators);
    auto quotientRemainderPair = gf_poly_div(product, truncator);

    return std::get<1>(quotientRemainderPair);
}

void print_vec(std::vector<uint8_t> &vec, bool hex) {
    for (auto element : vec) {
        if (hex)
            printf("0x%x ", element);
        else
            printf("%c ", element);
    }
    std::cout << std::endl;
}

std::vector<uint8_t> rs_correct_errata(std::vector<uint8_t> &data,
                                       std::vector<uint8_t> &syndrome,
                                       std::vector<uint8_t> &err_pos) {
    uint8_t data_size = data.size();
    std::vector<uint8_t> corrected;

    std::vector<uint8_t> coef_positions;
    coef_positions.resize(err_pos.size());
    std::transform(err_pos.cbegin(), err_pos.cend(),
                   coef_positions.begin(),
                   [data_size](uint8_t pos) { return data_size - 1 - pos; });
    std::vector<uint8_t> err_locators = rs_find_errata_locator(coef_positions);

    std::vector rsyndrome = syndrome;
    std::reverse(rsyndrome.begin(), rsyndrome.end());

    std::vector<uint8_t> err_evaluator = rs_find_error_evaluator(
        rsyndrome, err_locators, err_locators.size() - 1);
    std::reverse(err_evaluator.begin(), err_evaluator.end());

    std::vector<uint8_t> X;
    X.reserve(coef_positions.size());
    for (int i = 0; i < coef_positions.size(); i++) {
        uint16_t l = 255 - coef_positions[i];
        X.push_back(gf_pow(2, -l));
    }

    // Forney algorithm
    std::vector<uint8_t> em_poly;
    uint8_t x_size = X.size();
    em_poly.resize(data.size());

    for (uint8_t i = 0; i < x_size; i++) {
        uint8_t Xi = X[i];
        uint8_t Xi_inv = gf_inverse(Xi);

        std::vector<uint8_t> err_loc_prime_tmp;
        for (int j = 0; j < x_size; j++) {
            if (j != i) {
                err_loc_prime_tmp.push_back(gf_sub(1, gf_mul(Xi_inv, X[j])));
            }
        }

        // TODO: use reduce
        uint8_t err_loc_prime = 1;
        for (auto coef : err_loc_prime_tmp) {
            err_loc_prime = gf_mul(err_loc_prime, coef);
        }

        auto rerr_evaluator = err_evaluator;
        std::reverse(rerr_evaluator.begin(), rerr_evaluator.end());
        uint8_t y = gf_poly_eval(rerr_evaluator, Xi_inv);
        y = gf_mul(gf_pow(Xi, 1), y);

        if (err_loc_prime == 0) {
            throw std::runtime_error(
                "Could not find err magnitude; err_loc_prime is 0");
        }

        uint8_t magnitude = gf_div(y, err_loc_prime);
        em_poly[err_pos[i]] = magnitude;
    }
    corrected = gf_poly_add(data, em_poly);
    return corrected;
}
