#include "GreedyHeuristic.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestGreedyHeuristic
#include <boost/test/unit_test.hpp>

struct F {
	F() {}
	GreedyHeuristic heuristic;
};

BOOST_FIXTURE_TEST_CASE(always_prefer_lower_cost, F)
{
	BOOST_CHECK_EQUAL(heuristic.compare(2.0, 1.0), 1);
}

BOOST_FIXTURE_TEST_CASE(never_prefer_higher_cost, F)
{
	BOOST_CHECK_EQUAL(heuristic.compare(1.0, 2.0), -1);
}

BOOST_FIXTURE_TEST_CASE(never_prefer_same_cost, F)
{
	BOOST_CHECK_EQUAL(heuristic.compare(1.0, 1.0), -1);
}
