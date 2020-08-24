#ifndef FILTER_H
#define FILTER_H
#include "Image.h"

class Filter {

public:
	
	//default constructor
	Filter() {}

	//Copy constructor
	Filter(const Filter & src) {}
	
	//Destructor
	virtual ~Filter() {}

	//pure virtual operator
	virtual imaging::Image operator << (const imaging::Image & image) = 0;

};

#endif