#include "Proto.h"

namespace viva
{
	DrawManager& DrawManager::Get()
	{
		static DrawManager instance;
		return instance;
	}

	void DrawManager::Initialize()
	{
		if (initialized)
			throw std::runtime_error("Core::Initialize()\nEngine is initialized");
		
		initialized = true;
	}

	void DrawManager::ThrowUninitialized()
	{
		if (!initialized)
			throw std::runtime_error("DrawManager is not initialized");
	}

	void DrawManager::DrawAll(const Core& core)
	{
		core.Draw(renderTargets);
	}


	void DrawManager::Destroy()
	{
	}
}