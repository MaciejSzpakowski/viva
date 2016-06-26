#pragma once

#include <viva/viva.h>

namespace viva
{
    class Surface;

    class IDrawable
    {
    protected:
        Surface* surface;
    public:
        virtual void _Draw() = 0;

        Surface* GetSurface() const
        {
            return surface;
        }

        void _SetSurface(Surface* s)
        {
            surface = s;
        }

        virtual Node* GetNode() = 0;
    };
}