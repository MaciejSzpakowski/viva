#include "viva.h"

namespace viva
{
    class Camera
    {
    private:
        Transform transform;
        Matrix view;
        Matrix proj;
        Matrix viewProj;
        Vector up;
        float nearPlane;
        float farPlane;
        float fovAngle;
        float aspectRatio;
    public:
        // Default ctor.
        // size: viewport size
        Camera(const Size& size)
        {
            nearPlane = 0.1f;
            farPlane = 50.0f;
            fovAngle = 0.4f*3.14f; //72 deg
                                   //Camera information
            transform.SetPosition(0, 0, -20);  // by default camera is at -20
            Vector target(0.0f, 0.0f, 0.0f, 0.0f);
            up = Vector(0.0f, 1.0f, 0.0f, 0.0f);

            //Set the View matrix
            Matrix::LookAtLH(transform.GetPosition(), target, up, &view);

            //Set the Projection matrix
            aspectRatio = (float)size.Width / size.Height;
            Matrix::PerspectiveFovLH(fovAngle, aspectRatio, nearPlane, farPlane, &proj);
        }

        /*XMFLOAT3 GetCursorWorldPos(float z);
        XMMATRIX GetViewMatrix();
        XMMATRIX GetProjMatrix();*/

        // Get size on frustum/viewport in world coordinates at speciic Z.
        // It's different at different distance from the camera.
        // z: z offset in world coordinates
        Size GetFrustumSize(float z)
        {
            Size s;
            s.Width = (20 + z) * tan(fovAngle / 2) * aspectRatio * 2;
            s.Height = (20 + z) * tan(fovAngle / 2) * 2;
            return s;
        }

        // Get view matrix.
        const Matrix& GetView() const
        {
            return view;
        }

        // Get projection matrix.
        const Matrix& GetProj() const
        {
            return proj;
        }

        // Get viewProj matrix. Cached once per frame.
        const Matrix& GetViewProj() const
        {
            return viewProj;
        }

        void _CalcViewProj()
        {
            Matrix::Multiply(view, proj, &viewProj);
        }

        // Returns screen coordinates in pixels of the given world coordinates
        Point WorldToScreen(const Vector& pos) const
        {
            Vector res;
            Matrix::Multiply(viewProj, pos, &res);

            return Point(res.X(), res.Y());
        }

        Vector ScreenToWorld(const Point& pos, float z) const
        {
            return Vector();
        }

        void Destroy()
        {
            delete this;
        }
    };
}