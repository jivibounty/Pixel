
#include <Pixel\Halftoning.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{
	Halftoning::Halftoning(float threshold)
		: m_fThreshold(threshold)
	{
	}

	void Halftoning::setThreshold(float threshold)
	{
		m_fThreshold = threshold;
	}

	Image* Halftoning::process(Image* pInImage)
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

		//allocate memory for error propagated at position and set to zero
		float* eP = new float[numPixels];
		memset(eP, 0, sizeof(float) * numPixels);
		
		//allocate memory for error generated at position and set to zero
		float* eG = new float[numPixels];
		memset(eG, 0, sizeof(float) * numPixels);

		float sumP = 0.0f;
		float c[2][3];
		c[0][0] = 0.0f;
		c[0][1] = 0.2f;
		c[0][2] = 0.0f;
		c[1][0] = 0.6f;
		c[1][1] = 0.1f;
		c[1][2] = 0.1f;

		pOutImage->setSize(width, height, 1);
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				sumP = 0.0f;
				for(int i = 0; i < 2; ++i)
				{
					for(int j = 0; j < 3; ++j)
					{
						int xx = x - i + 1;
						if(xx < 0)
						{
							xx = 0;
						}
						else if(xx >= width)
						{
							xx = width - 1;
						}
						int yy = y - j + 1;
						if(yy < 0)
						{
							yy = 0;
						}
						else if(yy >= height)
						{
							yy = height - 1;
						}
						sumP += (c[i][j] * eG[xx + yy * width]);
					}
				}
				unsigned int offset = x + y * width;
				eP[offset] = sumP;
				float t = (float)pInData[offset * pInImage->getBytesPerPixel()] + eP[offset];
				if(t > m_fThreshold)
				{
					eG[offset] = t - m_fThreshold * 2.0f;
					pOutData[offset * pOutImage->getBytesPerPixel()] = 255;
				}
				else
				{
					eG[offset] = t;
					pOutData[offset * pOutImage->getBytesPerPixel()] = 0;
				}
			}
		}
		delete [] eG;
		delete [] eP;
		return pOutImage;
	}

}
