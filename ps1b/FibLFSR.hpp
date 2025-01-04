// CopyRight 2024 Ashish kosana
#ifndef FIBLFSR_HPP
#define FIBLFSR_HPP

#include <string>
#include <iostream>

namespace PhotoMagic {

class FibLFSR {
 public:
explicit FibLFSR(std::string seed);
    int step();
    int generate(int k);
    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr);
    friend std::istream& operator>>(std::istream& is, FibLFSR& lfsr);

 private:
    std::string register_state;
};

}  // namespace PhotoMagic

#endif  // FIBLFSR_HPP
