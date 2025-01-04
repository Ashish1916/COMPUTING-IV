#include "FibLFSR.hpp"
#include <functional>
#include <stdexcept>

namespace PhotoMagic {

FibLFSR::FibLFSR(const std::string& seed) : reg_(seed) {
    if (reg_.length() != 16) {
        throw std::invalid_argument("Seed must be exactly 16 bits long.");
    }
    for (char c : reg_) {
        if (c != '0' && c != '1') {
            throw std::invalid_argument("Seed must contain only '0's and '1's.");
        }
    }
}

int FibLFSR::step() {
    int newBit = (reg_[0] - '0') ^ (reg_[2] - '0') ^ (reg_[3] - '0') ^ (reg_[5] - '0');
    reg_ = reg_.substr(1) + std::to_string(newBit);
    return newBit;
}

int FibLFSR::generate(int k) {
    int result = 0;
    for (int i = 0; i < k; ++i) {
        result = (result << 1) | step();
    }
    return result;
}

std::string FibLFSR::toString() const {
    return reg_;  // Return the current state of the register
}

std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr) {
    out << lfsr.reg_;
    return out;
}

std::string FibLFSR::convertPasswordToSeed(const std::string& password, size_t seedLength) {
    std::hash<std::string> hasher;
    size_t hash = hasher(password);

    std::string seed;
    for (size_t i = 0; i < seedLength; ++i) {
        seed += ((hash >> i) & 1) ? '1' : '0';
    }

    return seed;
}

}  // namespace PhotoMagic
