
#include <Pixel\SobelEdgeDetection.h>
#include <Pixel\Image.h>
#include <Math.h>

namespace Pixel
{
	SobelEdgeDetection::SobelEdgeDetection(float threshold)
		: m_fThreshold(threshold)
	{
	}

	void SobelEdgeDetection::setThreshold(float threshold)
	{
		m_fThreshold = threshold;
	}

	Image* SobelEdgeDetection::process(Image* pInImage)
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

		int sobelX[3][3] = {
			{ -1, 0, 1 },
			{ -2, 0, 2 },
			{ -1, 0, 1 }
		};

		int sobelY[3][3] = {
			{ -1, -2, -1 },
			{ 0, 0, 0 },
			{ 1, 2, 1 }
		};

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				float gX = 0.0f;
				float gY = 0.0f;
				for(int i = -1; i <= 1; ++i)
				{
					for(int j = -1; j <= 1; ++j)
					{
						int xx = x + i;
						if(xx < 0)
						{
							xx = 0;
						}
						else if(xx >= width)
						{
							xx = width - 1;
						}
						int yy = y + j;
						if(yy < 0)
						{
							yy = 0;
						}
						else if(yy >= height)
						{
							yy = height - 1;
						}
						int offsetxy = xx + yy * width;
						gX += (sobelX[i][j] * pInData[offsetxy]);
						gX += (sobelX[i][j] * pInData[offsetxy]);
					}
				}
				unsigned int g = (unsigned int)sqrt((float)(gX * gX + gY * gY));
				unsigned int offset = x + y * width;
				if(g > m_fThreshold)
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
