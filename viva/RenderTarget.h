#pragma once

namespace viva
{
	class RenderTarget
	{
	private:
		ID3D11Texture2D* tex;
		ID3D11RenderTargetView* rtv;
		ID3D11ShaderResourceView* srv;

		vector<RenderTarget*>* parentContainer;
		PixelShader* pixelShader;
		vector<Polygon*> polygons;
		//vector<Sprite*> sprites;
		//vector<BitmapText*> texts;

	public:
		RenderTarget(ID3D11Texture2D* _tex, ID3D11RenderTargetView* _rtv, ID3D11ShaderResourceView* _srv) :
			tex(_tex), rtv(_rtv), srv(_srv), parentContainer(nullptr) {}

		void Draw(ID3D11DeviceContext* context, ID3D11DepthStencilView* dsv, PixelShader* defaultPs,
			ID3D11RasterizerState* wireframe, float gametime, Camera* cam, ID3D11Buffer* cbbuffervs);

		// move to the top of the stack
		void MoveToTop();

		// move to the bottom of the stack
		void MoveToBottom();

		// move one place up i.e. swap with one above
		void MoveUp();

		// move one place down i.e. swap with one below
		void MoveDown();

		// used by draw manager to insert
		void Insert(vector<RenderTarget*>* _parentContainer);

		// unsed by draw manager to remove
		void Remove();

		// dstroy the render target and all objects on it
		void Destroy();
	};
}