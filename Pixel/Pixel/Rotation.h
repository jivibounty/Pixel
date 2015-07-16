
#ifndef Rotation_h
#define Rotation_h

#include <Pixel\CompileSettings.h>
#include <Pixel\IImageOperation.h>

namespace Pixel
{

	class  Image;

	class PIXEL_API Rotation : public IImageOperation
	{
	public:
		//constructor
		Rotation(float fAngle, int centerX = 0, int centerY = 0);

		//sets angle of rotation
		void setAngle(float fAngle);

		//gets angle of rotation
		float getAngle() const { return m_fAngle; }

		//sets center of rotation
		void setCenter(int centerX, int centerY);

		//gets center of rotation in the x axis
		int getCenterX() const { return m_CenterX; }

		//gets center of rotation in the y axis
		int getCenterY() const { return m_CenterY; }

		//processes the input image to return an output image
		virtual Image* process(Image* pInImage);
	protected:
		//destructor
		virtual ~Rotation() {}
	protected:
		float m_fAngle;
		int m_CenterX;
		int m_CenterY;
	};

}

#endif //Rotation_h
