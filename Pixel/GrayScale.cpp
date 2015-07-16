
#include <Pixel\GrayScale.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{

	Image* GrayScale::process(Image* pInImage)
	{
		//check if input is null
		if(pInImage == NULL)
		{
			return NULL;
		}
		//return null if image does not contain an rgb/rgba channel
		if(pInImage->getBytesPerPixel() < 3)
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
				float fGrayScale = 0.21f * (float)pInData[offset * pInImage->getBytesPerPixel()]
				+ 0.72f * (float)pInData[offset * pInImage->getBytesPerPixel() + 1]
				+ 0.07f * (float)pInData[offset * pInImage->getBytesPerPixel() + 2];
				if(offset > 255.0f)
				{
					offset = 255.0f;
				}
				pOutData[offset * pOutImage->getBytesPerPixel()] = (unsigned char)fGrayScale;
			}
		}
		return pOutImage;
	}

}
