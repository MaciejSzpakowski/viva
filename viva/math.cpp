#include <viva/viva.h>

namespace viva
{
    namespace Math
    {
        float Pi = 3.1415926f;
    }

    void Matrix::LookAtLH(const Vector& position, const Vector& target, const Vector& up, Matrix* result)
    {
        result->m = DirectX::XMMatrixLookAtLH(position.v, target.v, up.v);
    }

    void  Matrix::PerspectiveFovLH(float fovAngle, float aspectRatio, float nearPlane, float farPlane, Matrix* result)
    {
        result->m = DirectX::XMMatrixPerspectiveFovLH(fovAngle, aspectRatio, nearPlane, farPlane);
    }

    void Matrix::Translation(const Vector& position, Matrix* result)
    {
        result->m = DirectX::XMMatrixTranslationFromVector(position.v);
    }

    void Matrix::Scale(const Point& scale, Matrix* result)
    {
        result->m = DirectX::XMMatrixScaling(scale.X, scale.Y, 1);
    }

    void Matrix::Transpose()
    {
        m = DirectX::XMMatrixTranspose(m);
    }

    void Matrix::Multiply(const Matrix& m1, const Matrix& m2, Matrix* result)
    {
        result->m = DirectX::XMMatrixMultiply(m1.m, m2.m);
    }
    
    void Matrix::Identity(Matrix* result)
    {
        result->m = DirectX::XMMatrixIdentity();
    }

    void Matrix::Rotation(float angle, Matrix* result)
    {
        result->m = DirectX::XMMatrixRotationZ(angle);
    }
}