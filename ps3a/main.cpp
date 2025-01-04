// CopyRight [2024] Ashish Kosana
#include <iostream>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    NB::Universe universe;
    std::cin >> universe;

    sf::RenderWindow window(sf::VideoMode(800, 800), "ASHISH'S SOLAR SYSTEM");

    // Calculate the view size based on the universe radius
    float viewSize = static_cast<float>(universe.getRadius() * 2.5e-9);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(viewSize, viewSize));
    window.setView(view);

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("starfield.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
        return 1;
    }
    sf::Sprite background(backgroundTexture);

    // Load and play music
    sf::Music music;
    if (!music.openFromFile("2001.wav")) {
        std::cerr << "Failed to load music file" << std::endl;
        return 1;
    }
    music.setLoop(true);
    music.play();

    std::cout << "Music started playing." << std::endl;

    // Scale background to fit the view
    background.setScale(
        viewSize / backgroundTexture.getSize().x,
        viewSize / backgroundTexture.getSize().y);
    background.setPosition(-viewSize/2, -viewSize/2);

    sf::Clock clock;
    bool firstDraw = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                if (music.getStatus() == sf::Music::Playing) {
                    music.pause();
                    std::cout << "Music paused" << std::endl;
                } else {
                    music.play();
                    std::cout << "Music resumed" << std::endl;
                }
            }
        }

        double dt = clock.restart().asSeconds();
        universe.update(dt);

        window.clear();
        window.draw(background);
        window.draw(universe);

        if (firstDraw) {
            std::cout << "Drawing universe for the first time" << std::endl;
            firstDraw = false;
        }

        window.display();
    }

    std::cout << universe;

    return 0;
}
