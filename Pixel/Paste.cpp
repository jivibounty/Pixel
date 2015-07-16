
#include <Pixel\Paste.h>
#include <Pixel\Image.h>
#include <Pixel\Utils.h>
#include <string.h>

namespace Pixel
{
	Paste::Paste(unsigned int xOffset, unsigned int yOffset, Image* pImage)
		: m_XOffset(xOffset)
		, m_YOffset(yOffset)
	{
		m_pPasteImage = NULL;
		SAFE_ASSIGN(m_pPasteImage, pImage);
	}

	void Paste::setPasteImage(Image* pImage)
	{
		SAFE_ASSIGN(m_pPasteImage, pImage);
	}

	Image* Paste::getPasteImage() const
	{
		return m_pPasteImage;
	}

	void Paste::setOffset(int xOffset, int yOffset)
	{
		m_XOffset = xOffset;
		m_YOffset = yOffset;
	}

	Image* Paste::process(Image* pInImage)
	{
		//check if input is null
		if(m_pPasteImage == NULL || pInImage == NULL)
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
		unsigned char* pPasteData = m_pPasteImage->getData();
		unsigned int size = width * height * pInImage->getBytesPerPixel();
		memcpy(pOutData, pInData, sizeof(unsigned char) * size);
		unsigned int minBytesPerPixel = min(pOutImage->getBytesPerPixel(), m_pPasteImage->getBytesPerPixel());
		unsigned int pasteWidth = m_pPasteImage->getWidth();
		unsigned int pasteHeight = m_pPasteImage->getHeight();

		for(unsigned int x = 0; x < pasteWidth; ++x)
		{
			for(unsigned int y = 0; y < pasteHeight; ++y)
			{
				int ax = (int)x + m_XOffset;
				int ay = (int)y + m_YOffset;
				
				if(ax < 0 || ax >= (int)width || ay < 0 || ay >= (int)height)
				{
					continue;
				}
				unsigned int offsetPaste = x + y * pasteWidth;
				unsigned int offsetOut = ax + ay * width;
				for(unsigned int n = 0; n < minBytesPerPixel; ++n)
				{
					pOutData[offsetOut + n] = pPasteData[offsetPaste + n];
				}
			}
		}
		return pOutImage;
	}

}
