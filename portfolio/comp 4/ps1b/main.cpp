#include <iostream>
#include <SFML/Graphics.hpp>
#include "PhotoMagic.hpp"

int processImage(const std::string& inFile, const std::string& outFile, const std::string& pass) {
   sf::Image img;

   if (!img.loadFromFile(inFile)) {
       std::cerr << "Error: Unable to load input image." << std::endl;
       return 1;
   }

   PhotoMagic::FibLFSR cipher(PhotoMagic::FibLFSR::convertPasswordToSeed(pass));
   PhotoMagic::transform(img, cipher); // Pass by reference

   if (!img.saveToFile(outFile)) {
       std::cerr << "Error: Failed to save output image." << std::endl;
       return 1;
   }

   return 0;
}

void displayImages(const std::string& inFile, const std::string& outFile) {
   sf::Texture inTex, outTex;

   if (!inTex.loadFromFile(inFile) || !outTex.loadFromFile(outFile)) {
       std::cerr << "Error: Unable to load textures." << std::endl;
       return;
   }

   sf::Sprite inSprite(inTex), outSprite(outTex);
   sf::Vector2u size = inTex.getSize();

   sf::RenderWindow inWindow(sf::VideoMode(size.x, size.y), "Input Image");
   sf::RenderWindow outWindow(sf::VideoMode(size.x, size.y), "Output Image");

   while (inWindow.isOpen() && outWindow.isOpen()) {
       sf::Event event;

       auto handleEvents = [&event](sf::RenderWindow& window) {
           while (window.pollEvent(event)) {
               if (event.type == sf::Event::Closed)
                   window.close();
           }
       };

       handleEvents(inWindow);
       handleEvents(outWindow);

       inWindow.clear();
       inWindow.draw(inSprite);
       inWindow.display();

       outWindow.clear();
       outWindow.draw(outSprite);
       outWindow.display();
   }
}

int main(int argc, char* argv[]) {
   if (argc != 4) {
       std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <password>" << std::endl;
       return 1;
   }

   std::string inFile = argv[1], outFile = argv[2], pass = argv[3];

   // Process the image with encryption
   if (int result = processImage(inFile, outFile, pass)) {
       return result;
   }

   // Display the original and transformed images
   displayImages(inFile, outFile);

   return 0;
}