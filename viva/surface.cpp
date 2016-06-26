#include <viva/viva.h>

namespace viva
{
    void Surface::Add(IDrawable* d)
    {
        Node* n = d->GetNode();

        if (n->_GetIndex() != -1)
            return;

        d->_SetSurface(this);
        n->_SetIndex((int)drawables.size());
        drawables.push_back(d);
    }

    void Surface::Remove(IDrawable* d)
    {
        int index = d->GetNode()->_GetIndex();

        if (index == -1)
            return;
        else if (index == drawables.size() - 1)
            drawables.pop_back();
        else
        {
            drawables[index] = drawables.back();
            drawables.pop_back();
        }

        d->_SetSurface(nullptr);
        d->GetNode()->_SetIndex(-1);
    }
}