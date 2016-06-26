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
        Node() : index(-1) {}
        // Remove from all managers and memory.
        virtual void Destroy() = 0;

        // Get transform of the object.
        Transform* T() { return &transform; }
        
        int _GetIndex() const { return index; }

        void _SetIndex(int i) { index = i; }
    };
}