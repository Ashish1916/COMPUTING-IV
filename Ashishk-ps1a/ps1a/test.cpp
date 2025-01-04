// CopyRight [2024] <Ashish Kosana>
#include <string>
#include "FibLFSR.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
using PhotoMagic::FibLFSR;
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE(testStepInstr) {
FibLFSR l("1011011000110110");
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 1);
}
BOOST_AUTO_TEST_CASE(testGenerateInstr) {
FibLFSR l("1101011000111101");
BOOST_REQUIRE_EQUAL(l.generate(7), 124);
}
BOOST_AUTO_TEST_CASE(testStepInstr1) {
FibLFSR l("1101011000111101");
BOOST_REQUIRE_EQUAL(l.step(), 1);
BOOST_REQUIRE_EQUAL(l.step(), 1);
BOOST_REQUIRE_EQUAL(l.step(), 1);
BOOST_REQUIRE_EQUAL(l.step(), 1);
}
BOOST_AUTO_TEST_CASE(testGenerateInstr1) {
FibLFSR l("0011001100100111");
BOOST_REQUIRE_EQUAL(l.generate(7), 1);
}
BOOST_AUTO_TEST_CASE(testStepInstr2) {
FibLFSR l("0101010101010111");
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
}
BOOST_AUTO_TEST_CASE(testGenerateInstr2) {
FibLFSR l("1111000011110000");
BOOST_REQUIRE_EQUAL(l.generate(7), 85);
}
