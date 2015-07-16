
#ifndef Cut_h
#define Cut_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Cut : public IImageOperation
	{
	public:
		//constructor
		Cut(int x1, int y1, int x2, int y2);

		//sets cut bound
		void setCutBound(int x1, int y1, int x2, int y2);

		//gets X1
		int getX1() const { return m_X1; }

		//gets Y1
		int getY1() const { return m_Y1; }

		//gets X2
		int getX2() const { return m_X2; }

		//gets Y2
		int getY2() const { return m_Y2; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Cut() {}
	protected:
		int m_X1;
		int m_Y1;
		int m_X2;
		int m_Y2;
	};

}

#endif //Cut_h
