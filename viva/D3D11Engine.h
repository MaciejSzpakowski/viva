#pragma once

namespace viva
{
	class D3D11Engine : public Engine
	{
	private:
		ID3D11BlendState* blendState;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* backBuffer;
		ID3D11Device* device;
		ID3D11DeviceContext* context;
		ID3D11InputLayout* layout; //vertex input layout pos:float[3] col:float[3] uv:float[2]
		ID3D11DepthStencilView* depthStencilView;
		ID3D11Texture2D* depthStencilBuffer;
		ID3D11RasterizerState* rsSolid;
		ID3D11RasterizerState* rsWire;

		double frequency;
		long long startTime;
		long long prevFrameTime;
		double gameTime;
		double frameTime;
	public:
		D3D11Engine(const wstring& title, int clientWidth, int clientHeigth);
		Window* GetWindow() override { return window; }
		void Destroy() override;

		// start the engine
		// gameloop: function called every frame
		void Run(std::function<void()>& gameloop, std::function<void()>& intloop) override;

		PixelShader* CreatePixelShaderFromFile(const wstring& filepath, void* args) override;

		PixelShader* CreatePixelShaderFromString(const char* str, void* args) override;

		RenderTarget* CreateRenderTarget() override;

		Sprite* CreateSprite(const wstring& filepath) override;

		Sprite* CreateSprite(Texture* texture) override;

		Texture* CreateTexture(const wstring& filepath, bool cached) override;

		Texture* CreateTexture(const Pixel data[], const Size& size, wstring& name) override;

		Polygon* CreatePolygon(const vector<Point>& points) override;

		void Draw(const vector<RenderTarget*>& targets, const Camera* camera) override;
	};
}