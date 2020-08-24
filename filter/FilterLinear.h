#ifndef FILTERLINEAR_H
#define FILTERLINEAR_H

#include "Filter.h"
#include "Vec3.h"

class FilterLinear : public Filter {

private:
	math::Vec3<float> a, c;

public:

	//Default constructor
	FilterLinear();

	//Constructor
	FilterLinear(math::Vec3<float> a, math::Vec3<float> c);

	//Copy-Constructor
	FilterLinear(const FilterLinear &src);

	//Destructor
	~FilterLinear();

	//Filter Linear
	imaging::Image operator << (const imaging::Image & image);

};

#endif