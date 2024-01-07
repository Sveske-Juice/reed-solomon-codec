#include <cstring>
#include <iostream>
#include <unistd.h>

#include "gf.h"
#include "rs.h"


int main(int argc, char** argv) {
    init_lookup_tables();

    if (argc < 2) {
        std::cerr << "To few arguments provided" << std::endl;
        std::cout << "Usage: ./rsc <-e|-d> <count_of_redundancy_bits>" << std::endl;
        return 1;
    }

    else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 2) { std::cerr << "Count of redundancy bits is required" << std::endl; return 2; }

        // Get input from stdin (date to encode)
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(std::cin), {});
        size_t size = buffer.size();

        uint8_t nsym = std::stoi(argv[2], 0, 10);
        auto encoded_msg = rs_encode(buffer, nsym);
        write(STDOUT_FILENO, encoded_msg.data(), encoded_msg.size());
    }
    else if (strcmp(argv[1], "-d") == 0) {
        if (argc == 2) { std::cerr << "A redundancy bit count is required" << std::endl; return 3; }

        // Get input from stdin (data to decode)
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(std::cin), {});
        size_t size = buffer.size();

        uint8_t nsym = std::stoi(argv[2], 0, 10);

        int erasure_pos_count = argc - 3;
        std::vector<uint8_t> erasure_positions;
        erasure_positions.reserve(erasure_pos_count);
        for (int i = 0; i < erasure_pos_count; i++) {
            erasure_positions.push_back(std::stoi(argv[3 + i], 0, 10));
        }

        // std::cout << "err_pos: ";
        // print_vec(erasure_positions);

        auto syndrome = rs_calc_syndrome(buffer, nsym);

        // std::cout << "syndrom: ";
        // print_vec(syndrome);

        auto corrected = rs_correct_errata(buffer, syndrome, erasure_positions);
        write(STDOUT_FILENO, corrected.data(), corrected.size());
    }

    return 0;
}
