
#ifndef Binarization_h
#define Binarization_h

#include <Pixel\CompileSettings.h>
#include <Pixel\ImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Binarization : public ImageOperation
	{
	public:
		//constructor
		Binarization(float threshold = 128.0f);

		//sets threshold
		void setThreshold(float threshold);

		//gets threshold
		float getThreshold() const { return m_fThreshold; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Binarization() {}
	protected:
		float m_fThreshold;
	};

}

#endif //Binarization_h
