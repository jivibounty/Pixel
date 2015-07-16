
#ifndef Segmentation_h
#define Segmentation_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Segmentation : public IImageOperation
	{
	public:
		//constructor
		Segmentation() {}

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Segmentation() {}
	};

}

#endif //Segmentation_h
