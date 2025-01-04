// Copyright [2024] Ashish Kosana
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  // Include SFML Audio module
#include "Sokoban.hpp"

// Function to load best time from file
int loadBestTime(const std::string& levelName) {
    std::ifstream file(levelName + "_best_time.txt");
    int bestTime = -1;
    if (file >> bestTime) {
        return bestTime;
    }
    return -1;  // If no time is recorded, return -1
}

// Function to save best time to file
void saveBestTime(const std::string& levelName, int bestTime) {
    std::ofstream file(levelName + "_best_time.txt");
    file << bestTime;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>" << std::endl;
        return 1;
    }

    SB::Sokoban game(argv[1]);
    sf::RenderWindow window(sf::VideoMode(game.pixelWidth(),
    game.pixelHeight()), "ASHISH'S SOKOBAN");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arialn.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    // Load victory music
    sf::Music victoryMusic;
    if (!victoryMusic.openFromFile("victory.wav")) {
        std::cerr << "Error loading victory music" << std::endl;
        return 1;
    }

    // Timer and reset texts
    sf::Text timerText("", font, 20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10);

    // Move counter text
    sf::Text moveCounterText("Moves: 0", font, 20);
    moveCounterText.setFillColor(sf::Color::White);
    moveCounterText.setPosition(10, 40);

    // Best time display
    sf::Text bestTimeText("Best Time: --:--", font, 20);
    bestTimeText.setFillColor(sf::Color::Yellow);
    bestTimeText.setPosition(10, 70);

    // Load the best time from file
    int bestTime = loadBestTime(argv[1]);
    if (bestTime != -1) {
        int bestMinutes = bestTime / 60;
        int bestSeconds = bestTime % 60;
        std::stringstream bestTimeStream;
        bestTimeStream << "Best Time: " << std::setw(2) << std::setfill('0')
                       << bestMinutes << ":" << std::setw(2) << std::setfill('0')
                       << bestSeconds;
        bestTimeText.setString(bestTimeStream.str());
    }

    sf::Clock clock;
    int moveCount = 0;
    bool gameWon = false;
    bool musicPlayed = false;  // Flag to check if music has been played

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (!gameWon) {
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                        case sf::Keyboard::W:
                            game.movePlayer(SB::Direction::Up);
                            moveCount++;
                            break;
                        case sf::Keyboard::Down:
                        case sf::Keyboard::S:
                            game.movePlayer(SB::Direction::Down);
                            moveCount++;
                            break;
                        case sf::Keyboard::Left:
                        case sf::Keyboard::A:
                            game.movePlayer(SB::Direction::Left);
                            moveCount++;
                            break;
                        case sf::Keyboard::Right:
                        case sf::Keyboard::D:
                            game.movePlayer(SB::Direction::Right);
                            moveCount++;
                            break;
                        case sf::Keyboard::U:  // Undo move
                            game.undo();
                            if (moveCount > 0) moveCount--;
                            break;
                        case sf::Keyboard::R:  // Reset game
                            game.reset();
                            clock.restart();
                            moveCount = 0;
                            musicPlayed = false;  // Reset music played flag
                            victoryMusic.stop();  // Stop music if playing
                            break;
                        default:
                            break;
                    }
                }
                // Check for reset after winning
                if (gameWon && event.key.code == sf::Keyboard::R) {
                    game.reset();
                    clock.restart();
                    moveCount = 0;
                    gameWon = false;  // Reset gameWon status to allow playing again
                    musicPlayed = false;  // Reset music played flag
                    victoryMusic.stop();  // Stop music if playing
                }
            }
        }

        window.clear();
        window.draw(game);

        // Update timer display
        int seconds = static_cast<int>(clock.getElapsedTime().asSeconds());
        int minutes = seconds / 60;
        seconds %= 60;
        std::stringstream timeStream;
        timeStream << std::setw(2) << std::setfill('0') << minutes
                   << ":" << std::setw(2) << std::setfill('0') << seconds;
        timerText.setString(timeStream.str());
        window.draw(timerText);

        // Update move counter display
        std::stringstream moveStream;
        moveStream << "Moves: " << moveCount;
        moveCounterText.setString(moveStream.str());
        window.draw(moveCounterText);

        // Display best time
        window.draw(bestTimeText);

        // Check if the game is won and display the win message if true
        if (game.isWon()) {
            gameWon = true;
            sf::Text winText("Congratulations! You won!", font, 30);
            winText.setFillColor(sf::Color::Green);
            winText.setPosition(game.pixelWidth() / 2 - winText.getLocalBounds().width / 2,
                                game.pixelHeight() / 2 - winText.getLocalBounds().height / 2);
            window.draw(winText);

            // Play victory music if not already played
            if (!musicPlayed) {
                victoryMusic.play();
                musicPlayed = true;  // Set flag to indicate music has been played
            }

            // Calculate elapsed time and update best time if necessary
            int elapsedTime = static_cast<int>(clock.getElapsedTime().asSeconds());
            if (bestTime == -1 || elapsedTime < bestTime) {
                bestTime = elapsedTime;
                saveBestTime(argv[1], bestTime);
                bestTimeText.setString("Best Time: "
                + timeStream.str());  // Update best time display
            }
        }

        window.display();
    }

    return 0;
}
