
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

		//compute number of pixels
		unsigned int width1 = m_pBaseImage->getWidth();
		unsigned int height1 = m_pBaseImage->getHeight();
		unsigned int bytesPerPixel1 = m_pBaseImage->getBytesPerPixel();
		unsigned int width2 = pInImage->getWidth();
		unsigned int height2 = pInImage->getHeight();
		unsigned int bytesPerPixel2 = pInImage->getBytesPerPixel();
		
		unsigned int width = width1 > width2 ? width1 : width2;
		unsigned int height = height1 > height2 ? height1 : height2;
		unsigned int bytesPerPixel = bytesPerPixel1 > bytesPerPixel2 ? bytesPerPixel1 : bytesPerPixel2;
		if(bytesPerPixel > 4)
		{
			bytesPerPixel = 4;
		}

		pOutImage->setSize(width, height, bytesPerPixel);
		unsigned char* pBaseData = m_pBaseImage->getData();
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				unsigned char val1[4] = {0, 0, 0, 0};
				if(x < width1 && y < height1)
				{
					unsigned int offset1 = (x + y * width1) * m_pBaseImage->getBytesPerPixel();
					for(unsigned int n = 0; n < m_pBaseImage->getBytesPerPixel(); ++n)
					{
						val1[n] = pBaseData[offset1 + n];
					}
				}
				unsigned char val2[4] = {0, 0, 0, 0};
				if(x < width2 && y < height2)
				{
					unsigned int offset2 = (x + y * width2) * pInImage->getBytesPerPixel();
					for(unsigned int n = 0; n < pInImage->getBytesPerPixel(); ++n)
					{
						val2[n] = pInData[offset2 + n];
					}
				}
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
