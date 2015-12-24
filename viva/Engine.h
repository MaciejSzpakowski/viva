#pragma once

namespace viva
{
	class Engine : public Creator
	{
	protected:
		Window* window;
		Console* console;
		Color backgroundColor;
		Size size;		
		PixelShader* defaultPixelShader;
		PixelShader* defaultPostProcessing;
		VertexShader* defaultVertexShader;

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

		ID3D11SamplerState* zPointSampler;
		ID3D11SamplerState* zLineSampler;
		ID3D11ShaderResourceView* zWhiteRes;
		ID3D11Buffer* zIndexBufferSprite;
		ID3D11Buffer* zVertexBufferSprite;
		XMMATRIX zRenderTargetMatrix;
		ID3D11Buffer* zCbBufferVS;
		ID3D11Buffer* zCbBufferPS;
		ID3D11Buffer* zCbBufferUV;
		ID3D11Buffer* zCbBufferPSExtra;

		double frequency;
		long long startTime;
		long long prevFrameTime;
		double gameTime;
		double frameTime;
	public:
		Engine(Size _size, const wstring& title);
		virtual Window* GetWindow() = 0;
		virtual void Destroy() = 0;
		
		// start the engine
		// gameloop: function called every frame
		virtual void Run(std::function<void()>& gameloop, std::function<void()>& intloop) = 0;
		
		Color GetBackGroundColor() const { return backgroundColor; }

		void SetBackGroundColor(const Color& color) { backgroundColor = color; }		

		virtual void Draw(const vector<RenderTarget*>& targets, const Camera* camera) = 0;
	
		Console* GetConsole() const { return console; }
	
		PixelShader* CreatePixelShaderFromString(const char* str, void* args) override;

		PixelShader* CreatePixelShaderFromFile(const wstring& filepath, void* args) override;

		RenderTarget* CreateRenderTarget() override;

		/*Sprite* CreateSprite(const wstring& filepath) override;

		Sprite* CreateSprite(Texture* texture) override;*/

		Texture* CreateTexture(const wstring& filepath, bool cached) override;

		Texture* CreateTexture(const Pixel data[], const Size& size, wstring& name) override;

		Polygon* CreatePolygon(const vector<Point>& points) override;

		void Draw(const vector<RenderTarget*>& targets, const Camera* camera);

	};
}