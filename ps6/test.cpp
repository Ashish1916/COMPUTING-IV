// Copyright [2024] Ashish Kosana

#define BOOST_TEST_MODULE RandWriterTests
#define BOOST_TEST_DYN_LINK
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(TestConstructor) {
    // Test valid construction
    BOOST_REQUIRE_NO_THROW(RandWriter("abcde", 2));
    BOOST_REQUIRE_NO_THROW(RandWriter("abc", 0));

    // Test invalid construction
    BOOST_REQUIRE_THROW(RandWriter("", 2), std::invalid_argument);
    BOOST_REQUIRE_THROW(RandWriter("abc", 4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestOrderK) {
    RandWriter rw("abcde", 2);
    BOOST_REQUIRE_EQUAL(rw.orderK(), 2);
}

BOOST_AUTO_TEST_CASE(TestFreq) {
    RandWriter rw("abcabcabc", 2);
    BOOST_REQUIRE_EQUAL(rw.freq("ab"), 3);
    BOOST_REQUIRE_EQUAL(rw.freq("bc"), 3);
    BOOST_REQUIRE_EQUAL(rw.freq("ca"), 3);
    BOOST_REQUIRE_EQUAL(rw.freq("ab", 'c'), 3);
    BOOST_REQUIRE_THROW(rw.freq("a"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.freq("abc"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestKRand) {
    RandWriter rw("abcabcabc", 2);
    BOOST_REQUIRE_NO_THROW(rw.kRand("ab"));
    BOOST_REQUIRE_THROW(rw.kRand("xy"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.kRand("a"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestGenerate) {
    RandWriter rw("abcabcabc", 2);
    std::string generated = rw.generate("ab", 10);
    BOOST_REQUIRE_EQUAL(generated.length(), 10);
    BOOST_REQUIRE_EQUAL(generated.substr(0, 2), "ab");
    BOOST_REQUIRE_THROW(rw.generate("ab", 1), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.generate("a", 5), std::invalid_argument);
}
