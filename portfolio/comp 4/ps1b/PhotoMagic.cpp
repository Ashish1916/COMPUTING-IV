#include "PhotoMagic.hpp"
#include <stdexcept>
#include <bitset>
#include <cctype>
#include <algorithm>

namespace PhotoMagic {

void transform(sf::Image& image, FibLFSR& lfsr) {  
    sf::Vector2u size = image.getSize();
    
    for (unsigned int x = 0; x < size.x; ++x) {
        for (unsigned int y = 0; y < size.y; ++y) {
            sf::Color pixel = image.getPixel(x, y);
            pixel.r ^= lfsr.generate(8);
            pixel.g ^= lfsr.generate(8);
            pixel.b ^= lfsr.generate(8);
            image.setPixel(x, y, pixel);
        }
    }
}

std::string validateSeed(const std::string& input) {
    if (input.length() != 16) {
        throw std::invalid_argument("Seed must be exactly 16 bits long.");
    }
    
    for (char c : input) {
        if (c != '0' && c != '1') {
            throw std::invalid_argument("Seed must contain only '0's and '1's.");
        }
    }
    
    return input;
}

std::string passwordToSeed(const std::string& password) {
   if (password.length() == 16 && password.find_first_not_of("01") == std::string::npos) {
       return password; // Directly return if it's a valid binary string.
   }

   std::string seed;
   for (char c : password) {
       if (std::isalnum(c)) {
           int value = std::isalpha(c) ? (std::toupper(c) - 'A') : (c - '0' + 26);
           seed += std::bitset<6>(value).to_string();
       }
   }

   if (seed.length() < 16) {
       seed.append(16 - seed.length(), '0');
   } else if (seed.length() > 16) {
       seed = seed.substr(0, 16);
   }

   return seed;
}

}  // namespace PhotoMagic