#include "ppm.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace imaging;


float * imaging::ReadPPM(const char * filename, int * w, int * h) {

	std::ifstream file(filename, std::ios::binary);

	if (!file) {
		std::cerr << "Error opening!" << std::endl;
		return nullptr;
	}

	std::string header;
	unsigned int b;
	char c;
	file >> header >> *w >> *h >> b >> c;

	if (header != "P6") {
		std::cerr << "The PPM file isn't a P6 type..!!";
		return nullptr;
	}

	if (*w == 0) {
		std::cerr << "The width is missing!";
		return nullptr;
	}

	if (*h == 0) {
		std::cerr << "The height is missing!";
		return nullptr;
	}

	if ((b == 0) || (b > 255)) {
		std::cerr << "The highest permitted value is wrong!";
		return nullptr;
	}


	unsigned char  *temp = new unsigned char[3 * *w * *h];
	float  *data = new float[3 * *w * *h];

	file.read(reinterpret_cast<char *>(temp), 3 * *w * *h);
	for (unsigned int i = 0; i < 3 * *w * *h; i++) {
		data[i] = (float)temp[i] / 255.0f;
	}

	delete[] temp;
	file.close();
	return data;

}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {
	std::ofstream file(filename, std::ios::binary);

	if (!file) {
		std::cerr << "Could not open image!" << std::endl;
		return false;
	}

	file << "P6" << std::endl << w << std::endl << h << std::endl << "255\n" << std::endl;
	for (unsigned int i = 0; i < 3 * w * h; i++) {
		unsigned int temp = data[i] * 255;
		file.write(reinterpret_cast<const char *>(&temp), 1);
	}

	file.close();

	return true;

}


	

	


