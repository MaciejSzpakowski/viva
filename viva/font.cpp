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
        // UV cooridnates will be generated starting from 0,0 (upper left corner).
        // tex: texture to use
        // letterSize: width and height of each letter in pixels
        // charsPerRow: how many characters there are per row
        Font::Font(Texture* tex, const Size& letterSize, int charsPerRow)
        {
            texture = tex;

            for (int i = 0, k = 32; k < 127; i++)
            {
                for (int j = 0; j < charsPerRow && k < 127; j++, k++)
                {
                    charsUv.push_back(Rect(j*letterSize.Width / (float)texture->GetSize().Width,
                        i*letterSize.Height / (float)texture->GetSize().Height,
                        (j + 1)*letterSize.Width / (float)texture->GetSize().Width,
                        (i + 1)*letterSize.Height / (float)texture->GetSize().Height));
                }
            }
        }

        void Font::Destroy()
        {
        }
    };
}