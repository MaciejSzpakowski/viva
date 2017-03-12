#include "viva.h"

namespace viva
{
    // Wrapper for adding and removing drawables.
    class DrawManager
    {
    private:
        Surface* defaultSurface;
        Texture* whitePixel;
        FontMetrics defaultMetrics;
        //vector<RenderTarget*> renderTargets;
        Font* defaultFont;
        TextureFilter defaultFilter;
        VertexBuffer* rectVertexBuffer;
        VertexBuffer* circleVertexBuffer;
        //Matrix* renderTargetMatrix; // every render target has the same transform matrix
    public:
        DrawManager()
        {
            defaultFilter = TextureFilter::Point;
            defaultSurface = creator->CreateSurface();

            // create default font
            {
                vector<int> data =
                {
                    604,1,2,1,6,1,111,1,47,1,8,2,1,2,6,1,2,1,5,5,5,2,18,3,11,1,4,1,11,1,51,1,6,4,7,2,6,5,17,1,
                    8,2,1,2,5,1,2,1,5,1,4,1,4,1,2,1,17,3,10,1,6,1,10,1,9,1,40,1,6,1,4,1,4,2,1,1,5,1,5,1,
                    16,1,8,1,2,1,6,1,2,1,5,1,9,1,2,1,8,3,7,1,11,1,6,1,7,7,6,1,40,1,6,1,4,1,7,1,5,1,5,1,
                    16,1,8,1,2,1,4,8,3,1,10,2,8,1,10,1,10,1,8,1,9,1,9,1,39,1,7,1,4,1,7,1,11,1,16,1,18,1,2,1,
                    6,4,8,3,5,1,10,1,10,1,8,1,8,1,1,1,8,1,39,1,7,1,4,1,7,1,10,1,17,1,18,1,2,1,10,1,4,3,8,2,
                    20,1,8,1,7,1,3,1,4,7,13,7,15,1,8,1,4,1,7,1,8,2,18,1,16,8,8,1,7,2,5,1,1,1,2,1,17,1,8,1,
                    19,1,38,1,8,1,4,1,7,1,7,1,39,1,2,1,10,1,6,1,2,1,4,1,2,2,18,1,8,1,19,1,8,2,27,1,9,1,4,1,
                    7,1,6,1,20,3,17,1,2,1,5,1,4,1,6,1,2,1,4,1,3,1,18,1,8,1,19,1,8,1,19,2,7,1,9,1,4,1,7,1,
                    5,1,5,1,15,3,16,1,2,1,6,5,8,2,6,5,18,1,6,1,20,1,7,2,19,2,6,1,11,4,5,7,2,7,34,1,2,1,8,1,
                    41,1,6,1,28,1,28,1,82,1,42,1,4,1,29,1,1400,4,9,1,5,5,8,4,2,7,5,4,6,4,67,4,53,2,4,1,7,2,5,1,
                    11,1,6,1,5,1,4,1,4,1,4,1,4,1,29,2,12,2,10,4,6,1,4,1,4,3,5,6,6,4,1,1,2,6,4,7,9,1,6,1,
                    1,1,5,1,10,1,13,1,4,1,4,1,4,1,4,1,28,1,16,1,8,1,4,1,4,1,5,1,5,2,6,1,4,1,4,1,4,2,3,1,
                    4,1,4,1,4,1,9,1,5,1,2,1,5,1,9,1,13,1,5,1,4,1,4,1,4,1,5,2,9,2,8,2,5,8,5,2,6,1,4,1,
                    4,1,3,3,4,1,2,1,5,1,4,1,3,1,6,1,3,1,5,1,3,1,4,1,6,3,6,1,2,1,5,5,5,1,1,4,8,1,6,4,
                    5,1,3,2,5,2,9,2,7,1,22,1,10,1,4,1,2,1,2,1,4,1,2,1,5,1,4,1,3,1,10,1,5,1,3,1,2,1,10,1,
                    5,1,3,1,10,1,4,2,4,1,6,1,6,1,4,1,5,3,1,1,23,2,24,2,7,1,5,1,2,1,2,1,4,1,2,1,5,5,4,1,
                    10,1,5,1,3,4,11,1,4,6,9,1,4,1,5,1,6,1,6,1,4,1,9,1,25,1,7,8,7,1,8,1,6,1,2,1,2,1,3,6,
                    4,1,4,1,3,1,10,1,5,1,3,1,2,1,11,1,8,1,10,1,4,1,5,1,6,1,6,1,4,1,8,1,17,2,8,2,18,2,16,1,
                    3,3,3,1,4,1,4,1,4,1,3,1,10,1,5,1,3,1,4,1,3,1,5,1,8,1,4,1,5,1,4,1,5,1,5,1,7,1,4,1,
                    7,1,7,2,9,1,11,1,16,1,10,2,6,1,8,1,6,1,3,1,4,1,4,1,5,1,3,1,4,1,4,1,4,1,4,5,7,4,4,5,
                    6,5,6,1,8,4,5,3,8,2,8,2,12,2,12,2,11,2,7,1,3,1,2,3,4,3,1,6,6,5,3,6,4,7,85,1,50,3,1764,7,
                    5,4,1,1,2,3,2,3,2,7,5,6,2,3,1,4,2,5,4,3,3,3,1,3,3,3,4,4,5,6,5,4,4,6,6,3,1,1,3,7,
                    3,3,2,3,1,3,4,7,1,4,1,3,3,3,3,1,4,1,4,1,4,2,3,1,4,1,6,1,11,1,5,1,3,1,6,1,7,2,3,2,
                    3,2,4,1,4,1,4,1,5,1,4,1,3,1,4,1,4,1,4,1,4,1,3,2,3,1,2,1,2,1,4,1,4,1,3,1,6,1,2,1,
                    5,1,3,1,5,1,4,1,4,1,3,1,10,1,4,1,6,1,11,1,5,1,2,1,7,1,7,1,1,1,1,1,1,1,3,1,1,1,3,1,
                    3,1,6,1,4,1,4,1,2,1,6,1,3,1,4,1,4,1,4,1,3,1,2,1,2,1,4,1,4,1,4,1,4,1,3,1,2,1,2,1,
                    4,1,3,1,5,1,2,1,5,1,10,1,4,1,6,1,11,1,5,1,1,1,8,1,7,1,1,1,1,1,1,1,3,1,1,1,3,1,3,1,
                    6,1,4,1,4,1,2,1,6,1,3,1,4,1,4,1,8,1,2,1,2,1,4,1,4,1,4,1,4,1,3,1,2,1,2,1,5,1,1,1,
                    6,4,5,1,10,6,6,1,11,1,5,4,7,1,7,1,1,1,1,1,1,1,3,1,2,1,2,1,3,1,6,1,4,1,4,1,2,1,6,1,
                    3,5,6,4,7,1,7,1,4,1,5,1,2,1,4,1,1,1,1,1,1,1,6,1,7,1,2,1,5,1,3,5,2,1,4,1,6,1,6,1,
                    4,1,5,1,3,1,6,1,4,1,2,1,2,1,2,1,3,1,3,1,1,1,3,1,6,1,4,5,3,1,6,1,3,1,2,1,11,1,6,1,
                    7,1,4,1,5,1,2,1,4,1,1,1,1,1,1,1,5,1,1,1,6,1,8,1,6,1,3,1,4,1,6,1,6,1,4,1,5,1,3,1,
                    6,1,4,1,2,1,5,1,3,1,3,1,1,1,3,1,6,1,4,1,7,1,6,1,3,1,3,1,5,1,4,1,6,1,7,1,4,1,5,1,
                    2,1,4,1,1,1,1,1,1,1,4,1,3,1,5,1,9,1,5,1,3,1,4,1,6,1,6,1,4,1,5,1,4,1,5,1,4,1,2,1,
                    5,1,3,1,4,2,4,1,4,1,5,1,8,1,4,1,4,1,4,1,4,2,3,1,6,1,7,1,4,1,6,2,5,1,1,1,1,1,1,1,
                    3,1,5,1,3,5,7,5,3,3,2,3,2,7,4,4,5,3,3,2,2,8,1,3,3,3,1,3,3,2,5,4,5,5,6,4,4,3,3,2,
                    3,1,1,3,5,5,6,4,7,2,6,1,3,1,3,3,3,3,115,5,1432,1,22,1,109,1,10,1,38,3,4,1,10,3,9,1,18,1,17,2,
                    23,2,16,5,12,2,11,1,10,1,5,2,7,3,3,3,3,6,6,1,7,1,11,1,8,1,1,1,18,1,17,1,24,1,15,1,18,1,29,1,
                    8,1,5,1,4,1,4,1,6,1,7,1,11,1,7,1,3,1,18,1,16,1,24,1,15,1,18,1,29,1,9,1,3,1,9,1,7,1,8,1,
                    10,1,6,1,5,1,25,4,5,1,1,3,6,4,1,1,4,3,1,1,5,3,5,7,5,3,1,2,3,1,1,3,5,3,7,5,5,1,2,3,
                    5,1,1,1,9,1,8,1,8,1,10,1,37,1,4,1,4,2,3,1,4,1,4,2,3,1,3,2,4,1,3,1,6,1,8,1,3,2,4,2,
                    3,1,6,1,11,1,5,1,2,1,8,1,10,1,8,1,8,1,10,1,42,1,4,1,5,1,2,1,9,1,5,1,3,1,5,1,5,1,7,1,
                    5,1,4,1,4,1,6,1,11,1,5,1,1,1,9,1,9,1,9,1,9,1,9,1,37,6,4,1,5,1,2,1,9,1,5,1,3,7,5,1,
                    7,1,5,1,4,1,4,1,6,1,11,1,5,3,9,1,8,1,3,1,6,1,9,1,9,1,36,1,5,1,4,1,5,1,2,1,9,1,5,1,
                    3,1,11,1,7,1,5,1,4,1,4,1,6,1,11,1,5,1,2,1,8,1,7,1,4,1,6,1,10,1,8,1,36,1,4,2,4,2,3,1,
                    4,1,5,1,3,1,3,2,4,1,4,1,5,1,8,1,3,2,4,1,4,1,6,1,11,1,5,1,3,1,5,5,5,6,6,1,10,1,8,1,
                    37,4,1,2,2,2,1,3,6,5,5,3,1,2,4,4,5,5,6,3,1,1,3,3,2,3,2,7,8,1,4,2,2,4,25,1,11,1,7,1,
                    102,1,28,1,37,3,15,3,102,1,28,1,155,5,24,5,74,10,1072,3,159,1,29,1,77,1,72,1,8,1,9,1,19,1,77,1,71,1,9,1,
                    10,1,18,1,5,2,1,1,2,1,4,2,1,3,6,3,5,2,1,3,6,3,1,2,3,2,2,3,3,4,1,1,2,7,4,2,3,2,3,3,
                    2,3,1,3,5,2,1,3,2,3,1,3,3,3,2,7,6,1,9,1,10,1,18,1,6,2,1,2,1,1,4,2,3,1,4,1,3,1,5,2,
                    3,1,4,1,3,2,5,3,5,1,4,2,4,1,9,1,4,1,4,1,4,1,3,1,3,1,3,1,2,1,4,1,3,1,5,1,3,1,4,1,
                    7,1,9,1,10,1,6,2,10,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,5,1,7,1,10,1,9,1,
                    4,1,5,1,2,1,4,1,3,1,3,1,3,1,2,1,5,1,3,1,8,1,8,1,9,1,10,1,5,1,2,1,2,1,6,1,6,1,2,1,
                    2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,5,1,8,5,5,1,9,1,4,1,5,1,2,1,5,1,1,1,1,1,1,1,
                    5,2,6,1,3,1,7,1,8,1,10,1,11,1,8,2,7,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,
                    5,1,13,1,4,1,9,1,4,1,5,1,2,1,5,1,1,1,1,1,1,1,4,1,2,1,6,1,1,1,7,1,10,1,9,1,10,1,18,1,
                    6,1,2,1,2,1,4,1,4,1,4,1,3,1,5,2,3,1,4,1,3,2,5,1,7,1,5,1,4,1,4,1,4,1,3,2,6,2,6,1,
                    1,1,1,1,1,1,3,1,4,1,5,1,1,1,6,1,4,1,6,1,9,1,10,1,15,7,2,3,1,2,1,2,2,3,2,3,4,3,6,1,
                    1,3,6,3,1,1,4,5,4,6,6,4,6,3,1,2,5,2,7,1,3,1,3,3,2,3,5,1,6,7,6,1,9,1,10,1,56,1,14,1,
                    76,1,19,1,9,1,10,1,56,1,14,1,75,1,21,1,8,1,9,1,56,3,12,3,71,5,435
                };

                // here's how above encoding works, each number represents how many consecutive pixels in a row are transparent or white
                // they simply alternate between white or transparent
                // e.g. 4,7,2 means 4 pixels transparent then 7 pixels white then 2 pixels transparent
                vector<Pixel> data2;
                Pixel current = Pixel(0,0,0,0);
                
                for (auto i : data)
                {
                    for (int j = 0; j < i; j++)
                        data2.push_back(current);

                    current = current.R == 0 ? Pixel(255, 255, 255, 255) : Pixel(0, 0, 0, 0);
                }

                Texture* t = creator->CreateTexture(data2.data(), Size(190, 95), L"?vivaDefaultFontTexture");
                resourceManager->Remove(L"?vivaDefaultFontTexture");
                defaultFont = creator->CreateFontV(t);
                defaultFont->CalcGlyphs({ 15,15 }, 18);
            }

            Pixel p[] = { Pixel(255,255,255,255) };
            whitePixel = creator->CreateTexture(p, Size(1, 1), L"?whitePixel");
            resourceManager->Remove(L"?whitePixel");

            vector<Point> square({Point(-1,-1),Point(-1,1) ,Point(1,1) ,Point(1,-1) ,Point(-1,-1) });
            rectVertexBuffer = creator->CreateVertexBuffer(square);

            vector<Point> circle;
            for (int i = 0; i < 21; i++)
                circle.push_back(Point(sinf(2 * Math::Pi / 20.0f * i), cosf(2 * Math::Pi / 20.0f * i)));
            circleVertexBuffer = creator->CreateVertexBuffer(circle);
        }

