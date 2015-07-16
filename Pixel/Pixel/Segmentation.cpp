
#include <Pixel\Segmentation.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{

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
		pOutImage->setSize(width, height, 1);
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{

			}
		}
		return pOutImage;
	}

}
