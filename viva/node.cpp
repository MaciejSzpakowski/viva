#include "viva.h"

namespace viva
{
    // Generic game object.
    class Node
    {
    public:
        Node() 
        {
        }

        // Remove from all managers and memory.
        virtual void Destroy() = 0;

        // Get transform of the object.
        virtual Transform* T() = 0;

        // Get transform of the object.
        virtual Transform* GetTransform() = 0;
    };
}