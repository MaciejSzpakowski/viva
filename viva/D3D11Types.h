#pragma once

namespace viva
{
	struct D3D11Rect
	{
		float left;
		float top;
		float right;
		float bottom;
		D3D11Rect() {}
		D3D11Rect(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}
	};

	struct D3D11PixelShader : public PixelShader
	{
		ID3D11PixelShader* ps;

		D3D11PixelShader(ID3D11PixelShader* _ps):ps(_ps) { }
		void Destroy() override;
	};

	struct D3D11VertexShader : public VertexShader
	{
		ID3D11VertexShader* vs;

		D3D11VertexShader(ID3D11VertexShader* _vs):vs(_vs) { }
		void Destroy() override;
	};

	class D3D11RenderTarget : public RenderTarget
	{
	private:
		ID3D11Texture2D* tex;
		ID3D11RenderTargetView* rtv;
		ID3D11ShaderResourceView* srv;
	public:
		D3D11RenderTarget(ID3D11Texture2D* _tex, ID3D11RenderTargetView* _rtv, ID3D11ShaderResourceView* _srv) :
			tex(_tex), rtv(_rtv), srv(_srv) {}

		void Draw() override;

		void Destroy() override;
	};

	class D3D11Dynamic : public Dynamic
	{
		vector<D3D11Dynamic>* parentContainer;
		int zVertexCount;
		vector<XMVECTOR> zVertices;
		vector<XMVECTOR> zTransformedVertices;
		int zIndex;
		ID3D11Buffer* zVertexBuffer;
		void* zExtraBufferPSdata;
		XMMATRIX zWorld;
		XMVECTOR zPosition;
		XMVECTOR zRotation;
		XMVECTOR zVelocity;
		XMVECTOR zAcceleration;
		XMVECTOR zAngularVel;
		XMVECTOR zAngularAcc;
		XMVECTOR zAbsolutePosition;
		XMVECTOR zAbsoluteRotation;
		D3D11Dynamic* zParent;
		vector<D3D11Dynamic*> zChildren;
		//matrix algebra for
		//produces worldViewProj used by VS
		void zTransform();
		//updates PVAJ etc.
		void zUpdate();
		virtual XMMATRIX zGetScaleMatrix() = 0;
		virtual void zCheckForCursor(XMMATRIX transform) {}
		bool zUnderCursor;
		virtual void zTransformVertices();
		virtual void zDraw() = 0;

		D3D11Dynamic* GetParent();
		void SetParent(D3D11Dynamic* parent);
		vector<D3D11Dynamic*> GetChildren();
		XMMATRIX GetWorldMatrix();
		bool IsUnderCursor();
		//used to send custom data to PS		
		void SetExtraBufferPS(void* data);
		D3D11Dynamic();

		bool Pickable;
		float SizeVelocity;
		float SizeAcceleration;
		float Size;
		XMFLOAT2 Origin;
		bool Visible;
		Color Color;
		D3D11Rect UV;
		bool TransformVertices;

		void SetColor(float r, float g, float b, float a);

