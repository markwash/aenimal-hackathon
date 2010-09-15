#include <boost/random.hpp>
#include <Magick++.h>

#include "CircleImageNeighborFactory.h"

using namespace std;
using namespace boost;
using namespace Magick;

typedef mt19937 generator_type;
typedef variate_generator<generator_type&, uniform_real<> > rng;

int main(int argc, char **argv)
{
	InitializeMagick(*argv);
	CircleImage img(800, 600);
	generator_type generator;
	uniform_real<> uni_dist(0, 1);
	rng uni(generator, uni_dist);

	CircleImageNeighborFactory<rng> neighborhood(uni, 100);
	
	for (int i = 0; i < 10000; i++) {
		img = neighborhood.getNeighbor(img);
	}

	Image image = img.draw();
	image.display();

	return 0;
}
