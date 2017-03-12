#include "viva.h"

namespace viva
{
    namespace Math
    {
        const float Pi = 3.1415926f;

        float Deg2Rad(float deg)
        {
            return deg * 2 * Pi / 360;
        }

        float Rad2Deg(float rad)
        {
            return rad * 360 / 2 / Pi;
        }
    }

    union Vector
    {
        __m128 m;
        struct {float x; float y; float z; float w; } f;
        DirectX::XMVECTOR v;

        Vector()
            :f{ 0,0,0,0 }
        {
        }

        Vector(float x, float y, float z, float w) 
            :f{ x,y,z,w }
        {
        }

        static Vector Zero() 
        { 
            return Vector(0, 0, 0, 0);
        }

        static Vector One() 
        {
            return Vector(1, 1, 1, 1);
        }

        float GetX() const 
        { 
            return f.x; 
        }

        float GetY() const 
        { 
            return f.y; 
        }

        float GetZ() const 
        { 
            return f.z; 
        }

        float GetW() const 
        { 
            return f.w; 
        }

        Vector* SetX(float x)
        { 
            f.x = x;
            return this;
        }

        Vector* SetY(float y)
        { 
            f.y = y;
            return this;
        }

        Vector* SetZ(float z)
        { 
            f.z = z;
            return this;
        }

        Vector* SetW(float w)
        { 
            f.w = w;
            return this;
        }

        // Adds rhs to this.
        // rhs: another vector
        Vector* Add(const Vector& rhs)
        {
            f.x += rhs.f.x;
            f.y += rhs.f.y;
            f.z += rhs.f.z;
            f.w += rhs.f.w;
            return this;
        }

        // Adds two vectors and returns a new one.
        Vector operator+(const Vector& rhs)
        {
            return Vector(f.x + rhs.f.x, f.y + rhs.f.y, f.z + rhs.f.z, f.w + rhs.f.w);
        }

        /*static void Multiply(float scalar);

        void Normalize();

        void NormalizeEst();*/
    };

    union Matrix
    {
        struct {__m128 r0; __m128 r1; __m128 r2; __m128 r3; } f;
        DirectX::XMMATRIX m;

        Matrix() 
        { 
        }

        Matrix(const DirectX::XMMATRIX& _m) 
        { 
            m = _m; 
        }

        Matrix(DirectX::XMMATRIX&& _m) 
        { 
            m = _m; 
        }

        static void LookAtLH(const Vector& position, const Vector& target, const Vector& up, Matrix* result)
        {
            result->m = DirectX::XMMatrixLookAtLH(position.v, target.v, up.v);
        }

        static void  PerspectiveFovLH(float fovAngle, float aspectRatio, float nearPlane, float farPlane, Matrix* result)
        {
            result->m = DirectX::XMMatrixPerspectiveFovLH(fovAngle, aspectRatio, nearPlane, farPlane);
        }

        static void Translation(const Vector& position, Matrix* result)
        {
            result->m = DirectX::XMMatrixTranslationFromVector(position.v);
        }

        static void Scaling(const Point& scale, Matrix* result)
        {
            result->m = DirectX::XMMatrixScaling(scale.X, scale.Y, 1);
        }

        static void Multiply(const Matrix& m1, const Matrix& m2, Matrix* result)
        {
            result->m = DirectX::XMMatrixMultiply(m1.m, m2.m);
        }

        static void Multiply(const Matrix& m, const Vector& v, Vector* result)
        {
            result->v = DirectX::XMVector3Transform(v.v, m.m);
        }

        static void Identity(Matrix* result)
        {
            result->m = DirectX::XMMatrixIdentity();
        }

        static void Rotation(float angle, Matrix* result)
        {
            result->m = DirectX::XMMatrixRotationZ(angle);
        }

        void Transpose()
        {
            m = DirectX::XMMatrixTranspose(m);
        }
    };
}
