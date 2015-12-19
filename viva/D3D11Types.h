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

	class D3D11Sprite : public Sprite
	{
	private:
	public:
	};
}