#pragma once

#pragma message ("DirectXMath.h is temporary")
#include <DirectXMath.h>

namespace viva
{
    namespace Math
    {
        extern float Pi;

        inline float Deg2Rad(float deg)
        {
            return deg * 2 * Pi / 360;
        }

        inline float Rad2Deg(float rad)
        {
            return rad * 360 / 2 / Pi;
        }
    }

    union Vector
    {
        __m128 m;
        struct {
            float x;
            float y;
            float z;
            float w;
        }f;
        DirectX::XMVECTOR v;

        Vector(float x=0, float y=0, float z=0, float w=0) { f = { x,y,z,w }; }

        static Vector Zero() { return Vector(0, 0, 0, 0); }
        static Vector One() { return Vector(1, 1, 1, 1); }

        float X() const { return f.x; }
        float Y()const { return f.y; }
        float Z()const { return f.z; }
        float W()const { return f.w; }

        void X(float x) { f.x = x; }
        void Y(float y) { f.y = y; }
        void Z(float z) { f.z = z; }
        void W(float w) { f.w = w; }

        /*static void Add(const Vector& v1, const Vector& v2);

        static void Multiply(float scalar);

        void Normalize();

        void NormalizeEst();*/
    };

    union Matrix
    {
        struct
        {
            __m128 r0;
            __m128 r1;
            __m128 r2;
            __m128 r3;
        }f;
        DirectX::XMMATRIX m;

        Matrix() { }
        Matrix(const DirectX::XMMATRIX& _m) { m = _m; }
        Matrix(DirectX::XMMATRIX&& _m) { m = _m; }

        static void LookAtLH(const Vector& position, const Vector& target, 
            const Vector& up, Matrix* result);

        static void PerspectiveFovLH(float fovAngle, float aspectRatio, float nearPlane, 
            float farPlane, Matrix* result);

        static void Translation(const Vector& position, Matrix* result);

        static void Scale(const Point& scale, Matrix* result);

        static void Multiply(const Matrix& m1, const Matrix& m2, Matrix* result);
        
        static void Identity(Matrix* result);

        static void Rotation(float angle, Matrix* result);

        void Transpose();
    };
}