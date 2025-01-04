// copyright [2024] Ashish Kosana
#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

class Pentaflake : public sf::Drawable {
 public:
    Pentaflake(double sideLength, int depth);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void createPentaflake(double sideLength, int depth, sf::Vector2f position, float rotation);

    std::vector<sf::ConvexShape> pentagons;
    const double PHI = (1 + std::sqrt(5)) / 2;
};
