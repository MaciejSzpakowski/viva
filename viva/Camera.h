#pragma once

namespace viva
{
	class Camera : public Dynamic
	{
	public:
		XMMATRIX zView;
		XMMATRIX zProj;
		XMVECTOR zUp;
		XMMATRIX zGetScaleMatrix() override;
		void zCamTransform(float gametime);
		void zDraw() override {};
		float zNearPlane;
		float zFarPlane;
		float zFovAngle;
		float zAspectRatio;

		Camera(Size clientSize);
		XMFLOAT3 GetCursorWorldPos(float z);
		XMFLOAT2 GetFrustumSize(float z);
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();
		void Destroy();
	};
}