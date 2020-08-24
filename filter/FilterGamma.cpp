#include "Vec3.h"
#include "FilterGamma.h"
#include <math.h>
#include <iostream>

FilterGamma::FilterGamma() {}

FilterGamma::FilterGamma(float k) : k(k) {}

FilterGamma::FilterGamma(const FilterGamma &src) {
	k = src.k;
}

FilterGamma::~FilterGamma() {}

imaging::Image FilterGamma::operator << (const  imaging::Image & Image) {
	
	unsigned int w = Image.getWidth();
	unsigned int h = Image.getHeight();
	imaging::Image img = imaging::Image(w, h);
	for (unsigned int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			math::Vec3<float> pixel = Image.getPoint(x, y);
			float r = pow(pixel[0], k);
			float g = pow(pixel[1], k);
			float b = pow(pixel[2], k);
			math::Vec3<float> Gammapixel = math::Vec3<float>(r, g, b);
			Gammapixel = Gammapixel.clampToLowerBound(0);
			Gammapixel = Gammapixel.clampToUpperBound(1);
			img.setPoint(x, y, Gammapixel);
		}
	}
	return img;
}