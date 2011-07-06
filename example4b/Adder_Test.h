#pragma once
 
// For BOOST testing
#include <boost/test/unit_test.hpp>
 
// The class to be tested
#include "../example4a/Adder.h"
 
BOOST_AUTO_TEST_SUITE(adder_test_suite);
 
BOOST_AUTO_TEST_CASE(add_test_case)
{
  Adder adder;
  BOOST_REQUIRE_EQUAL(adder.add(10, 5), 15);
}
 
BOOST_AUTO_TEST_SUITE_END();
