
// Copyright [2024] Ashish Kosana
#include "Sokoban.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

// Explicit instantiation for int
template std::ostream& operator<<(std::ostream&, const sf::Vector2<int>&);

namespace SB {

Sokoban::Sokoban() : m_width(0), m_height(0), m_lastDirection(Direction::Down) {
    loadTextures();
}

Sokoban::Sokoban(const std::string& filename) : m_width(0), m_height(0),
m_lastDirection(Direction::Down) {
    loadTextures();
    loadFromFile(filename);
}

void Sokoban::loadTextures() {
    const std::string textureFiles[] = {
        "ground_01.png", "block_06.png", "crate_03.png", "ground_04.png",
        "player_05.png", "player_20.png", "player_17.png", "player_08.png"
    };

    for (int i = 0; i < 8; ++i) {
        if (!m_textures[i].loadFromFile(textureFiles[i])) {
            std::cerr << "Failed to load " << textureFiles[i] << std::endl;
        }
        m_sprites[i].setTexture(m_textures[i]);
    }
}

int Sokoban::width() const { return m_width; }
int Sokoban::height() const { return m_height; }
sf::Vector2i Sokoban::playerLoc() const { return m_playerPos; }

void Sokoban::movePlayer(Direction dir) {
    sf::Vector2i newPos = m_playerPos;
    switch (dir) {
        case Direction::Up: newPos.y--; break;
        case Direction::Down: newPos.y++; break;
        case Direction::Left: newPos.x--; break;
        case Direction::Right: newPos.x++; break;
    }

    m_lastDirection = dir;
    updatePlayerSprite();

    if (newPos.x >= 0 && newPos.x < m_width &&
        newPos.y >= 0 && newPos.y < m_height) {
        char &targetCell = m_grid[newPos.y * m_width + newPos.x];
        Move move{m_playerPos, newPos, {-1, -1}, {-1, -1}, false};

        if (targetCell == '.' || targetCell == 'a' || targetCell == 'b') {
            std::swap(m_grid[m_playerPos.y * m_width + m_playerPos.x], targetCell);
            m_playerPos = newPos;
            m_moveHistory.push(move);
        } else if (targetCell == 'A' || targetCell == 'B' ||
                   targetCell == '1' || targetCell == '2') {
            sf::Vector2i boxNewPos = newPos + (newPos - m_playerPos);
            if (boxNewPos.x >= 0 && boxNewPos.x < m_width &&
                boxNewPos.y >= 0 && boxNewPos.y < m_height) {
                char &boxTargetCell = m_grid[boxNewPos.y * m_width + boxNewPos.x];
                if (boxTargetCell == '.' || boxTargetCell == 'a' ||
                    boxTargetCell == 'b') {
                    move.isBoxMove = true;
                    move.boxOldPos = newPos;
                    move.boxNewPos = boxNewPos;

                    if (targetCell == 'A' || targetCell == '1') {
                        boxTargetCell = (boxTargetCell == '.') ? 'A' :
                            (boxTargetCell == 'a' ? '1' : 'A');
                    } else {  // 'B' or '2'
                        boxTargetCell = (boxTargetCell == '.') ? 'B' :
                            (boxTargetCell == 'b' ? '2' : 'B');
                    }

                    targetCell = (targetCell == 'A' || targetCell == 'B') ? '.' :
                        (targetCell == '1' ? 'a' : 'b');
                    m_grid[m_playerPos.y * m_width + m_playerPos.x] =
                        (m_grid[m_playerPos.y * m_width + m_playerPos.x] == '@') ?
                        '.' : (m_grid[m_playerPos.y * m_width + m_playerPos.x] == '!' ?
                        'a' : 'b');
                    m_playerPos = newPos;
                    m_grid[m_playerPos.y * m_width + m_playerPos.x] = '@';
                    m_moveHistory.push(move);
                }
            }
        }
    }

    if (isWon()) {
        // Victory condition reached, perform relevant action
    }
}

bool Sokoban::isWon() const {
    return std::none_of(m_grid.begin(), m_grid.end(), [](char c) {
        return c == 'A' || c == 'B'; });
}

void Sokoban::updatePlayerSprite() {
    switch (m_lastDirection) {
        case Direction::Up:
            m_sprites[4] = sf::Sprite(m_textures[7]);  // Up sprite
            break;
        case Direction::Down:
            m_sprites[4] = sf::Sprite(m_textures[4]);  // Down sprite
            break;
        case Direction::Left:
            m_sprites[4] = sf::Sprite(m_textures[5]);  // Left sprite
            break;
        case Direction::Right:
            m_sprites[4] = sf::Sprite(m_textures[6]);  // Right sprite
            break;
    }
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            char cell = m_grid[y * m_width + x];
            sf::Sprite sprite = m_sprites[0];  // Background sprite
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(sprite, states);

            switch (cell) {
                case '#': sprite = m_sprites[1]; break;
                case 'A': sprite = m_sprites[2]; break;
                case 'B': sprite = m_sprites[7]; break;
                case 'a':
                case 'b': sprite = m_sprites[3]; break;
                case '@':
                    sprite = m_sprites[4];  // Player sprite based on direction
                    break;
                default: continue;  // Skip drawing for empty spaces
            }
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(sprite, states);
        }
    }
}

