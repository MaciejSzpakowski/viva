#pragma once

namespace viva
{
    class Surface;

    class Drawable
    {
    protected:
        Surface* parent;
        int index;
    public:
        Drawable() :parent(nullptr), index(-1) {}

        // Draw all objects frm this collection.
        virtual void _Draw() = 0;

        Surface* GetSurface() const
        {
            return parent;
        }

        void _SetSurface(Surface* surface)
        {
            parent = surface;
        }

        void _SetIndex(int i)
        {
            index = i;
        }

        int _GetIndex() const
        {
            return index;
        }

        virtual Node* GetNode() = 0;
    };
}