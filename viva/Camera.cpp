#include <viva/proto.h>

namespace viva
{
    Camera::Camera(const Size& size)
    {
        nearPlane = 0.1f;
        farPlane = 1000.0f;
        fovAngle = 0.4f*3.14f; //72 deg
                               //Camera information
        transform.SetPosition(0, 0, -20);
        Vector target(0.0f, 0.0f, 0.0f, 0.0f);
        up = Vector(0.0f, 1.0f, 0.0f, 0.0f);

        //Set the View matrix
        Matrix::LookAtLH(transform.GetPosition(), target, up, &view);

        //Set the Projection matrix
        aspectRatio = (float)size.Width / size.Height;
        Matrix::PerspectiveFovLH(fovAngle, aspectRatio, nearPlane, farPlane, &proj);
    }

	/*void Camera::Transform()
	{
	}*/

	void Camera::Destroy()
	{
		delete this;
	}
}