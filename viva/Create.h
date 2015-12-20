#pragma once

namespace viva
{
	class Creator
	{
	public:
		// create pixel shader from file
		virtual PixelShader* CreatePixelShaderFromFile(const wstring& filepath, void* args) = 0;

		// create pixel shader from const char*
		virtual PixelShader* CreatePixelShaderFromString(const char* str, void* args) = 0;

		// create render target
		virtual RenderTarget* CreateRenderTarget() = 0;

		// create texture from file
		virtual Texture* CreateTexture(const wstring& filepath, bool cached) = 0;

		// create texture from byte array
		virtual Texture* CreateTexture(const byte data[], const Size& size, wstring& name) = 0;

		// create sprite from file
		virtual Sprite* CreateSprite(const wstring& filepath) = 0;

		// create sprite from texture
		virtual Sprite* CreateSprite(Texture* texture) = 0;
	};
}