#ifndef CIRCLEIMAGENEIGHBORFACTORY_H
#define CIRCLEIMAGENEIGHBORFACTORY_H

#include "CircleImage.h"
#include "NeighborFactory.h"

template <class RNG>
class CircleImageNeighborFactory: public NeighborFactory<CircleImage>
{
	public:
	CircleImageNeighborFactory(RNG &rng, int target_size):
		rng(rng), target_size(target_size)
		{}
	CircleImage getNeighbor(CircleImage &img) const;

	private:
	void addRandomCircle(CircleImage &img) const;
	void changeRandomCircle(CircleImage &img) const;

	int target_size;
	RNG &rng;
};

template <class RNG>
CircleImage CircleImageNeighborFactory<RNG>::getNeighbor(CircleImage &img) const
{
	CircleImage neighbor = img;
	if (neighbor.count() < target_size)
		addRandomCircle(neighbor);
	return neighbor;
}

template <class RNG>
void CircleImageNeighborFactory<RNG>::addRandomCircle(CircleImage &img) const
{
	Circle circle;
	circle.x = rng() * img.getWidth();
	circle.y = rng() * img.getHeight();
	circle.radius = rng() * 10 + 10;
	circle.red = rng();
	circle.green = rng();
	circle.blue = rng();
	img.add(circle);
}

#endif
