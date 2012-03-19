#include <boost/random.hpp>
#include <Magick++.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;
using namespace boost;
using namespace Magick;

#include "InMemoryRecorder.h"
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
	bool cost_data_input_given;
	char *cost_data_file_input;
	char *cost_data_file_output;
};

Config parse_args(int argc, char **argv)
{
	if (argc < 7 || argc > 9) {
		cerr << "Usage: " << argv[0];
		cerr << " <image file> <circles> <iterations>";
		cerr << " <temp> <data out> <cost data out>";
		cerr << " [<data in> [<cost data in>]]";
		cerr << endl;
		exit(2);
	}
	Config config;
	config.image_file_input = argv[1];
	config.circles = atoi(argv[2]);
	config.iterations = atoi(argv[3]);
	config.temperature = atof(argv[4]);
	config.data_file_output = argv[5];
	config.cost_data_file_output = argv[6];
	config.data_input_given = (argc > 7);
	config.cost_data_input_given = (argc > 8);
	if (config.data_input_given)
		config.data_file_input = argv[7];
	if (config.cost_data_input_given)
		config.cost_data_file_input = argv[8];
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
	InMemoryRecorder<CircleImageChangeDimension> recorder;
	CircleImage circles(target.baseColumns(), target.baseRows());
	CircleImage best_circles(target.baseColumns(), target.baseRows());
	if (config.data_input_given) { 
		ifstream input(config.data_file_input);
		best_circles = CircleImage(input);
		circles = CircleImage(input);
		cout << config.data_file_input << " ";
		cout << "width " << circles.getWidth() << endl;
		input.close();
	}
	if (config.cost_data_input_given) {
		ifstream input(config.cost_data_file_input);
		input >> recorder;
		input.close();
	} else {
		recorder.recordInitial(cost_function.getCost(circles));
	}

	HeuristicSearcher<CircleImage, CircleImageChangeDimension>
		searcher(cost_function, heuristic,
			 neighbor_factory, recorder,
			 circles, best_circles);

	cout << setiosflags(ios::fixed) << setprecision(2);
	for (int i = 0; i < config.iterations; i++) {
		if (i % 25 == 0) {
			cout << "\r";
			cout << 100.0 * i / config.iterations << "%";
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
	ofstream cost_output(config.cost_data_file_output);
	cost_output << recorder;
	cout << "Cost: " << searcher.bestCost() << endl;

	return 0;
}


