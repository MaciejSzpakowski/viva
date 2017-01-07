#pragma once

namespace viva
{
    // Window where everything is being drawn.
	class Window
	{
	public:
        // Ctor.
		Window(){}

        // Destroy window.
		virtual void _Destroy() = 0;

        virtual void SetWindowTitle(const wstring& title) = 0;

        // Get native handle.
		virtual void* GetHandle() const = 0;
	};
}
