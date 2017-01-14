#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>
#include <map>
#include <array>
#include "viva.h"

namespace viva
{
    using std::wstring;
    using std::vector;

    typedef unsigned char byte;
    typedef unsigned int uint;

    Engine* engine = nullptr;
    Camera* camera = nullptr;;
    Creator* creator = nullptr;
    DrawManager* drawManager = nullptr;
    Window* window = nullptr;
    ResourceManager* resourceManager = nullptr;
    Input::Mouse* mouse = nullptr;
    Input::Keyboard* keyboard = nullptr;
    RoutineManager* routineManager = nullptr;
    Time* time;
}
