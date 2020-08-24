#ifndef FILTERGAMMA_
#define FILTERGAMMA_

#include "Filter.h"


class FilterGamma : public Filter {

	float k;

public:

	//Default constructor
	FilterGamma();

	//Constructor
	FilterGamma(float k);

	//Copy-Constructor
	FilterGamma(const FilterGamma &src);

	//Destructor
	~FilterGamma();

	//Filter Gamma
	imaging::Image operator << (const  imaging::Image & Image);

};

#endif //FILTERGAMMA
