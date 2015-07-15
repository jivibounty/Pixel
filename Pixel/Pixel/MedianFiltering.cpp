
#include <Pixel\MedianFiltering.h>
#include <Pixel\Image.h>
#include <Pixel\Utils.h>

namespace Pixel
{
	MedianFiltering::MedianFiltering(unsigned int filterWindowSize)
		: m_FilterWindowSize(filterWindowSize)
	{
	}

	void MedianFiltering::setFilterWindowSize(unsigned int filterWindowSize)
	{
		m_FilterWindowSize = filterWindowSize;
		if(m_FilterWindowSize == 0)
		{
			m_FilterWindowSize = 3;
		}
	}

	unsigned char MedianFiltering::getMedian(unsigned char val[], int no)
	{
		unsigned char median;
		for(int n = 0; n < no; ++n)
		{
			for(int i = n + 1; i < no; ++i)
			{
				if(val[n] > val[i])
				{
					char temp = val[n];
					val[n] = val[i];
					val[i] = temp;
				}
			}
		}
		int medianid;
		if((no%2) == 1)
		{
			medianid = (no+1) / 2;
			median = val[medianid];
		}
		else
		{
			medianid = no / 2;
			median = (unsigned char)(((float)val[medianid] + (float)val[medianid+1]) / 2.0f);
		}
		return median;
	}

	Image* MedianFiltering::process(Image* pInImage)
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
		unsigned char* pFilterHelperData[4] = { NULL, NULL, NULL, NULL };
		for(unsigned int n = 0; n < bytesPerPixel; ++n)
		{
			pFilterHelperData[n] = new unsigned char[m_FilterWindowSize * m_FilterWindowSize];
		}

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
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
							pFilterHelperData[i][numPixels] = pInData[offsetJK + i];
						}
						++numPixels;
					}
				}
				unsigned int offsetXY = (x + y * width) * pOutImage->getBytesPerPixel();
				for(unsigned int i = 0; i < bytesPerPixel; ++i)
				{
					pOutData[offsetXY + i] = getMedian(pFilterHelperData[i], numPixels);
				}

			}
		}
		for(unsigned int n = 0; n < bytesPerPixel; ++n)
		{
			SAFE_DELETE(pFilterHelperData[n]);
		}
		return pOutImage;
	}

}
