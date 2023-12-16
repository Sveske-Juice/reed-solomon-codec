#include <iostream>

#include "gf.h"
#include "rs.h"

uint8_t nsym = 8;

int main(int argc, char** argv) {
    init_lookup_tables();

    std::vector<uint8_t> data = { 0x41, 0x42, 0x43, 0x44, 0x45};
    std::vector<uint8_t> encoded_msg = rs_encode(data, nsym);
    encoded_msg[0] = 'L';

    auto syndrome = rs_calc_syndrome(encoded_msg, nsym);

    std::vector<uint8_t> error_pos = {0};
    auto fixed = rs_correct_errata(encoded_msg, syndrome, error_pos);

    print_vec(fixed, false);

    return 0;
}
