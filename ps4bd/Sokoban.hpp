#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <ostream>
#include <vector>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>

namespace SB {

enum class Direction { Up, Down, Left, Right };

struct Move {
    sf::Vector2i playerOldPos;
    sf::Vector2i playerNewPos;
    sf::Vector2i boxOldPos;
    sf::Vector2i boxNewPos;
    bool isBoxMove;
};

class Sokoban : public sf::Drawable {
 public:
    Sokoban();
    explicit Sokoban(const std::string& filename);

    int width() const;
    int height() const;
    sf::Vector2i playerLoc() const;
    void movePlayer(Direction dir);
    bool isWon() const;
    void reset();
    int pixelWidth() const;
    int pixelHeight() const;
    void undo();

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    static const int TILE_SIZE = 64;
    int m_width;
    int m_height;
    std::vector<char> m_grid;
    std::vector<char> m_initialGrid;
    sf::Vector2i m_playerPos;
    sf::Vector2i m_initialPlayerPos;
    sf::Texture m_textures[8];
    sf::Sprite m_sprites[8];
    Direction m_lastDirection;
    std::stack<Move> m_moveHistory;
    sf::SoundBuffer m_victorySoundBuffer;
    sf::Sound m_victorySound;

    void loadTextures();
    void loadSounds();
    void loadFromFile(const std::string& filename);
    void updatePlayerSprite();
};

}  // namespace SB

#endif  // SOKOBAN_HPP
