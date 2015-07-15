
#ifndef Paste_h
#define Paste_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Paste : public IImageOperation
	{
	public:
		//constructor
		Paste(unsigned int xOffset, unsigned int yOffset, Image* pImage);

		//sets paste image
		void setPasteImage(Image* pImage);

		//gets paste image
		Image* getPasteImage() const;

		//sets paste offset
		void setOffset(int xOffset, int yOffset);

		//gets x offset
		int getXOffset() const { return m_XOffset; }

		//gets y offset
		int getYOffset() const { return m_YOffset; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Paste() {}
	protected:
		Image* m_pPasteImage;
		int m_XOffset;
		int m_YOffset;
	};

}

#endif //Paste_h
