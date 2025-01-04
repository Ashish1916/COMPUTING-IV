// CopyRight [2024] <Ashish Kosana>
#include "FibLFSR.hpp"
#include <stdexcept>
#include <bitset>
#include <array>

namespace PhotoMagic {
FibLFSR::FibLFSR(const std::string& seed) {
    taps_ = {0, 2, 3, 5};
    
    // Initialize the bits array
    for (size_t i = 0; i < 16; ++i) {
        bits_[i] = (seed[15 - i] == '1') ? 1 : 0; // Fill the array from the seed
    }
    
    // Check if all bits are zero
    if (std::all_of(std::begin(bits_), std::end(bits_), [](int bit) { return bit == 0; })) {
        throw std::invalid_argument("Seed must be non-zero.");
    }
}

unsigned int FibLFSR::step() {
    unsigned int feedback = 0;

    for (int tap : taps_) {
        feedback ^= bits_[tap];
    }

    // Shift the array left and insert feedback at the start
    for (int i = 15; i > 0; --i) {
        bits_[i] = bits_[i - 1];
    }
    bits_[0] = feedback;

    return feedback;
}

unsigned int FibLFSR::generate(int numBits) {
    unsigned int result = 0;
    
    for (int i = 0; i < numBits; ++i) {
        result = (result << 1) | step();
    }
    
    return result;
}
}  // namespace PhotoMagic
