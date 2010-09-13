#include "HeuristicSearcher.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

#include <map>
using namespace std;

class MockCostFunction: public CostFunction<int> {
	public:
	void addCost(int state, double cost) {
		costs[state] = cost;
	}
	double getCost(int state) {
		return costs[state];
	}

	private:
	map<int, double> costs;
};

class MockCostHeuristic: public CostHeuristic {
};

class MockNeighborFactory: public NeighborFactory<int> {
	public:
	void addNeighbor(int state, int neighbor) {
		neighbors[state] = neighbor;
	}
	int getNeighbor(int state) {
		return neighbors[state];
	}

	private:
	map<int, int> neighbors;
};

struct F {
	CostFunction<int> cost_function;
	CostHeuristic cost_heuristic;
	NeighborFactory<int> neighbor_factory;
	int initial_state;

	HeuristicSearcher<int> searcher;

	F():
		initial_state(0),
		searcher(cost_function, cost_heuristic,
			 neighbor_factory, initial_state)
	{};
	
};

BOOST_FIXTURE_TEST_CASE(initial_is_best_state, F)
{
	BOOST_CHECK_EQUAL(searcher.best(), initial_state);
}

BOOST_FIXTURE_TEST_CASE(one_run_goes_to_next_state, F)
{
	
}
