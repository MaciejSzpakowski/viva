#include "Viva.h"

namespace viva
{
	Core& Core::Get()
	{
		static Core instance;
		return instance;
	}

	void Core::Initialize(const wstring& title, int clientWidth, int clientHeigth)
	{
		if (initialized)
			throw std::runtime_error("Core::Initialize()\nEngine is initialized");

		engine = new Engine(title, clientWidth, clientHeigth);

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

	void Core::Draw(const vector<RenderTarget*>& targets, const Camera* camera) const
	{
		engine->Draw(targets, camera);
	}
}