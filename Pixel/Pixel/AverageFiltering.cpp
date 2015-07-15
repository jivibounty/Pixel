
#include <Pixel\AverageFiltering.h>
#include <Pixel\Image.h>
#include <Pixel\Utils.h>

namespace Pixel
{
	AverageFiltering::AverageFiltering(unsigned int filterWindowSize)
		: m_FilterWindowSize(filterWindowSize)
	{
	}

	void AverageFiltering::setFilterWindowSize(unsigned int filterWindowSize)
	{
		m_FilterWindowSize = filterWindowSize;
		if(m_FilterWindowSize == 0)
		{
			m_FilterWindowSize = 3;
		}
	}

	Image* AverageFiltering::process(Image* pInImage)
	{
		//check if input is null
		if(pInImage == NULL)
		{
			return NULL;
		}
		if(m_FilterWindowSize == 0)
		{
			m_FilterWindowSize = 3;
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
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();

		unsigned int bytesPerPixel = min(4, pInImage->getBytesPerPixel());
		int halfFilterWindowSize = m_FilterWindowSize >> 1;
		int sumPixels[4] = { 0, 0, 0, 0 };

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				for(unsigned int n = 0; n < bytesPerPixel; ++n)
				{
					sumPixels[n] = 0;
				}
				unsigned int numPixels = 0;
				for(int j = (int)x - halfFilterWindowSize; j <= ((int)x + halfFilterWindowSize); ++j)
				{
					if(j < 0 || j >= (int)width)
					{
						continue;
					}
					for(int k = (int)y - halfFilterWindowSize; k <= ((int)y + halfFilterWindowSize); ++k)
					{
						if(k < 0 || k >= (int)height)
						{
							continue;
						}
						unsigned int offsetJK = (j + k * width) * pInImage->getBytesPerPixel();
						for(unsigned int i = 0; i < bytesPerPixel; ++i)
						{
							sumPixels[i] += pInData[offsetJK + i];
						}
						++numPixels;
					}
				}
				unsigned int offsetXY = (x + y * width) * pOutImage->getBytesPerPixel();
				for(unsigned int i = 0; i < bytesPerPixel; ++i)
				{
					float avgValue = 0.0f;
					if(numPixels > 0)
					{
						avgValue = (float)sumPixels[i] / (float)numPixels;
					}
					if(avgValue > 255.0f)
					{
						avgValue = 255.0f;
					}
					pOutData[offsetXY + i] = (unsigned char)avgValue;
				}

			}
		}
		return pOutImage;
	}

}
