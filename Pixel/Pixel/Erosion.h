
#ifndef Erosion_h
#define Erosion_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Erosion : public IImageOperation
	{
	public:
		//constructor
		Erosion() {}

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Erosion() {}
	};

}

#endif //Erosion_h
