#pragma once

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
        Font(Texture* tex, const Size& letterSize, int charsPerRow);

        void Destroy();
    };
}