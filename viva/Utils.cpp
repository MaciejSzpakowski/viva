#include <viva/utils.h>
#include <viva/error.h>
#include <fstream>

namespace viva
{
	namespace utils
	{
		std::string ReadFileToString(const std::wstring& filepath)
		{
			std::ifstream file(filepath);

            if (!file)
                throw viva::Error("ReadFileToString()", "could not open the file");

			return std::string((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
		}
	}
}