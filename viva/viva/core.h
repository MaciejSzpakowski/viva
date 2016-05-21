#pragma once

#include <viva/types.h>
#include <viva/engine.h>

namespace viva
{
	class Core
	{        
	private:
		Engine* engine;
	public:
        // path is the default path, engine will look for default shaders there
        Core(const wstring& title, const Size& size, const wstring& path = L"");
        
		// starts the engine
		// gameloop: function called every frame
        void Run(const std::function<void()>& gameloop = []() {});

		//void Draw(const vector<RenderTarget*>& targets, const Camera* camera) const;

		// completely destroys core object
		void Destroy();

        Engine* GetEngine() const
        {
            return engine;
        }

        void Exit()
        {
            engine->Exit();
        }

		void OpenConsole() { engine->OpenConsole(); }
        void CloseConsole() { engine->CloseConsole(); }

		//Creator* GetCreator() { return engine; }

        ~Core();
	};
}