#pragma once

namespace viva
{
	class Win32Console : public Console
	{
	private:
		bool opened;
	public:
		Win32Console();

		void Open() override;

		void Close() override;

		void WriteLine(std::wstring& str) override;

		void Write(std::wstring& str) override;

		wstring ReadLine() override;
	};
}