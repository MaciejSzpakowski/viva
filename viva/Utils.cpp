#include "viva.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace viva
{
    namespace util
    {
        // Read file contents to ASCII string.
        // filepath: path to file
        std::string ReadFileToStringA(const std::wstring& filepath)
        {
            std::ifstream file(filepath);

            if (!file)
                throw viva::Error("ReadFileToString()", "could not open the file");

            return std::string((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
        }

        // Read file to byte vector.
        // dst: destination vector
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

        // Reads image at 'filepath' to array of pixels
        // It's 3rd party library written in C, that's why raw array is used.
        // fileparth: filepath
        // dst: destination. This function creates a pointer to data and has to write it somewhere.
        Size ReadImageToPixels(const std::wstring& filepath, Pixel** dst)
        {
            std::string str(filepath.begin(), filepath.end());
            int x, y, n;
            const int components = 4; // components means how many elements from 'RGBA'
                                      // you want to return, I want 4 (RGBA) even in not all 4 are present
            byte* data = stbi_load(str.c_str(), &x, &y, &n, components);

            if (data == nullptr)
            {
                std::string msg = "could not open: " + std::string(filepath.begin(), filepath.end()) + " reason: ";
                msg += stbi_failure_reason();
                throw Error(__FUNCTION__, msg.c_str());
            }

            *dst = (Pixel*)data;

            return{ (float)x,(float)y };
        }

        // Returns true if 's' end with 'end'.
        // s: string where to look
        // end: substring thats should be at the end
        bool EndsWith(const wstring& s, const wstring& end)
        {
            if (s.length() < end.length())
                return false;

            return s.rfind(end) == (s.length() - end.length());
        }

        // Reads a tga file to raw array of pixels.
        // this function has been provided by Wroclai from SO
        // http://stackoverflow.com/questions/7046270/loading-a-tga-file-and-using-it-with-opengl
        // filepath: file path
        // dst: where to store the pixels
        Size ReadTgaToPixels(const std::wstring& filepath, vector<Pixel>& dst)
        {
            Size size;
            std::ifstream file(filepath, std::ios::binary);
            int imageSize;
            int colorMode;
            byte imageTypeCode;
            byte bitCount;

            // Open the TGA file.
            if (!file)
                throw viva::Error("ReadTgaToPixels()", L"could not open the file " + filepath);

            // Read the two first bytes we don't need.
            file.get();
            file.get();

            // Which type of image gets stored in imageTypeCode.
            imageTypeCode = file.get();

            // For our purposes, the type code should be 2 (uncompressed RGB image)
            // or 3 (uncompressed black-and-white images).
            if (imageTypeCode != 2 && imageTypeCode != 3)
                throw viva::Error("ReadTgaToPixels()", "unsupported tga format");

            // Read 9 bytes of data we don't need.
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
            dst.resize(size.Width * size.Height);

            // Read the image data.
            for (int i = 0; i < imageSize; i++)
            {
                byte b = (byte)file.get();
                byte g = (byte)file.get();
                byte r = (byte)file.get();
                if (colorMode == 3)
                    dst.at(i) = { r, g, b, 255 };
                else if (colorMode == 4)
                    dst.at(i) = { r, g, b, (byte)file.get() };
            }

            return size;
        }
    }
}