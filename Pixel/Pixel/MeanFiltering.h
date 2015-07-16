
#ifndef MeanFiltering_h
#define MeanFiltering_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API MeanFiltering : public IImageOperation
	{
	public:
		//constructor
		MeanFiltering(unsigned int filterWindowSize = 3);

		//sets filter window size
		void setFilterWindowSize(unsigned int filterWindowSize);

		//gets filter window size
		unsigned int getFilterWindowSize() const { return m_FilterWindowSize; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~MeanFiltering() {}
	protected:
		unsigned int m_FilterWindowSize;
	};

}

#endif //MeanFiltering_h
