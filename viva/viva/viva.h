#pragma once

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>

namespace viva
{
    using std::wstring;
    using std::vector;
}

#include <viva/error.h>
#include <viva/types.h>
#include <viva/utils.h>
#include <viva/math.h>
#include <viva/transform.h>
#include <viva/node.h>
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
    extern Core* core;
    extern Engine* engine;
    extern Camera* camera;
    extern Creator* creator;
    extern DrawManager* drawManager;

}