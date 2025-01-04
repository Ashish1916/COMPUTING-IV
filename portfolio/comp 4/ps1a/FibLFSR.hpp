// CopyRight [2024] <Ashish Kosana>
#pragma once
#include <iostream>
#include <string>
namespace PhotoMagic {
class FibLFSR {
 public:
explicit FibLFSR(std::string seed);
int step();
int generate(int k);
friend std::ostream& operator<<(std::ostream &out, const FibLFSR &lfsr);
 private:
std::string ss;
static const int tapPositions[3];
};
}  // namespace PhotoMagic
