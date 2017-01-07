#include <viva/viva.h>

namespace viva
{
    Camera::Camera(const Size& size)
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

    Size Camera::GetFrustumSize(float z)
    {
        Size s;
        s.Width = (20 + z) * tan(fovAngle / 2) * aspectRatio * 2;
        s.Height = (20 + z) * tan(fovAngle / 2) * 2;
        return s;
    }

    void Camera::_CalcViewProj()
    {
        Matrix::Multiply(view, proj, &viewProj);
    }

    Point Camera::WorldToScreen(const Vector& pos) const
    {
        Vector res;
        Matrix::Multiply(viewProj, pos, &res);

        return Point(res.X(), res.Y());
    }

    Vector Camera::ScreenToWorld(const Point& pos, float z) const
    {
        return Vector();
    }

	void Camera::Destroy()
	{
		delete this;
	}
}