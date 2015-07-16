
#ifndef Dilation_h
#define Dilation_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Dilation : public IImageOperation
	{
	public:
		//constructor
		Dilation() {}

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Dilation() {}
	};

}

#endif //Dilation_h
