#include "HeuristicSearcher.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

class MockCostFunction: public CostFunction<int> {
};

class MockCostHeuristic: public CostHeuristic {
};

class MockNeighborFactory: public NeighborFactory<int> {
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
	//BOOST_CHECK_EQUAL(searcher.best(), initial_state);
}

