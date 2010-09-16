#include <boost/random.hpp>
#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace boost;
using namespace Magick;

#include "ImageDrawerCostFunction.h"
#include "CircleImageNeighborFactory.h"
#include "GreedyHeuristic.h"
#include "HeuristicSearcher.h"

typedef mt19937 generator_type;
typedef variate_generator<generator_type&, uniform_real<> > rng;

generator_type generator;
uniform_real<> uni_dist(0, 1);
rng uni(generator, uni_dist);

char *parse_args(int argc, char **argv)
{
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <image file>" << endl;
		exit(2);
	}
	return argv[1];
}

int main(int argc, char **argv)
{
	InitializeMagick(*argv);
	char *target_image_file = parse_args(argc, argv);
	Image target = Image(target_image_file);

	return 0;
}

