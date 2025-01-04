// CopyRight 2024 Ashish kosana
#include <iostream>
#include <bitset>
#include "PhotoMagic.hpp"
#include "FibLFSR.hpp"
#include <SFML/Graphics.hpp>

// Converts alphanumeric key to a binary seed
std::string convertKeyToBinary(const std::string &key) {
    std::string binarySeed;
    for (char c : key) {
        binarySeed += std::bitset<8>(c).to_string();
    }
    // Ensure the binary seed is exactly 16 bits long
    if (binarySeed.size() > 16) {
        binarySeed = binarySeed.substr(0, 16);
    } else if (binarySeed.size() < 16) {
        binarySeed.append(16 - binarySeed.size(), '0');
    }
    return binarySeed;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <input-file> <output-file> <LFSR-seed>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string seed = argv[3];

    // Convert the alphanumeric seed to binary
    std::string binarySeed = convertKeyToBinary(seed);

    sf::Image inputImage;
    if (!inputImage.loadFromFile(inputFile)) {
        std::cerr << "Failed to load input image." << std::endl;
        return 1;
    }

    PhotoMagic::FibLFSR lfsr(binarySeed);
    sf::Image outputImage = inputImage;
    PhotoMagic::transform(outputImage, &lfsr);

    if (!outputImage.saveToFile(outputFile)) {
        std::cerr << "Failed to save output image." << std::endl;
        return 1;
    }

    sf::Texture inputTexture, outputTexture;
    inputTexture.loadFromImage(inputImage);
    outputTexture.loadFromImage(outputImage);

    sf::Sprite inputSprite(inputTexture), outputSprite(outputTexture);

    sf::Vector2u size = inputImage.getSize();
    sf::RenderWindow inputWindow(sf::VideoMode(size.x, size.y), "Original Image");
    sf::RenderWindow outputWindow(sf::VideoMode(size.x, size.y), "Transformed Image");

    while (inputWindow.isOpen() && outputWindow.isOpen()) {
        sf::Event event;
        while (inputWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                inputWindow.close();
        }
        while (outputWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                outputWindow.close();
        }

        inputWindow.clear();
        inputWindow.draw(inputSprite);
        inputWindow.display();

        outputWindow.clear();
        outputWindow.draw(outputSprite);
        outputWindow.display();
    }
    return 0;
}
