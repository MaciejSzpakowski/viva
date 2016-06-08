#pragma once

namespace viva
{
	/*struct D3D11PixelShader : public PixelShader
	{
		ID3D11PixelShader* ps;

		D3D11PixelShader(ID3D11PixelShader* _ps):ps(_ps) { }
		void Destroy() override;
	};

	struct D3D11VertexShader : public VertexShader
	{
		ID3D11VertexShader* vs;

		D3D11VertexShader(ID3D11VertexShader* _vs):vs(_vs) { }
		void Destroy() override;
	};

	class D3D11RenderTarget : public RenderTarget
	{
	private:
		ID3D11Texture2D* tex;
		ID3D11RenderTargetView* rtv;
		ID3D11ShaderResourceView* srv;
	public:
		D3D11RenderTarget(ID3D11Texture2D* _tex, ID3D11RenderTargetView* _rtv, ID3D11ShaderResourceView* _srv) :
			tex(_tex), rtv(_rtv), srv(_srv) {}

		void Draw() override;

		void Destroy() override;
	};

	class D3D11Polygon : public Polygon
	{
	private:
	public:
		D3D11Polygon() {}

		void Destroy() override;
	};

	class D3D11Sprite : public Sprite
	{
	private:
	public:
		D3D11Sprite() {}

		void Destroy() override;

		void Draw() override;

		void Transform() override;
	};

	struct D3D11Matrix : public Matrix
    {
		DirectX::XMMATRIX matrix;
	};*/

	class Win32Texture : public Texture
	{
	private:		
		ID3D11ShaderResourceView* shaderResource;
	public:
        Win32Texture(const wstring& _name, ID3D11ShaderResourceView* _shaderResource)
			:Texture(_name)
		{
			shaderResource = _shaderResource;
		}
		void Destroy() override;
	};
}