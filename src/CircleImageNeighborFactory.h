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
	Circle &getRandomCircle(CircleImage &img) const;
	void growCircle(Circle &circle) const;
	void shrinkCircle(Circle &circle) const;
	void moveCircle(Circle &circle, int width, int height) const;
	void changeCircleColor(Circle & circle) const;
	void changeColor(double &color, double max_diff) const;

	RNG &rng;
	int target_size;
};

template <class RNG>
CircleImage CircleImageNeighborFactory<RNG>::getNeighbor(CircleImage &img) const
{
	CircleImage neighbor = img;
	if (neighbor.count() < target_size)
		addRandomCircle(neighbor);
	else
		changeRandomCircle(neighbor);
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

template <class RNG>
void CircleImageNeighborFactory<RNG>::changeRandomCircle(CircleImage &img) const
{
	double choice = rng();
	Circle &circle = getRandomCircle(img); 
	if (choice < 0.05)
		shrinkCircle(circle);
	else if (choice < 0.10)
		growCircle(circle);
	else if (choice < 0.55)
		changeCircleColor(circle);
	else
		moveCircle(circle, img.getWidth(), img.getHeight());
}

template <class RNG>
Circle &CircleImageNeighborFactory<RNG>::getRandomCircle(CircleImage &img) const
{
	return img.get(rng() * img.count());
}

template <class RNG>
void CircleImageNeighborFactory<RNG>::shrinkCircle(Circle &circle) const
{
	if (circle.radius > 1) 
		circle.radius--;
}

template <class RNG>
void CircleImageNeighborFactory<RNG>::growCircle(Circle &circle) const
{
	circle.radius++;
}

template <class RNG>
void CircleImageNeighborFactory<RNG>::changeCircleColor(Circle &circle) const
{
	changeColor(circle.red, 0.05);
	changeColor(circle.blue, 0.05);
	changeColor(circle.green, 0.05);
}

template <class RNG>
void CircleImageNeighborFactory<RNG>::changeColor(double &color, double max_diff) const
{
	color += 2 * max_diff * rng() - max_diff;
	if (color < 0.0) color = 0.0;
	if (color > 1.0) color = 1.0;
}

template <class RNG>
void CircleImageNeighborFactory<RNG>::moveCircle(Circle &circle, int width, int height) const
{
	double choice = rng();
	if (choice < 0.25)
		circle.x = (circle.x + 1) % width;
	else if (choice < 0.50)
		circle.x = (width + circle.x - 1) % width;
	else if (choice < 0.75)
		circle.y = (circle.y + 1) % height;
	else
		circle.y = (height + circle.y - 1) % height;
}


#endif
