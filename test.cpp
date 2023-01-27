// Copyright [2021] Peter Nguyen
/*
Name: Peter Nguyen
Assignment: ps6
Instructor: Dr. Yelena Rykalova
Due: 11/29/21
Last Updated: 11/29/21
test.cpp: BOOST test file that holds unit tests for
          RandWriter. Tests each function
          for correct functionality and tests for
          exceptions to be thrown correctly.
*/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE_NO_MAIN
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "RandWriter.h"
using boost::test_tools::output_test_stream;

// Test RandWriter(string, int)
BOOST_AUTO_TEST_CASE(constructor) {
    RandWriter a("gagggagaggcgagaaa", 3);
    BOOST_REQUIRE(a.order_k() == 3);
    BOOST_REQUIRE(a.freq("gag") == 4);
}

// Test order_k
BOOST_AUTO_TEST_CASE(orderk) {
    RandWriter b("gagggagaggcgagaaa", 4);
    BOOST_REQUIRE(b.order_k() == 4);
}

// Test freq(string)
BOOST_AUTO_TEST_CASE(kgramFreq) {
    RandWriter c("gagggagaggcgagaaa", 3);
    // Exception when string is not of order k
    BOOST_REQUIRE_THROW(c.freq("four"), std::runtime_error);
    BOOST_REQUIRE_NO_THROW(c.freq("gag"));
    BOOST_REQUIRE(c.freq("gag") == 4);
}

// Test freq(string, char)
BOOST_AUTO_TEST_CASE(charFreq) {
    RandWriter d("gagggagaggcgagaaa", 3);
    // Exception when string is not of order k
    BOOST_REQUIRE_THROW(d.freq("test", 'a'), std::runtime_error);
    BOOST_REQUIRE_NO_THROW(d.freq("gag", 'a'));
    BOOST_REQUIRE(d.freq("gag", 'a') == 2);
}

// Test k_rand()
BOOST_AUTO_TEST_CASE(krand) {
    RandWriter e("gagggagaggcgagaaa", 3);
    // Exception when kgram is not found
    BOOST_REQUIRE_THROW(e.k_rand("no"), std::runtime_error);
    BOOST_REQUIRE_NO_THROW(e.k_rand("gag"));
    // Exception when string is not of order k
    BOOST_REQUIRE_THROW(e.k_rand("gagg"), std::runtime_error);
    BOOST_REQUIRE(e.k_rand("gaa") == 'a');
}

// Test generate()
BOOST_AUTO_TEST_CASE(generate) {
    RandWriter f("gagggagaggcgagaaa", 3);
    // Exception for when string is not of k order
    BOOST_REQUIRE_THROW(f.generate("ag a", 3), std::runtime_error);
    BOOST_REQUIRE_NO_THROW(f.generate("agg", 3));
    BOOST_REQUIRE(f.generate("ag", 3) == "ag ");
}
