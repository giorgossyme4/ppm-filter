#include <iostream>
#include "Image.h"
#include "ppm/ppm.h"

namespace imaging {

	Image::Image() : Array() {}

	Image::Image(unsigned int width, unsigned int height) : Array(width, height) {}

	Image::Image(unsigned int width, unsigned int height, const std::vector<math::Vec3<float>> data_ptr) : Array(width, height, data_ptr) {}

	bool Image::load(const std::string & filename, const std::string & format) {
		if (format == "ppm") {
			int w = 0;
			int h = 0;
			float *array = imaging::ReadPPM(filename.c_str(), &w, &h);
			width = w;
			height = h;
			if (array == nullptr) { return false; }
			buffer.clear();
			buffer.assign(width * height, 0);
			float r, g, b;
			int j = 0;
			for (unsigned int i = 0; i < 3 * width * height; i = i + 3) {
				r = array[i];
				g = array[i + 1];
				b = array[i + 2];
				buffer[j] = math::Vec3<float>(r, g, b);
				j++;
			}

			return true;
		}
		else {
			return false;
		}
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		if (format == "ppm") {
			float *sarray = new float[width * height * 3];
			if (buffer.empty() == true) { return false; }
			int j = 0;
			for (unsigned int i = 0; i < width * height * 3; i = i + 3) {

				sarray[i] = buffer[j].r;
				sarray[i + 1] = buffer[j].g;
				sarray[i + 2] = buffer[j].b;
				j++;
			}
			bool saving = imaging::WritePPM(sarray, width, height, filename.c_str());
			if (saving = true) {
				return true;
			}
			else {
				return false;
			}
		}
		else { return false; }
	}
}