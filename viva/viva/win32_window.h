#pragma once

namespace viva
{
	class Win32Window : public Window
	{
	private:
        RAWINPUTDEVICE Rid[1]; // you can have more than one
		HWND handle;
		MSG msg;
        std::function<void()> worker;   // lib side worker
        std::function<void()> activity; // client size activity
	public:
		Win32Window(const std::wstring& title, const Size& size);

		void* Win32Window::GetHandle() const override;

		void Win32Window::Destroy() override;

		// start win32 message pump
		// gameloop: user's function that runs every frame
		// intloop: engine function that runs every frame
		void Run(const std::function<void()>& gameloop, const std::function<void()>& intloop);
	};
}