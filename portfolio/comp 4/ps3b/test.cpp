// CopyRight [2024] Ashish Kosana
#define BOOST_TEST_MODULE NBodyTests
#include <sstream>
#include <boost/test/included/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

const float EPSILON = 1e-6f;

BOOST_AUTO_TEST_CASE(CelestialBodyInputOutput) {
    std::stringstream ss("1.496e+11 0 0 29800 5.974e+24 earth.gif");
    NB::CelestialBody body;
    ss >> body;

    BOOST_CHECK_CLOSE(body.getPosition().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(body.getPosition().y, EPSILON);
    BOOST_CHECK_SMALL(body.getVelocity().x, EPSILON);
    BOOST_CHECK_CLOSE(body.getVelocity().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(body.getMass(), 5.974e+24f, EPSILON);

    std::stringstream out;
    out << body;
    BOOST_CHECK_EQUAL(out.str(), "1.496e+11 0 0 29800 5.974e+24 image.png");
}

BOOST_AUTO_TEST_CASE(UniverseInitialization) {
    NB::Universe universe;
    BOOST_CHECK_EQUAL(universe.size(), 0);
    BOOST_CHECK_SMALL(static_cast<float>(universe.getRadius()), EPSILON);
}

BOOST_AUTO_TEST_CASE(UniverseInputOutput) {
    std::stringstream ss("1 2.50e+11\n1.496e+11 0 0 29800 5.974e+24 mars.gif\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_EQUAL(universe.size(), 1);
    BOOST_CHECK_CLOSE(static_cast<float>(universe.getRadius()), 2.50e+11f, EPSILON);

    std::stringstream out;
    out << universe;
    BOOST_CHECK_EQUAL(out.str(), "1 2.5e+11\n1.496e+11 0 0 29800 5.974e+24 image.png\n");
}

BOOST_AUTO_TEST_CASE(UniverseAccessOperator) {
    std::stringstream ss("1 2.50e+11\n1.496e+11 0 0 29800 5.974e+24 mercury.gif\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_CLOSE(universe[0].getPosition().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(universe[0].getPosition().y, EPSILON);
    BOOST_CHECK_SMALL(universe[0].getVelocity().x, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].getVelocity().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].getMass(), 5.974e+24f, EPSILON);
}

BOOST_AUTO_TEST_CASE(UniverseSimulationStep) {
    std::stringstream ss("1 2.50e+11\n1.496e+11 0 0 29800 5.974e+24 sun.gif\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_CLOSE(universe[0].getPosition().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(universe[0].getPosition().y, EPSILON);

    universe.step(1.0);

    BOOST_CHECK_CLOSE(universe[0].getPosition().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].getPosition().y, 29800.0f, EPSILON);
}

BOOST_AUTO_TEST_CASE(UniverseMultipleBodies) {
    std::stringstream ss("3 2.50e+11\n"
                         "1.496e+11 0 0 29800 5.974e+24 saturn.gif\n"
                         "2.279e+11 0 0 24100 6.419e+23 pluto.gif\n"
                         "5.790e+10 0 0 47900 3.302e+23 uranus.gif\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_EQUAL(universe.size(), 3);
    BOOST_CHECK_CLOSE(static_cast<float>(universe.getRadius()), 2.50e+11f, EPSILON);

    // Check Earth
    BOOST_CHECK_CLOSE(universe[0].getPosition().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].getVelocity().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].getMass(), 5.974e+24f, EPSILON);

    // Check Mars
    BOOST_CHECK_CLOSE(universe[1].getPosition().x, 2.279e+11f, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].getVelocity().y, 24100.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].getMass(), 6.419e+23f, EPSILON);

    // Check Mercury
    BOOST_CHECK_CLOSE(universe[2].getPosition().x, 5.790e+10f, EPSILON);
    BOOST_CHECK_CLOSE(universe[2].getVelocity().y, 47900.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[2].getMass(), 3.302e+23f, EPSILON);

    universe.step(1.0);

    // Check updated positions
    BOOST_CHECK_CLOSE(universe[0].getPosition().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].getPosition().y, 24100.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[2].getPosition().y, 47900.0f, EPSILON);
}

// New test case for physics simulation
BOOST_AUTO_TEST_CASE(PhysicsSimulation) {
    std::stringstream ss("2 2.50e+11\n"
                         "0 0 0 0 1.989e+30 sun.gif\n"
                         "1.496e+11 0 0 29800 5.974e+24 earth.gif\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_EQUAL(universe.size(), 2);

    // Initial positions
    BOOST_CHECK_SMALL(universe[0].getPosition().x, EPSILON);
    BOOST_CHECK_SMALL(universe[0].getPosition().y, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].getPosition().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(universe[1].getPosition().y, EPSILON);

    // Simulate for 1 day
    double dt = 86400;  // 1 day in seconds
    universe.step(dt);

    // Check that the sun has not moved significantly
    BOOST_CHECK_SMALL(universe[0].getPosition().x, 1e5f);
    BOOST_CHECK_SMALL(universe[0].getPosition().y, 1e5f);

    // Check that the Earth has moved
    BOOST_CHECK_CLOSE(universe[1].getPosition().x, 1.496e+11f, 1.0f);
    BOOST_CHECK(std::abs(universe[1].getPosition().y) > 2.5e+9f);

    // Check that the Earth's velocity has changed slightly due to the sun's gravity
    BOOST_CHECK(universe[1].getVelocity().x < 0);
    BOOST_CHECK_CLOSE(universe[1].getVelocity().y, 29800.0f, 1.0f);
}
