#include "HeuristicSearcher.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

class MockCostFunction: public CostFunction<int> {
};

class MockCollation: public Collation<int> {
};

struct F {
	F() {
		CostFunction<int> cost_function = MockCostFunction();
		HeuristicSearcher<int> searcher =
			HeuristicSearcher<int>(cost_function);
	};
	
};

BOOST_FIXTURE_TEST_CASE(null, F)
{
}

