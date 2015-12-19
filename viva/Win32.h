#pragma once

#include "Proto.h"

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <gdiplus.h>
#include <d3dcompiler.h>
#include <Xinput.h>

#include "Win32Window.h"
#include "D3D11Types.h"
#include "D3D11Engine.h"

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
