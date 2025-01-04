// Copyright [2024] Ashish Kosana
#define BOOST_TEST_MODULE SokobanTest
#include <fstream>
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "Sokoban.hpp"

// Helper function to create and initialize a test level
void setup_test_level(SB::Sokoban& game, const std::string& level) {
    std::ofstream levelFile(level);
    levelFile << "5 5\n"
              << "#####\n"
              << "#.@.#\n"
              << "#.A.#\n"
              << "#.a.#\n"  // 'a' is the storage location
              << "#####\n";
    levelFile.close();
    game = SB::Sokoban(level);
}

// Updated simulateWin function with additional logging
bool simulateWin(SB::Sokoban& game) {
    game.movePlayer(SB::Direction::Down);  // Move player to box
    game.movePlayer(SB::Direction::Down);  // Push box onto storage
    return game.isWon();
}

BOOST_AUTO_TEST_CASE(test_basic_movement) {
    SB::Sokoban game;
    setup_test_level(game, "test_level_basic.lvl");

    sf::Vector2i initial_pos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.playerLoc().x, initial_pos.x + 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initial_pos.y);
}

BOOST_AUTO_TEST_CASE(test_wall_collision) {
    SB::Sokoban game;
    setup_test_level(game, "test_level_wall.lvl");

    sf::Vector2i initial_pos = game.playerLoc();
    game.movePlayer(SB::Direction::Up);  // Move towards wall
    BOOST_CHECK_EQUAL(game.playerLoc().x, initial_pos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initial_pos.y);
}

BOOST_AUTO_TEST_CASE(test_box_push) {
    SB::Sokoban game;
    setup_test_level(game, "test_level_push.lvl");

    BOOST_CHECK(simulateWin(game));  // Check if the game registers as won
}

BOOST_AUTO_TEST_CASE(test_box_blocked) {
    SB::Sokoban game;
    setup_test_level(game, "test_level_blocked.lvl");

    game.movePlayer(SB::Direction::Down);  // Move to box
    game.movePlayer(SB::Direction::Right);  // Attempt to push in blocked direction
    BOOST_CHECK_EQUAL(game.playerLoc().x, 3);  // Confirms that the push fails
}

BOOST_AUTO_TEST_CASE(test_win_condition) {
    SB::Sokoban game;
    setup_test_level(game, "test_level_win.lvl");

    BOOST_CHECK(simulateWin(game));  // Should return true if win is registered
}

BOOST_AUTO_TEST_CASE(test_reset) {
    SB::Sokoban game;
    setup_test_level(game, "test_level_reset.lvl");

    sf::Vector2i initial_pos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    game.reset();
    BOOST_CHECK_EQUAL(game.playerLoc().x, initial_pos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initial_pos.y);
}