        // Destroys DrawManager and all drawables.
        void _Destroy()
        {
            defaultSurface->Destroy();
            defaultFont->Destroy();
            whitePixel->Destroy();
            rectVertexBuffer->Destroy();
            circleVertexBuffer->Destroy();
            delete this;
        }

        // Draw all objects on their surfaces.
        void _DrawNodes()
        {
            defaultSurface->_DrawAll();
        }

        // Draw surfaces.
        void _DrawSurfaces()
        {
            defaultSurface->_DrawSurface();
        }

        // Create and add polygon to be drawn.
        // points: list of points
        // surface: which surface
        Polygon* AddPolygon(const vector<Point>& points, Surface* surface)
        {
            Polygon* p = creator->CreatePolygon(points);
            Add(p, surface);
            return p;
        }

        // Create and add polygon to be drawn.
        // points: list of points
        // surface: which surface
        Polygon* AddPolygon(VertexBuffer* vb, Surface* surface)
        {
            Polygon* p = creator->CreatePolygon(vb);
            Add(p, surface);
            return p;
        }

        Polygon* AddRectangle()
        {
            return AddRectangle(defaultSurface);
        }

        Polygon* AddRectangle(Surface* surface)
        {
            Polygon* p = creator->CreatePolygon(rectVertexBuffer);
            Add(p, surface);
            return p;
        }

