#pragma once

namespace viva
{
    using std::wstring;

	class Win32Engine : public Engine
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
        ID3D11VertexShader* defaultVS;
        ID3D11PixelShader* defaultPS;
        ID3D11PixelShader* defaultPost;
        ID3D11Buffer* constantBufferVS;

        // TIME OBJECT
		/*double frequency;
		long long startTime;
		long long prevFrameTime;
		double gameTime;
		double frameTime;*/
	public:
        Win32Engine(const wstring& title, const Size& size, const wstring& path);
		void Destroy() override;

		// start the engine
		// gameloop: function called every frame
		void Run(const std::function<void()>& gameloop) override;

        ID3D11PixelShader* CreatePixelShaderFromString(const std::string& str, const char* target = "ps_5_0");

		/*PixelShader* CreatePixelShaderFromFile(const wstring& filepath, void* args) override;

		RenderTarget* CreateRenderTarget() override;

		Sprite* CreateSprite(const wstring& filepath) override;

		Sprite* CreateSprite(Texture* texture) override;

		Texture* CreateTexture(const wstring& filepath, bool cached) override;

		Texture* CreateTexture(const Pixel data[], const Size& size, wstring& name) override;

		void Draw(const vector<RenderTarget*>& targets, const Camera* camera) override;*/

        // breaks the gameloop i.e.
        // makes the function core->Run() return
        void Exit() override;

        void render();
	};
}