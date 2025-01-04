// copyright [2024] Ashish Kosana
#include "penta.hpp"
#include <ctime>

Pentaflake::Pentaflake(double sideLength, int depth) {
    sf::Vector2f center(400, 400);
    createPentaflake(sideLength, depth, center, 0);
}

void Pentaflake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    static float rotationAngle = 0.0f;
    rotationAngle += 100.5f;  // Adjust this value to change rotation speed

    sf::Transform rotation;
    rotation.rotate(rotationAngle, 400, 400);  // Rotate around the center (400, 400)

    for (const auto& pentagon : pentagons) {
        sf::RenderStates rotatedStates = states;
        rotatedStates.transform *= rotation;
        target.draw(pentagon, rotatedStates);
    }
}

void Pentaflake::createPentaflake(double sideLength,
 int depth, sf::Vector2f position, float rotation) {
    if (depth < 0) return;

    sf::ConvexShape pentagon;
    pentagon.setPointCount(5);
    int r = static_cast<int>((position.x / 800.0) * 255);
    int g = static_cast<int>((position.y / 800.0) * 255);
    int b = static_cast<int>((depth / 5.0) * 255);
    sf::Color fillColor(r, g, b, 128);
    pentagon.setFillColor(fillColor);
    pentagon.setOutlineColor(sf::Color::Black);
    pentagon.setOutlineThickness(1);

    double angle = 2 * M_PI / 5;
    double radius = sideLength / (2 * std::sin(M_PI / 5));

    for (int i = 0; i < 5; ++i) {
        double x = radius * std::cos(i * angle - M_PI / 2 + rotation);
        double y = radius * std::sin(i * angle - M_PI / 2 + rotation);
        pentagon.setPoint(i, sf::Vector2f(x, y));
    }

    pentagon.setPosition(position);
    pentagons.push_back(pentagon);

    if (depth > 0) {
        double newSideLength = sideLength / (1 + PHI);
        double newRadius = newSideLength / (2 * std::sin(M_PI / 5));
        double offset = radius + newRadius;

        for (int i = 0; i < 5; ++i) {
            double x = offset * std::cos(i * angle - M_PI / 2 + rotation);
            double y = offset * std::sin(i * angle - M_PI / 2 + rotation);
            sf::Vector2f newPosition(position.x + x, position.y + y);
            createPentaflake(newSideLength, depth - 1, newPosition, rotation + i * angle);
        }

        createPentaflake(newSideLength, depth - 1, position, rotation + M_PI);
    }
}
