#include <viva/viva.h>

namespace viva
{
	namespace util
	{
		std::string ReadFileToString(const std::wstring& filepath)
		{
			std::ifstream file(filepath);

            if (!file)
                throw viva::Error("ReadFileToString()", "could not open the file");

			return std::string((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
		}

        void ReadFileToBytes(const std::wstring& filepath, vector<byte>& dst)
        {
            std::ifstream file(filepath, std::ios::binary);

            if (!file)
                throw viva::Error("ReadFileToString()", "could not open the file");

            byte c;
            while (!file.eof())
            {
                c = file.get();
                dst.push_back(c);
            }
            dst.pop_back();
        }

        // this function has been provided by Wroclai from SO
        // http://stackoverflow.com/questions/7046270/loading-a-tga-file-and-using-it-with-opengl
        Size ReadTgaToPixels(const std::wstring& filepath, Array<Pixel>& dst)
        {
            Size size;
            std::ifstream file(filepath, std::ios::binary);
            int imageSize;
            int colorMode;
            byte imageTypeCode;
            byte bitCount;

            // Open the TGA file.
            if (!file)
                throw viva::Error("ReadTgaToPixels()", "could not open the file");

            // Read the two first bytes we don't need.
            file.get();
            file.get();

            // Which type of image gets stored in imageTypeCode.
            imageTypeCode = file.get();

            // For our purposes, the type code should be 2 (uncompressed RGB image)
            // or 3 (uncompressed black-and-white images).
            if (imageTypeCode != 2 && imageTypeCode != 3)
                throw viva::Error("ReadTgaToPixels()", "unsupported tga format");

            // Read 13 bytes of data we don't need.
            for (int i = 0; i < 9; i++)
                file.get();

            // Read the image's width and height
            size.Width = (float)(file.get() + (file.get() << 8));
            size.Height = (float)(file.get() + (file.get() << 8));

            // Read the bit depth.
            bitCount = file.get();

            // Read one byte of data we don't need.
            file.get();

            // Color mode -> 3 = BGR, 4 = BGRA.
            colorMode = bitCount / 8;
            imageSize = (int)(size.Height * size.Width);

            // Allocate memory for the image data.
            dst = Array<Pixel>((int)(size.Width * size.Height));

            // Read the image data.
            for (int i = 0; i < imageSize; i++)
            {
                byte b = (byte)file.get();
                byte g = (byte)file.get();
                byte r = (byte)file.get();
                if (colorMode == 3)
                    dst[i] = { r, g, b, 255 };
                else if (colorMode == 4)
                    dst[i] = { r, g, b, (byte)file.get() };
            }

            return size;
        }
	}
}