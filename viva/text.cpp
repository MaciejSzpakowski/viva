#include "viva.h"

namespace viva
{
    class Text : public Drawable, public Node, public Colorable
    {
    private:
        wstring text;
        TextureFilter texFilter;
        Font* font;
        Transform transform;
        Sprite* sprite;

        Surface* parent;
        uint index;
        bool visible;
    public:
        Text(const wstring& str, Font* f)
            : font(f), text(str), texFilter(drawManager->GetDefaultTextureFilter()),
            parent(nullptr), index(-1), visible(true)
        {
            sprite = creator->CreateSprite(font->GetTexture());
        }

        Text(const wstring& str)
            : Text(str, drawManager->GetDefaultFont())
        {
        }

        // Get transform of the object.
        Transform* T() override
        {
            return &transform;
        }

        Text* SetText(const wstring& _text)
        {
            text = _text;

            return this;
        }

        const wstring& GetText() const
        {
            return text;
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

        Text* SetTextureFilter(TextureFilter filter)
        {
            texFilter = filter;

            return this;
        }

        void Destroy() override
        {
            sprite->Destroy();

            delete this;
        }

        void _Draw() override
        {
            int row = 0;
            int col = 0;

            for (int i = 0; i < text.length(); i++)
            {
                if (text.at(i) == '\n')
                {
                    row++;
                    col = 0;
                    continue;
                }

                sprite->SetUV(font->GetChar(text.at(i)));
                sprite->T()->SetPosition(col * 1.0f + transform.GetPosition().GetX(), 1.3f * row + transform.GetPosition().GetY(), transform.GetPosition().GetZ());
                sprite->SetPixelScale(20, 38);
                sprite->_Draw();

                col++;
            }            
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

        Node* GetNode()
        {
            return this;
        }
    };
}
