
#include <Pixel\Segmentation.h>
#include <Pixel\Image.h>
#include <Pixel\Utils.h>
#include <Math.h>
#include <list>

namespace Pixel
{

	Segmentation::Segmentation(float threshold)
		: m_fThreshold(threshold)
	{
	}

	void Segmentation::setThreshold(float threshold)
	{
		m_fThreshold = threshold;
	}

	Image* Segmentation::process(Image* pInImage)
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
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();
		bool* pClassified = new bool[numPixels];

		for(unsigned int n = 0; n < numPixels; ++n)
		{
			pClassified[n] = false;
		}

		unsigned int bytesPerPixel = min(4, pInImage->getBytesPerPixel());
		float fThresholdSquared = m_fThreshold * m_fThreshold;

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				unsigned int offsetClassified = x + y * width;
				if(pClassified[offsetClassified])
				{
					continue;
				}
				std::list<int> xl;
				std::list<int> yl;
				xl.push_back(x);
				yl.push_back(y);
				pClassified[offsetClassified] = true;
				
				unsigned int offset = (x + y * width) * pInImage->getBytesPerPixel();
				int color[4] = {0, 0, 0, 0};
				for(unsigned int n = 0; n < bytesPerPixel; ++n)
				{
					color[n] = pInData[offset + n];
					pOutData[offset + n] = color[n];
				}
				while(!xl.empty())
				{
					int valX = (*xl.begin());
					xl.pop_front();
					int valY = (*yl.begin());
					yl.pop_front();
					for(int j = valX - 1; j <= (valX + 1); ++j)
					{
						for(int k = valY - 1; k <= (valY + 1); ++k)
						{
							if(j < 0 || j > (int)width || k < 0 || k > (int)height)
							{
								continue;
							}
							unsigned int offsetJK = (j + k * width) * pInImage->getBytesPerPixel();
							int sumSquared = 0;
							for(unsigned int i = 0; i < bytesPerPixel; ++i)
							{
								int val = color[i] - (int)pInData[offsetJK + i];
								sumSquared += val * val;
							}
							
							if((float)sumSquared > fThresholdSquared)
							{
								continue;
							}
							xl.push_back(j);
							yl.push_back(k);
							pClassified[j + k * width] = true;
							for(unsigned int i = 0; i < bytesPerPixel; ++i)
							{
								pOutData[offsetJK + i] = color[i];
							}

						}
					}
				}
			}
		}
		return pOutImage;
	}

}