        Polygon* AddCircle()
        {
            return AddCircle(defaultSurface);
        }

        Polygon* AddCircle(Surface* surface)
        {
            Polygon* p = creator->CreatePolygon(circleVertexBuffer);
            Add(p, surface);
            return p;
        }

        Polygon* AddCircle(uint vertices)
        {
            return AddCircle(vertices, defaultSurface);
        }

        Polygon* AddCircle(uint vertices, Surface* surface)
        {
            vector<Point> circle;
            for (int i = 0; i < vertices + 1; i++)
                circle.push_back(Point(sinf(2.0f * Math::Pi / vertices * i), cosf(2.0f * Math::Pi / vertices * i)));

            Polygon* p = creator->CreatePolygon(circle);
            Add(p, surface);
            return p;
        }

        // Create and add polygon to be drawn.
        // points: list of points
        Polygon* AddPolygon(const vector<Point>& points)
        {
            return AddPolygon(points, defaultSurface);
        }

        // Create and add polygon to be drawn.
        // points: list of points
        Polygon* AddPolygon(VertexBuffer* vb)
        {
            return AddPolygon(vb, defaultSurface);
        }

        // Create and add sprite to be drawn.
        // t: texture to be used by the sprite
        // surface: which surface
        Sprite* AddSprite(Texture* t, Surface* surface)
        {
            Sprite* s = creator->CreateSprite(t);
            Add(s, surface);
            return s;
        }

