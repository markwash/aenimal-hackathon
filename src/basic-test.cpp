#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE BasicTest
#include <boost/test/unit_test.hpp>

int add(int i, int j) {
	return i + j;
}

BOOST_AUTO_TEST_CASE(universeInOrder) {
	BOOST_CHECK(add(2, 2) == 4);
}
