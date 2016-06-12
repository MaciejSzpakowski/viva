#pragma once

#include <viva/math.h>

namespace viva
{
    // Transform object responsible for position, rotation, scale etc. of its owner.
    class Transform
    {
    private:
        Vector position;
        float rotation;
        Vector scale;
        float size;

        Vector velocity;
        float angularVelocity;
        Vector scaleVelocity;
        float sizeVelocity;

        Vector acceleration;
        float angularAcceleration;
        Vector scaleAcceleration;
        float sizeAcceleration;
    public:
        // Ctor.
        Transform();

        void SetPosition(float x, float y, float z);
        void SetPosition(float x, float y);
        void SetPositionX(float x) { position.X(x); }
        void SetPositionY(float y) { position.Y(y); }
        void SetPositionZ(float z) { position.Z(z); }

        void SetRotation(float radians) { rotation = radians; }
        
        const Vector& GetPosition() const
        {
            return position;
        }

        // Simply position + (x,y,z).
        // x: offset x
        // y: offset y
        // z: offset z
        void Translate(float x, float y, float z);

        // Simply position + v.
        // v: offset
        void Translate(const Vector& v);
    };
}