#include <boost/random.hpp>
#include <Magick++.h>

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

int main(int argc, char **argv)
{
	InitializeMagick(*argv);

	return 0;
}
