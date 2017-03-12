#include "viva.h"

namespace viva
{
    // Drawable that consist of lines.
    class Polygon : public Node, public Drawable, public Colorable
    {
    protected:
        //float span; //distance from origin to the furthest vertex
        uint vertexCount;
        Transform transform;

        Surface* parent;
        uint index;
        bool visible;
    public:
        // Ctor.
        // count: vertex count
        Polygon() : parent(nullptr), index(-1), visible(true)
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

        Node* GetNode() override
        {
            return this;
        }

        //XMMATRIX _GetScaleMatrix() override;

        //float GetSpan() const { return span; }

        //make exact (but independent) copy and add to draw manager
        //stuff that is not copied: children (since they can have only one parent)
        //virtual Polygon* Clone();

        // Get pixel shader.
        virtual PixelShader* GetPixelShader() const = 0;

        // Set pixel shader.
        // ps: the ps
        virtual void SetPixelShader(PixelShader* ps) = 0;

        // Get vertex count.
        uint GetVertexCount() const
        {
            return vertexCount;
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