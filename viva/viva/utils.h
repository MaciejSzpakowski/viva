#pragma once

namespace viva
{
	namespace util
	{
        // Read file contents to ASCII string.
        // filepath: path to file
		std::string ReadFileToString(const std::wstring& filepath);

        // Read file to byte vector.
        // dst: destination vector
        void ReadFileToBytes(const std::wstring& filepath, vector<byte>& dst);

        Size ReadImageToPixels(const std::wstring& filepath, vector<Pixel>& dst);
	}
}