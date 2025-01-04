// CopyRight 2024 Ashish kosana
#ifndef PHOTOMAGIC_HPP
#define PHOTOMAGIC_HPP

#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

namespace PhotoMagic {
void transform(sf::Image &image, FibLFSR *lfsr);
}

#endif  // PHOTOMAGIC_HPP
