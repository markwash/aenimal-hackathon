#include "SimulatedAnnealingHeuristic.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestSimulatedAnnealingHeuristic
#include <boost/test/unit_test.hpp>

struct F {
	F(): heuristic(10.0) {}
	SimulatedAnnealingHeuristic heuristic;
};

BOOST_FIXTURE_TEST_CASE(get_temperature, F)
{
	BOOST_CHECK_EQUAL(heuristic.getTemp(), 10.0);
}

BOOST_FIXTURE_TEST_CASE(set_temperature, F)
{
	heuristic.setTemp(100.0);
	BOOST_CHECK_EQUAL(heuristic.getTemp(), 100.0);
}

BOOST_FIXTURE_TEST_CASE(call_comparison, F)
{
	int choice = heuristic.compare(10.0, 20.0);
}

BOOST_FIXTURE_TEST_CASE(always_prefer_lower_cost, F)
{
	double cost;
	for (int i = 0; i < 10000; i++) {
		cost = 100.0 - 1.0 / i;
		BOOST_CHECK_EQUAL(heuristic.compare(100.0, cost), 1);
	}
}
