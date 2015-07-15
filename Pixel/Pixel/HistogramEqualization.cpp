
#include <Pixel\HistogramEqualization.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{

	Image* HistogramEqualization::process(Image* pInImage)
	{
		//check if input is null
		if(pInImage == NULL)
		{
			return NULL;
		}

		//create output image
		Image* pOutImage = new Image;
		pOutImage->addRef();

		//compute number of pixels
		unsigned int width = pInImage->getWidth();
		unsigned int height = pInImage->getHeight();
		unsigned int numPixels = width * height;
		if(numPixels == 0)
		{
			return pOutImage;
		}
		pOutImage->setSize(width, height, 1);
		
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();
		
		unsigned int histogram[256];
		unsigned char lut[256];
		memset(histogram, 0, sizeof(histogram));
		//compute histogram
		for(unsigned int n = 0; n < numPixels; ++n)
		{
			++histogram[pInData[n * pInImage->getBytesPerPixel()]];
		}

		unsigned int sum = 0;
		//compute cummulative histogram
		for(unsigned int n = 0; n < numPixels; ++n)
		{
			sum += histogram[n];
			lut[n] = (unsigned char)((float)(sum / numPixels) * 255.0f);
		}

		for(unsigned int n = 0; n < numPixels; ++n)
		{
			pOutData[n * pOutImage->getBytesPerPixel()] = lut[pInData[n * pInImage->getBytesPerPixel()]];
		}

		return pOutImage;
	}

}
