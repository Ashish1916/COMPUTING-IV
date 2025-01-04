// CopyRight 2024 Ashish kosana
#include <stdexcept>
#include "FibLFSR.hpp"

namespace PhotoMagic {

FibLFSR::FibLFSR(std::string seed) : register_state(seed) {
    if (seed.empty() || seed.find_first_not_of("01") != std::string::npos) {
        throw std::invalid_argument("Seed must be a non-empty binary string");
    }
}

int FibLFSR::step() {
    int new_bit = (register_state[0] - '0') ^ (register_state[2] - '0') ^
                  (register_state[3] - '0') ^ (register_state[5] - '0');
    register_state = register_state.substr(1) + std::to_string(new_bit);
    return new_bit;
}

int FibLFSR::generate(int k) {
    int result = 0;
    for (int i = 0; i < k; ++i) {
        result = (result << 1) | step();
    }
    return result;
}

std::string FibLFSR::toString() const {
    return register_state;
}

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    return os << lfsr.toString();
}

std::istream& operator>>(std::istream& is, FibLFSR& lfsr) {
    std::string seed;
    is >> seed;
    lfsr = FibLFSR(seed);
    return is;
}

}  // namespace PhotoMagic
