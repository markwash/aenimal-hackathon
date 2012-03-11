#include <boost/random.hpp>
#include <Magick++.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;
using namespace boost;
using namespace Magick;

#include "ImageDrawerCostFunction.h"
#include "CircleImageNeighborFactory.h"
#include "GreedyHeuristic.h"
#include "SimulatedAnnealingHeuristic.h"
#include "HeuristicSearcher.h"

typedef mt19937 generator_type;
typedef variate_generator<generator_type&, uniform_real<> > rng;

generator_type generator(static_cast<unsigned int>(time(0)));
uniform_real<> uni_dist(0, 1);
rng uni(generator, uni_dist);

class Config {
	public:
	char *image_file_input;
	int iterations;
	double temperature;
	int circles;
	bool data_input_given;
	char *data_file_input;
	char *data_file_output;
};

Config parse_args(int argc, char **argv)
{
	if (argc != 6 && argc != 7) {
		cerr << "Usage: " << argv[0];
		cerr << " <image file> <circles> <iterations>";
		cerr << " <temp> <data out> [<data in>]";
		cerr << endl;
		exit(2);
	}
	Config config;
	config.image_file_input = argv[1];
	config.circles = atoi(argv[2]);
	config.iterations = atoi(argv[3]);
	config.temperature = atof(argv[4]);
	config.data_file_output = argv[5];
	if (argc == 6) {
		config.data_input_given = false;
	} else {
		config.data_input_given = true;
		config.data_file_input = argv[6];
	}
	return config;
}

int main(int argc, char **argv)
{
	InitializeMagick(*argv);
	Config config = parse_args(argc, argv);
	Image target = Image(config.image_file_input);

	ImageDrawerCostFunction<CircleImage> cost_function(target);
	SimulatedAnnealingHeuristic<rng> heuristic(uni, config.temperature);
	CircleImageNeighborFactory<rng> neighbor_factory(uni, config.circles);
	CircleImage circles(target.baseColumns(), target.baseRows());
	CircleImage best_circles(target.baseColumns(), target.baseRows());
	if (config.data_input_given) { 
		ifstream input(config.data_file_input);
		best_circles = CircleImage(input);
		circles = CircleImage(input);
		input.close();
	}

	HeuristicSearcher<CircleImage> searcher(cost_function, heuristic,
						neighbor_factory, circles,
						best_circles);

	for (int i = 0; i < config.iterations; i++) {
		if (i % 25 == 0) {
			cout << "\r";
			cout << 100.0 * i / config.iterations << "%      ";
			cout << flush;
		}
		searcher.runOnce();
	}
	cout << "\r" << flush;

	best_circles = searcher.bestState();
	circles = searcher.currentState();
	Image image = circles.draw();
	ofstream output(config.data_file_output);
	best_circles.save(output);
	circles.save(output);
	cout << "Ratio: " << searcher.acceptRatio() << endl;
	cout << "Cost: " << searcher.bestCost() << endl;

	return 0;
}


