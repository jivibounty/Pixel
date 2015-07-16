
#ifndef ImageOperation_h
#define ImageOperation_h

#include <Pixel\CompileSettings.h>
#include <Pixel\ReferenceCounter.h>

namespace Pixel
{

	class Image;

	class PIXEL_API IImageOperation : public ReferenceCounter
	{
	public:
		//constructor
		IImageOperation() {}
		virtual Image* process(Image* pInImage) = 0;
	protected:
		//destructor
		virtual ~IImageOperation() {}
	};

}

#endif //ImageOperation_h
