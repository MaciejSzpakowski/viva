#include "Win32.h"

namespace viva
{
	void D3D11PixelShader::Destroy()
	{
		if (ps != nullptr)
			ps->Release();

		delete this;
	}

	void D3D11VertexShader::Destroy()
	{
		if (vs != nullptr)
			vs->Release();

		delete this;
	}

	void D3D11RenderTarget::Draw()
	{
	}

	void D3D11RenderTarget::Destroy()
	{
		delete this;
	}

	void D3D11Polygon::Destroy()
	{
		delete this;
	}

	D3D11Polygon::D3D11Polygon(ID3D11Device* device, const vector<Point>& points)
	{
		int n = points.size();
		float radius = 0;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;				   // GPU writes and reads
		bd.ByteWidth = sizeof(Vertex) * n;             // size is the VERTEX struct * n
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = 0;		                   // CPU does nothing

		for (int i = 0; i < n; i++)
		{
			float distFromOrigin = sqrtf(points[i].x*points[i].x + points[i].y*points[i].y);
			if (distFromOrigin > radius)
				radius = distFromOrigin;
			transformedVertices.push_back(DirectX::XMVectorSet(points[i].x, points[i].y, 0, 0));
			vertices.push_back({ points[i].x, points[i].y});
		}

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertices.data();  //Memory in CPU to copy in to GPU

		device->CreateBuffer(&bd, &sd, &vertexBuffer);
	}

	void D3D11Polygon::Draw()
	{
	}

	void D3D11Polygon::Transform()
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

	void D3D11Sprite::Destroy()
	{
		delete this;
	}

	void D3D11Sprite::Draw()
	{
	}

	void D3D11Sprite::Transform()
	{
	}

	void D3D11Texture::Destroy()
	{
		if (cached)
			ResourceManager::Get().RemoveResource(name);

		shaderResource->Release();
		delete this;
	}

}