#include <viva/viva.h>

namespace viva
{
    Transform::Transform():
        position(), rotation(0), scale({1,1,1,1}),size(1)
        {}

    void Transform::SetPosition(float x, float y, float z)
    {
        position.X(x);
        position.Y(y);
        position.Z(z);
    }

    void Transform::SetPosition(float x, float y)
    {
        position.X(x);
        position.Y(y);
    }

    void Transform::Translate(float x, float y, float z)
    {
        position.X(position.X() + x);
        position.Y(position.Y() + y);
        position.Z(position.Z() + z);
    }

    void Transform::Translate(const Vector& v)
    {

    }
}