#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

#include "CircleImage.h"

char *parse_args(int argc, char **argv)
{
	if (argc != 2) {
		cerr << "Usage: " << argv[0];
		cerr << " <data file>";
		cerr << endl;
		exit(2);
	}
	return argv[1];
}

int main(int argc, char **argv)
{
	InitializeMagick(*argv);
	char *file = parse_args(argc, argv);

	CircleImage circles(file);
	Image image = circles.draw();
	image.display();
	return 0;
}


