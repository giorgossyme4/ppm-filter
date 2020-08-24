#ifndef _IMAGE
#define _IMAGE

#include "Array.h"
#include "Vec3.h"
#include <string>

namespace imaging {

	class Image : public math::Array<math::Vec3<float>> {
	public:
		
		Image();

		Image(unsigned int width, unsigned int height);

		Image(unsigned int width, unsigned int height, const std::vector<math::Vec3<float>> data_ptr);

		bool load(const std::string & filename, const std::string & format);

		bool save(const std::string & filename, const std::string & format);

	};

} //namespace imaging

#endif