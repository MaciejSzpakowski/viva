#pragma once

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>
#include <map>
#include <array>
#include <math.h>

namespace viva
{
    using std::wstring;
    using std::vector;

    typedef unsigned char byte;
    typedef unsigned int uint;
}

#include <viva/error.h>
#include <viva/types.h>
#include <viva/resource_manager.h>
#include <viva/utils.h>
#include <viva/time.h>
#include <viva/routine_manager.h>
#include <viva/keys.h>
#include <viva/input.h>
#include <viva/math.h>
#include <viva/transform.h>
#include <viva/node.h>
#include <viva/drawable.h>
#include <viva/camera.h>
#include <viva/polygon.h>
#include <viva/sprite.h>
#include <viva/surface.h>
#include <viva/creator.h>
#include <viva/window.h>
#include <viva/engine.h>
#include <viva/draw_manager.h>
#include <viva/core.h>

namespace viva
{
    extern Engine* engine;
    extern Camera* camera;
    extern Creator* creator;
    extern DrawManager* drawManager;
    extern Window* window;
    extern ResourceManager* resourceManager;
    extern Input::Mouse* mouse;
    extern Input::Keyboard* keyboard;
    extern RoutineManager* routineManager;
    extern Time* time;
}