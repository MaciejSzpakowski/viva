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
	}
}