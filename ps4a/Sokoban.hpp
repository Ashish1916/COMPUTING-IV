// CopyRight [2024] Ashish Kosana
#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP
#include <vector>
#include <SFML/Graphics.hpp>
namespace SB {
enum class Direction { Up, Down, Left, Right };
class Sokoban : public sf::Drawable {
 public:
Sokoban();
int width() const;
int height() const;
sf::Vector2i playerLoc() const;
void movePlayer(Direction dir);
bool isWon() const;
void reset();
friend std::istream& operator>>(std::istream& is, Sokoban& sokoban);
friend std::ostream& operator<<(std::ostream& os, const Sokoban& sokoban);
 protected:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
int m_width;
int m_height;
std::vector<char> m_grid;
std::vector<char> m_initialGrid;  // Store the initial state of the grid
sf::Vector2i m_playerPos;
sf::Vector2i m_initialPlayerPos;  // Store the initial player position
sf::Texture m_textures[5];
sf::Sprite m_sprites[5];
void loadTextures();
};
}  // namespace SB
#endif  // SOKOBAN_HPP
