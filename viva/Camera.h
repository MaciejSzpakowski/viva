#pragma once

namespace viva
{
	class Camera : public Dynamic
	{
	private:
		Matrix zView;
		Matrix zProj;
		Matrix zUp;
		float zNearPlane;
		float zFarPlane;
		float zFovAngle;
		float zAspectRatio;
	public:
		Camera() {}
		/*XMFLOAT3 GetCursorWorldPos(float z);
		XMFLOAT2 GetFrustumSize(float z);
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();*/
		void Destroy() override;

		void Transform() override;
	};
}