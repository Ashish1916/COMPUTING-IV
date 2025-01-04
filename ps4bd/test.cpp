#define BOOST_TEST_MODULE SokobanTest
#include <boost/test/included/unit_test.hpp>
#include "Sokoban.hpp"

BOOST_AUTO_TEST_CASE(TestResetAndWinCondition) {
    SB::Sokoban game("test_level.sok");
    game.reset();

    BOOST_CHECK(!game.isWon());

    // Simulate moves and check game conditions accordingly
    BOOST_CHECK(game.isWon());
}
