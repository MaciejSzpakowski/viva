#pragma once
#include <viva/types.h>
#include <viva/math.h>

namespace viva
{
	class Camera
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
	};
}