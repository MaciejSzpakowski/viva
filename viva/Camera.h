#pragma once

namespace viva
{
	template <class Vector, class Matrix>
	class Camera : public Dynamic
	{
	private:
		Matrix view;
		Matrix proj;
		Matrix up;
		float nearPlane;
		float farPlane;
		float fovAngle;
		float aspectRatio;
	public:
		Camera(const Vector& pos,const  Vector& rot,const Vector& sca, float near, 
			float far, float fov, float aspect):Dynamic(pos,rot,sca),nearPlane(near),
			farPlane(far),fovAngle(fov),aspectRatio(aspect) {}
		/*XMFLOAT3 GetCursorWorldPos(float z);
		XMFLOAT2 GetFrustumSize(float z);
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();*/
		void Destroy() override;

		void Transform() override;
	};
}