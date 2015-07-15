
#ifndef Invert_h
#define Invert_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Invert : public IImageOperation
	{
	public:
		//constructor
		Invert() {}

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Invert() {}
	};

}

#endif //Invert_h
