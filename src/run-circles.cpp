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

class Config {
	public:
	char *image_file_input;
	char *image_file_output;
	bool data_input_given;
	char *data_file_input;
	char *data_file_output;
};

Config parse_args(int argc, char **argv)
{
	if (argc != 4 && argc != 5) {
		cerr << "Usage: " << argv[0];
		cerr << " <image file> <image output> <data out> [<data in>]";
		cerr << endl;
		exit(2);
	}
	Config config;
	config.image_file_input = argv[1];
	config.image_file_output = argv[2];
	config.data_file_output = argv[3];
	if (argc == 4) {
		config.data_input_given = false;
	} else {
		config.data_input_given = true;
		config.data_file_input = argv[4];
	}
	return config;
}

int main(int argc, char **argv)
{
	InitializeMagick(*argv);
	Config config = parse_args(argc, argv);
	Image target = Image(config.image_file_input);

	ImageDrawerCostFunction<CircleImage> cost_function(target);
	GreedyHeuristic heuristic;
	CircleImageNeighborFactory<rng> neighbor_factory(uni, 20);
	CircleImage circles(target.baseColumns(), target.baseRows());
	if (config.data_input_given) 
		circles = CircleImage(config.data_file_input);

	HeuristicSearcher<CircleImage> searcher(cost_function, heuristic,
						neighbor_factory, circles);

	for (int i = 0; i < 5000; i++) {
		cout << i << endl;
		searcher.runOnce();
	}

	circles = searcher.bestState();
	Image image = circles.draw();
	image.write(config.image_file_output);
	circles.save(config.data_file_output);
	image.display();

	return 0;
}


