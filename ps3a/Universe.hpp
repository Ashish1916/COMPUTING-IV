// CopyRight [2024] Ashish Kosana
#pragma once

#include <vector>

#include "CelestialBody.hpp"
#include <SFML/Graphics/Drawable.hpp>

namespace NB {

class Universe : public sf::Drawable {
 public:
    Universe();
    explicit Universe(const std::string& filename);

    void update(double dt);
    size_t size() const;
    double getRadius() const;
    const CelestialBody& operator[](size_t index) const;

    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::vector<CelestialBody> bodies;
    double radius;
};

}  // namespace NB
