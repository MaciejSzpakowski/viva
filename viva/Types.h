// structures that are not big enough to have their own file
#pragma once

namespace viva
{
	typedef unsigned char byte;

	class Resource
	{
	protected:
		wstring name;
		bool cached;
	public:
		Resource(const wstring& _name) { name = _name; }

		bool IsCached() const { return cached; }

		void _SetCached(bool _cached) { cached = _cached; }
		
		wstring GetName() const { return name; }
	};

	struct Matrix
	{
	};

	struct Color
	{
		float r, g, b, a;
		Color() : r(0), g(0), b(0), a(0) {}
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
		Color(byte _r, byte _g, byte _b, byte _a) : r(_r / 255.0f), g(_g / 255.0f), b(_b / 255.0f), a(_a / 255.0f) {}
	};

	struct Pixel
	{
		byte r, g, b, a;
	};

	struct Size
	{
		float width;
		float height;

		Size() :width(0), height(0) {}
		Size(float _width, float _height) :width(_width), height(_height) {}
	};

	struct Vertex
	{
		float x, y, z;
		float r, g, b;
		float u, v;
		Vertex() {}
		Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v)
			: x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), u(_u), v(_v) {}
	};

	class PixelShader
	{
	protected:
	public:
		virtual void Destroy() = 0;
	};

	class VertexShader
	{
	protected:
	public:
		virtual void Destroy() = 0;
	};

	enum class TextureFilter
	{
		POINT, LINEAR
	};

	enum class ViewMode
	{
		WIREFRAME, TEXTURED //, SOLID <-- maybe i can figure it out later
	};

	class Texture : public Resource
	{
	protected:
		Size size;
	public:
		Texture(const wstring& _name):Resource(_name) { }

		virtual void Destroy() = 0;

		Size GetSize() const { return size; }
	};

	class Dynamic
	{
	protected:
		int index; // index in the parent container
	public:
		Dynamic() :index(-1) {}

		virtual void Transform() = 0;

		virtual void Destroy() = 0;
	};

	class Drawable : public Dynamic
	{
	protected:
		//RenderTarget* renderTarget;
	public:
		virtual void Draw() = 0;
	};

	class Polygon : Drawable
	{
	protected:
	public:
	};
}