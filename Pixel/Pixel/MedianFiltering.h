
#ifndef MedianFiltering_h
#define MedianFiltering_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API MedianFiltering : public IImageOperation
	{
	public:
		//constructor
		MedianFiltering(unsigned int filterWindowSize = 5);

		//sets filter window size
		void setFilterWindowSize(unsigned int filterWindowSize);

		//gets filter window size
		unsigned int getFilterWindowSize() const { return m_FilterWindowSize; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~MedianFiltering() {}

		//computes the median of an array of values
		unsigned char getMedian(unsigned char val[], int no);
	protected:
		unsigned int m_FilterWindowSize;
	};

}

#endif //MedianFiltering_h
