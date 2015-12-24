// PUBLIC GLOBAL HEADER FILE
#pragma once

#include <stdexcept>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <gdiplus.h>
#include <d3dcompiler.h>
#include <Xinput.h>

#include "Utils.h"
#include "Console.h"
#include "Types.h"
#include "ResourceManager.h"
#include "RenderTarget.h"
#include "Dynamic.h"
#include "Camera.h"
#include "Polygon.h"
//#include "Sprite.h"
#include "Window.h"
#include "Creator.h"
#include "Engine.h"
#include "Core.h"
#include "DrawManager.h"

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

namespace viva
{
	using namespace DirectX;
	using std::wstring;
	using std::vector;
	using std::map;

	// initializes all viva objects
	void Initialize(const wstring& title, int clientWidth, int clientHeigth);

	// starts the engine
	void Run(std::function<void()> gameloop);

	// destroys all viva objects
	void Destroy();
}