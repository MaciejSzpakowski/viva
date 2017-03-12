#include "viva.h"

namespace viva
{
    class VertexBuffer
    {
    protected:
        uint vertexCount;
        bool shared;
    public:
        virtual void Destroy() = 0;

        int GetVertexCount() const
        {
            return vertexCount;
        }

        VertexBuffer(uint vertexCount)
            : shared(false), vertexCount(vertexCount)
        {
        }

        bool IsShared() const
        {
            return shared;
        }

        void _MakeShared()
        {
            shared = true;
        }
    };
}