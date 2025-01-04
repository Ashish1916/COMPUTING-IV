// CopyRight [2024] Ashish Kosana
#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
    CelestialBody();
    CelestialBody(double x, double y, double vx, double vy, double mass,
                  const std::string& filename);

    void update(double dt);
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    double getMass() const;

    void setVelocity(const sf::Vector2f& newVelocity);
    void setPosition(const sf::Vector2f& newPosition);
    void applyForce(const sf::Vector2f& force, double dt);

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    double mass;
    sf::Texture texture;
    mutable sf::Sprite sprite;
    static constexpr float SCALE = 1e-9f;
    static constexpr double G = 6.67430e-11;
};

}  // namespace NB
