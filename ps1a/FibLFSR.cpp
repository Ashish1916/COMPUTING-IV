// Copyright 2024 <Ashish Kosana>

#include "FibLFSR.hpp"
#include <iostream>
#include <sstream>
#include <bitset>

namespace PhotoMagic {


const int FibLFSR::tapPositions[3] = {2, 3, 5};


FibLFSR::FibLFSR(std::string seed) : ss(seed) {}


int FibLFSR::step() {
    int newBit = (ss[0] - '0') ^
                 (ss[tapPositions[0]] - '0') ^
                 (ss[tapPositions[1]] - '0') ^
                 (ss[tapPositions[2]] - '0');

    ss = ss.substr(1) + std::to_string(newBit);


    return ss.back() - '0';
}


int FibLFSR::generate(int z) {
    int result = 0;
    for (int i = 0; i < z; ++i) {
        result = (result << 1) | step();
    }
    return result;
}


std::ostream& operator<<(std::ostream &out, const FibLFSR &lfsr) {
    out << lfsr.ss;
    return out;
}

}  // namespace PhotoMagic
