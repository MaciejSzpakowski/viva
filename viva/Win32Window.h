#pragma once

namespace viva
{
	class Win32Window : public Window
	{
	private:
		HWND handle;
		MSG msg;
	public:
		Win32Window(LPCWSTR title, int width, int heigth);
		void* Win32Window::GetNativeHandle() override;
		void Win32Window::Destroy() override;

		// start win32 message pump
		// gameloop: user's function that runs every frame
		// intloop: engine function that runs every frame
		void Run(std::function<void()>& gameloop, std::function<void()>& intloop);
	};
}