#include "viva.h"

namespace viva
{
    enum class TransformMode
    {
        World, Screen
    };

    // Transform object responsible for position, rotation, scale etc. of its owner.
    class Transform
    {
    public:
        
    private:
        Transform* parent;
        vector<Transform*> children;
        uint index; // index in parents collection
        TransformMode mode;

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
        Transform() 
            : position(), rotation(0), scale({ 1,1 }), size(1),
            parent(nullptr), mode(TransformMode::World), index(-1)
        {
        }

        Transform* SetCoordMode(TransformMode m)
        {
            mode = m;
            return this;
        }

        TransformMode GetMode() const
        {
            return mode;
        }

        // Converts rotation, scale, position and parent relationship to matrix transformation.
        void GetWorld(Matrix* dst)
        {
            Matrix::Translation(Vector(-origin.f.x, -origin.f.y, 0, 0), dst);
            Matrix sca, rot, loc;
            Matrix::Scaling({ scale.X * size, scale.Y * size }, &sca);
            Matrix::Rotation(rotation, &rot);
            Matrix::Translation(position, &loc);

            Matrix::Multiply(*dst, sca, dst);
            Matrix::Multiply(*dst, rot, dst);
            Matrix::Multiply(*dst, loc, dst);

            /*if (parent != nullptr)
            {
            XMMATRIX parentRot = XMMatrixRotationRollPitchYawFromVector(parent->absoluteRotation);
            XMMATRIX parentLoc = XMMatrixTranslationFromVector(parent->absolutePosition);
            XMMATRIX parentRotLoc = parentRot * parentLoc;
            absolutePosition = DirectX::XMVector3Transform(position, parentRotLoc);
            absoluteRotation = rotation + parent->absoluteRotation;
            world = world * parentRotLoc;
            }
            else
            {
            absolutePosition = position;
            absoluteRotation = rotation;
            }*/
        }

        void GetWorldViewProj(Matrix* dst)
        {
            if (mode == TransformMode::World)
            {
                GetWorld(dst);
                Matrix::Multiply(*dst, camera->GetViewProj(), dst);
            }
            else
            {
                GetWorldScreen(dst);
            }
        }

        void GetWorldScreen(Matrix* dst)
        {
            auto screenSize = engine->GetClientSize();
            float w = scale.X * size / screenSize.Width;
            float h = scale.Y * size / screenSize.Height;

            float ox = origin.GetX() / screenSize.Width + w;
            float oy = origin.GetY() / screenSize.Height - h;

            float x = position.GetX() * 2 / screenSize.Width - 1;
            float y = -position.GetY() * 2 / screenSize.Height + 1;

            Matrix::Identity(dst);
            Matrix sca, ori, rot, loc;

            Matrix::Translation(Vector(ox, oy, 0, 0), &ori);
            Matrix::Scaling({ w,h }, &sca);
            Matrix::Rotation(rotation, &rot);
            Matrix::Translation(Vector(x, y, position.GetZ(), 0), &loc);

            Matrix::Multiply(*dst, sca, dst);
            Matrix::Multiply(*dst, ori, dst);
            //Matrix::Multiply(*dst, rot, dst);
            Matrix::Multiply(*dst, loc, dst);
        }

        //// ORIGIN   //////
        Transform* SetOrigin(float x, float y) 
        { 
            origin.f.x = x; origin.f.y = y;
            return this;
        }

        Transform* SetOrigin(const Vector& v)
        { 
            origin = v;
            return this;
        }

        const Vector& GetOrigin() const 
        { 
            return origin; 
        }

        /////   POSITION  ////
        Transform* SetPosition(float x, float y, float z)
        {
            position.SetX(x);
            position.SetY(y);
            position.SetZ(z);
            return this;
        }

        Transform* SetPosition(float x, float y)
        {
            position.SetX(x);
            position.SetY(y);
            return this;
        }

        Transform* SetX(float x)
        { 
            position.SetX(x);
            return this;
        }

        Transform* SetY(float y)
        { 
            position.SetY(y);
            return this;
        }

        Transform* SetZ(float z)
        { 
            position.SetZ(z);
            return this;
        }

        Transform* SetPosition(const Vector& v)
        { 
            position = v;
            return this;
        }

        const Vector& GetPosition() const 
        { 
            return position; 
        }

        // Simply position += (x,y,z).
        // x: delta x
        // y: delta y
        // z: delta z
        Transform* Translate(float x, float y, float z)
        {
            position.Add(Vector(x, y, z, 0));

            return this;
        }

        // Simply position += v.
        // v: delta
        Transform* Translate(const Vector& v)
        {
            position.Add(v);
            return this;
        }

        /////    ROTATION    ///////
        Transform* SetRotation(float radians)
        { 
            rotation = radians;
            return this;
        }

        float GetRotation() const 
        { 
            return rotation; 
        }

        // Simply rotation += angle. Positive angle rotates ccw.
        // angle: delta
        Transform* Rotate(float angle)
        { 
            rotation += angle;
            return this;
        }

        ///////     SCALE    //////
        Transform* SetScale(float width, float height)
        {
            scale.X = width;
            scale.Y = height;
            return this;
        }

        Transform* SetScale(const Point& s)
        { 
            scale = s;
            return this;
        }

        Transform* SetScaleX(float x)
        { 
            scale.X = x;
            return this;
        }

        Transform* SetScaleY(float y)
        {
            scale.Y = y;
            return this;
        }

        const Point& GetScale() const 
        { 
            return scale; 
        }

        // Simply scale += s
        Transform* Scale(const Point& s)
        { 
            scale.X += s.X; scale.Y += s.Y;
            return this;
        }

        /////     SIZE     //////
        Transform* SetSize(float s)
        { 
            size = s;
            return this;
        }

        float GetSize() const
        { 
            return size; 
        }

        Transform* Grow(float factor)
        {
            size *= factor;
            return this;
        }

        Transform* Shrink(float factor)
        { 
            size /= factor;
            return this;
        }

        Transform* SetParent(Transform* p)
        {
            if (index != -1)
                throw Error(__FUNCTION__, "Object can have only one parent");

            parent = p;
            index = parent->children.size();
            parent->children.push_back(this);

            return this;
        }

        Transform* GetParent()
        {
            return parent;
        }

        Transform* RemoveChild(Transform* child)
        {
            if (child->index == -1)
                throw Error(__FUNCTION__, "Object doesn't have a parent");

            if(children.at(child->index) != child)
                throw Error(__FUNCTION__, "Wrong index");

            children.erase(children.begin() + child->index);
            child->index = -1;
            child->parent = nullptr;

            return this;
        }
    };
}
