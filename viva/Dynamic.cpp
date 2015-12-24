#include "Viva.h"

namespace viva
{
	Dynamic::Dynamic()
	{
		zVertexCount = 0;
		zVertexBuffer = nullptr;
		Visible = true;
		UV = Rect(0, 0, 1, 1);
		color = Color(0.0f, 0, 0, 0);
		zIndex = -1;
		zExtraBufferPSdata = nullptr;
		TransformVertices = false;
		zPosition = zAbsolutePosition = XMVectorZero();
		zRotation = zAbsoluteRotation = XMVectorZero();
		zVelocity = XMVectorZero();
		zAcceleration = XMVectorZero();
		zAngularAcc = XMVectorZero();
		zAngularVel = XMVectorZero();
		Origin = { 0, 0 };
		SizeAcceleration = 0;
		SizeVelocity = 0;
		size = 1;
		zParent = nullptr;
		Pickable = false;
		zUnderCursor = false;
	}

	void Dynamic::SetExtraBufferPS(void* data)
	{
		zExtraBufferPSdata = data;
	}

	void Dynamic::zTransform(XMMATRIX _view, XMMATRIX _proj, 
		ID3D11DeviceContext* context, ID3D11Resource* zCbBufferVS)
	{
		if (TransformVertices)
			zTransformVertices();

		zAbsolutePosition = zPosition;
		zAbsoluteRotation = zRotation;
		XMMATRIX origin = XMMatrixTranslation(-Origin.x, -Origin.y, 0);
		XMMATRIX scale = zGetScaleMatrix();
		XMMATRIX rot = XMMatrixRotationRollPitchYawFromVector(zAbsoluteRotation);
		XMMATRIX loc = XMMatrixTranslationFromVector(zAbsolutePosition);
		zWorld = origin * scale * rot * loc;
		if (zParent != nullptr)
		{
			XMMATRIX parentRot = XMMatrixRotationRollPitchYawFromVector(zParent->zAbsoluteRotation);
			XMMATRIX parentLoc = XMMatrixTranslationFromVector(zParent->zAbsolutePosition);
			zAbsolutePosition += zParent->zAbsolutePosition;
			zAbsoluteRotation += zParent->zAbsoluteRotation;
			zAbsolutePosition = XMVector2Transform(zAbsolutePosition, parentRot);
			zWorld = zWorld * parentRot * parentLoc;
		}
		XMMATRIX worldViewProj = zWorld * _view * _proj;
		//check for cursor
		if (Pickable)
			zCheckForCursor(zWorld);
		worldViewProj = XMMatrixTranspose(worldViewProj);
		context->UpdateSubresource(zCbBufferVS, 0, NULL, &worldViewProj, 0, 0);
	}

	void Dynamic::zUpdate(float frameTime)
	{
		XMVECTOR a = zAcceleration * frameTime;
		XMVECTOR v = zVelocity * frameTime;
		zVelocity += a;
		zPosition += v;
		XMVECTOR ra = zAngularAcc * frameTime;
		XMVECTOR rv = zAngularVel * frameTime;
		zAngularVel += ra;
		zRotation += rv;
		float sa = SizeAcceleration * frameTime;
		SizeVelocity += sa;
	}

	bool Dynamic::IsUnderCursor()
	{
		return zUnderCursor;
	}

	void Dynamic::zTransformVertices()
	{
		for (int i = 0; i < zVertexCount; i++)
			zTransformedVertices[i] = XMVector2Transform(zVertices[i], zWorld);
	}

	Dynamic* Dynamic::GetParent()
	{
		return zParent;
	}

	void Dynamic::SetParent(Dynamic* parent)
	{
		//add this to parent's children if applicable
		if (parent != zParent && parent != nullptr)
			parent->zChildren.push_back(this);

		//remove this from parents children if applicable
		else if (zParent != parent && zParent != nullptr)
		{
			for (int i = 0; i < (int)zParent->zChildren.size(); i++)
			{
				if (zParent->zChildren[i] == this)
				{
					zParent->zChildren.erase(zParent->zChildren.begin() + i);
					break;
				}
			}
		}

		zParent = parent;
	}

	vector<Dynamic*> Dynamic::GetChildren()
	{
		return zChildren;
	}

	XMMATRIX Dynamic::GetWorldMatrix()
	{
		return zWorld;
	}

	void Dynamic::SetColor(float r, float g, float b, float a)
	{
		color = Color(r, g, b, a);
	}
}