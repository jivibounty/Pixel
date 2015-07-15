
#ifndef ImageOperation_h
#define ImageOperation_h

#include <Pixel\CompileSettings.h>
#include <Pixel\ReferenceCounter.h>

namespace Pixel
{

	class Image;

	class PIXEL_API ImageOperation : public ReferenceCounter
	{
	public:
		//constructor
		ImageOperation() {}
		virtual Image* process(Image* pInImage) = 0;
	protected:
		//destructor
		virtual ~ImageOperation() {}
	};

}

#endif //ImageOperation_h