        // Create and add sprite to be drawn.
        // t: texture to be used by the sprite
        Sprite* AddSprite(Texture* t)
        {
            return AddSprite(t, defaultSurface);
        }

        // Create and add a unicolor rectangle to be drawn.
        // surface: which surface,nullptr for default
        Sprite* AddFillRectangle(Surface* surface)
        {
            Sprite* s = AddSprite(whitePixel, surface);
            return s;
        }

        // Create and add a unicolor rectangle to be drawn.
        Sprite* AddFillRectangle()
        {
            return AddFillRectangle(defaultSurface);
        }

        // Create and add sprite to be drawn. Also, create texture if it doesnt exist.
        // filepath: file path of the image to be used by the texture
        // surface: which surface,nullptr for default
        Sprite* AddSprite(const wstring& filepath, Surface* surface)
        {
            Sprite* s = creator->CreateSprite(filepath);
            Add(s, surface);
            return s;
        }

        // Create and add sprite to be drawn. Also, create texture if it doesnt exist.
        // filepath: file path of the image to be used by the texture
        Sprite* AddSprite(const wstring& filepath)
        {
            return AddSprite(filepath, defaultSurface);
        }

        void Remove(Drawable* drawable)
        {
            drawable->GetSurface()->Remove(drawable);
        }

        void Add(Drawable* drawable, Surface* surface)
        {
            surface->Add(drawable);
        }

        void Add(Drawable* drawable)
        {
            defaultSurface->Add(drawable);
        }

        TextureFilter GetDefaultTextureFilter() const
        {
            return defaultFilter;
        }

        void SetDefaultTextureFilter(TextureFilter filter)
        {
            defaultFilter = filter;
        }

        const FontMetrics& GetDefaultFontMetrics() const
        {
            return defaultMetrics;
        }

        void SetDefaultFontMetrics(const FontMetrics& metrics)
        {
            defaultMetrics = metrics;
        }

        Texture* GetPixel()
        {
            return whitePixel;
        }

        Font* GetDefaultFont() const
        {
            return defaultFont;
        }

        // Destroy all surfaces (except the default one) and all object from the default surface.
        void Clear()
        {
            /*for (auto& s : surfaces)
                s->Destroy();

            surfaces.clear();*/

            defaultSurface->Clear();
        }
    };
}