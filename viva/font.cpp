#include <viva/viva.h>

namespace viva
{
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
}