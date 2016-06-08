#pragma once

#include <viva/math.h>

namespace viva
{
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

        void Translate(float x, float y, float z);

        void Translate(const Vector& v);
    };
}