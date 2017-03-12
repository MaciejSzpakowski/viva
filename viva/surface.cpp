#include "viva.h"

namespace viva
{
    // Special drawable where all of its objects are drawn on it.
    class Surface
    {
    protected:
        //PixelShader* pixelShader;
        vector<Drawable*> drawables;
    public:
        // Ctor.
        Surface() 
        {
        }

        // 
        virtual void _DrawAll() = 0;

        // Draw surface itself.
        virtual void _DrawSurface() = 0;

        // Get pixel shader.
        virtual PixelShader* GetPixelShader() const = 0;

        // Set pixel shader.
        // ps: ps
        virtual void SetPixelShader(PixelShader* ps) = 0;
                
        // Add drawable into this surface.
        // d: drawable to add
        void Add(Drawable* d)
        {
            d->_SetIndex(drawables.size());
            d->_SetSurface(this);
            drawables.push_back(d);
        }

        // Remove all drawables from the surface without destroying them.
        void RemoveAll()
        {
            for (uint i = 0; i < drawables.size(); i++)
            {
                drawables.at(i)->_SetIndex(-1);
                drawables.at(i)->_SetSurface(nullptr);
            }

            drawables.clear();
        }

        //
        void Remove(Drawable* d)
        {
            int indexOfd = d->_GetIndex();

            if (indexOfd == -1)
                return;
            
            // if d is not at the end
            if (indexOfd != drawables.size() - 1)
            {
                // move back to where d is and update its index
                drawables.back()->_SetIndex(indexOfd);
                drawables.at(indexOfd) = drawables.back();
            }

            drawables.pop_back();
            d->_SetIndex(-1);
            d->_SetSurface(nullptr);
        }

        // Destroy all drawables from this surface.
        void Clear()
        {
            for (uint i = 0; i < drawables.size(); i++)
                drawables.at(i)->GetNode()->Destroy();

            drawables.clear();
        }

        // Destroy the surface and all drawables it contains.
        virtual void Destroy() = 0;

    };
}