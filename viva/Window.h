#pragma once

namespace viva
{
	class Window
	{
	public:
		Window() {}
		virtual void Destroy() = 0;
		virtual void* GetNativeHandle() = 0;
	};
}
