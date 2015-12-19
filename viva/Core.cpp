#include "Win32.h"

namespace viva
{
	Core& Core::Get()
	{
		static Core instance;
		return instance;
	}

	void Core::Initialize(EngineType type, const wstring& title, int clientWidth, int clientHeigth)
	{
		if (initialized)
			throw std::runtime_error("Core::Initialize()\nEngine is initialized");

		if (type == EngineType::DirectX11)
			engine = new D3D11Engine(title, clientWidth, clientHeigth);
		else
			throw std::runtime_error("Core::Initialize()\nEngine not implemented");

		initialized = true;
	}

	void Core::ThrowUninitialized()
	{
		if (!initialized)
			throw std::runtime_error("Engine is not initialized");
	}

	void Core::Destroy()
	{
		ThrowUninitialized();
		initialized = false;
		engine->Destroy();
		delete engine;
	}

	void Core::Run(std::function<void()>& gameloop, std::function<void()> intloop)
	{
		ThrowUninitialized();
		engine->Run(gameloop, intloop);
	}

	void Core::Draw(const vector<RenderTarget*>& targets) const
	{
		engine->Draw(targets);
	}
}