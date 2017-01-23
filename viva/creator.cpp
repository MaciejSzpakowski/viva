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

        // Create sprite from file. Supported files BMP, GIF, JPEG, PNG, TGA.
        // filepath: file path to image
        virtual Sprite* CreateSprite(const wstring& filepath) = 0;

        // Create sprite from texture.
        // texture: existing texture object
        virtual Sprite* CreateSprite(Texture* texture) = 0;

        // Create polygon from points.
        // points: vector of points where each point is x,y in world coordinates
        virtual Polygon* CreatePolygon(const vector<Point>& points) = 0;

        // Create surface to render objects on.
        virtual Surface* CreateSurface() = 0;

        virtual void _Destroy() = 0;
    };
}