#pragma once

#include <viva/viva.h>

namespace viva
{
    class IDrawable
    {
    protected:
        IDrawable* parent;
        vector<IDrawable*> children;
        int index;
    public:
        IDrawable() :parent(nullptr), index(-1) {}

        // Draw all objects frm this collection.
        virtual void _Draw() = 0;

        IDrawable* GetParent() const
        {
            return parent;
        }

        // Insert drawable into this drawable.
        // d: drawable to add
        void Add(IDrawable* d)
        {
            d->index = (int)children.size();
            d->parent = this;
            children.push_back(d);
        }

        void Remove(IDrawable* d)
        {
            if (d->index == -1)
                return;

            if (d->index == children.size() - 1)
            {
                children.pop_back();
                d->index = -1;
                d->parent = nullptr;
            }
            else
            {
                children[d->index] = children.back();
                children.pop_back();
                d->index = -1;
                d->parent = nullptr;
            }
        }

        virtual Node* GetNode() = 0;
    };
}