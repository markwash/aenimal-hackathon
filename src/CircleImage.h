#ifndef CIRCLEIMAGE_H
#define CIRCLEIMAGE_H

#include <vector>
#include <list>
#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

struct Circle {
	int x, y;
	int radius;
	double red, green, blue;
};

class CircleImage {
	public:
	CircleImage(int width, int height):
		width(width), height(height) {}
	void add(Circle circle) { circles.push_back(circle); }
	void deleteLast(void) { circles.pop_back(); }
	int count(void) const { return circles.size(); }
	Circle &get(int i) { return circles[i]; }

	int getWidth(void) const { return width; }
	int getHeight(void) const { return height; }

	Image draw(void) const;

	private:
	void buildDrawList(list<Drawable> &draw_list) const;

	int width, height;
	vector<Circle> circles;
};

Image CircleImage::draw(void) const {
	Image image(Geometry(width, height), Color("white"));
	image.strokeWidth(0);
	list<Drawable> draw_list;
	buildDrawList(draw_list);
	if (draw_list.size() > 0)
		image.draw(draw_list);
	return image;
}

void CircleImage::buildDrawList(list<Drawable> &draw_list) const {
	Circle circle;
	for (unsigned int i = 0; i < circles.size(); i++) {
		circle = circles[i];
		ColorRGB color = ColorRGB(circle.red, circle.blue, circle.green);
		draw_list.push_back(DrawableFillColor(color));
		draw_list.push_back(
			DrawableCircle(circle.x, circle.y,
				       circle.x, circle.y + circle.radius));
	}
}

#endif
