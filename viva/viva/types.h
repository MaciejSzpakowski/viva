// structures that are not big enough to have their own file
#pragma once

namespace viva
{
	typedef unsigned char byte;
    using std::wstring;

	class Resource
	{
    public:
        enum class Type { Texture };
	protected:
		wstring name;
		bool cached;
        Type type;
	public:
        Resource(const wstring& _name, Type t) { name = _name; type = t; }

		bool IsCached() const { return cached; }

        Type GetType() const { return type; }

		void _SetCached(bool _cached) { cached = _cached; }
		
		const wstring& GetName() const { return name; }
	};

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
        float R, G, B, A;

        //  color rgba(1,1,1,1)
		Color() : R(1), G(1), B(1), A(1) {}

        // each value should be 0 to 1
		Color(float _r, float _g, float _b, float _a): R(_r), G(_g), B(_b), A(_a) {}
	};

    class IColorable
    {
    protected:
        Color color;
    public:
        const Color& GetColor() const
        {
            return color;
        }

        void SetColor(float r, float g, float b, float a)
        {
            color.A = a;
            color.B = b;
            color.G = g;
            color.R = r;
        }

        void SetColor(const Color& c)
        {
            color = c;
        }

        void SetColorR(float r)
        {
            color.R = r;
        }

        void SetColorG(float g)
        {
            color.G = g;
        }

        void SetColorB(float b)
        {
            color.B = b;
        }

        void SetColorA(float a)
        {
            color.A = a;
        }
    };

	struct Pixel
	{
        byte R, G, B, A;
	};

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

    struct Rect
    {
        float left, top, right, bottom;

        Rect() :left(0), top(0), right(0), bottom(0) {}
        Rect(float _left, float _top, float _right, float _bottom) :
            left(_left), top(_top), right(_right), bottom(_bottom) {}
    };

	class PixelShader
	{
	protected:
	public:
		virtual void Destroy() = 0;
	};

	//class VertexShader
	//{
	//protected:
	//public:
	//	virtual void Destroy() = 0;
	//};

	enum class TextureFilter
	{
		POINT, LINEAR
	};

	//enum class ViewMode
	//{
	//	WIREFRAME, TEXTURED //, SOLID <-- maybe i can figure it out later
	//};

	class Texture : public Resource
	{
	protected:
		Size size;
	public:
		Texture(const wstring& _name):
            Resource(_name, Resource::Type::Texture) { }

		virtual void Destroy() = 0;

		Size GetSize() const { return size; }
	};
}