
#include <Pixel\Thinning.h>
#include <Pixel\Image.h>
#include <string.h>

namespace Pixel
{

	Image* Thinning::process(Image* pInImage)
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
		pOutImage->setSize(width, height, pInImage->getBytesPerPixel());
		unsigned char* pInData = pInImage->getData();
		unsigned char* pOutData = pOutImage->getData();

		unsigned char P[9];
		int no_deleted=100; //initialize to any value greater than zero
		int *pDeleter=0;
		unsigned int size = width * height;
		pDeleter=new int[size];
		unsigned int bytesPerPixel = pOutImage->getBytesPerPixel();

		for(unsigned int x = 1; x < width - 1; ++x)
		{
			for(unsigned int y = 1; y < height - 1; ++y)
			{
				pOutData[(x + y * width) * bytesPerPixel] = pInData[(x + y * width) * bytesPerPixel] / 255;
			}
		}

		while(no_deleted>0)
		{
			no_deleted=0;
			memset(pDeleter, 0, sizeof(int) * size);

			//first sub iteration
			for(unsigned int x = 1; x < width - 1; ++x)
			{
				for(unsigned int y = 1; y < height - 1; ++y)
				{
					unsigned int offsetb = (x + y * width);
					unsigned int offset = offsetb * bytesPerPixel;
					if(pInData[offset])
					{
						getNeighbours(pOutImage, x, y, P);
						if(isNeighbourSumSatisfied(P))
						{
							if(isZeroOneSequenceSatisfied(P))
							{
								if (!(P[1] && P[3] && P[5]))
								{
									if(!(P[3] && P[5] && P[7]))
									{
										pDeleter[offsetb] = 1;
										no_deleted++;
									}
								}
							}
						}
					}
				}
			}
			for(unsigned int x = 1; x < width - 1; ++x)
			{
				for(unsigned int y = 1; y < height - 1; ++y)
				{
					unsigned int offsetb = (x + y * width);
					unsigned int offset = offsetb * bytesPerPixel;
					int val = pInData[offset] - pDeleter[offsetb];
					if(val < 0)
					{
						pInData[offset] = 0;
					}
					else
					{
						pInData[offset] = val;
					}
				}
			}

			memset(pDeleter, 0, sizeof(int) * size);

			//second sub iteration
			for(unsigned int x = 1; x < width - 1; ++x)
			{
				for(unsigned int y = 1; y < height - 1; ++y)
				{
					unsigned int offsetb = (x + y * width);
					unsigned int offset = offsetb * bytesPerPixel;
					if(pInData[offset])
					{
						getNeighbours(pOutImage, x, y, P);
						if(isNeighbourSumSatisfied(P))
						{
							if(isZeroOneSequenceSatisfied(P))
							{
								if (!(P[1] && P[3] && P[7]))
								{
									if(!(P[1] && P[5] && P[7]))
									{
										pDeleter[offsetb] = 1;
										no_deleted++;
									}
								}
							}
						}
					}
				}
			}
			for(unsigned int x = 1; x < width - 1; ++x)
			{
				for(unsigned int y =1 ; y < height - 1; ++y)
				{
					unsigned int offsetb = (x + y * width);
					unsigned int offset = offsetb * bytesPerPixel;
					int val = pInData[offset] - pDeleter[offsetb];
					if(val < 0)
					{
						pInData[offset] = 0;
					}
					else
					{
						pInData[offset] = val;
					}
				}
			}	
		}

		for(unsigned int x = 1; x < width - 1; ++x)
		{
			for(unsigned int y = 1; y < height - 1; ++y)
			{
				unsigned int offset = (x + y * width) * bytesPerPixel;
				pInData[offset] = pInData[offset] * 255;
			}
		}
		if(pDeleter)
		{
			delete [] pDeleter;
		}

		return pOutImage;
	}

	bool Thinning::isZeroOneSequenceSatisfied(unsigned char p[9])
	{
		int A = 0;
		if(!p[1]&&p[2]) A++;
		if(!p[2]&&p[3]) A++;
		if(!p[3]&&p[4]) A++;
		if(!p[4]&&p[5]) A++;
		if(!p[5]&&p[6]) A++;
		if(!p[6]&&p[7]) A++;
		if(!p[7]&&p[8]) A++;
		if(!p[8]&&p[1]) A++;
		if(A==1)return true;
		else return false;
	}

	int Thinning::getNeighbourSum(unsigned char p[9])
	{
		return p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8];
	}

	bool Thinning::isNeighbourSumSatisfied(unsigned char p[9])
	{
		int B= p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8];
		if(B>=2&&B<=6) return true;
		else return false;
	}

	void Thinning::getNeighbours(Image* pImage, int x, int y, unsigned char p[9])
	{
		if(pImage == NULL)
		{
			return;
		}

		unsigned char* pData = pImage->getData();
		unsigned int width = pImage->getWidth();
		unsigned int bytesPerPixel = pImage->getBytesPerPixel();

		p[0]=pData[(y*width+x)*bytesPerPixel];
		p[1]=pData[((y-1)*width+x)*bytesPerPixel];
		p[2]=pData[((y-1)*width+(x+1))*bytesPerPixel];
		p[3]=pData[(y*width+(x+1))*bytesPerPixel];
		p[4]=pData[((y+1)*width+(x+1))*bytesPerPixel];
		p[5]=pData[((y+1)*width+x)*bytesPerPixel];
		p[6]=pData[((y+1)*width+(x-1))*bytesPerPixel];
		p[7]=pData[(y*width+(x-1))*bytesPerPixel];
		p[8]=pData[((y-1)*width+(x-1))*bytesPerPixel];
	}

}
