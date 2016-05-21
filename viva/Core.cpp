#include <viva/graphics.h>
#include <viva/win32_engine.h>

namespace viva
{
    Core* core;

    Core::Core(const wstring& title, const Size& size, const wstring& path)
    {
        viva::core = this;

#ifdef _WIN32
        engine = new Win32Engine(title, size, path);
#endif // _WIN32
    }

    Core::~Core()
    {
        Destroy();
    }

	void Core::Destroy()
	{
        engine->Destroy();
        core = nullptr;
	}

	void Core::Run(const std::function<void()>& gameloop)
	{
		engine->Run(gameloop);
	}
}
