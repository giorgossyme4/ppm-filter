#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

namespace math {

	template <typename T>
	class Array {

	protected:
		std::vector<T> buffer;                              //! Holds the image data.

		unsigned int width, 						 //! The width of the image (in pixels)
			height;		                 //! The height of the image (in pixels)

	public:
		// metric accessors

		/*! Returns the width of the image
		 */
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the image
		 */
		const unsigned int getHeight() const { return height; }

		/*! Obtains a pointer to the internal data.
		 *
		 *  This is NOT a copy of the internal image data, but rather a pointer
		 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
		 */
		std::vector<T> getRawDataPtr() {
			return buffer;
		}

		/*! Obtains the color of the image at location (x,y).
		 *
		 *  The method should do any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to get.
		 *  \param y is the (zero-based) vertical index of the pixel to get.
		 *
		 *  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		 */
		T getPoint(unsigned int x, unsigned int y) const {
			if ((x > width) || (y > height)) {
				return T();
			}
			return buffer[(width*y) + x];
		}

		// data mutators

		/*! Sets the RGB values for an (x,y) pixel.
		 *
		 *  The method should perform any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to set.
		 *  \param y is the (zero-based) vertical index of the pixel to set.
		 *  \param value is the new color for the (x,y) pixel.
		 */
		void setPoint(unsigned int x, unsigned int y, T & value) {
			if ((x > width) || (y > height)) {
				return;
			}
			buffer[(width*y) + x] = value;
		}

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		 *  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		 *  width or height of the image are 0, the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		 */
		void setData(const std::vector<T> & data_ptr) {
			if ((width == 0) || (height == 0) || (data_ptr.empty() == true)) {
				return;
			}

			buffer.clear();

			for (unsigned int i = 0; i < width * height; i++) {
				buffer.push_back(data_ptr[i]);
			}
		}

		// constructors and destructor

		/*! Default constructor.
		 *
		 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		 */
		Array() {
			height = 0;
			width = 0;
			buffer.clear();
		}

		/*! Constructor with width and height specification.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 */
		Array(unsigned int width, unsigned int height){
			this->width = width;
			this->height = height;
			buffer.assign(width * height, 0);
		}

		/*! Constructor with data initialization.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 *
		 * \see setData
		 */
		Array(unsigned int width, unsigned int height, const std::vector<T> data_ptr){
			this->width = width;
			this->height = height;
			setData(data_ptr);
		}

		//! Copy constructor.
		Array(const Array &src) {
			width = src.width;
			height = src.height;
			setData(src.buffer);
		}

		//! The Array destructor.
		~Array() {
			buffer.clear();
		}

		/*! Copy assignment operator.
		 *
		 * \param right is the source image.
		 */
		Array & operator = (const Array & right) {
			int size = width * height;
			int n_size = right.width * right.height;
			if (size != n_size) {
				buffer.clear();
				size = n_size;
				buffer.assign(size, 0);
			}

			this->width = right.width;
			this->height = right.height;
			setData(right.buffer);

			return *this;
		}

		/*
		*@return a reference to object T at position with coordinates i, j
		*/
		T & operator () (unsigned int i, unsigned int j) const {
			return buffer[(getWidth()*j) + i];
		}

	};
}

#endif