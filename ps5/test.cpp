// Copyright Ashish Kosana [2024]
#include <stdexcept>
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/included/unit_test.hpp>
#include "EDistance.hpp"

BOOST_AUTO_TEST_CASE(penalty_test) {
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'A'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'T'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('G', 'G'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('C', 'A'), 1);
}

BOOST_AUTO_TEST_CASE(min3_test) {
    BOOST_CHECK_EQUAL(EDistance::min3(1, 2, 3), 1);
    BOOST_CHECK_EQUAL(EDistance::min3(3, 2, 1), 1);
    BOOST_CHECK_EQUAL(EDistance::min3(3, 3, 3), 3);
    BOOST_CHECK_EQUAL(EDistance::min3(-1, 0, 1), -1);
}

BOOST_AUTO_TEST_CASE(opt_distance_test) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    BOOST_CHECK_EQUAL(ed.optDistance(), 7);

    EDistance ed2("ACGT", "ACGT");
    BOOST_CHECK_EQUAL(ed2.optDistance(), 0);
}

BOOST_AUTO_TEST_CASE(alignment_test) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    int distance = ed.optDistance();
    BOOST_CHECK_EQUAL(distance, 7);

    std::string result = ed.alignment();
    BOOST_CHECK(!result.empty());
}

BOOST_AUTO_TEST_CASE(exception_handling_test) {
    BOOST_REQUIRE_THROW(EDistance("", "TACG"), std::invalid_argument);
    BOOST_REQUIRE_THROW(EDistance("ACGT", ""), std::invalid_argument);

    BOOST_REQUIRE_NO_THROW(EDistance("ACGT", "TACG"));
    BOOST_REQUIRE_NO_THROW(EDistance("A", "G"));
}

BOOST_AUTO_TEST_CASE(complex_alignment_test) {
    EDistance ed("ACGTACGT", "TACG");
    int distance = ed.optDistance();
    BOOST_CHECK_EQUAL(distance, 8);

    std::string result = ed.alignment();
    BOOST_CHECK(!result.empty());
    BOOST_CHECK(result.find("2\n") != std::string::npos);
}
