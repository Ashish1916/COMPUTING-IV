#ifndef PHOTOMAGIC_HPP
#define PHOTOMAGIC_HPP

#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

namespace PhotoMagic {
void transform(sf::Image& image, FibLFSR& lfsr);  // Changed from FibLFSR* to FibLFSR&
std::string validateSeed(const std::string& input); // Add this declaration
std::string passwordToSeed(const std::string& password);
}  // namespace PhotoMagic

#endif  // PHOTOMAGIC_HPP