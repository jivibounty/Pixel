
#ifndef Addition_h
#define Addition_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Addition : public IImageOperation
	{
	public:
		//constructor
		Addition(Image* pImage);

		//sets base image
		void setBaseImage(Image* pImage);

		//gets base image
		Image* getBaseImage() const;

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Addition() {}
	protected:
		Image* m_pBaseImage;
	};

}

#endif //Addition_h
