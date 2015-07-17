
#include <Pixel\Addition.h>
#include <Pixel\Image.h>

namespace Pixel
{
	Addition::Addition(Image* pImage)
	{
		m_pBaseImage = NULL;
		SAFE_ASSIGN(m_pBaseImage, pImage);
	}

	void Addition::setBaseImage(Image* pImage)
	{
		SAFE_ASSIGN(m_pBaseImage, pImage);
	}

	Image* Addition::getBaseImage() const
	{
		return m_pBaseImage;
	}

	Image* Addition::process(Image* pInImage)
	{
		//check if input is null
		if(m_pBaseImage == NULL || pInImage == NULL)
		{
			return NULL;
		}

		//create output image
		Image* pOutImage = new Image;
		pOutImage->addRef();

		//compute pixel width, height and bytesPerPixel as the greater one of the two images(the base image and the input image)
		unsigned int width1 = m_pBaseImage->getWidth();
		unsigned int height1 = m_pBaseImage->getHeight();
		unsigned int bytesPerPixel1 = m_pBaseImage->getBytesPerPixel();
		unsigned int width2 = pInImage->getWidth();
		unsigned int height2 = pInImage->getHeight();
		unsigned int bytesPerPixel2 = pInImage->getBytesPerPixel();
		
		unsigned int width = width1 > width2 ? width1 : width2;
		unsigned int height = height1 > height2 ? height1 : height2;
		unsigned int bytesPerPixel = bytesPerPixel1 > bytesPerPixel2 ? bytesPerPixel1 : bytesPerPixel2;
		
		//limit bytes per pixel to 4
		if(bytesPerPixel > 4)
		{
			bytesPerPixel = 4;
		}

		//initialize output image data
		pOutImage->setSize(width, height, bytesPerPixel);
		unsigned char* pBaseData = m_pBaseImage->getData();

		//get input image data
		unsigned char* pInData = pInImage->getData();
		//get output image data
		unsigned char* pOutData = pOutImage->getData();

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				//get pixel values from base image
				unsigned char val1[4] = {0, 0, 0, 0};
				//ensure the pixel is within the bounds of the base image
				if(x < width1 && y < height1)
				{
					unsigned int offset1 = (x + y * width1) * m_pBaseImage->getBytesPerPixel();
					for(unsigned int n = 0; n < m_pBaseImage->getBytesPerPixel(); ++n)
					{
						val1[n] = pBaseData[offset1 + n];
					}
				}
				//get pixel values from input image
				unsigned char val2[4] = {0, 0, 0, 0};
				//ensure the pixel is within the bounds of the input image
				if(x < width2 && y < height2)
				{
					unsigned int offset2 = (x + y * width2) * pInImage->getBytesPerPixel();
					for(unsigned int n = 0; n < pInImage->getBytesPerPixel(); ++n)
					{
						val2[n] = pInData[offset2 + n];
					}
				}
				//add the pixel values and set the result as the output image pixel
				unsigned int offset = x + y * width;
				for(unsigned int n = 0; n < pOutImage->getBytesPerPixel(); ++n)
				{
					int val = val1[n] + val2[n];
					if(val > 255)
					{
						val = 255;
					}
					pOutData[offset + n] = val;
				}
			}
		}
		return pOutImage;
	}

}
