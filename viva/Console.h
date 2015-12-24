#pragma once

namespace viva
{
	class Console
	{
	protected:
		bool opened;
	public:
		Console();

		// open a new console
		void Open();

		// close the console
		void Close();

		// write something with line break at the end
		void WriteLine(std::wstring& str);

		// write something
		void Write(std::wstring& str);

		// get something from user until enter
		wstring ReadLine();
	};
}