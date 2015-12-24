#include "Viva.h"

namespace viva
{
	Console::Console()
	{
		opened = false;		
	}

	void Console::Open()
	{
		if (opened)
			throw std::runtime_error("Win32Console::Open() already opened");

		opened = true;
		AllocConsole();
		SetConsoleTitle(L"Console");
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
	}

	void Console::Close()
	{
		if (!opened)
			throw std::runtime_error("Win32Console::Close() already closed");

		opened = false;
		FreeConsole();
	}

	void Console::WriteLine(std::wstring& str)
	{
		if (!opened)
			throw std::runtime_error("Win32Console::WriteLine() console not opened");

		std::wcout << str << std::endl;
	}

	void Console::Write(std::wstring& str)
	{
		if (!opened)
			throw std::runtime_error("Win32Console::Write() console not opened");

		std::wcout << str;
	}

	wstring Console::ReadLine()
	{
		if (!opened)
			throw std::runtime_error("Win32Console::ReadLine() console not opened");

		std::string str;
		std::getline(std::cin, str);

		return wstring(str.begin(), str.end());
	}
}