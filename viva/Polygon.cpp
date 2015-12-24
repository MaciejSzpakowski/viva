#include "Viva.h"

namespace viva
{

	Polygon::Polygon(XMFLOAT2 points[], int n)
	{
		Color = Color(0, 0, 0, 0);
		zVertexCount = n;
		zRadius = 0;

		/*/method 1
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;                // CPU writes, GPU reads
		bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // CPU writes
		Device->CreateBuffer(&bd, NULL, &vertexBuffer);

		VERTEX* vertices = new VERTEX[n];
		for (int i = 0; i < n; i++)
		vertices[i] = { points[i].x, points[i].y, 0.0f, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };

		D3D11_MAPPED_SUBRESOURCE ms;
		Context->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, vertices, sizeof(VERTEX)*n);
		Context->Unmap(vertexBuffer, NULL);
		delete[] vertices;//*/

		//method 2
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;				   // GPU writes and reads
		bd.ByteWidth = sizeof(Vertex) * n;	           // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = 0;		                   // CPU does nothing

		Vertex* vertices = new Vertex[n];
		for (int i = 0; i < n; i++)
		{
			float distFromOrigin = sqrtf(points[i].x*points[i].x + points[i].y*points[i].y);
			if (distFromOrigin > zRadius)
				zRadius = distFromOrigin;
			zVertices.push_back(XMVectorSet(points[i].x, points[i].y, 0, 0));
			vertices[i] = { points[i].x, points[i].y, 0, 1, 1, 1, 0, 0 };
		}
		zTransformedVertices = zVertices;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertices;                   //Memory in CPU to copy in to GPU

		Core->zDevice->CreateBuffer(&bd, &sd, &zVertexBuffer);
		delete[] vertices;//*/
	}

	Polygon* Polygon::Clone()
	{
		Polygon* newPoly = new Polygon(*this);
		newPoly->zIndex = -1;
		newPoly->zChildren.clear();
		DrawManager->AddPoly(newPoly, newPoly->zRenderTarget);
		return newPoly;
	}

	XMMATRIX Polygon::zGetScaleMatrix()
	{
		return XMMatrixIdentity();
	}

	void Polygon::Destroy()
	{
		delete this;
	}

	void Polygon::Transform()
	{
		DirectX::XMMATRIX scale = DirectX::XMMatrixIdentity();
		//DirectX::XMMATRIX origin = XMMatrixTranslation(-Origin.x, -Origin.y, 0);
		//DirectX::XMMATRIX norigin = XMMatrixTranslation(Origin.x, Origin.y, 0);
		DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYawFromVector(zRotation);
		DirectX::XMMATRIX loc = DirectX::XMMatrixTranslationFromVector(zPosition);
		//zWorld = origin * scale * rot * loc * norigin;
		if (zParent != nullptr)
		{
			XMMATRIX parentLoc = XMMatrixRotationRollPitchYawFromVector(zParent->zRotation);
			XMMATRIX parentRot = XMMatrixTranslationFromVector(zParent->zPosition);
			zWorld = zWorld * parentLoc * parentRot;
		}
		XMMATRIX worldViewProj = zWorld * Camera->zView * Camera->zProj;
		//check for cursor
		/*if (Pickable)
			zCheckForCursor(zWorld);*/
		worldViewProj = XMMatrixTranspose(worldViewProj);
		Core->zContext->UpdateSubresource(DrawManager->zCbBufferVS, 0, NULL, &worldViewProj, 0, 0);
	}
}