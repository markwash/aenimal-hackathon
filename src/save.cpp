#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

#include "CircleImage.h"

class Config {
	public:
	char *data_file_in;
	char *image_file_out;
};

Config parse_args(int argc, char **argv)
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0];
		cerr << " <data file in> <image file out>";
		cerr << endl;
		exit(2);
	}
	Config config;
	config.data_file_in = argv[1];
	config.image_file_out = argv[2];
	return config;
}

int main(int argc, char **argv)
{
	InitializeMagick(*argv);
	Config config = parse_args(argc, argv);

	CircleImage circles(config.data_file_in);
	Image image = circles.draw();
	image.write(config.image_file_out);
	return 0;
}


