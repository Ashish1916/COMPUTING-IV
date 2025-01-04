// Copyright [2024] <Ashish Kosana>
#include<iostream>
#include <SFML/Graphics.hpp>
int main() {
sf::RenderWindow window(sf::VideoMode(1000, 800),  "Ashish's Moving Sprite");
sf::RectangleShape rec(sf::Vector2f(100, 120));
rec.setFillColor(sf::Color::Red);
rec.setPosition(50.f, 55.f);
window.setFramerateLimit(60);
sf::Texture spriteTexture;
if (!spriteTexture.loadFromFile("Sprite.png")) {
std::cerr << "image loading failed!" << std::endl;
return -1;
}
sf::Sprite sprite;
sprite.setTexture(spriteTexture);
sprite.setScale(0.5f, 0.5f);
sf::Vector2u windowSize = window.getSize();
sf::FloatRect spriteBounds = sprite.getGlobalBounds();
float posX = (windowSize.x - spriteBounds.width) / 3.0f;
float posY = (windowSize.y - spriteBounds.height) / -20.0f;
sprite.setPosition(posX, posY);
sprite.setScale(0.2f, 0.2f);
float movementSpeed = 200.0f;
sf::Clock frameClock;
sf::Color backgroundColor = sf::Color::White;
while (window.isOpen()) {
sf::Event event;
while (window.pollEvent(event)) {
if(event.type == sf::Event::Closed) {
window.close();
}
}
sf::Time elapsedTime = frameClock.restart();
float deltaTime = elapsedTime.asSeconds();
backgroundColor = sf::Color::White;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
sprite.move(-movementSpeed * deltaTime, 0);
backgroundColor = sf::Color::Magenta;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
sprite.move(movementSpeed * deltaTime, 0);
backgroundColor = sf::Color::Green;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
sprite.move(0, -movementSpeed * deltaTime);
backgroundColor = sf::Color::Cyan;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
sprite.move(0, movementSpeed * deltaTime);
backgroundColor = sf::Color::Yellow;
}
window.clear(backgroundColor);
window.draw(sprite);
window.draw(rec);
window.display();
}
return 0;
}
