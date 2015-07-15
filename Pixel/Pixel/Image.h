
#ifndef Image_h
#define Image_h

#include <Pixel\CompileSettings.h>
#include <Pixel\ReferenceCounter.h>
#include <string>

namespace Pixel
{

	class PIXEL_API Image : public ReferenceCounter
	{
	public:
		//constructor
		Image();

		//release image data memory
		void clear();

		//loads image from file
		bool load(const std::string& szFilename);

		//saves image to file
		bool save(const std::string& szFilename) const;

		//sets image size
		void setSize(unsigned int width, unsigned int height, unsigned int bytesPerPixel);

		//gets image data
		unsigned char* getData() const { return m_Data; }

		//gets image width
		unsigned int getWidth() const { return m_Width; }

		//gets image height
		unsigned int getHeight() const { return m_Height; }

		//gets image bytes per pixel
		unsigned int getBytesPerPixel() const { return m_BytesPerPixel; }
	protected:
		//destructor
		virtual ~Image();
	protected:
		unsigned char* m_Data; //> image data
		unsigned int m_Width; //> image width
		unsigned int m_Height; //> image height
		unsigned int m_BytesPerPixel; //> image bytes per pixel
	};

}

#endif //Image_h
