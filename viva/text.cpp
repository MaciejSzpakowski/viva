#include <viva/viva.h>

namespace viva
{
    Text::Text(Font* font)
    {

    }

    void Text::Destroy()
    {
        sprite->Destroy();
    }

    void Text::_Draw()
    {
    }
}