
#include <Pixel\LocalThresholding.h>
#include <Pixel\Image.h>

namespace Pixel
{

	LocalThresholding::LocalThresholding(unsigned int thresholdingWindowSize)
		: m_ThresholdingWindowSize(thresholdingWindowSize)
	{
	}

	void LocalThresholding::setThresholdingWindowSize(unsigned int thresholdingWindowSize)
	{
		m_ThresholdingWindowSize = thresholdingWindowSize;
	}

	Image* LocalThresholding::process(Image* pInImage)
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
		
		int halfThresholdingWindowSize = m_ThresholdingWindowSize >> 1;

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				unsigned int offset = x + y * width;
				int sumPixels = 0;
				unsigned int numPixels = 0;
				for(int j = (int)x - halfThresholdingWindowSize; j <= ((int)x + halfThresholdingWindowSize); ++j)
				{
					if(j < 0 || j >= (int)width)
					{
						continue;
					}
					for(int k = (int)y - halfThresholdingWindowSize; k <= ((int)y + halfThresholdingWindowSize); ++k)
					{
						if(k < 0 || k >= (int)height)
						{
							continue;
						}
						unsigned int offsetJK = (j + k * width) * pInImage->getBytesPerPixel();
						sumPixels += pInData[offsetJK];
						++numPixels;
					}
				}
				float mean = 0.0f;
				if(numPixels > 0)
				{
					mean = (float)sumPixels / (float)numPixels;
				}
				if((float)pInData[offset * pInImage->getBytesPerPixel()] > mean)
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
