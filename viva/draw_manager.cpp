#include "viva.h"

namespace viva
{
    // Wrapper for adding and removing drawables.
    class DrawManager
    {
    private:
        Sprite* defaultFont;
        Surface* defaultSurface;
        Texture* whitePixel;
        //vector<RenderTarget*> renderTargets;
        //BitmapFont* defaultFont;
        //TextureFilter defaultFilter;
        //Matrix* renderTargetMatrix; // every render target has the same transform matrix
    public:
        DrawManager()
        {
            defaultSurface = creator->CreateSurface();

            // create default font
            {
                vector<int> data = {
                    421,3,12,3,71,5,97,1,14,1,75,1,21,1,8,1,9,1,57,1,14,1,76,1,19,1,9,1,10,1,15,7,2,3,1,2,1,2,2,3,2,3,4,3,6,1,1,3,6,3,1,1,4,5,4,6,6,4,6,3,1,2,5,2,7,1,3,1,3,3,2,3,5,1,6,7,6,1,9,1,10,1,18
                    ,1,6,1,2,1,2,1,4,1,4,1,4,1,3,1,5,2,3,1,4,1,3,2,5,1,7,1,5,1,4,1,4,1,4,1,3,2,6,2,6,1,1,1,1,1,1,1,3,1,4,1,5,1,1,1,6,1,4,1,6,1,9,1,10,1,18,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,
                    1,5,1,13,1,4,1,9,1,4,1,5,1,2,1,5,1,1,1,1,1,1,1,4,1,2,1,6,1,1,1,7,1,10,1,9,1,10,1,18,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,5,1,8,5,5,1,9,1,4,1,5,1,2,1,5,1,1,1,1,1,1,1,5,2,6,
                    1,3,1,7,1,8,1,10,1,11,1,8,2,7,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,5,1,7,1,10,1,9,1,4,1,5,1,2,1,4,1,3,1,3,1,3,1,2,1,5,1,3,1,8,1,8,1,9,1,10,1,5,1,2,1,2,1,6,1,6,2,1,2,1,1,4,
                    2,3,1,4,1,3,1,5,2,3,1,4,1,3,2,5,3,5,1,4,2,4,1,9,1,4,1,4,1,4,1,3,1,3,1,3,1,2,1,4,1,3,1,5,1,3,1,4,1,7,1,9,1,10,1,6,2,10,1,5,2,1,1,2,1,4,2,1,3,6,3,5,2,1,3,6,3,1,2,3,2,2,3,3,4,1,1,2,7,
                    4,2,3,2,3,3,2,3,1,3,5,2,1,3,2,3,1,3,3,3,2,7,6,1,9,1,10,1,18,1,77,1,71,1,9,1,10,1,18,1,77,1,72,1,8,1,9,1,17,3,159,1,1035,10,262,5,24,5,38,3,15,3,102,1,28,1,37,1,11,1,7,1,102,1,28,1,
                    15,5,5,6,6,1,10,1,8,1,37,4,1,2,2,2,1,3,6,5,5,3,1,2,4,4,5,5,6,3,1,1,3,3,2,3,2,7,8,1,4,2,2,4,5,1,7,1,4,1,6,1,10,1,8,1,36,1,4,2,4,2,3,1,4,1,5,1,3,1,3,2,4,1,4,1,5,1,8,1,3,2,4,1,4,1,6,1
                    ,11,1,5,1,3,1,7,1,8,1,3,1,6,1,9,1,9,1,36,1,5,1,4,1,5,1,2,1,9,1,5,1,3,1,11,1,7,1,5,1,4,1,4,1,6,1,11,1,5,1,2,1,8,1,9,1,9,1,9,1,9,1,37,6,4,1,5,1,2,1,9,1,5,1,3,7,5,1,7,1,5,1,4,1,4,1,6,
                    1,11,1,5,3,9,1,10,1,8,1,8,1,10,1,42,1,4,1,5,1,2,1,9,1,5,1,3,1,5,1,5,1,7,1,5,1,4,1,4,1,6,1,11,1,5,1,1,1,8,1,1,1,9,1,8,1,8,1,10,1,37,1,4,1,4,2,3,1,4,1,4,2,3,1,3,2,4,1,3,1,6,1,8,1,3,2
                    ,4,2,3,1,6,1,11,1,5,1,2,1,6,1,3,1,9,1,7,1,8,1,10,1,6,1,5,1,25,4,5,1,1,3,6,4,1,1,4,3,1,1,5,3,5,7,5,3,1,2,3,1,1,3,5,3,7,5,5,1,2,3,3,1,5,1,4,1,4,1,6,1,7,1,11,1,7,1,3,1,18,1,16,1,24,1,
                    15,1,18,1,29,1,7,3,3,3,3,6,6,1,7,1,11,1,8,1,1,1,18,1,17,1,24,1,15,1,18,1,29,1,31,3,4,1,10,3,9,1,18,1,17,2,23,2,16,5,12,2,11,1,10,1,5,2,38,1,22,1,109,1,10,1,1458,5,72,5,7,5,3,3,2,3,
                    2,7,4,4,5,3,3,2,2,8,1,3,3,3,1,3,3,2,5,4,5,5,6,4,4,3,3,2,3,1,1,3,5,5,6,4,7,2,6,1,3,1,3,3,3,3,3,1,9,1,5,1,3,1,4,1,6,1,6,1,4,1,5,1,4,1,5,1,4,1,2,1,5,1,3,1,4,2,4,1,4,1,5,1,8,1,4,1,4,1,
                    4,1,4,2,3,1,6,1,7,1,4,1,6,2,5,1,1,1,1,1,1,1,3,1,5,1,4,1,8,1,6,1,3,1,4,1,6,1,6,1,4,1,5,1,3,1,6,1,4,1,2,1,5,1,3,1,3,1,1,1,3,1,6,1,4,1,7,1,6,1,3,1,3,1,5,1,4,1,6,1,7,1,4,1,5,1,2,1,4,1,
                    1,1,1,1,1,1,4,1,3,1,5,1,2,1,5,1,3,5,2,1,4,1,6,1,6,1,4,1,5,1,3,1,6,1,4,1,2,1,2,1,2,1,3,1,3,1,1,1,3,1,6,1,4,5,3,1,6,1,3,1,2,1,11,1,6,1,7,1,4,1,5,1,2,1,4,1,1,1,1,1,1,1,5,1,1,1,6,4,5,1
                    ,10,6,6,1,11,1,5,4,7,1,7,1,1,1,1,1,1,1,3,1,2,1,2,1,3,1,6,1,4,1,4,1,2,1,6,1,3,5,6,4,7,1,7,1,4,1,5,1,2,1,4,1,1,1,1,1,1,1,6,1,7,1,2,1,5,1,10,1,4,1,6,1,11,1,5,1,1,1,8,1,7,1,1,1,1,1,1,1
                    ,3,1,1,1,3,1,3,1,6,1,4,1,4,1,2,1,6,1,3,1,4,1,4,1,8,1,2,1,2,1,4,1,4,1,4,1,4,1,3,1,2,1,2,1,5,1,1,1,6,1,4,1,3,1,10,1,4,1,6,1,11,1,5,1,2,1,7,1,7,1,1,1,1,1,1,1,3,1,1,1,3,1,3,1,6,1,4,1,4
                    ,1,2,1,6,1,3,1,4,1,4,1,4,1,3,1,2,1,2,1,4,1,4,1,4,1,4,1,3,1,2,1,2,1,4,1,3,1,5,1,4,1,4,1,4,2,3,1,4,1,6,1,11,1,5,1,3,1,6,1,7,2,3,2,3,2,4,1,4,1,4,1,5,1,4,1,3,1,4,1,4,1,4,1,4,1,3,2,3,1,
                    2,1,2,1,4,1,4,1,3,1,6,1,2,1,5,1,3,1,5,1,3,7,5,4,1,1,2,3,2,3,2,7,5,6,2,3,1,4,2,5,4,3,3,3,1,3,3,3,4,4,5,6,5,4,4,6,6,3,1,1,3,7,3,3,2,3,1,3,4,7,1,4,1,3,3,3,1794,1,50,3,55,5,7,4,4,5,6,5
                    ,6,1,8,4,5,3,8,2,8,2,12,2,12,2,11,2,7,1,3,1,2,3,4,3,1,6,6,5,3,6,4,7,3,1,5,1,8,1,4,1,5,1,4,1,5,1,5,1,7,1,4,1,7,1,7,2,9,1,11,1,16,1,10,2,6,1,8,1,6,1,3,1,4,1,4,1,5,1,3,1,4,1,4,1,4,1,9
                    ,1,8,1,10,1,4,1,5,1,6,1,6,1,4,1,8,1,17,2,8,2,18,2,16,1,3,3,3,1,4,1,4,1,4,1,3,1,10,1,5,1,3,1,4,1,9,1,4,6,9,1,4,1,5,1,6,1,6,1,4,1,9,1,25,1,7,8,7,1,8,1,6,1,2,1,2,1,3,6,4,1,4,1,3,1,10,
                    1,5,1,3,1,2,1,10,1,5,1,3,1,10,1,4,2,4,1,6,1,6,1,4,1,5,3,1,1,23,2,24,2,7,1,5,1,2,1,2,1,4,1,2,1,5,5,4,1,10,1,5,1,3,4,8,3,6,1,2,1,5,5,5,1,1,4,8,1,6,4,5,1,3,2,5,2,9,2,7,1,22,1,10,1,4,1
                    ,2,1,2,1,4,1,2,1,5,1,4,1,3,1,10,1,5,1,3,1,2,1,11,1,5,1,2,1,5,1,9,1,13,1,5,1,4,1,4,1,4,1,5,2,9,2,8,2,5,8,5,2,6,1,4,1,4,1,3,3,4,1,2,1,5,1,4,1,3,1,6,1,3,1,5,1,3,1,4,1,9,1,6,1,1,1,5,1,
                    10,1,13,1,4,1,4,1,4,1,4,1,28,1,16,1,8,1,4,1,4,1,5,1,5,2,6,1,4,1,4,1,4,2,3,1,4,1,4,1,4,1,3,2,4,1,7,2,5,1,11,1,6,1,5,1,4,1,4,1,4,1,4,1,29,2,12,2,10,4,6,1,4,1,4,3,5,6,6,4,1,1,2,6,4,7,
                    5,4,9,1,5,5,8,4,2,7,5,4,6,4,67,4,1426,1,42,1,4,1,29,1,99,1,2,1,8,1,41,1,6,1,28,1,28,1,51,3,16,1,2,1,6,5,8,2,6,5,18,1,6,1,20,1,7,2,19,2,6,1,11,4,5,7,2,7,15,3,17,1,2,1,5,1,4,1,6,1,2,
                    1,4,1,3,1,18,1,8,1,19,1,8,1,19,2,7,1,9,1,4,1,7,1,5,1,5,1,35,1,2,1,10,1,6,1,2,1,4,1,2,2,18,1,8,1,19,1,8,2,27,1,9,1,4,1,7,1,6,1,21,1,16,8,8,1,7,2,5,1,1,1,2,1,17,1,8,1,19,1,38,1,8,1,4
                    ,1,7,1,7,1,20,1,18,1,2,1,10,1,4,3,8,2,20,1,8,1,7,1,3,1,4,7,13,7,15,1,8,1,4,1,7,1,8,2,18,1,18,1,2,1,6,4,8,3,5,1,10,1,10,1,8,1,8,1,1,1,8,1,39,1,7,1,4,1,7,1,10,1,17,1,8,1,2,1,4,8,3,1,
                    10,2,8,1,10,1,10,1,8,1,9,1,9,1,39,1,7,1,4,1,7,1,11,1,16,1,8,1,2,1,6,1,2,1,5,1,9,1,2,1,8,3,7,1,11,1,6,1,7,7,6,1,40,1,6,1,4,1,7,1,5,1,5,1,16,1,8,2,1,2,5,1,2,1,5,1,4,1,4,1,2,1,17,3,10
                    ,1,6,1,10,1,9,1,40,1,6,1,4,1,4,2,1,1,5,1,5,1,16,1,8,2,1,2,6,1,2,1,5,5,5,2,18,3,11,1,4,1,11,1,51,1,6,4,7,2,6,5,37,1,2,1,6,1,111,1,603
                };

                vector<byte> data2;
                byte b = 0;

                for (auto i : data)
                {
                    for (int j = 0; j < i; j++)
                    {
                        data2.push_back(b);
                        data2.push_back(b);
                        data2.push_back(b);
                        data2.push_back(b);
                    }

                    b = b == 0 ? 255 : 0;
                }

                //Texture* t = creator->CreateTexture(reinterpret_cast<Pixel*>(data2.data()), Size(190, 95), L"__vivaDefaultFontTexture", true);

                //defaultFont = creator->CreateSprite(t);
                //defaultFont->SetScale2TextureSize();
                //defaultFont->SetFlipVertically(true);
            }

            Pixel p[] = { Pixel(255,255,255,255) };
            whitePixel = creator->CreateTexture(p, Size(1, 1), L"__whitePixel");

            //Add(defaultFont);
        }

        // Destroys DrawManager and all drawables.
        void _Destroy()
        {
            defaultSurface->Destroy();
            //defaultFont->Destroy();
            delete this;
        }

        //void SetDefaultTextureFilter(TextureFilter filter) { defaultFilter = filter; }

        //TextureFilter GetDefaultTextureFilter() const { return defaultFilter; }

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
        Polygon* AddPolygon(const vector<Point>& points)
        {
            return AddPolygon(points, defaultSurface);
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
        Sprite* AddRectangle(Surface* surface)
        {
            Sprite* s = AddSprite(whitePixel, surface);
            return s;
        }

        // Create and add a unicolor rectangle to be drawn.
        Sprite* AddRectangle()
        {
            return AddRectangle(defaultSurface);
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

        Sprite* GetDefaultFont() const
        {
            return defaultFont;
        }
    };
}