#include <Adder.h>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestAdder
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE ( empty )
{
	Adder adder = Adder();
	BOOST_CHECK_EQUAL( adder.add(2, 3), 5);
}
