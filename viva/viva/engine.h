#pragma once

#include <viva/types.h>
#include <viva/window.h>
#include <functional>

namespace viva
{
	class Engine
	{
	protected:
        wstring defaultPath;
		Window* window;
		Color backgroundColor;
       /* Creator creator;
		Console console;
		EngineType type;
		Size size;
		
		PixelShader* defaultPixelShader;
		PixelShader* defaultPostProcessing;
		VertexShader* defaultVertexShader;*/
	public:
        Engine(const std::wstring& path) :backgroundColor(0, 0.25f, 0.5f, 1),
        defaultPath(path){}

        void* GetWindowHandle() { window->GetHandle(); }
		virtual void Destroy() = 0;
		//
		//// start the engine
		//// gameloop: function called every frame
		virtual void Run(const std::function<void()>& gameloop) = 0;
		//
		//EngineType GetType() { return type; }

		Color GetBackGroundColor() const { return backgroundColor; }

		void SetBackGroundColor(const Color& color) { backgroundColor = color; }

        const std::wstring& GetDefaultPath() const
        {
            return defaultPath;
        }

        void SetDefaultPath(const std::wstring& path)
        {
            defaultPath = path;
        }

        virtual void Exit() = 0;

		//virtual void Draw(const vector<RenderTarget*>& targets, const Camera* camera) = 0;
	
		void OpenConsole() const {  }
        void CloseConsole() const {}
	};
}