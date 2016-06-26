#pragma once

namespace viva
{
    using std::wstring;

    struct D3D11
    {
        ID3D11BlendState* blendState;
        IDXGISwapChain* swapChain;
        ID3D11RenderTargetView* backBuffer;
        ID3D11Device* device;
        ID3D11DeviceContext* context;
        ID3D11InputLayout* layout; //vertex input layout: float[3] pos, float[3] col, float[2] uv
        ID3D11DepthStencilView* depthStencil;
        ID3D11Texture2D* depthStencilBuffer;
        ID3D11RasterizerState* rsSolid;
        ID3D11RasterizerState* rsWire;
        ID3D11VertexShader* defaultVS;
        Win32PixelShader* defaultPS;
        Win32PixelShader* defaultPost;
        ID3D11Buffer* constantBufferVS; // cb for worldViewProj matrix
        ID3D11Buffer* constantBufferPS; // cb for color
        ID3D11Buffer* constantBufferUV; // cb for uv
        ID3D11Buffer* constantBufferPSExtra; // cb for user varsiables for ps
        ID3D11Buffer* indexBuffer; // for sprites and surfaces
        ID3D11Buffer* vertexBuffer; // for sprites and surfaces
        ID3D11SamplerState* samplerPoint;
        ID3D11SamplerState* samplerLinear;
    };

    extern D3D11 d3d;

	class Win32Engine : public Engine
	{
	private:
        void Activity() override;
	public:
        Win32Engine(const wstring& title, const Size& size, const wstring& path);

		void _Destroy() override;

        void _Init() override;

		void Run(const std::function<void()>& gameloop) override;
        
        void OpenConsole() override;

        void CloseConsole() override;

        void Exit() override;
	};
}