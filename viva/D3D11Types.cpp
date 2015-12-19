#include "Win32.h"

namespace viva
{
	void D3D11PixelShader::Destroy()
	{
		if (ps != nullptr)
			ps->Release();

		delete this;
	}

	void D3D11VertexShader::Destroy()
	{
		if (vs != nullptr)
			vs->Release();

		delete this;
	}

	void D3D11RenderTarget::Draw()
	{
	}

	void D3D11RenderTarget::Destroy()
	{
	}
}