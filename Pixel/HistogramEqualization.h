
#ifndef HistogramEqualization_h
#define HistogramEqualization_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API HistogramEqualization : public IImageOperation
	{
	public:
		//constructor
		HistogramEqualization() {}
		
		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~HistogramEqualization() {}
	};

}

#endif //HistogramEqualization_h
