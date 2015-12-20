#pragma once

namespace viva
{
	struct D3D11PixelShader : public PixelShader
	{
		ID3D11PixelShader* ps;

		D3D11PixelShader() { ps = nullptr; }
		void Destroy() override;
	};

	struct D3D11VertexShader : public VertexShader
	{
		ID3D11VertexShader* vs;

		D3D11VertexShader() { vs = nullptr; }
		void Destroy() override;
	};

	class D3D11RenderTarget : public RenderTarget
	{
	private:

	public:
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
	};

	class D3D11Texture : public Texture
	{
	private:		
		ID3D11ShaderResourceView* shaderResource;
	public:
		D3D11Texture(const wstring& _name, ID3D11ShaderResourceView* _shaderResource)
			:Texture(_name)
		{
			shaderResource = _shaderResource;
		}
		void Destroy() override;
	};
}