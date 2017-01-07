#pragma once

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
        Text(Font* font);

        void Destroy() override;

        void _Draw() override;
    };
}