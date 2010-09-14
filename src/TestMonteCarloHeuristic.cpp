#include "MonteCarloHeuristic.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMonteCarloHeuristic
#include <boost/test/unit_test.hpp>

struct F {
	F() {}
	MonteCarloHeuristic heuristic;
};

BOOST_FIXTURE_TEST_CASE(get_temperature, F)
{
	BOOST_CHECK_EQUAL(heuristic.getTemp(), 1.0);
}
