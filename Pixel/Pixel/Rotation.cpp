
#include <Pixel\Rotation.h>
#include <Pixel\Image.h>
#include <Pixel\Utils.h>
#include <Math.h>

namespace Pixel
{
	
	Rotation::Rotation(float fAngle, int centerX, int centerY)
		: m_fAngle(fAngle)
		, m_CenterX(centerX)
		, m_CenterY(centerY)
	{
	}

	void Rotation::setAngle(float fAngle)
	{
		m_fAngle = fAngle;
	}

	void Rotation::setCenter(int centerX, int centerY)
	{
		m_CenterX = centerX;
		m_CenterY = centerY;
	}

	Image* Rotation::process(Image* pInImage)
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
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();
		
		float angRadians = m_fAngle * PI_RAD;
		float cosAng = cos(angRadians);
		float sinAng = sin(angRadians);
		unsigned int bytesPerPixel = pInImage->getBytesPerPixel();

		for(unsigned int x = 0; x < width; ++x)
		{
			for(unsigned int y = 0; y < height; ++y)
			{
				int xRel = (int)x - m_CenterX;
				int yRel = (int)y - m_CenterY;
				float fX = (float)xRel * cosAng + (float)yRel * sinAng + (float)m_CenterX;
				float fY = -(float)xRel * sinAng + (float)yRel * cosAng + (float)m_CenterY;
				int xP = (int)fX;
				int yP = (int)fY;
				if(xP < 0 || xP >= (int)width || yP < 0 || yP >= (int)height)
				{
					continue;
				}
				float xInterp = fX - (float)xP;
				float yInterp = fY - (float)yP;
				unsigned int offset = (x + y * width) * pOutImage->getBytesPerPixel();
				unsigned int offsetP = (xP + yP * width) * pOutImage->getBytesPerPixel();
				for(int n = 0; n < (int)bytesPerPixel; ++n)
				{
					int valX = pInData[offset + n];
					int valY = valX;
					int xP2 = xP + 1;
					if(xP2 >= 0 || xP2 < (int)width)
					{
						valX = (int)((float)valX * (1.0f - xInterp) + (float)pInData[(xP2 + yP * width) * bytesPerPixel] * xInterp);
					}
					int yP2 = yP + 1;
					if(yP2 >= 0 || yP2 < (int)height)
					{
						valY = (int)((float)valY * (1.0f - yInterp) + (float)pInData[(xP + yP2 * width) * bytesPerPixel] * yInterp);
					}
					int val = (int)((float)(valX + valY) * 0.5f);
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
