#include "SimulatedAnnealingHeuristic.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestSimulatedAnnealingHeuristic
#include <boost/test/unit_test.hpp>

struct FakeRand
{
	double canned_response;
	double operator()() { return canned_response; }
};

struct F {
	F(): heuristic(rand, 10.0) {}
	FakeRand rand;
	SimulatedAnnealingHeuristic<FakeRand> heuristic;
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
	for (int i = 0; i < 1000; i++) {
		rand.canned_response = 1.0 * i / 1000.0;
		BOOST_CHECK_EQUAL(heuristic.compare(100.0, 99.0), 1);
	}
}

BOOST_FIXTURE_TEST_CASE(never_prefer_higher_cost_if_rand_1, F)
{
	rand.canned_response = 1.0;
	BOOST_CHECK_EQUAL(heuristic.compare(100.0, 101.0), -1);
}
