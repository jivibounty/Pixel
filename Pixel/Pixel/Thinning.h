
#ifndef Thinning_h
#define Thinning_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Thinning : public IImageOperation
	{
	public:
		//constructor
		Thinning() {}

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Thinning() {}

	private:
		//returns true if 01 sequence is satisfied
		bool isZeroOneSequenceSatisfied(unsigned char p[9]);

		//gets sum of input values
		int getNeighbourSum(unsigned char p[9]);

		//returns true if neighbour or input sum is satisfied
		bool isNeighbourSumSatisfied(unsigned char p[9]);

		//get the neighbour pixel values from image
		void getNeighbours(Image* pImage, int x, int y, unsigned char p[9]);
	};

}

#endif //Thinning_h
