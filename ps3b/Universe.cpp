// CopyRight [2024] Ashish Kosana
#include "Universe.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : radius(0) {}

Universe::Universe(const std::string& filename) {
std::ifstream file(filename);
if (file) {
file >> *this;
} else {
std::cerr << "Failed to open file: " << filename << std::endl;
}
}

void Universe::update(double dt) {
for (auto& body : bodies) {
body->update(dt);
}
}

void Universe::step(double seconds) {
for (auto& body : bodies) {
sf::Vector2f totalForce(0, 0);
for (const auto& otherBody : bodies) {
if (body.get() != otherBody.get()) {
totalForce += calculateForce(*body, *otherBody);
}
}
body->applyForce(totalForce, seconds);
}

for (auto& body : bodies) {
body->update(seconds);
}
}

size_t Universe::size() const { return bodies.size(); }
double Universe::getRadius() const { return radius; }

const CelestialBody& Universe::operator[](size_t index) const {
return *bodies[index];
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
for (const auto& body : bodies) {
target.draw(*body, states);
}
}

sf::Vector2f Universe::calculateForce(const CelestialBody& body1,
const CelestialBody& body2) const {
sf::Vector2f delta = body2.getPosition() - body1.getPosition();
double distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
double force = (6.67430e-11 * body1.getMass() * body2.getMass()) / (distance * distance);
return (delta / static_cast<float>(distance)) * static_cast<float>(force);
}

std::istream& operator>>(std::istream& is, Universe& universe) {
size_t n;
is >> n >> universe.radius;
universe.bodies.clear();
for (size_t i = 0; i < n; ++i) {
auto body = std::make_unique<CelestialBody>();
is >> *body;
universe.bodies.push_back(std::move(body));
}
return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
os << universe.bodies.size() << " " << universe.radius << "\n";
for (const auto& body : universe.bodies) {
os << *body << "\n";
}
return os;
}

}  // namespace NB
