
#include <Pixel\Invert.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{

	Image* Invert::process(Image* pInImage)
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
		for(unsigned int n = 0; n < size; ++n)
		{
			pOutData[n] = 255 - pInData[n];
		}
		return pOutImage;
	}

}
