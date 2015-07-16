
#include <Pixel\Binarization.h>
#include <Pixel\Image.h>

namespace Pixel
{
	Binarization::Binarization(float threshold)
		: m_fThreshold(threshold)
	{
	}

	void Binarization::setThreshold(float threshold)
	{
		m_fThreshold = threshold;
	}

	Image* Binarization::process(Image* pInImage)
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

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				unsigned int offset = x + y * width;
				if(pInData[offset * pInImage->getBytesPerPixel()] > m_fThreshold)
				{
					pOutData[offset * pOutImage->getBytesPerPixel()] = 255;
				}
				else
				{
					pOutData[offset * pOutImage->getBytesPerPixel()] = 0;
				}
			}
		}
		return pOutImage;
	}

}
