
#include <Pixel\Pruning.h>
#include <Pixel\Image.h>

namespace Pixel
{
	
	Pruning::Pruning(unsigned int numIterations)
		: m_NumIterations(numIterations)
	{
	}

	void Pruning::setNumberOfIterations(unsigned int numIterations)
	{
		m_NumIterations = numIterations;
	}

	Image* Pruning::process(Image* pInImage)
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
		unsigned int bytesPerPixel = pInImage->getBytesPerPixel();
		unsigned int numPixels = width * height;
		if(numPixels == 0)
		{
			return pOutImage;
		}
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();

		unsigned char P[9];
		for(unsigned int x = 1; x < width - 1; ++x)
		{
			for(unsigned int y = 1; y < height - 1; ++y)
			{
				unsigned int offset = (x + y * width) * bytesPerPixel;
				int val = pInData[offset];
				if(val)
				{
					getNeighboursAsValuesZeroOrOne(pInImage, x, y, P);
					int sum = getNeighbourSum(P);
					if(sum <= 1)
					{
						val = 0;
					}
				}
				pOutData[offset] = val;
			}
		}
		for(unsigned int a = 0; a < m_NumIterations; ++a)
		{
			for(unsigned int x = 1; x < width - 1; ++x)
			{
				for(unsigned int y = 1; y < height - 1; ++y)
				{
					unsigned int offset = (x + y * width) * bytesPerPixel;
					int val = pOutData[offset];
					if(val)
					{
						getNeighboursAsValuesZeroOrOne(pInImage, x, y, P);
						int sum = getNeighbourSum(P);
						if(sum <= 1)
						{
							val = 0;
						}
					}
					pOutData[offset] = val;
				}
			}
		}
		for(unsigned int x = 1; x < width - 1; ++x)
		{
			for(unsigned int y = 1; y < height - 1; ++y)
			{
				unsigned int offset = (x + y * width) * bytesPerPixel;
				int val = pOutData[offset];
				if(val)
				{
					getNeighboursAsValuesZeroOrOne(pInImage, x, y, P);
					int sum = getNeighbourSum(P);
					if(sum == 0)
					{
						val = 0;
					}
				}
				pOutData[offset] = val;
			}
		}
		return pOutImage;
	}

	int Pruning::getNeighbourSum(unsigned char P[9])
	{
		return P[1] + P[2] + P[3] + P[4] + P[5] + P[6] + P[7] + P[8];
	}

	void Pruning::getNeighboursAsValuesZeroOrOne(Image* pImage, int x, int y, unsigned char P[9])
	{
		if(pImage == NULL)
		{
			return;
		}

		unsigned char* pData = pImage->getData();
		unsigned int width = pImage->getWidth();
		unsigned int bytesPerPixel = pImage->getBytesPerPixel();

		P[0] = pData[(y * width + x) * bytesPerPixel] & 1;
		P[1] = pData[((y - 1) * width + x) * bytesPerPixel] & 1;
		P[2] = pData[((y - 1) * width + (x + 1)) * bytesPerPixel] & 1;
		P[3] = pData[(y * width + (x + 1)) * bytesPerPixel] & 1;
		P[4] = pData[((y + 1) * width + (x + 1)) * bytesPerPixel] & 1;
		P[5] = pData[((y + 1) * width + x) * bytesPerPixel] & 1;
		P[6] = pData[((y + 1) * width + (x - 1)) * bytesPerPixel] & 1;
		P[7] = pData[(y * width + (x - 1)) * bytesPerPixel] & 1;
		P[8] = pData[((y - 1) * width + (x - 1)) * bytesPerPixel] & 1;
	}

}
