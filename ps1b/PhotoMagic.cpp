// CopyRight 2024 Ashish kosana
#include "PhotoMagic.hpp"
namespace PhotoMagic {
void transform(sf::Image& image, FibLFSR* lfsr) {
        sf::Vector2u size = image.getSize();
        for (unsigned int y = 0; y < size.y; ++y) {
            for (unsigned int x = 0; x < size.x; ++x) {
                sf::Color pixel = image.getPixel(x, y);
                uint8_t r = pixel.r ^ lfsr->generate(8);
                uint8_t g = pixel.g ^ lfsr->generate(8);
                uint8_t b = pixel.b ^ lfsr->generate(8);
                image.setPixel(x, y, sf::Color(r, g, b, pixel.a));
}
}
}
}  // namespace PhotoMagic
