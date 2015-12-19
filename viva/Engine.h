#pragma once

namespace viva
{
	enum class EngineType
	{
		DirectX11,
		DirectX12,
		Vulcan // YEAH! i wish
	};

	class Engine
	{
	protected:
		Window* window;
		EngineType type;
		Color backgroundColor;
		Size size;
		
		PixelShader* defaultPixelShader;
		PixelShader* defaultPostProcessing;
		VertexShader* defaultVertexShader;
	public:
		Engine(EngineType _type, Size _size):type(_type),window(nullptr), size(_size), 
			backgroundColor(Color(0.0f,0.0f,0.0f,0.0f)), defaultPixelShader(nullptr),
			defaultPostProcessing(nullptr), defaultVertexShader(nullptr){}
		virtual Window* GetWindow() = 0;
		virtual void Destroy() = 0;
		
		// start the engine
		// gameloop: function called every frame
		virtual void Run(std::function<void()>& gameloop, std::function<void()>& intloop) = 0;
		
		EngineType GetType() { return type; }

		Color GetBackGroundColor() const { return backgroundColor; }

		void SetBackGroundColor(const Color& color) { backgroundColor = color; }

		virtual PixelShader* CreatePixelShaderFromString(void* args) = 0;

		virtual RenderTarget* CreateRenderTarget() = 0;

		virtual void Draw(const vector<RenderTarget*>& targets) = 0;
	};
}