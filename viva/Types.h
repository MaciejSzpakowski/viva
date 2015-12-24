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

	struct Point
	{
		float x, y;
	};

	struct Size
	{
		float width;
		float height;

		Size() :width(0), height(0) {}
		Size(float _width, float _height) :width(_width), height(_height) {}
	};

	struct Rect
	{
		float left;
		float top;
		float right;
		float bottom;
		Rect() :left(0), right(0), top(0), bottom(0) {}
		Rect(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}
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
	public:
		ID3D11PixelShader* ps;
		PixelShader(ID3D11PixelShader* _ps) :ps(_ps) {}
		void Destroy()
		{
			if (ps != nullptr)
				ps->Release();

			delete this;
		}
	};

	class VertexShader
	{
	public:
		ID3D11VertexShader* vs;
		VertexShader(ID3D11VertexShader* _vs) :vs(_vs) {}
		void Destroy()
		{
			if (vs != nullptr)
				vs->Release();

			delete this;
		}
	};

	enum class TextureFilter
	{
		Point, Linear
	};

	enum class ViewMode
	{
		Wireframe, Textured //, SOLID <-- maybe i can figure it out later
	};

	class Texture : public Resource
	{
	private:
		ID3D11ShaderResourceView* shaderResource;
		Size size;
	public:
		Texture(const wstring& _name, ID3D11ShaderResourceView* srv):Resource(_name) { }

		void Destroy()
		{
			if (cached)
				ResourceManager::Get().RemoveResource(name);

			shaderResource->Release();
			delete this;
		}

		Size GetSize() const { return size; }
	};	

	/*class Drawable : public Dynamic
	{
	private:
		Color color;
		bool flipHorizontally;
		bool flipVertically;
	public:
		Drawable():color(Color(1.0f, 1, 1, 1)), flipHorizontally(false), 
			flipVertically(false) {}
		virtual void Draw() = 0;
	};*/
}