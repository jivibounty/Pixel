
#ifndef Halftoning_h
#define Halftoning_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Halftoning : public IImageOperation
	{
	public:
		//constructor
		Halftoning(float threshold = 128.0f);

		//sets threshold
		void setThreshold(float threshold);

		//gets threshold
		float getThreshold() const { return m_fThreshold; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Halftoning() {}
	protected:
		float m_fThreshold;
	};

}

#endif //Halftoning_h
