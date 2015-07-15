
#ifndef AverageFiltering_h
#define AverageFiltering_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API AverageFiltering : public IImageOperation
	{
	public:
		//constructor
		AverageFiltering(unsigned int filterWindowSize = 3);

		//sets filter window size
		void setFilterWindowSize(unsigned int filterWindowSize);

		//gets filter window size
		unsigned int getFilterWindowSize() const { return m_FilterWindowSize; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~AverageFiltering() {}
	protected:
		unsigned int m_FilterWindowSize;
	};

}

#endif //AverageFiltering_h
