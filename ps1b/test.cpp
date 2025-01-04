// CopyRight [2024] Ashish Kosana
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PhotoMagicTest
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;
using PhotoMagic::transform;

BOOST_AUTO_TEST_CASE(testInitialization) {
    FibLFSR l("1010101010101010");
    BOOST_REQUIRE_EQUAL(l.toString(), "1010101010101010");
}

BOOST_AUTO_TEST_CASE(testEmptySeed) {
    BOOST_CHECK_THROW(FibLFSR l(""), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testInvalidSeedCharacters) {
    BOOST_CHECK_THROW(FibLFSR l("1010A01010101010"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testImageTransform) {
    sf::Image image;
    if (!image.loadFromFile("input.png")) {
        BOOST_FAIL("Failed to load test image file 'input.png'");
    }

    sf::Image originalImage = image;

    // Initialize LFSR with a seed and transform the image (encrypt)
    FibLFSR lfsrEncrypt("1010101010101010");
    transform(image, &lfsrEncrypt);

    // Reinitialize LFSR with the same seed and transform the image again (decrypt)
    FibLFSR lfsrDecrypt("1010101010101010");
    transform(image, &lfsrDecrypt);

    // Verify if each pixel in the decrypted image matches the original
    sf::Vector2u size = image.getSize();
    for (unsigned int x = 0; x < size.x; ++x) {
        for (unsigned int y = 0; y < size.y; ++y) {
            BOOST_REQUIRE(image.getPixel(x, y) == originalImage.getPixel(x, y));
        }
    }
}