		//repetitive code
		void SetPosition(XMFLOAT3 v) { zPosition = XMLoadFloat3(&v); }
		void SetPosition(float x, float y, float z) { zPosition = XMVectorSet(x, y, z, 1); }
		void SetPositionX(float x) { zPosition = XMVectorSetX(zPosition, x); }
		void SetPositionY(float y) { zPosition = XMVectorSetY(zPosition, y); }
		void SetPositionZ(float z) { zPosition = XMVectorSetZ(zPosition, z); }
		XMFLOAT3 GetPosition() { XMFLOAT3 v; XMStoreFloat3(&v, zPosition); return v; }
		XMVECTOR GetPositionVector() { return zPosition; }
		void SetVelocity(XMFLOAT3 v) { zVelocity = XMLoadFloat3(&v); }
		void SetVelocity(float x, float y, float z) { zVelocity = XMVectorSet(x, y, z, 1); }
		void SetVelocityX(float x) { zVelocity = XMVectorSetX(zVelocity, x); }
		void SetVelocityY(float y) { zVelocity = XMVectorSetY(zVelocity, y); }
		void SetVelocityZ(float z) { zVelocity = XMVectorSetZ(zVelocity, z); }
		XMFLOAT3 GetVelocity() { XMFLOAT3 v; XMStoreFloat3(&v, zVelocity); return v; }
		void SetAcceleration(XMFLOAT3 v) { zAcceleration = XMLoadFloat3(&v); }
		void SetAcceleration(float x, float y, float z) { zAcceleration = XMVectorSet(x, y, z, 1); }
		void SetAccelerationX(float x) { zAcceleration = XMVectorSetX(zAcceleration, x); }
		void SetAccelerationY(float y) { zAcceleration = XMVectorSetY(zAcceleration, y); }
		void SetAccelerationZ(float z) { zAcceleration = XMVectorSetZ(zAcceleration, z); }
		XMFLOAT3 GetAcceleration() { XMFLOAT3 v; XMStoreFloat3(&v, zAcceleration); return v; }
		void SetRotation(XMFLOAT3 v) { zRotation = XMLoadFloat3(&v); }
		void SetRotation(float x, float y, float z) { zRotation = XMVectorSet(x, y, z, 1); }
		void SetRotationX(float x) { zRotation = XMVectorSetX(zRotation, x); }
		void SetRotationY(float y) { zRotation = XMVectorSetY(zRotation, y); }
		void SetRotationZ(float z) { zRotation = XMVectorSetZ(zRotation, z); }
		XMFLOAT3 GetRotation() { XMFLOAT3 v; XMStoreFloat3(&v, zRotation); return v; }
		void SetAngularVel(XMFLOAT3 v) { zAngularVel = XMLoadFloat3(&v); }
		void SetAngularVel(float x, float y, float z) { zAngularVel = XMVectorSet(x, y, z, 1); }
		void SetAngularVelX(float x) { zAngularVel = XMVectorSetX(zAngularVel, x); }
		void SetAngularVelY(float y) { zAngularVel = XMVectorSetY(zAngularVel, y); }
		void SetAngularVelZ(float z) { zAngularVel = XMVectorSetZ(zAngularVel, z); }
		XMFLOAT3 GetAngularVel() { XMFLOAT3 v; XMStoreFloat3(&v, zAngularVel); return v; }
		void SetAngularAcc(XMFLOAT3 v) { zAngularAcc = XMLoadFloat3(&v); }
		void SetAngularAcc(float x, float y, float z) { zAngularAcc = XMVectorSet(x, y, z, 1); }
		void SetAngularAccX(float x) { zAngularAcc = XMVectorSetX(zAngularAcc, x); }
		void SetAngularAccY(float y) { zAngularAcc = XMVectorSetY(zAngularAcc, y); }
		void SetAngularAccZ(float z) { zAngularAcc = XMVectorSetZ(zAngularAcc, z); }
		XMFLOAT3 GetAngularAcc() { XMFLOAT3 v; XMStoreFloat3(&v, zAngularAcc); return v; }
		//It's different from position if object has a parent
		XMFLOAT3 GetAbsolutePosition() { XMFLOAT3 v; XMStoreFloat3(&v, zAbsolutePosition); return v; }
	};

	class D3D11Camera : public Camera
	{
	public:
		XMMATRIX zView;
		XMMATRIX zProj;
		XMVECTOR zUp;
		XMMATRIX zGetScaleMatrix() override;
		void zCamTransform();
		void zDraw() override {};
		float zNearPlane;
		float zFarPlane;
		float zFovAngle;
		float zAspectRatio;

		CCamera();
		XMFLOAT3 GetCursorWorldPos(float z);
		XMFLOAT2 GetFrustumSize(float z);
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();
		void Destroy();
	};

	class D3D11Drawable : public Drawable
	{
	};

	class D3D11Sprite : public Sprite
	{
	private:
	public:
		D3D11Sprite() {}

		void Destroy() override;

		void Draw() override;

		void Transform() override;
	};

	struct D3D11Matrix : public Matrix
    {
		DirectX::XMMATRIX matrix;
	};

	class D3D11Texture : public Texture
	{
	private:		
		ID3D11ShaderResourceView* shaderResource;
	public:
		D3D11Texture(const wstring& _name, ID3D11ShaderResourceView* _shaderResource)
			:Texture(_name)
		{
			shaderResource = _shaderResource;
		}
		void Destroy() override;
	};

	class D3D11Animation : public Animation
	{
	private:
	public:
	};

	class D3D11Polygon : public Polygon
	{
	private:
		ID3D11Buffer* vertexBuffer;
		vector<DirectX::XMVECTOR> transformedVertices;
	public:
		D3D11Polygon(ID3D11Device* device, const vector<Point>& points);

		void Destroy() override;

		void Draw() override;

		void Transform() override;
	};
}