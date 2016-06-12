#pragma once

namespace viva
{
    class Win32Creator : public Creator
    {
    private:
    public:

        Polygon* CreatePolygon(const vector<Point>& points) override;

        Surface* CreateSurface() override;

        PixelShader* CreatePixelShader(const wstring& filepath) override;

        PixelShader* CreatePixelShader(const std::string& str) override;

        Sprite* CreateSprite(Texture* texture);

        Texture* CreateTexture(const vector<Pixel>& pixels, const Size& size, const wstring& name) override
        {
            return CreateTextureWin32(pixels, size, name);
        }

        Texture* CreateTexture(const wstring& filepath, bool cached)
        {
            return CreateTextureWin32(filepath, cached);
        }

        Win32Texture* CreateTextureWin32(const wstring& filepath, bool cached)
        {
            vector<Pixel> pixels;
            Size size = util::ReadImageToPixels(filepath, pixels);
            return CreateTextureWin32(pixels, size, filepath);
        }

        ID3D11ShaderResourceView* SrvFromPixels(const vector<Pixel>& pixels, const Size& _size);

        Win32Texture* CreateTextureWin32(const vector<Pixel>& pixels, const Size& size, const wstring& name);
    };
}