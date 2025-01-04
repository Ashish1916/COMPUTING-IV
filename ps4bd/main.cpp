#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>" << std::endl;
        return 1;
    }

    SB::Sokoban game(argv[1]);
    sf::RenderWindow window(sf::VideoMode(game.pixelWidth(), game.pixelHeight()), "Sokoban");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arialn.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    bool gameWon = false;
    sf::Clock clock;
    int moveCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && !gameWon) {
                // Implement player movement based on key press
            }
            if (gameWon && event.key.code == sf::Keyboard::R) {
                game.reset();
                clock.restart();
                moveCount = 0;
                gameWon = false;
            }
        }

        window.clear();
        window.draw(game);

        if (game.isWon() && !gameWon) {
            gameWon = true;
            game.playVictorySound();
        }

        window.display();
    }

    return 0;
}
