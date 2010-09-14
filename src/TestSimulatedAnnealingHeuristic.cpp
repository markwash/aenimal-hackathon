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
