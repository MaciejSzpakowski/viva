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
        // size: viewport size
        Camera(const Size& size);
		/*XMFLOAT3 GetCursorWorldPos(float z);
		XMFLOAT2 GetFrustumSize(float z);
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();*/

        const Matrix& _GetView() const { return view; }
        const Matrix& _GetProj() const { return proj; }

        void Destroy();
	};
}