#pragma once

namespace viva
{
	class Window
	{
	private:
		HWND handle;
		MSG msg;
	public:
		Window() {}
		void Destroy();
		HWND GetHandle();

		// start win32 message pump
		// gameloop: user's function that runs every frame
		// intloop: engine function that runs every frame
		void Run(std::function<void()>& gameloop, std::function<void()>& intloop);
	};
}
