#include "Win32.h"

namespace viva
{
	Win32Console::Win32Console()
	{
		opened = false;		
	}

	void Win32Console::Open()
	{
		if (opened)
			throw std::runtime_error("Win32Console::Open() already opened");

		opened = true;
		AllocConsole();
		SetConsoleTitle(L"Console");
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
	}

	void Win32Console::Close()
	{
		if (!opened)
			throw std::runtime_error("Win32Console::Close() already closed");

		opened = false;
		FreeConsole();
	}

	void Win32Console::WriteLine(std::wstring& str)
	{
		if (!opened)
			throw std::runtime_error("Win32Console::WriteLine() console not opened");

		std::wcout << str << std::endl;
	}

	void Win32Console::Write(std::wstring& str)
	{
		if (!opened)
			throw std::runtime_error("Win32Console::Write() console not opened");

		std::wcout << str;
	}

	wstring Win32Console::ReadLine()
	{
		if (!opened)
			throw std::runtime_error("Win32Console::ReadLine() console not opened");

		std::string str;
		std::getline(std::cin, str);

		return wstring(str.begin(), str.end());
	}
}