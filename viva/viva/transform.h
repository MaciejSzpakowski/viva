#pragma once

#include <viva/math.h>

namespace viva
{
    // Transform object responsible for position, rotation, scale etc. of its owner.
    class Transform
    {
    public:
        enum class Mode
        {
            World, Screen
        };
    private:
        Transform* parent;
        vector<Transform*> children;
        Mode mode;

        Vector origin;
        Vector position;
        float rotation;
        Point scale;
        float size;

        Vector velocity;
        float angularVelocity;
        Point scaleVelocity;
        float sizeVelocity;

        Vector acceleration;
        float angularAcceleration;
        Point scaleAcceleration;
        float sizeAcceleration;

    public:
        // Ctor.
        Transform();

        void SetCoordMode(Mode m)
        {
            mode = m;
        }

        Mode GetMode() const
        {
            return mode;
        }

        // Converts rotation, scale, position and parent relationship to matrix transformation.
        void GetWorld(Matrix* dst);
        void GetWorldViewProj(Matrix* dst);
        void GetWorldScreen(Matrix* dst);

        //// ORIGIN   //////
        void SetOrigin(float x, float y) { origin.f.x = x; origin.f.y = y; }
        void SetOrigin(const Vector& v) { origin = v; }
        const Vector& GetOrigin() const { return origin; }

        /////   POSITION  ////
        void SetPosition(float x, float y, float z);
        void SetPosition(float x, float y);
        void SetPositionX(float x) { position.X(x); }
        void SetPositionY(float y) { position.Y(y); }
        void SetPositionZ(float z) { position.Z(z); }
        void SetPosition(const Vector& v) { position = v; }
        const Vector& GetPosition() const { return position; }                

        // Simply position += (x,y,z).
        // x: delta x
        // y: delta y
        // z: delta z
        void Translate(float x, float y, float z);

        // Simply position += v.
        // v: delta
        void Translate(const Vector& v);

        /////    ROTATION    ///////
        void SetRotation(float radians) { rotation = radians; }
        float GetRotation() const { return rotation; }

        // Simply rotation += angle. Positive angle rotates ccw.
        // angle: delta
        void Rotate(float angle) { rotation += angle; }
        
        ///////     SCALE    //////
        void SetScale(float width, float height) { scale.X = width; scale.Y = height; }
        void SetScale(const Point& s) { scale = s; }
        void SetScaleX(float x) { scale.X = x; }
        void SetScaleY(float y) { scale.Y = y; }

        const Point& GetScale() const { return scale; }

        // Simply scale += s
        void Scale(const Point& s) { scale.X += s.X; scale.Y += s.Y; }
        
        /////     SIZE     //////
        void SetSize(float s) { size = s; }
        float GetSize() const { return size; }
        void Grow(float factor) { size *= factor; }
        void Shrink(float factor) { size /= factor; }
    };
}