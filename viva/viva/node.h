#pragma once

namespace viva
{
    // Generic game object.
    class Node
    {
    protected:
        Transform transform;
        int index; // sometimes used by managers
    public:
        // Remove from all managers and memory.
        virtual void Destroy() = 0;

        // Get transform of the object.
        Transform* T() { return &transform; }

        // Transform the object.
        virtual void _Transform() = 0;

        // Get index.
        int _GetIndex() const { return index; }

        // Set index.
        // i: index
        int SetIndex(int i) { index = i; }
    };
}