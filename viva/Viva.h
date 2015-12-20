// PUBLIC GLOBAL HEADER FILE
#pragma once
#include "Includes.h"
#include "Utils.h"
#include "Dynamic.h"
#include "Drawable.h"
#include "Types.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Window.h"
#include "RenderTarget.h"
#include "Create.h"
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