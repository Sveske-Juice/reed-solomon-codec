#include <catch2/catch_test_macros.hpp>

#include "gf.h"

TEST_CASE("Galois Field Addition", "[Add][GF(2^8)]") {
    REQUIRE(gf_add(0, 0) == 0);
    REQUIRE(gf_add(0xFF, 0xFF) == 0);
    REQUIRE(gf_add(~0, 0) == 0xFF);
    REQUIRE(gf_add(0b10101010, 0b01010101) == 0xFF);
    REQUIRE(gf_add(0xF, 0xF) == 0);
}

// Subtraction is the same as addition GF(2^8) (XOR)
TEST_CASE("Galois Field Subtraction", "[Sub][GF(2^8)]") {
    REQUIRE(gf_sub(0, 0) == 0);
    REQUIRE(gf_sub(0xFF, 0xFF) == 0);
    REQUIRE(gf_sub(~0, 0) == 0xFF);
    REQUIRE(gf_sub(0b10101010, 0b01010101) == 0xFF);
    REQUIRE(gf_sub(0xF, 0xF) == 0);
}

TEST_CASE("Galois Field Multiplication", "[Mul][GF(2^8)]") {
    init_lookup_tables();

    REQUIRE(gf_mul(0, 0) == 0);

    REQUIRE(gf_mul(0b10001001, 0b00101010) == 0b11000011);
    // TODO: more tests
}

TEST_CASE("Galois Field Divition", "[Div][GF(2^8)]") {
    init_lookup_tables();

    REQUIRE(gf_div(0, ~0) == 0);
    // TODO: more tests
}

// TODO: gf_pow & gf_inverse
