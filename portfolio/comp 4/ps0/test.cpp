#define BOOST_TEST_MODULE NBodyTests
#include <boost/test/included/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <sstream>

const float EPSILON = 1e-6f;

BOOST_AUTO_TEST_CASE(CelestialBodyInputOutput)
{
    std::stringstream ss("1.496e+11 0 0 29800 5.974e+24 earth.png");
    NB::CelestialBody body;
    ss >> body;

    BOOST_CHECK_CLOSE(body.position().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(body.position().y, EPSILON);
    BOOST_CHECK_SMALL(body.velocity().x, EPSILON);
    BOOST_CHECK_CLOSE(body.velocity().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(body.mass(), 5.974e+24f, EPSILON);

    std::stringstream out;
    out << body;
    BOOST_CHECK_EQUAL(out.str(), "1.496e+11 0 0 29800 5.974e+24 earth.png");
}

BOOST_AUTO_TEST_CASE(UniverseInitialization)
{
    NB::Universe universe;
    BOOST_CHECK_EQUAL(universe.size(), 0);
    BOOST_CHECK_SMALL(static_cast<float>(universe.radius()), EPSILON);
}

BOOST_AUTO_TEST_CASE(UniverseInputOutput)
{
    std::stringstream ss("1 2.50e+11\n1.496e+11 0 0 29800 5.974e+24 mars.png\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_EQUAL(universe.size(), 1);
    BOOST_CHECK_CLOSE(static_cast<float>(universe.radius()), 2.50e+11f, EPSILON);

    std::stringstream out;
    out << universe;
    BOOST_CHECK_EQUAL(out.str(), "1 2.5e+11\n1.496e+11 0 0 29800 5.974e+24 mars.png\n");
}

BOOST_AUTO_TEST_CASE(UniverseAccessOperator)
{
    std::stringstream ss("1 2.50e+11\n1.496e+11 0 0 29800 5.974e+24 mercury.png\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_CLOSE(universe[0].position().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(universe[0].position().y, EPSILON);
    BOOST_CHECK_SMALL(universe[0].velocity().x, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].velocity().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].mass(), 5.974e+24f, EPSILON);
}

BOOST_AUTO_TEST_CASE(UniverseSimulationStep)
{
    std::stringstream ss("1 2.50e+11\n1.496e+11 0 0 29800 5.974e+24 sun.png\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_CLOSE(universe[0].position().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_SMALL(universe[0].position().y, EPSILON);

    universe.update(1.0);

    BOOST_CHECK_CLOSE(universe[0].position().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].position().y, 29800.0f, EPSILON);
}

BOOST_AUTO_TEST_CASE(UniverseMultipleBodies)
{
    std::stringstream ss("3 2.50e+11\n"
                         "1.496e+11 0 0 29800 5.974e+24 saturn.png\n"
                         "2.279e+11 0 0 24100 6.419e+23 pluto.png\n"
                         "5.790e+10 0 0 47900 3.302e+23 uranus.png\n");
    NB::Universe universe;
    ss >> universe;

    BOOST_CHECK_EQUAL(universe.size(), 3);
    BOOST_CHECK_CLOSE(static_cast<float>(universe.radius()), 2.50e+11f, EPSILON);

    // Check Earth
    BOOST_CHECK_CLOSE(universe[0].position().x, 1.496e+11f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].velocity().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[0].mass(), 5.974e+24f, EPSILON);

    // Check Mars
    BOOST_CHECK_CLOSE(universe[1].position().x, 2.279e+11f, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].velocity().y, 24100.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].mass(), 6.419e+23f, EPSILON);

    // Check Mercury
    BOOST_CHECK_CLOSE(universe[2].position().x, 5.790e+10f, EPSILON);
    BOOST_CHECK_CLOSE(universe[2].velocity().y, 47900.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[2].mass(), 3.302e+23f, EPSILON);

    universe.update(1.0);

    // Check updated positions
    BOOST_CHECK_CLOSE(universe[0].position().y, 29800.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[1].position().y, 24100.0f, EPSILON);
    BOOST_CHECK_CLOSE(universe[2].position().y, 47900.0f, EPSILON);
}