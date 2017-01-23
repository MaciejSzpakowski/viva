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
    }
}