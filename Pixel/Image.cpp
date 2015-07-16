
#include <Pixel\Image.h>
#include <Pixel\Utils.h>
#include <string.h>
#include <FreeImage.h>


#define RED		0x0
#define GREEN	0x1
#define BLUE	0x2
#define ALPHA	0x3


namespace Pixel
{

	Image::Image()
		: m_Data(NULL)
		, m_Width(0)
		, m_Height(0)
		, m_BytesPerPixel(0)
	{
	}

	Image::~Image()
	{
		clear();
	}

	void Image::clear()
	{
		SAFE_DELETE_ARRAY(m_Data);
		m_Width = 0;
		m_Height = 0;
		m_BytesPerPixel = 0;
	}

	bool Image::load(const std::string& szFilename)
	{
		std::string szProcessedFilename = szFilename;
		// find the buffer format
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(szProcessedFilename.c_str(), 0);

		if (fif == FIF_UNKNOWN)
		{
			if((szFilename[0] == '/' || szFilename[0] == '\\') && !szFilename.empty())
			{
				szProcessedFilename = szFilename.substr(1);
				fif = FreeImage_GetFileType(szProcessedFilename.c_str(), 0);
				if (fif == FIF_UNKNOWN)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		// load from the file handle
		FIBITMAP* dib = FreeImage_Load(fif, szProcessedFilename.c_str(), 0);

		if (!dib)
		{
			return false;
		}

		//copy to m_Data
		clear();
		m_Width = FreeImage_GetWidth(dib);
		m_Height = FreeImage_GetHeight(dib);
		m_BytesPerPixel = FreeImage_GetBPP(dib) / 8;
		unsigned int size = m_Width * m_Height * m_BytesPerPixel;
		m_Data = new unsigned char[size];
		if (m_Data == NULL)
		{
			return false;
		}

		FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);

		// test pixel access avoiding scanline calculations
		// to speed-up the image processing
		if (image_type == FIT_BITMAP)
		{
			if (FreeImage_GetBPP(dib) == 24)
			{
				BYTE* pixel = (BYTE*)FreeImage_GetBits(dib);

				for (unsigned int x = 0; x < m_Width; x++)
				{
					for (unsigned int y = 0; y < m_Height; y++)
					{
						RGBQUAD value;
						FreeImage_GetPixelColor(dib, x, y, &value);
						unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
						m_Data[offset + RED] = (unsigned char)value.rgbRed;
						m_Data[offset + GREEN] = (unsigned char)value.rgbGreen;
						m_Data[offset + BLUE] = (unsigned char)value.rgbBlue;
					}
				}
			}
			else if (FreeImage_GetBPP(dib) == 32)
			{
				BYTE* pixel = (BYTE*)FreeImage_GetBits(dib);

				for (unsigned int x = 0; x < m_Width; x++)
				{
					for (unsigned int y = 0; y < m_Height; y++)
					{
						RGBQUAD value;
						FreeImage_GetPixelColor(dib, x, y, &value);
						unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
						m_Data[offset + RED] = (unsigned char)value.rgbRed;
						m_Data[offset + GREEN] = (unsigned char)value.rgbGreen;
						m_Data[offset + BLUE] = (unsigned char)value.rgbBlue;
						m_Data[offset + ALPHA] = (unsigned char)value.rgbReserved;
					}
				}
			}
			else
			{
				memcpy(m_Data, FreeImage_GetBits(dib), size * sizeof(unsigned char));
			}
		}
		else if (image_type == FIT_RGBF)
		{
			FIRGBF* pixel = (FIRGBF*)FreeImage_GetBits(dib);

			for (unsigned int x = 0; x < m_Width; x++)
			{
				for (unsigned int y = 0; y < m_Height; y++)
				{
					unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
					m_Data[offset + RED] = (unsigned char)pixel[offset].red;
					m_Data[offset + GREEN] = (unsigned char)pixel[offset].green;
					m_Data[offset + BLUE] = (unsigned char)pixel[offset].blue;
				}
			}
		}
		else if (image_type == FIT_RGB16)
		{
			FIRGB16* pixel = (FIRGB16*)FreeImage_GetBits(dib);

			for (unsigned int x = 0; x < m_Width; x++)
			{
				for (unsigned int y = 0; y < m_Height; y++)
				{
					unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
					m_Data[offset + RED] = (unsigned char)pixel[offset].red;
					m_Data[offset + GREEN] = (unsigned char)pixel[offset].green;
					m_Data[offset + BLUE] = (unsigned char)pixel[offset].blue;
				}
			}
		}
		else if (image_type == FIT_RGBAF)
		{
			FIRGBAF* pixel = (FIRGBAF*)FreeImage_GetBits(dib);

			for (unsigned int x = 0; x < m_Width; x++)
			{
				for (unsigned int y = 0; y < m_Height; y++)
				{
					unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
					m_Data[offset + RED] = (unsigned char)pixel[offset].red;
					m_Data[offset + GREEN] = (unsigned char)pixel[offset].green;
					m_Data[offset + BLUE] = (unsigned char)pixel[offset].blue;
					m_Data[offset + ALPHA] = (unsigned char)pixel[offset].alpha;
				}
			}
		}
		else if (image_type == FIT_RGBA16)
		{
			FIRGBA16* pixel = (FIRGBA16*)FreeImage_GetBits(dib);

			for (unsigned int x = 0; x < m_Width; x++)
			{
				for (unsigned int y = 0; y < m_Height; y++)
				{
					unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
					m_Data[offset + RED] = (unsigned char)pixel[offset].red;
					m_Data[offset + GREEN] = (unsigned char)pixel[offset].green;
					m_Data[offset + BLUE] = (unsigned char)pixel[offset].blue;
					m_Data[offset + ALPHA] = (unsigned char)pixel[offset].alpha;
				}
			}
		}

		FreeImage_Unload(dib);
		return true;
	}

	bool Image::save(const std::string& szFilename) const
	{
		FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(szFilename.c_str());

		if (fif == FIF_UNKNOWN)
		{
			return false;
		}

		FREE_IMAGE_TYPE fit = FIT_BITMAP;
		if (sizeof(unsigned char) > 1)
		{
			if (m_BytesPerPixel == 1)
			{
				fit = FIT_FLOAT;
			}
			if (m_BytesPerPixel == 3)
			{
				fit = FIT_RGBF;
			}
			else if (m_BytesPerPixel == 4)
			{
				fit = FIT_RGBAF;
			}
		}

		FIBITMAP* dib = FreeImage_AllocateT(fit, m_Width, m_Height, m_BytesPerPixel * sizeof(unsigned char)* 8);

		if (!dib)
		{
			return false;
		}

		unsigned int size = m_Width * m_Height * m_BytesPerPixel;

		FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
		unsigned int pitch = FreeImage_GetPitch(dib);

		// test pixel access avoiding scanline calculations
		// to speed-up the image processing
		if (image_type == FIT_BITMAP)
		{
			if (FreeImage_GetBPP(dib) == 24)
			{
				BYTE* pixel = (BYTE*)FreeImage_GetBits(dib);

				for (unsigned int x = 0; x < m_Width; x++)
				{
					for (unsigned int y = 0; y < m_Height; y++)
					{
						unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
						pixel[offset + FI_RGBA_RED] = (BYTE)m_Data[offset];
						pixel[offset + FI_RGBA_GREEN] = (BYTE)m_Data[offset + 1];
						pixel[offset + FI_RGBA_BLUE] = (BYTE)m_Data[offset + 2];
					}
				}
			}
			else if (FreeImage_GetBPP(dib) == 32)
			{
				BYTE* pixel = (BYTE*)FreeImage_GetBits(dib);

				for (unsigned int x = 0; x < m_Width; x++)
				{
					for (unsigned int y = 0; y < m_Height; y++)
					{
						unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
						pixel[offset + FI_RGBA_RED] = (BYTE)m_Data[offset];
						pixel[offset + FI_RGBA_GREEN] = (BYTE)m_Data[offset + 1];
						pixel[offset + FI_RGBA_BLUE] = (BYTE)m_Data[offset + 2];
						pixel[offset + FI_RGBA_ALPHA] = (BYTE)m_Data[offset + 3];
					}
				}
			}
			else
			{
				memcpy(FreeImage_GetBits(dib), m_Data, size * sizeof(unsigned char));
			}
		}
		else if (image_type == FIT_RGBF)
		{

			FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
			unsigned int pitch = FreeImage_GetPitch(dib);

			FIRGBF* pixel = (FIRGBF*)FreeImage_GetBits(dib);

			for (unsigned int x = 0; x < m_Width; x++)
			{
				for (unsigned int y = 0; y < m_Height; y++)
				{
					unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
					pixel[offset].red = (float)m_Data[offset];
					pixel[offset].green = (float)m_Data[offset + 1];
					pixel[offset].blue = (float)m_Data[offset + 2];
				}
			}
		}
		else if (image_type == FIT_RGBAF)
		{
			FIRGBAF* pixel = (FIRGBAF*)FreeImage_GetBits(dib);

			for (unsigned int x = 0; x < m_Width; x++)
			{
				for (unsigned int y = 0; y < m_Height; y++)
				{
					unsigned int offset = (x + y * m_Width) * m_BytesPerPixel;
					pixel[offset].red = (float)m_Data[offset];
					pixel[offset].green = (float)m_Data[offset + 1];
					pixel[offset].blue = (float)m_Data[offset + 2];
					pixel[offset].alpha = (float)m_Data[offset + 3];
				}
			}
		}

		bool success = (FreeImage_Save(fif, dib, szFilename.c_str(), 0) == TRUE);
		FreeImage_Unload(dib);
		return success;
	}

	void Image::setSize(unsigned int width, unsigned int height, unsigned int bytesPerPixel)
	{
		clear();
		unsigned int size = width * height * bytesPerPixel;
		if(size == 0)
		{
			return;
		}
		m_Width = width;
		m_Height = height;
		m_BytesPerPixel = bytesPerPixel;
		m_Data = new unsigned char[size];
		memset(m_Data, 0, sizeof(unsigned char) * size);
	}


}
