#include "viva.h"

namespace viva
{
    // Bitmap font. Stores coordinates for where letters are on texture
    class Font
    {
    private:
        Texture* texture;
        vector<Rect> charsUv; // uv coordinates for glyphs
        Size charSize;

        Font* CalcGlyphs(const Size& letterSize, uint charsPerRow)
        {
            charsUv.clear();

            for (int i = 0; i < 32; i++)
                charsUv.push_back(Rect(0, 0, 0, 0));

            for (int i = 0, k = 32; k < 127; i++)
            {
                for (int j = 0; j < charsPerRow && k < 127; j++, k++)
                {
                    charsUv.push_back(Rect(j*letterSize.Width / texture->GetSize().Width,
                        i*letterSize.Height / texture->GetSize().Height,
                        (j + 1)*letterSize.Width / texture->GetSize().Width,
                        (i + 1)*letterSize.Height / texture->GetSize().Height));
                }
            }

            return this;
        }
    public:
        // Create bitmap font from texture.
        // tex: texture to use
        // glyphs: exact uv coordinate for glyphs. It should contain at least ascii 0-126
        Font(Texture* tex, const Size& letterSize, uint charsPerRow)
            : texture(tex)
        {
            CalcGlyphs(letterSize, charsPerRow);
            charSize = letterSize;
        }

        // Gets uv coordinate for char 'code'.
        const Rect& GetChar(uint code) const
        {
            return charsUv.at(code);
        }

        const Size& GetCharSize() const
        {
            return charSize;
        }

        Texture* GetTexture() const
        {
            return texture;
        }

        void Destroy()
        {
            if (!texture->IsCached())
                texture->Destroy();

            delete this;
        }
    };
}