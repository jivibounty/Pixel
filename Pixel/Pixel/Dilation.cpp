
#include <Pixel\Dilation.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{

	Image* Dilation::process(Image* pInImage)
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
		if(numPixels == 0 || pInImage->getBytesPerPixel() == 0)
		{
			return pOutImage;
		}
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();
		unsigned int size = width * height * pInImage->getBytesPerPixel();
		memcpy(pOutData, pInData, sizeof(unsigned char) * size);
		//*
		int mask[9]={
			1,1,1,
			1,1,1,
			1,1,1
		};
		//*/
		/*
		int mask[9]={
		0,1,0,
		1,1,1,
		0,1,0
		};
		//*/

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				unsigned int offset=(x + y * width) * pOutImage->getBytesPerPixel();
				if(pOutData[offset] > 0)
				{
					int a;
					int b;
					int j;
					int k;
					for(a = 0, j = x - 1; j <= ((int)x + 1); ++j, ++a)
					{
						for(b = 0, k = y - 1; k <= ((int)y + 1); ++k, ++b)
						{
							unsigned int offsetMask = b * 3 + a;
							if(!mask[offsetMask] || j < 0 || j >= (int)width || k < 0 || k >= (int)height)
							{
								continue;
							}
							unsigned int offsetJK = (k * width + j) * pOutImage->getBytesPerPixel();
							pOutData[offsetJK] = 0;
						}
					}
				}
			}
		}
		return pOutImage;
	}

}
