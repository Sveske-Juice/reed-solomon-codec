#include <iostream>

#include "gf.h"
#include "rs.h"

int main(int argc, char** argv) {
    init_lookup_tables();

    std::vector<uint8_t> data = { 0x41, 0x42, 0x43, 0x44, 0x45};
    std::vector<uint8_t> encoded_msg = rs_encode(data, 8);

    for (auto byte : encoded_msg) {
        std::cout << byte << " ";
    }
    std::cout << std::endl;

    return 0;
}
