#pragma once

namespace viva
{
    class Node
    {
    protected:
        Transform transform;
    public:
        virtual void Destroy() = 0;

        virtual void _Transform() = 0;
    };
}