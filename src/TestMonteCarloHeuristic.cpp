#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMonteCarloHeuristic
#include <boost/test/unit_test.hpp>

struct F {
	F() {}
};

BOOST_FIXTURE_TEST_CASE(null, F)
{
}
