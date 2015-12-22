// PUBLIC GLOBAL HEADER FILE
#pragma once
#define D3D11
#include "Includes.h"
#include "Utils.h"
#include "Console.h"
#include "Types.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Window.h"
#include "RenderTarget.h"
#include "Creator.h"
#include "Engine.h"
#include "Core.h"
#include "DrawManager.h"

namespace viva
{
	// initializes all viva objects
	void Initialize(EngineType type, const wstring& title, int clientWidth, int clientHeigth);

	// starts the engine
	void Run(std::function<void()> gameloop);

	// destroys all viva objects
	void Destroy();
}