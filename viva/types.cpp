// structures that are not big enough to have their own file
#include "viva.h"

namespace viva
{
    typedef unsigned char byte;
    using std::wstring;

    enum class ResourceType 
    { 
        Texture 
    };

    class Resource
    {
    public:
    protected:
        wstring name;
        bool cached;
        ResourceType type;
    public:
        Resource(const wstring& _name, ResourceType t)
        {
            name = _name; 
            type = t; 
        }

        bool IsCached() const 
        { 
            return cached; 
        }

        ResourceType GetType() const
        { 
            return type;
        }

        void _SetCached(bool _cached)
        { 
            cached = _cached; 
        }

        const wstring& GetName() const 
        {
            return name; 
        }

        virtual void Destroy() = 0;
    };

    struct Point
    {
        float X, Y;

        Point() :X(0), Y(0) 
        {
        }

        Point(float x, float y) :X(x), Y(y) 
        {
        }
    };

    struct Color
    {
        float R, G, B, A;

        //  color rgba(1,1,1,1)
        Color() : R(1), G(1), B(1), A(1) 
        {
        }

        // each value should be 0 to 1
        Color(float _r, float _g, float _b, float _a) : R(_r), G(_g), B(_b), A(_a) 
        {
        }

        Color(const Pixel& pixel)
            : R(pixel.R / 255.0f),
            G(pixel.G / 255.0f),
            B(pixel.B / 255.0f),
            A(pixel.A / 255.0f)
        {
        }
    };

    class Colorable
    {
    protected:
        Color color;
    public:
        const Color& GetColor() const
        {
            return color;
        }

        Colorable* SetColor(float r, float g, float b, float a)
        {
            color.A = a;
            color.B = b;
            color.G = g;
            color.R = r;

            return this;
        }

        Colorable* SetColor(const Color& c)
        {
            color = c;
            return this;
        }

        Colorable* SetR(float r)
        {
            color.R = r;
            return this;
        }

        Colorable* SetG(float g)
        {
            color.G = g;
            return this;
        }

        Colorable* SetB(float b)
        {
            color.B = b;
            return this;
        }

        Colorable* SetA(float a)
        {
            color.A = a;
            return this;
        }
    };

    struct Pixel
    {
        byte R, G, B, A;

        Pixel() : R(1), G(1), B(1), A(1)
        {
        }

        Pixel(byte r, byte g, byte b, byte a)
            : R(r), G(g), B(b), A(a)
        {
        }

        Pixel(const Color& color)
            : R((int)(color.R * 255)),
            G((int)(color.G * 255)),
            B((int)(color.B * 255)),
            A((int)(color.A * 255))
        {
        }
    };

    struct Size
    {
        float Width;
        float Height;

        // creates size(0,0)
        Size() :Width(0), Height(0) 
        {
        }

        Size(float _width, float _height) :Width(_width), Height(_height) 
        {
        }
    };

    struct Vertex
    {
        float X, Y, Z;
        float R, G, B;
        float U, V;

        Vertex() 
        {
        }

        Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v)
            : X(_x), Y(_y), Z(_z), R(_r), G(_g), B(_b), U(_u), V(_v) 
        {
        }
    };

    struct Rect
    {
        float left, top, right, bottom;

        Rect() :left(0), top(0), right(0), bottom(0) 
        {
        }

        Rect(float _left, float _top, float _right, float _bottom) 
            : left(_left), top(_top), right(_right), bottom(_bottom) 
        {
        }
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
        Point, Linear
    };

    class Texture : public Resource
    {
    protected:
        Size size;
    public:
        Texture(const wstring& _name) 
            : Resource(_name, ResourceType::Texture) 
        { 
        }

        Size GetSize() const 
        { 
            return size;
        }
    };
}