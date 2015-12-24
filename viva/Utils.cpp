#include "Viva.h"

namespace viva
{
	namespace Utils
	{
		wstring ReadFileToString(const wstring& filepath)
		{
			std::wifstream file(filepath);
			return wstring((std::istreambuf_iterator<wchar_t>(file)),
				std::istreambuf_iterator<wchar_t>());
		}

		std::string ReadFileToString(const std::string& filepath)
		{
			std::ifstream file(filepath);
			return std::string((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
		}
	}
}