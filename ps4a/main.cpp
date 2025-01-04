// CopyRight [2024] Ashish Kosana
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"
int main(int argc, char* argv[]) {
if (argc != 2) {
std::cerr << "Usage: " << argv[0] << " <level_file>" << std::endl;
return 1;
}
std::ifstream levelFile(argv[1]);
if (!levelFile) {
std::cerr << "Unable to open file: " << argv[1] << std::endl;
return 1;
}
SB::Sokoban game;
levelFile >> game;
sf::RenderWindow window(sf::VideoMode(game.width() * 64,
game.height() * 64), "ASHISH'S SOKOBAN");
sf::Font font;
if (!font.loadFromFile("arialn.ttf")) {
std::cerr << "Error loading font" << std::endl;
return 1;
}
sf::Text timerText("", font, 20);
timerText.setFillColor(sf::Color::White);
timerText.setPosition(10, 10);
sf::Clock clock;
while (window.isOpen()) {
sf::Event event;
while (window.pollEvent(event)) {
if (event.type == sf::Event::Closed) {
window.close();
}
if (event.type == sf::Event::KeyPressed) {
switch (event.key.code) {
case sf::Keyboard::Up:
game.movePlayer(SB::Direction::Up);
break;
case sf::Keyboard::Down:
game.movePlayer(SB::Direction::Down);
break;
case sf::Keyboard::Left:
game.movePlayer(SB::Direction::Left);
break;
case sf::Keyboard::Right:
game.movePlayer(SB::Direction::Right);
break;
default:
break;
}
}
}
window.clear();
window.draw(game);
int seconds = static_cast<int>(clock.getElapsedTime().asSeconds());
int minutes = seconds / 60;
seconds %= 60;
std::stringstream timeStream;
timeStream << std::setw(2) << std::setfill('0') << minutes
<< ":" << std::setw(2) << std::setfill('0') << seconds;
timerText.setString(timeStream.str());
window.draw(timerText);
window.display();
if (game.isWon()) {
std::cout << "Congratulations You won The Game!" << std::endl;
break;
}
}
return 0;
}
