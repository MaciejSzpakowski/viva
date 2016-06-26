#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    // global objects for faster access
    Engine* engine = nullptr;
    Camera* camera = nullptr;
    Creator* creator = nullptr;
    DrawManager* drawManager = nullptr;
    Window* window = nullptr;
    ResourceManager* resourceManager = nullptr;
    Input::Keyboard* keyboard = nullptr;
    Input::Mouse* mouse = nullptr;
    RoutineManager* routineManager = nullptr;
    Time* time = nullptr;

    Core::Core(const wstring& title, const Size& size, const wstring& path)
    {
#ifdef _WIN32
        engine = new Win32Engine(title, size, path);
#endif // _WIN32

        engine->_Init();
    }

    Core::~Core()
    {
        engine->_Destroy();        
    }
}
