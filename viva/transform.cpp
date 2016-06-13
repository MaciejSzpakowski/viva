#include <viva/viva.h>

namespace viva
{
    Transform::Transform():
        position(), rotation(0), scale({1,1}),size(1),
        parent(nullptr)
        {}

    void Transform::GetWorld(Matrix* dst)
    {
        Matrix::Translation(Vector(-origin.f.x, -origin.f.y, 0), dst);
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

    void Transform::GetWorldViewProj(Matrix* dst)
    {
        GetWorld(dst);

        Matrix::Multiply(*dst, camera->GetView(), dst);
        Matrix::Multiply(*dst, camera->GetProj(), dst);
    }

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
        position.Add(v);
    }
}