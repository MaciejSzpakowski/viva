#pragma once

#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

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

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <gdiplus.h>
#include <d3dcompiler.h>
#include <Xinput.h>

#pragma comment(lib,"Gdiplus.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")
#define XINPUT_91
#ifndef XINPUT_91
#pragma comment(lib, "Xinput.lib")
#else
#pragma comment(lib, "Xinput9_1_0.lib")
#endif
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include <viva/win32_types.h>
#include <viva/win32_sprite.h>
#include <viva/win32_window.h>
#include <viva/win32_polygon.h>
#include <viva/win32_surface.h>
#include <viva/win32_engine.h>
#include <viva/win32_creator.h>

#endif

namespace viva
{
    extern Core* core;
    extern Engine* engine;
    extern Camera* camera;
    extern Creator* creator;
    extern DrawManager* drawManager;
}