
#ifndef Difference_h
#define Difference_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Difference : public IImageOperation
	{
	public:
		//constructor
		Difference(Image* pImage);

		//sets base image
		void setBaseImage(Image* pImage);

		//gets base image
		Image* getBaseImage() const;

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Difference() {}
	protected:
		Image* m_pBaseImage;
	};

}

#endif //Difference_h
