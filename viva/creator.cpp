#include "viva.h"

namespace viva
{
    // Factory for all objects.
    class Creator
    {
    public:
        // Create pixel shader from file.
        // filepath: path to file containing pixel shader.
        virtual PixelShader* CreatePixelShader(const wstring& filepath) = 0;

        // Create pixel shader from string. This actually has to be ascii so wstring is not accepted.
        // str: pixel shader code itself
        virtual PixelShader* CreatePixelShader(const std::string& str) = 0;

        // Create texture from file. Supported files BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, EMF.
        // Named (name is given by filename) textures are stored in resource manager automatically. Can be removed by resourceManager::Remove()
        // filepath: file path
        Texture* CreateTexture(const wstring& filepath)
        {
            Pixel* pixels = nullptr;
            Size size = util::ReadImageToPixels(filepath, &pixels);
            Texture* tex = CreateTexture(pixels, size, filepath);

            if (pixels != nullptr)
                free(pixels);

            return tex;
        }
        
        Font* CreateFontV(const wstring& filename)
        {
            return new Font(filename);
        }

        Font* CreateFontV(Texture* tex, const vector<Rect>& glyphs)
        {
            return new Font(tex, glyphs);
        }

        Font* CreateFontV(Texture* tex)
        {
            return new Font(tex);
        }

        // Create texture from pixels.
        // Named textures are stored in resource manager automatically. Can be removed by resourceManager::Remove()
        // pixels: pixels for the texture starting from left top
        // size: size of the image in pixels
        // name: some name, used by resource manager for caching
        virtual Texture* CreateTexture(const Pixel* pixels, const Size& size, const wstring& name) = 0;
        
        // Create texture from pixels. Noname texture are not stored in resource manager but can be stored by resourceManager::Add()
        // pixels: pixels for the texture starting from left top
        // size: size of the image in pixels
        Texture* CreateTexture(const Pixel* pixels, const Size& size)
        {
            return CreateTexture(pixels, size, L"");
        }

        Text* CreateText(const wstring& text)
        {
            return new Text(text);
        }

        Text* CreateText(const wstring& text, Font* font)
        {
            return new Text(text, font);
        }
        
        // Create sprite from file. Supported files BMP, GIF, JPEG, PNG, TGA.
        // filepath: file path to image
        virtual Sprite* CreateSprite(const wstring& filepath) = 0;

        // Create sprite from texture.
        // texture: existing texture object
        virtual Sprite* CreateSprite(Texture* texture) = 0;

        // Create polygon from points.
        // points: vector of points where each point is x,y in world coordinates
        virtual Polygon* CreatePolygon(const vector<Point>& points) = 0;

        // Create polygon from vertex buffer.
        virtual Polygon* CreatePolygon(VertexBuffer* vb) = 0;

        // Create shared vertex buffer. That can be used by multiple polygons.
        virtual VertexBuffer* CreateVertexBuffer(const vector<Point>& points) = 0;

        // Create surface to render objects on.
        virtual Surface* CreateSurface() = 0;

        Animation* CreateAnimation(Sprite* sprite)
        {
            return new Animation(sprite);
        }

        Animation* CreateAnimation(const wstring& filename)
        {
            Sprite* sprite = CreateSprite(filename);
            return CreateAnimation(sprite);
        }

        virtual void _Destroy() = 0;
    };
}