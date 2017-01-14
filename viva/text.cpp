#include "viva.h"

namespace viva
{
    class Text : public Drawable, public Node, public Colorable
    {
    private:
        FontMetrics metrics;
        wstring text;
        TextureFilter texFilter;
        Sprite* sprite;
    public:
        Text(Font* font)
        {

        }

        void Destroy() override
        {
            sprite->Destroy();
        }

        void _Draw() override
        {
        }
    };
}
