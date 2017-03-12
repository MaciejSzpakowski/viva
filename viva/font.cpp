#include "viva.h"

namespace viva
{
    // Bitmap font. Stores coordinates for where letters are on texture
    class Font
    {
    private:
        Texture* texture;
        vector<Rect> charsUv; // uv coordinates for glyphs
    public:
        // Create bitmap font from texture.
        // tex: texture to use
        // glyphs: exact uv coordinate for glyphs. It should contain at least ascii 0-126
        Font(Texture* tex, const vector<Rect>& glyphs)
            : texture(tex), charsUv(glyphs)
        {
        }

        // Create bitmap font from texture.
        // tex: texture to use
        Font(Texture* tex)
            :texture(tex)
        {
        }

        // Create bitmap font from texture.
        // UV cooridnates will be generated starting from 0,0 (upper left corner).
        // filename: texture to use
        // letterSize: width and height of each letter in pixels
        // charsPerRow: how many characters there are per row
        Font(const wstring& filename)
        {
            Texture* t = resourceManager->GetTexture(filename);

            if (t == nullptr)
                t = creator->CreateTexture(filename);

            texture = t;
        }

        Font* SetGlyphs(const vector<Rect>& glyphs)
        {
            charsUv = glyphs;
            return this;
        }

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

        // Gets uv coordinate for char 'code'.
        const Rect& GetChar(uint code) const
        {
            return charsUv.at(code);
        }

        void Destroy()
        {
            if (!texture->IsCached())
                texture->Destroy();

            delete this;
        }
    };
}