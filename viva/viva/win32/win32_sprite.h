#pragma once

namespace viva
{
    class Win32Sprite : public Sprite
    {
    private:
        Win32Texture* texture;
    public:
        Win32Sprite(Win32Texture* tex):
            texture(tex) {}

        void _Draw() override;

        void Destroy() override;

        Texture* GetTexture() override
        {
            return texture;
        }
    };
}