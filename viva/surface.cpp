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

        //// move to the top of the stack
        //void MoveToTop();

        //// move to the bottom of the stack
        //void MoveToBottom();

        //// move one place up i.e. swap with one above
        //void MoveUp();

        //// move one place down i.e. swap with one below
        //void MoveDown();

        //// used by draw manager to insert
        //void Insert(vector<RenderTarget*>* _parentContainer);

        // unsed by draw manager to remove
        ////void Remove();

        // Insert drawable into this drawable.
        // d: drawable to add
        void Add(Drawable* d)
        {
            d->_SetIndex((int)drawables.size());
            d->_SetSurface(this);
            drawables.push_back(d);
        }

        void Remove(Drawable* d)
        {
            if (d->_GetIndex() == -1)
                return;

            if (d->_GetIndex() != drawables.size() - 1)
                drawables[d->_GetIndex()] = drawables.back();

            drawables.pop_back();
            d->_SetIndex(-1);
            d->_SetSurface(nullptr);
        }

        // Destroy the surface and all drawables it contains.
        virtual void Destroy() = 0;

    };
}