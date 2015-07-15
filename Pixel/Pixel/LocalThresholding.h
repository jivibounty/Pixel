
#ifndef LocalThresholding_h
#define LocalThresholding_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API LocalThresholding : public IImageOperation
	{
	public:
		//constructor
		LocalThresholding(unsigned int thresholdingWindowSize = 5);

		//sets thresholding window size
		void setThresholdingWindowSize(unsigned int thresholdingWindowSize);

		//gets thresholding window size
		unsigned int getThresholdingWindowSize() const { return m_ThresholdingWindowSize; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~LocalThresholding() {}
	protected:
		unsigned int m_ThresholdingWindowSize;
	};

}

#endif //LocalThresholding_h
