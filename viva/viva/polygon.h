#pragma once

namespace viva
{
    class Polygon : public Node, public IDrawable
    {
    protected:
        Transform transform;
        float span; //distance from origin to the furthest vertex
        int vertexCount;
    public:
        Polygon(int count) :vertexCount(count) {}
        //XMMATRIX _GetScaleMatrix() override;

        //float GetSpan() const { return span; }

        //make exact (but independent) copy and add to draw manager
        //stuff that is not copied: children (since they can have only one parent)
        //virtual Polygon* Clone();

        int GetVertexCount() const { return vertexCount; }
    };
}