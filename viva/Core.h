#pragma once

namespace viva
{
	class Core
	{
	private:
		bool initialized;
		Engine* engine;
		Core() { initialized = false; }				
		void ThrowUninitialized();
	public:
		// cannot construct singleton
		Core(Core const&) = delete;

		//cannot assign to singleton
		void operator=(Core const&) = delete;

		// get instance of Core singleton
		static Core& Get();

		// initializes Core object
		void Initialize(EngineType type, const wstring& title, int clientWidth, int clientHeigth);

		// starts the engine
		// gameloop: function called every frame
		void Run(std::function<void()>& gameloop, std::function<void()> intloop);

		void Draw(const vector<RenderTarget*>& targets, const Camera* camera) const;

		// completely destroys core object
		void Destroy();

		//Engine functions

		void SetBackgroundColor(const Color& color)
		{
			engine->SetBackGroundColor(color);
		}

		Color GetBackgroundColor() const
		{ 
			return engine->GetBackGroundColor(); 
		}

		Console* GetConsole() { return engine->GetConsole(); }

		Creator* GetCreator() { return engine; }
	};
}