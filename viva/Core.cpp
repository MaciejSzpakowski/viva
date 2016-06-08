#include <viva/proto.h>

namespace viva
{
    // global objects for faster access
    Core* core;
    Engine* engine;
    Camera* camera;
    Creator* creator;
    DrawManager* drawManager;

    Core::Core(const wstring& title, const Size& size, const wstring& path)
    {
        viva::core = this;

#ifdef _WIN32
        engine = new Win32Engine(title, size, path);
#endif // _WIN32

        viva::engine = this->engine;
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
