#pragma once

namespace viva
{
	class Camera
	{
	private:
        Transform transform;
		Matrix view;
		Matrix proj;
		Vector up;
		float nearPlane;
		float farPlane;
		float fovAngle;
		float aspectRatio;
	public:
        // Default ctor.
        // size: viewport size
        Camera(const Size& size);

		/*XMFLOAT3 GetCursorWorldPos(float z);
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();*/

        // Get size on frustum/viewport in world coordinates at speciic Z.
        // It's different at different distance from the camera.
        // z: z offset in world coordinates
		Size GetFrustumSize(float z);

        // Get view matrix.
        const Matrix& GetView() const { return view; }

        // Get projection matrix.
        const Matrix& GetProj() const { return proj; }

        void Destroy();
	};
}