#ifndef FIBLFSR_HPP
#define FIBLFSR_HPP

#include <string>
#include <iostream>

namespace PhotoMagic {

class FibLFSR {
public:
    explicit FibLFSR(const std::string& seed);
    int step();
    int generate(int k);
    std::string toString() const;  // Add toString method
    friend std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr);
    static std::string convertPasswordToSeed(const std::string& password, size_t seedLength = 16);

private:
    std::string reg_;
};

}  // namespace PhotoMagic

#endif  // FIBLFSR_HP