#pragma once

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

#include <viva/win32/win32_types.h>
#include <viva/win32/win32_window.h>
#include <viva/win32/win32_polygon.h>
#include <viva/win32/win32_sprite.h>
#include <viva/win32/win32_surface.h>
#include <viva/win32/win32_engine.h>
#include <viva/win32/win32_creator.h>

namespace viva
{
    void Checkhr(HRESULT hr, const char* function);
}

#endif