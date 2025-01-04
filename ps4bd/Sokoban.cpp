#include "Sokoban.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace SB {

Sokoban::Sokoban() : m_width(0), m_height(0), m_lastDirection(Direction::Down) {
    loadTextures();
    loadSounds();
}

void Sokoban::loadTextures() {
    const std::string textureFiles[] = {
        "ground.png", "block.png", "crate.png", "target.png",
        "player_down.png", "player_up.png", "player_left.png", "player_right.png"
    };

    for (int i = 0; i < 8; ++i) {
        if (!m_textures[i].loadFromFile(textureFiles[i])) {
            std::cerr << "Failed to load texture: " << textureFiles[i] << std::endl;
        }
        m_sprites[i].setTexture(m_textures[i]);
    }
}

void Sokoban::loadSounds() {
    if (!m_victorySoundBuffer.loadFromFile("victory.wav")) {
        std::cerr << "Error loading victory sound" << std::endl;
    } else {
        m_victorySound.setBuffer(m_victorySoundBuffer);
    }
}

void Sokoban::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file >> m_width >> m_height;
    m_grid.resize(m_width * m_height);
    m_initialGrid.resize(m_width * m_height);

    char tile;
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            file >> tile;
            m_grid[y * m_width + x] = tile;
            if (tile == 'P') m_playerPos = {x, y};
        }
    }

    m_initialGrid = m_grid;
    m_initialPlayerPos = m_playerPos;
}

bool Sokoban::isWon() const {
    return std::none_of(m_grid.begin(), m_grid.end(), [](char tile) {
        return tile == 'C';  // Assume 'C' represents an unfilled crate target
    });
}

void Sokoban::movePlayer(Direction dir) {
    // Movement logic implementation here, ensuring grid bounds and collision handling
}

void Sokoban::reset() {
    m_grid = m_initialGrid;
    m_playerPos = m_initialPlayerPos;
    m_moveHistory = std::stack<Move>();  // Clear move history
}

void Sokoban::undo() {
    if (!m_moveHistory.empty()) {
        Move lastMove = m_moveHistory.top();
        m_moveHistory.pop();

        // Restore positions
        m_playerPos = lastMove.playerOldPos;
        if (lastMove.isBoxMove) {
            m_grid[lastMove.boxNewPos.y * m_width + lastMove.boxNewPos.x] = ' ';
            m_grid[lastMove.boxOldPos.y * m_width + lastMove.boxOldPos.x] = 'C';
        }
    }
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Drawing logic for the game tiles, player, and other elements
}

}  // namespace SB
