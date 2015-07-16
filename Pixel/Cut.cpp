
#include <Pixel\Cut.h>
#include <Pixel\Image.h>

namespace Pixel
{
	Cut::Cut(int x1, int y1, int x2, int y2)
		: m_X1(x1)
		, m_Y1(y1)
		, m_X2(x2)
		, m_Y2(y2)
	{
	}

	void Cut::setCutBound(int x1, int y1, int x2, int y2)
	{
		m_X1 = x1;
		m_Y1 = y1;
		m_X2 = x2;
		m_Y2 = y2;
	}

	Image* Cut::process(Image* pInImage)
	{
		//check if input is null
		if(pInImage == NULL || m_X1 >= m_X2 || m_Y1 >= m_Y2)
		{
			return NULL;
		}

		//create output image
		Image* pOutImage = new Image;
		pOutImage->addRef();

		//compute number of pixels
		unsigned int width = m_X2 - m_X1;
		unsigned int height = m_Y2 - m_Y1;
		unsigned int numPixels = width * height;
		if(numPixels == 0 || pInImage->getBytesPerPixel() == 0)
		{
			return pOutImage;
		}
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();
		unsigned int inWidth = pInImage->getWidth();
		unsigned int inHeight = pInImage->getHeight();

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				int ax = (int)x + m_X1;
				int ay = (int)y + m_Y1;
				if(ax < 0 || ax >= (int)inWidth || ay < 0 || ay >= (int)inHeight)
				{
					continue;
				}
				unsigned int offset = x + y * width;
				unsigned int offsetIn = ax + ay * inWidth;
				for(unsigned int n = 0; n < pOutImage->getBytesPerPixel(); ++n)
				{
					pOutData[offset + n] = pInData[offsetIn + n];
				}
			}
		}
		return pOutImage;
	}

}
