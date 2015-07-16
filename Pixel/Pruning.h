
#ifndef Pruning_h
#define Pruning_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Pruning : public IImageOperation
	{
	public:
		//constructor
		Pruning(unsigned int numIterations);

		//sets number of pruning iterations
		void setNumberOfIterations(unsigned int numIterations);

		//gets number of pruning iterations
		unsigned int getNumberOfIterations() const { return m_NumIterations; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Pruning() {}

	private:

		//gets sum of input values
		int getNeighbourSum(unsigned char p[9]);

		//get the neighbour pixel values from image as 0 for 0 or 1 for 255.
		void getNeighboursAsValuesZeroOrOne(Image* pImage, int x, int y, unsigned char p[9]);
	protected:
		unsigned int m_NumIterations;
	};

}

#endif //Pruning_h
