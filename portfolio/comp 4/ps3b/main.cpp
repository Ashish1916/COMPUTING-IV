// CopyRight [2024] Ashish Kosana
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Function to draw a digit using rectangles
void drawDigit(sf::RenderWindow& window, int digit, float x, float y, float size) {
    const bool segments[10][7] = {
        {1, 1, 1, 0, 1, 1, 1},  // 0
        {0, 0, 1, 0, 0, 1, 0},  // 1
        {1, 0, 1, 1, 1, 0, 1},  // 2
        {1, 0, 1, 1, 0, 1, 1},  // 3
        {0, 1, 1, 1, 0, 1, 0},  // 4
        {1, 1, 0, 1, 0, 1, 1},  // 5
        {1, 1, 0, 1, 1, 1, 1},  // 6
        {1, 0, 1, 0, 0, 1, 0},  // 7
        {1, 1, 1, 1, 1, 1, 1},  // 8
        {1, 1, 1, 1, 0, 1, 1}   // 9
    };

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

    // Draw the segments
    if (segments[digit][0]) {
        rect.setSize(sf::Vector2f(size, size/5));
        rect.setPosition(x, y);
        window.draw(rect);
    }
    if (segments[digit][1]) {
        rect.setSize(sf::Vector2f(size/5, size));
        rect.setPosition(x, y);
        window.draw(rect);
    }
    if (segments[digit][2]) {
        rect.setSize(sf::Vector2f(size/5, size));
        rect.setPosition(x+size-size/5, y);
        window.draw(rect);
    }
    if (segments[digit][3]) {
        rect.setSize(sf::Vector2f(size, size/5));
        rect.setPosition(x, y+size-size/5);
        window.draw(rect);
    }
    if (segments[digit][4]) {
        rect.setSize(sf::Vector2f(size/5, size));
        rect.setPosition(x, y+size);
        window.draw(rect);
    }
    if (segments[digit][5]) {
        rect.setSize(sf::Vector2f(size/5, size));
        rect.setPosition(x+size-size/5, y+size);
        window.draw(rect);
    }
    if (segments[digit][6]) {
        rect.setSize(sf::Vector2f(size, size/5));
        rect.setPosition(x, y+size*2-size/5);
        window.draw(rect);
    }
}

// Function to draw "sec" using rectangles
void drawSec(sf::RenderWindow& window, float x, float y, float size) {
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

    // Draw 's'
    rect.setSize(sf::Vector2f(size, size/5));
    rect.setPosition(x, y);
    window.draw(rect);
    rect.setPosition(x, y + size/2);
    window.draw(rect);
    rect.setPosition(x, y + size - size/5);
    window.draw(rect);
    rect.setSize(sf::Vector2f(size/5, size/2));
    rect.setPosition(x, y);
    window.draw(rect);
    rect.setPosition(x + size - size/5, y + size/2);
    window.draw(rect);

    // Draw 'e'
    x += size * 1.2;
    rect.setSize(sf::Vector2f(size, size/5));
    rect.setPosition(x, y);
    window.draw(rect);
    rect.setPosition(x, y + size/2);
    window.draw(rect);
    rect.setPosition(x, y + size - size/5);
    window.draw(rect);
    rect.setSize(sf::Vector2f(size/5, size/2 + size/5));
    rect.setPosition(x, y);
    window.draw(rect);
    rect.setSize(sf::Vector2f(size, size/5));
    rect.setPosition(x, y + size/2);
    window.draw(rect);

    // Draw 'c'
    x += size * 1.2;
    rect.setSize(sf::Vector2f(size, size/5));
    rect.setPosition(x, y);
    window.draw(rect);
    rect.setPosition(x, y + size - size/5);
    window.draw(rect);
    rect.setSize(sf::Vector2f(size/5, size));
    rect.setPosition(x, y);
    window.draw(rect);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <T> <dt>" << std::endl;
        return 1;
    }

    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    NB::Universe universe;
    std::cin >> universe;

    // Create render window
    sf::RenderWindow window(sf::VideoMode(800, 800), "ASHISH'S SOLAR SYSTEM");

    // Set vertical sync enabled (no return value check, since it's void)
    window.setVerticalSyncEnabled(true);

    double viewSize = universe.getRadius() * 2.5e-9;
    sf::View universeView(sf::Vector2f(0, 0), sf::Vector2f(static_cast<float>(viewSize),
                          static_cast<float>(viewSize)));
    sf::View defaultView = window.getDefaultView();

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

    // Scale and position the background
    background.setScale(
        static_cast<float>(viewSize) / backgroundTexture.getSize().x,
        static_cast<float>(viewSize) / backgroundTexture.getSize().y);
    background.setPosition(static_cast<float>(-viewSize/2), static_cast<float>(-viewSize/2));

    // Setup for displaying elapsed time using shapes
    sf::RectangleShape timeBox(sf::Vector2f(150, 50));
    timeBox.setFillColor(sf::Color(0, 0, 0, 128));
    timeBox.setPosition(defaultView.getSize().x - 160, 10);

    sf::Clock clock;
    double elapsedTime = 0.0;
    bool firstDraw = true;

    // Main window loop
    while (window.isOpen() && elapsedTime < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
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

        // Calculate frame time
        double frameTime = clock.restart().asSeconds();
        elapsedTime += frameTime;

        // Update universe state
        universe.step(dt);

        // Clear and draw everything
        window.clear();

        // Draw universe
        window.setView(universeView);
        window.draw(background);
        window.draw(universe);

        // Draw time
        window.setView(defaultView);
        window.draw(timeBox);

        // Display elapsed time in simulation
        int seconds = static_cast<int>(elapsedTime);
        int tens = seconds / 10;
        int ones = seconds % 10;

        drawDigit(window, tens, defaultView.getSize().x - 150, 15, 20);
        drawDigit(window, ones, defaultView.getSize().x - 120, 15, 20);

        // Draw "sec" for seconds
        drawSec(window, defaultView.getSize().x - 90, 15, 20);

        if (firstDraw) {
            std::cout << "Drawing universe for the first time" << std::endl;
            firstDraw = false;
        }

        // Display rendered frame
        window.display();
    }

    // Output universe state at the end
    std::cout << universe;

    return 0;
}
