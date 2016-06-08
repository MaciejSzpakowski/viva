#pragma once

namespace viva
{
	class Engine
	{
	protected:
        wstring defaultPath;
		Window* window;
		Color backgroundColor;
		Size clientSize;
       /* Creator creator;
		
		PixelShader* defaultPixelShader;
		PixelShader* defaultPostProcessing;
		VertexShader* defaultVertexShader;*/
	public:
        Engine(const std::wstring& path, const Size& size) :backgroundColor(0, 0.25f, 0.5f, 1),
        defaultPath(path),clientSize(size){}

        void* GetWindowHandle() { window->GetHandle(); }
		virtual void Destroy() = 0;
		//
		//// start the engine
		//// gameloop: function called every frame
		virtual void Run(const std::function<void()>& gameloop) = 0;

		const Color& GetBackgroundColor() const { return backgroundColor; }
        
		void SetBackgroundColor(const Color& color) { backgroundColor = color; }

        const std::wstring& GetDefaultPath() const
        {
            return defaultPath;
        }

        const Size& GetClientSize() const
        {
            return clientSize;
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