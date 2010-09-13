#include "HeuristicSearcher.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

struct F {
	F() {
		HeuristicSearcher searcher = HeuristicSearcher();
	};
	
};

BOOST_FIXTURE_TEST_CASE(null, F)
{
	
}
