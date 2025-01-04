// copyright [2024] Ashish Kosana
#include <iostream>
#include <SFML/Graphics.hpp>
#include "penta.hpp"
int main(int argc, char* argv[]) {
if (argc != 3) {
std::cerr << "Usage: " << argv[0] <<
" <side_length> <recursion_depth>" << std::endl;
return 1;
}
double L = std::stod(argv[1]);
int N = std::stoi(argv[2]);
sf::RenderWindow window(sf::VideoMode(800, 800), "Pentaflake");
window.setFramerateLimit(60);
Pentaflake pentaflake(L, N);
while (window.isOpen()) {
sf::Event event;
while (window.pollEvent(event)) {
if (event.type == sf::Event::Closed)
window.close();
}
window.clear(sf::Color::Cyan);
window.draw(pentaflake);
window.display();
}
return 0;
}
