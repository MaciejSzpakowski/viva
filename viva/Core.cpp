#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    // global objects for faster access
    Core* core = nullptr;
    Engine* engine = nullptr;
    Camera* camera = nullptr;
    Creator* creator = nullptr;
    DrawManager* drawManager = nullptr;
    Window* window = nullptr;
    ResourceManager* resourceManager = nullptr;

    Core::Core(const wstring& title, const Size& size, const wstring& path)
    {
        viva::core = this;

#ifdef _WIN32
        engine = new Win32Engine(title, size, path);
#endif // _WIN32

        viva::engine = this->engine;
        engine->_Init();
    }

    Core::~Core()
    {
        engine->_Destroy();

        resourceManager = nullptr;
        core = nullptr;
        engine = nullptr;
        camera = nullptr;
        creator = nullptr;
        drawManager = nullptr;
        window = nullptr;
    }
}
