#include "ImageDrawerCostFunction.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestImageDrawerCostFunction
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <Magick++.h>
using namespace Magick;
using namespace std;

class MockImageDrawer
{
	public:
	MockImageDrawer(Image image):
		image(image) {}
	Image draw() const {
		return image;
	}

	private:
	Image image;
};

struct F {
	F(): cost_function(Image(Geometry(400, 400), Color("black"))) {}
	ImageDrawerCostFunction<MockImageDrawer> cost_function;
};

BOOST_FIXTURE_TEST_CASE(get_cost_works, F)
{
	Image image(Geometry(400, 400), Color("white"));
	MockImageDrawer drawer = MockImageDrawer(image);
	double cost = cost_function.getCost(drawer);
	cout << cost << endl;
}
