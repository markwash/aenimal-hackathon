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
	F() {
		CostFunction<int> cost_function = MockCostFunction();
		CostHeuristic cost_heuristic = MockCostHeuristic();
		NeighborFactory<int> neighbor_factory = MockNeighborFactory();
		int initial_state = 0;

		HeuristicSearcher<int> searcher =
			HeuristicSearcher<int>(cost_function, cost_heuristic,
					       neighbor_factory, initial_state);
	};
	
};

BOOST_FIXTURE_TEST_CASE(null, F)
{
}

