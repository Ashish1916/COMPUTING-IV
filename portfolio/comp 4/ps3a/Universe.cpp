// CopyRight [2024] Ashish Kosana
#include "Universe.hpp"
#include <fstream>
#include <iostream>

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
        body.update(dt);
    }
}

size_t Universe::size() const { return bodies.size(); }
double Universe::getRadius() const { return radius; }

const CelestialBody& Universe::operator[](size_t index) const {
    return bodies[index];
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& body : bodies) {
        target.draw(body, states);
    }
}

std::istream& operator>>(std::istream& is, Universe& universe) {
    size_t n;
    is >> n >> universe.radius;
    universe.bodies.resize(n);
    for (auto& body : universe.bodies) {
        is >> body;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.bodies.size() << " " << universe.radius << "\n";
    for (const auto& body : universe.bodies) {
        os << body << "\n";
    }
    return os;
}

}  // namespace NB
