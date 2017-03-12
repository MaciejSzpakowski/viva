#include "viva.h"

namespace viva
{
    class Drawable
    {
    public:
        Drawable()
        {
        }

        // Draw all objects frm this collection.
        virtual void _Draw() = 0;

        virtual Surface* GetSurface() const = 0;

        virtual bool IsVisible() const = 0;

        virtual Drawable* SetVisible(bool val) = 0;

        virtual void _SetSurface(Surface* surface) = 0;

        virtual void _SetIndex(uint i) = 0;

        virtual int _GetIndex() const = 0;

        virtual Node* GetNode() = 0;
    };
}