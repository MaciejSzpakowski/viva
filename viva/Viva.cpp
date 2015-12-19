#include "Proto.h"

namespace viva
{
	void InternalLoop()
	{
		DrawManager::Get().DrawAll(Core::Get());
	}

	void Initialize(EngineType type, const wstring& title, int clientWidth, int clientHeigth)
	{
		Core::Get().Initialize(type, title, clientWidth, clientHeigth);
		DrawManager::Get().Initialize();
	}

	void Run(std::function<void()> gameloop)
	{
		Core::Get().Run(gameloop, InternalLoop);
	}

	void Destroy()
	{
		DrawManager::Get().Destroy();
		Core::Get().Destroy();
	}
}