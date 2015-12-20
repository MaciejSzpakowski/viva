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
			throw std::runtime_error("DrawManager::Initialize()\nDrawManager is initialized");
		
		initialized = true;

		camera = new Camera();
	}

	void DrawManager::ThrowUninitialized()
	{
		if (!initialized)
			throw std::runtime_error("DrawManager is not initialized");
	}

	void DrawManager::DrawAll(const Core& core)
	{
		core.Draw(renderTargets, camera);
	}

	void DrawManager::Destroy()
	{
		if (!initialized)
			throw std::runtime_error("DrawManager::Destroy()\nDrawManager is not initialized");

		initialized = false;

		camera->Destroy();
	}
}