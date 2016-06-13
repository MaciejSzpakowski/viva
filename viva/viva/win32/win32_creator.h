#pragma once

namespace viva
{
    class Win32Creator : public Creator
    {
    private:
    public:
        /// POLYGONS ///
        Polygon* CreatePolygon(const vector<Point>& points) override;

        /// SURFACE ///
        Surface* CreateSurface() override;

        /// SHADERS ///
        PixelShader* CreatePixelShader(const wstring& filepath) override;

        PixelShader* CreatePixelShader(const std::string& str) override;

        /// SPRITE ///
        Sprite* CreateSprite(Texture* texture);

        Sprite* CreateSprite(const wstring& filepath);

        /// TEXTURE ///
        Texture* CreateTexture(const Array<Pixel>& pixels, const Size& size, const wstring& name) override
        {
            return CreateTextureWin32(pixels, size, name, false);
        }

        Texture* CreateTexture(const wstring& filepath, bool cached)
        {
            return CreateTextureWin32(filepath, cached);
        }

        Win32Texture* CreateTextureWin32(const wstring& filepath, bool cached)
        {
            Array<Pixel> pixels;
            Size size = util::ReadImageToPixels(filepath, pixels);
            return CreateTextureWin32(pixels, size, filepath, cached);
        }

        Win32Texture* CreateTextureWin32(const Array<Pixel>& pixels, const Size& size, const wstring& name, bool cached)
        {
            Win32Texture* tex = new Win32Texture(name, SrvFromPixels(pixels, size), size);

            if (cached)
                resourceManager->AddResource(tex);

            return tex;
        }

        ID3D11ShaderResourceView* SrvFromPixels(const Array<Pixel>& pixels, const Size& _size);
    };
}