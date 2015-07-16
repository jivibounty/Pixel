
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
		Segmentation(float threshold = 30.0f);

		//sets threshold
		void setThreshold(float threshold);

		//gets threshold
		float getThreshold() const { return m_fThreshold; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Segmentation() {}
	protected:
		float m_fThreshold;
	};

}

#endif //Segmentation_h