void Sokoban::reset() {
    m_grid = m_initialGrid;
    m_playerPos = m_initialPlayerPos;
    m_moveHistory = std::stack<Move>();
}

int Sokoban::pixelWidth() const { return m_width * TILE_SIZE; }
int Sokoban::pixelHeight() const { return m_height * TILE_SIZE; }

void Sokoban::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        file >> *this;
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

void Sokoban::undo() {
    if (!m_moveHistory.empty()) {
        Move lastMove = m_moveHistory.top();
        m_moveHistory.pop();

        // Undo player move
        char &oldCell = m_grid[lastMove.playerOldPos.y *
            m_width + lastMove.playerOldPos.x];
        char &newCell = m_grid[lastMove.playerNewPos.y *
            m_width + lastMove.playerNewPos.x];

        newCell = (newCell == '@') ? '.' : (newCell == '!') ? 'a' : 'b';
        oldCell = '@';
        m_playerPos = lastMove.playerOldPos;

        // Undo box move if applicable
        if (lastMove.isBoxMove) {
            char &boxOldCell = m_grid[lastMove.boxOldPos.y *
                m_width + lastMove.boxOldPos.x];
            char &boxNewCell = m_grid[lastMove.boxNewPos.y *
                m_width + lastMove.boxNewPos.x];

            if (boxNewCell == 'A' || boxNewCell == '1') {
                boxOldCell = 'A';
                boxNewCell = (boxNewCell == 'A') ? '.' : 'a';
            } else if (boxNewCell == 'B' || boxNewCell == '2') {
                boxOldCell = 'B';
                boxNewCell = (boxNewCell == 'B') ? '.' : 'b';
            }
        }
    }
}

std::istream& operator>>(std::istream& is, Sokoban& sokoban) {
    is >> sokoban.m_height >> sokoban.m_width;
    sokoban.m_grid.resize(sokoban.m_height * sokoban.m_width);
    sokoban.m_initialGrid.resize(sokoban.m_height * sokoban.m_width);
    is.ignore();
    for (int y = 0; y < sokoban.m_height; ++y) {
        for (int x = 0; x < sokoban.m_width; ++x) {
            char cell;
            is.get(cell);
            sokoban.m_grid[y * sokoban.m_width + x] = cell;
            sokoban.m_initialGrid[y * sokoban.m_width + x] = cell;
            if (cell == '@') {
                sokoban.m_playerPos = sf::Vector2i(x, y);
                sokoban.m_initialPlayerPos = sf::Vector2i(x, y);
            }
        }
        is.ignore();
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Sokoban& sokoban) {
    os << sokoban.m_height << " " << sokoban.m_width << std::endl;
    for (int y = 0; y < sokoban.m_height; ++y) {
        for (int x = 0; x < sokoban.m_width; ++x) {
            os << sokoban.m_grid[y * sokoban.m_width + x];
        }
        os << std::endl;
    }
    return os;
}

}  // namespace SB
