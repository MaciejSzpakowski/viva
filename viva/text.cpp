#include "viva.h"

namespace viva
{
    class Text : public Drawable, public Node, public Colorable
    {
    private:
        FontMetrics metrics;
        wstring text;
        TextureFilter texFilter;
        Font* font;
        Transform transform;

        Surface* parent;
        uint index;
        bool visible;
    public:
        Text(const wstring& str, Font* f, FontMetrics m)
            : metrics(m), font(f), text(str), texFilter(drawManager->GetDefaultTextureFilter()),
            parent(nullptr), index(-1), visible(true)
        {
        }

        Text(const wstring& str)
            : Text(str, drawManager->GetDefaultFont(), drawManager->GetDefaultFontMetrics())
        {
        }

        Text(const wstring& str, Font* f)
            : Text(str, f, drawManager->GetDefaultFontMetrics())
        {
        }

        // Get transform of the object.
        Transform* T() override
        {
            return &transform;
        }

        // Get transform of the object.
        Transform* GetTransform() override
        {
            return &transform;
        }

        TextureFilter GetTextureFilter() const
        {
            return texFilter;
        }

        Text* SetTexFilter(TextureFilter filter)
        {
            texFilter = filter;

            return this;
        }

        void Destroy() override
        {
            delete this;
        }

        void _Draw() override
        {
        }

        Surface* GetSurface() const override
        {
            return parent;
        }

        bool IsVisible() const override
        {
            return visible;
        }

        Drawable* SetVisible(bool val) override
        {
            visible = val;
            return this;
        }

        void _SetSurface(Surface* surface) override
        {
            parent = surface;
        }

        void _SetIndex(uint i) override
        {
            index = i;
        }

        int _GetIndex() const override
        {
            return index;
        }
    };
}
