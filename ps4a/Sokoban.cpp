// CopyRight [2024] Ashish Kosana
#include "Sokoban.hpp"
#include <iostream>
#include <algorithm>
namespace SB {
Sokoban::Sokoban() : m_width(0), m_height(0) {
loadTextures();
}
void Sokoban::loadTextures() {
if (!m_textures[0].loadFromFile("ground_01.png")) {
std::cerr << "Failed to load ground_01.png" << std::endl;
}
if (!m_textures[1].loadFromFile("block_06.png")) {
std::cerr << "Failed to load block_06.png" << std::endl;
}
if (!m_textures[2].loadFromFile("crate_03.png")) {
std::cerr << "Failed to load crate_03.png" << std::endl;
}
if (!m_textures[3].loadFromFile("ground_04.png")) {
std::cerr << "Failed to load ground_04.png" << std::endl;
}
if (!m_textures[4].loadFromFile("player_05.png")) {
std::cerr << "Failed to load player_05.png" << std::endl;
}
for (int i = 0; i < 5; ++i) {
m_sprites[i].setTexture(m_textures[i]);
}
}
int Sokoban::width() const {
return m_width;
}
int Sokoban::height() const {
return m_height;
}
sf::Vector2i Sokoban::playerLoc() const {
return m_playerPos;
}
void Sokoban::movePlayer(Direction dir) {
}
bool Sokoban::isWon() const {
for (char cell : m_grid) {
if (cell == 'A') {
return false;
}
}
return true;
}
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
for (int y = 0; y < m_height; ++y) {
for (int x = 0; x < m_width; ++x) {
char cell = m_grid[y * m_width + x];
sf::Sprite sprite;
sprite = m_sprites[0];
sprite.setPosition(x * 64, y * 64);
target.draw(sprite, states);
switch (cell) {
case '#': sprite = m_sprites[1]; break;
case 'A': sprite = m_sprites[2]; break;
case 'a': sprite = m_sprites[3]; break;
case '@': sprite = m_sprites[4]; break;
default: continue;
}
sprite.setPosition(x * 64, y * 64);
target.draw(sprite, states);
}
}
}
void Sokoban::reset() {
m_grid = m_initialGrid;
m_playerPos = m_initialPlayerPos;
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
