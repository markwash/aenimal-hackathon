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

BOOST_FIXTURE_TEST_CASE(always_prefer_higher_cost_if_rand_0, F)
{
	rand.canned_response = 0.0;
	BOOST_CHECK_EQUAL(heuristic.compare(100.0, 200.0), 1);
}

BOOST_FIXTURE_TEST_CASE(sometimes_prefer_higher_cost_if_rand_05, F)
{
	rand.canned_response = 0.5;
	// C2 - C1 <=> T * log(0.5) ~ 6.93
	for (int i = 1; i < 7; i++) 
		BOOST_CHECK_EQUAL(heuristic.compare(0.0, 1.0 * i), 1);
	for (int i = 7; i < 10; i++)
		BOOST_CHECK_EQUAL(heuristic.compare(0.0, 1.0 * i), -1);
}

BOOST_FIXTURE_TEST_CASE(go_greedy_if_temperature_zero, F)
{
	heuristic.setTemp(0.0);
	rand.canned_response = 0.0;
	BOOST_CHECK_EQUAL(heuristic.compare(100.0, 200.0), -1);
}

BOOST_FIXTURE_TEST_CASE(default_statistics, F)
{
	SimulatedAnnealingStatistics stats;
	stats = heuristic.statistics();
	BOOST_CHECK_EQUAL(stats.acceptRatio(), 0.0);
	BOOST_CHECK_EQUAL(stats.greedyAcceptRatio(), 0.0);
	BOOST_CHECK_EQUAL(stats.speculativeAcceptRatio(), 0.0);
	BOOST_CHECK_EQUAL(stats.rejectRatio(), 0.0);
}

BOOST_FIXTURE_TEST_CASE(all_greedy_accept_ratio, F)
{
	heuristic.setTemp(0.0);  // go greedy
	// 3 rejects
	for (int i = 0; i < 3; i++)
		BOOST_CHECK_EQUAL(heuristic.compare(100.0, 200.0), -1);
	// 7 accepts
	for (int i = 0; i < 7; i++)
		BOOST_CHECK_EQUAL(heuristic.compare(100.0, 50.0), 1);

	SimulatedAnnealingStatistics stats = heuristic.statistics();
	BOOST_CHECK_EQUAL(stats.acceptRatio(), 0.7);
	BOOST_CHECK_EQUAL(stats.rejectRatio(), 0.3);
	BOOST_CHECK_EQUAL(stats.greedyAcceptRatio(), 0.7);
	BOOST_CHECK_EQUAL(stats.speculativeAcceptRatio(), 0.0);
}

BOOST_FIXTURE_TEST_CASE(mixed_accept_ratio, F)
{
	// accept anything speculatively
	rand.canned_response = 0.0;
	for (int i = 0; i < 3; i++)
		BOOST_CHECK_EQUAL(heuristic.compare(1, 2), 1);
	for (int i = 0; i < 5; i++)
		BOOST_CHECK_EQUAL(heuristic.compare(2, 1), 1);

	// go greedy
	rand.canned_response = 1.0;
	for (int i = 0; i < 2; i++)
		BOOST_CHECK_EQUAL(heuristic.compare(1, 2), -1);
	
	SimulatedAnnealingStatistics stats = heuristic.statistics();
	BOOST_CHECK_EQUAL(stats.acceptRatio(), 0.8);
	BOOST_CHECK_EQUAL(stats.rejectRatio(), 0.2);
	BOOST_CHECK_EQUAL(stats.greedyAcceptRatio(), 0.5);
	BOOST_CHECK_EQUAL(stats.speculativeAcceptRatio(), 0.3);
}

BOOST_FIXTURE_TEST_CASE(reset_statistics, F)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			heuristic.compare(i, j);
	heuristic.resetStatistics();
	SimulatedAnnealingStatistics stats = heuristic.statistics();
	BOOST_CHECK_EQUAL(stats.acceptRatio(), 0.0);
	BOOST_CHECK_EQUAL(stats.greedyAcceptRatio(), 0.0);
	BOOST_CHECK_EQUAL(stats.speculativeAcceptRatio(), 0.0);
	BOOST_CHECK_EQUAL(stats.rejectRatio(), 0.0);
}
