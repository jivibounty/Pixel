
#ifndef Subtraction_h
#define Subtraction_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Subtraction : public IImageOperation
	{
	public:
		//constructor
		Subtraction(Image* pImage);

		//sets base image
		void setBaseImage(Image* pImage);

		//gets base image
		Image* getBaseImage() const;

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Subtraction() {}
	protected:
		Image* m_pBaseImage;
	};

}

#endif //Subtraction_h
