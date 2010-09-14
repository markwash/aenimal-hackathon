#include "SimulatedAnnealingHeuristic.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestSimulatedAnnealingHeuristic
#include <boost/test/unit_test.hpp>

struct F {
	F() {}
	SimulatedAnnealingHeuristic heuristic;
};

BOOST_FIXTURE_TEST_CASE(get_temperature, F)
{
	BOOST_CHECK_EQUAL(heuristic.getTemp(), 1.0);
}
