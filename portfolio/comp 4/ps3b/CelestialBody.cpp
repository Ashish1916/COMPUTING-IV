// CopyRight [2024] Ashish Kosana
#include "CelestialBody.hpp"
#include <iostream>

namespace NB {

CelestialBody::CelestialBody() : mass(0) {}

CelestialBody::CelestialBody(double x, double y, double vx, double vy, double m,
const std::string& filename)
: position(x, y), velocity(vx, vy), mass(m) {
if (!texture.loadFromFile(filename)) {
std::cerr << "Failed to load texture: " << filename << std::endl;
}
sprite.setTexture(texture);
sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
sprite.setPosition(position.x * SCALE, position.y * SCALE);
}

void CelestialBody::update(double dt) {
position += velocity * static_cast<float>(dt);
sprite.setPosition(position.x * SCALE, position.y * SCALE);
}

sf::Vector2f CelestialBody::getPosition() const {
return position;
}

sf::Vector2f CelestialBody::getVelocity() const {
return velocity;
}

double CelestialBody::getMass() const {
return mass;
}

void CelestialBody::setVelocity(const sf::Vector2f& newVelocity) {
velocity = newVelocity;
}

void CelestialBody::setPosition(const sf::Vector2f& newPosition) {
position = newPosition;
sprite.setPosition(position.x * SCALE, position.y * SCALE);
}

void CelestialBody::applyForce(const sf::Vector2f& force, double dt) {
sf::Vector2f acceleration = force / static_cast<float>(mass);
velocity += acceleration * static_cast<float>(dt);
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
target.draw(sprite, states);
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
std::string filename;
is >> body.position.x >> body.position.y >> body.velocity.x >> body.velocity.y
>> body.mass >> filename;
if (!body.texture.loadFromFile(filename)) {
std::cerr << "Failed to load texture: " << filename << std::endl;
}
body.sprite.setTexture(body.texture);
body.sprite.setOrigin(body.sprite.getLocalBounds().width / 2,
body.sprite.getLocalBounds().height / 2);
body.sprite.setPosition(body.position.x * body.SCALE, body.position.y * body.SCALE);
return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
os << body.position.x << " " << body.position.y << " "
<< body.velocity.x << " " << body.velocity.y << " "
<< body.mass << " " << "image.png";  // Assuming image filename
return os;
}

}  // namespace NB
