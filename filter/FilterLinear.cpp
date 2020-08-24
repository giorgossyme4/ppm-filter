#include "FilterLinear.h"
#include <vector>
#include <iostream>

FilterLinear::FilterLinear() : a(), c() {}

FilterLinear::FilterLinear(math::Vec3<float> a, math::Vec3<float> c) : a(a), c(c) {}

FilterLinear::FilterLinear(const FilterLinear &src) {
	a = src.a;
	c = src.c;
}

FilterLinear::~FilterLinear() {}

imaging::Image FilterLinear::operator << (const imaging::Image & Image) {

	unsigned int w = Image.getWidth();
	unsigned int h = Image.getHeight();
	imaging::Image img = imaging::Image(w, h);
	for (unsigned int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			math::Vec3<float> pixel = Image.getPoint(x, y);
			math::Vec3<float> Linearpixel = a * pixel + c;
			Linearpixel = Linearpixel.clampToLowerBound(0.0);
			Linearpixel = Linearpixel.clampToUpperBound(1.0);
			img.setPoint(x, y, Linearpixel);
		}
	}

	return img;
}