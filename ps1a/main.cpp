// Copyright 2024 <Ashish Kosana>

#include <iostream>
#include "FibLFSR.hpp"

using PhotoMagic::FibLFSR;

int main() {
    FibLFSR lfsr("1011011000110110");

    std::cout << "Initial state: " << lfsr << std::endl;

    // Perform some steps
    for (int i = 0; i < 5; ++i) {
        std::cout << "Step " << (i + 1) << ": " << lfsr.step() << ", State: " << lfsr << std::endl;
    }

    std::cout << "Generate 5 bits: " << lfsr.generate(5) << std::endl;

    return 0;
}