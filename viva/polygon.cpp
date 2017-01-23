#include "viva.h"

namespace viva
{
    // Drawable that consist of lines.
    class Polygon : public Node, public Drawable, public Colorable
    {
    protected:
        float span; //distance from origin to the furthest vertex
        uint vertexCount;
    public:
        // Ctor.
        // count: vertex count
        Polygon(int count) :vertexCount(count) 
        {
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
        int GetVertexCount() const 
        { 
            return vertexCount; 
        }
    };
}