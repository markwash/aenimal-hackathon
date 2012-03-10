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
	F() {}
};

BOOST_FIXTURE_TEST_CASE(get_cost_works, F)
{
	InitializeMagick(NULL);
	Image black(Geometry(400, 400), Color("black"));
	Image white(Geometry(400, 400), Color("white"));
	ImageDrawerCostFunction<MockImageDrawer> cost_function(black);
	MockImageDrawer drawer = MockImageDrawer(white);
	double cost = cost_function.getCost(drawer);
	cout << cost << endl;
}
