#include "viva.h"

namespace viva
{
    // Generic game object.
    class Node
    {
    protected:
        Transform transform;
    public:
        Node() 
        {
        }

        // Remove from all managers and memory.
        virtual void Destroy() = 0;

        // Get transform of the object.
        Transform* T() 
        { 
            return &transform; 
        }

        // Get transform of the object.
        Transform* GetTransform()
        {
            return &transform;
        }
    };
}