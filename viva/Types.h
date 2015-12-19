// structures that are not big enough to have their own file
#pragma once

namespace viva
{
	typedef unsigned char byte;

	struct Color
	{
		float r, g, b, a;
		Color() : r(0), g(0), b(0), a(0) {}
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
		Color(byte _r, byte _g, byte _b, byte _a) : r(_r / 255.0f), g(_g / 255.0f), b(_b / 255.0f), a(_a / 255.0f) {}
	};

	struct Size
	{
		float width;
		float height;

		Size() :width(0), height(0) {}
		Size(float _width, float _height) :width(_width), height(_height) {}
	};

	struct TextureSampler
	{
	};

	struct Polygon
	{
	};

	struct RasterizerState
	{
	};

	struct Matrix
	{
	};

	struct PixelShader
	{
		virtual void Destroy() = 0;
	};

	struct VertexShader
	{
		virtual void Destroy() = 0;
	};
}