#include <viva/viva.h>

namespace viva
{
    Transform::Transform():
        position(), rotation(0), scale({1,1}),size(1),
        parent(nullptr), mode(Mode::World)
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

    void Transform::GetWorldScreen(Matrix* dst)
    {
        auto screenSize = engine->GetClientSize();
        float w = scale.X * size / screenSize.Width;
        float h = scale.Y * size / screenSize.Height;

        float ox = origin.X() / screenSize.Width + w;
        float oy = origin.Y() / screenSize.Height - h;

        float x = position.X() * 2 / screenSize.Width - 1;
        float y = - position.Y() * 2 / screenSize.Height + 1;

        static float d = 0;
        if (keyboard->IsKeyDown(Input::KeyboardKey::Left))
            d += time->GetFrameTime();
        else if (keyboard->IsKeyDown(Input::KeyboardKey::Right))
            d -= time->GetFrameTime();

        auto t = std::to_wstring(d);
        window->SetWindowTitle(t);

        Matrix::Identity(dst);

        Matrix sca, ori, rot, loc;

        Matrix::Translation(Vector(ox, oy, 0), &ori);
        Matrix::Scaling({ w,h }, &sca);
        Matrix::Rotation(rotation, &rot);
        Matrix::Translation(Vector(x, y, position.Z()), &loc);

        Matrix::Multiply(*dst, sca, dst);
        Matrix::Multiply(*dst, ori, dst);
        //Matrix::Multiply(*dst, rot, dst);
        Matrix::Multiply(*dst, loc, dst);
    }

    void Transform::GetWorldViewProj(Matrix* dst)
    {
        if (mode == Mode::World)
        {
            GetWorld(dst);
            Matrix::Multiply(*dst, camera->GetViewProj(), dst);
        }
        else
        {
            GetWorldScreen(dst);
        }
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