
#ifndef GrayScale_h
#define GrayScale_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API GrayScale : public IImageOperation
	{
	public:
		//constructor
		GrayScale() {}

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~GrayScale() {}
	};

}

#endif //GrayScale_h
