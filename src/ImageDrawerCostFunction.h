#ifndef IMAGEDRAWERCOSTFUNCTION_H
#define IMAGEDRAWERCOSTFUNCTION_H

#include <Magick++.h>
#include "CostFunction.h"

using namespace Magick;

template <class ImageDrawer>
class ImageDrawerCostFunction: public CostFunction<ImageDrawer>
{
	public:
	ImageDrawerCostFunction(Image target):
		target(target)
		{}
	double getCost(ImageDrawer &drawer) const;

	private:
	Image target;
};

template <class ImageDrawer>
double ImageDrawerCostFunction<ImageDrawer>::getCost(ImageDrawer &drawer) const
{
	Image drawn = drawer.draw();
	drawn.compare(target);
	return drawn.meanErrorPerPixel();
}

#endif
