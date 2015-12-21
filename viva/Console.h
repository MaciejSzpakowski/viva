#pragma once

namespace viva
{
	class Console
	{
	protected:
	public:

		// open a new console
		virtual void Open() = 0;

		// close the console
		virtual void Close() = 0;

		// write something with line break at the end
		virtual void WriteLine(std::wstring& str) = 0;

		// write something
		virtual void Write(std::wstring& str) = 0;

		// get something from user until enter
		virtual wstring ReadLine() = 0;
	};
}