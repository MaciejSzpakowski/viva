// structures that are not big enough to have their own file
#pragma once

namespace viva
{
	typedef unsigned char byte;
    using std::wstring;

	//class Resource
	//{
	//protected:
	//	wstring name;
	//	bool cached;
	//public:
	//	Resource(const wstring& _name) { name = _name; }

	//	bool IsCached() const { return cached; }

	//	void _SetCached(bool _cached) { cached = _cached; }
	//	
	//	wstring GetName() const { return name; }
	//};

    class IDrawable
    {
    public:
        virtual void _Draw() = 0;
    };

    struct Point
    {
        float X;
        float Y;

        Point() :X(0), Y(0) {}
        Point(float x, float y) :X(x), Y(y) {}
    };

	struct Color
	{
        float R;
        float G;
        float B;
        float A;

        //  color rgba(0,0,0,0)
		Color() : R(0), G(0), B(0), A(0) {}

        // white = (1,1,1,1)
		Color(float _r, float _g, float _b, float _a): R(_r), G(_g), B(_b), A(_a) {}
	};

	//struct Pixel
	//{
	//	byte r, g, b, a;
	//};

	struct Size
	{
		float Width;
		float Height;

        // creates size(0,0)
		Size() :Width(0), Height(0) {}
		Size(float _width, float _height) :Width(_width), Height(_height) {}
	};

	struct Vertex
	{
		float X, Y, Z;
		float R, G, B;
		float U, V;
		Vertex() {}
		Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v)
			: X(_x), Y(_y), Z(_z), R(_r), G(_g), B(_b), U(_u), V(_v) {}
	};

	//class PixelShader
	//{
	//protected:
	//public:
	//	virtual void Destroy() = 0;
	//};

	//class VertexShader
	//{
	//protected:
	//public:
	//	virtual void Destroy() = 0;
	//};

	//enum class TextureFilter
	//{
	//	POINT, LINEAR
	//};

	//enum class ViewMode
	//{
	//	WIREFRAME, TEXTURED //, SOLID <-- maybe i can figure it out later
	//};

	class Texture// : public Resource
	{
	protected:
		Size size;
	public:
		Texture(const wstring& _name) { }

		virtual void Destroy() = 0;

		Size GetSize() const { return size; }
	};

	//class Dynamic
	//{
	//protected:
	//	int index; // index in the parent container
	//public:
	//	Dynamic() :index(-1) {}

	//	virtual void Transform() = 0;

	//	virtual void Destroy() = 0;
	//};

	//class Drawable : public Dynamic
	//{
	//protected:
	//	//RenderTarget* renderTarget;
	//public:
	//	virtual void Draw() = 0;
	//};

	//class Polygon : Drawable
	//{
	//protected:
	//public:
	//};
}