#include "Viva.h"

namespace viva
{
	void RenderTarget::MoveToTop()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveToTop()\nThis render target is not on a render target list");

		if (it == parentContainer->begin())
			return;

		parentContainer->erase(it);
		parentContainer->insert(parentContainer->begin(), this);
	}

	void RenderTarget::MoveToBottom()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveToBottom()\nThis render target is not on a render target list");

		if (it == parentContainer->end() - 1)
			return;

		parentContainer->erase(it);
		parentContainer->push_back(this);
	}

	void RenderTarget::MoveUp()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveUp()\nThis render target is not on a render target list");

		if (it == parentContainer->begin())
			return;

		it--;
		auto temp = *it;
		*it = this;
		it++;
		*it = temp;
	}

	void RenderTarget::MoveDown()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveDown()\nThis render target is not on a render target list");

		if (it == parentContainer->end() - 1)
			return;

		it++;
		auto temp = *it;
		*it = this;
		it--;
		*it = temp;
	}

	void RenderTarget::Insert(vector<RenderTarget*>* _parentContainer)
	{
		if(_parentContainer != nullptr)
			throw std::runtime_error("RenderTarget::Insert()\nThis render target has a container already");

		parentContainer = _parentContainer;
		parentContainer->push_back(this);
	}

	void RenderTarget::Remove()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::Remove()\nThis render target is not on a render target list");

		parentContainer->erase(it);
		parentContainer = nullptr;
	}

	void RenderTarget::Draw(ID3D11DeviceContext* context, ID3D11DepthStencilView* dsv, PixelShader* defaultPs,
		ID3D11RasterizerState* wireframe, float gametime, Camera* cam, ID3D11Buffer* cbbuffervs)
	{
		context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		/*if (Core->EnableAlpha)
			Core->zContext->OMSetBlendState(Core->zBlendState, 0, 0xffffffff);*/

		context->OMSetRenderTargets(1, &rtv, dsv);
		float four0[4] = { 0, 0, 0, 0 };
		context->ClearRenderTargetView(rtv, four0);

		//polys
		context->PSSetShader(defaultPs->ps, 0, 0);
		context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
		context->RSSetState(wireframe);
		for (Polygon* p : polygons)
		{
			p->zUpdate(gametime);
			p->zTransform(cam->GetViewMatrix(),cam->GetProjMatrix(),context, cbbuffervs);
			if (p->Visible)
			{
				p->zDraw();
			}
		}

		//sprites, animations
		//Core->zContext->RSSetState(DrawManager->zSolid);
		//Core->zContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//UINT stride = sizeof(Vertex);
		//UINT offset = 0;
		//Core->zContext->IASetVertexBuffers(0, 1, &DrawManager->zVertexBufferSprite, &stride, &offset);
		//if (Core->EnableAlpha)
		//	std::sort(zSprites.begin(), zSprites.end(), myfunc);
		//for (CSprite* s : zSprites)
		//{
		//	s->zUpdate();
		//	s->zSpriteUpdate();
		//	s->zPlay();
		//	s->zTransform();
		//	if (s->Visible)
		//	{
		//		if (s->TexFilter == TEX_FILTER::LINEAR)
		//			Core->zContext->PSSetSamplers(0, 1, &DrawManager->zLineSampler);
		//		else
		//			Core->zContext->PSSetSamplers(0, 1, &DrawManager->zPointSampler);
		//		s->zDraw();
		//	}
		//}
		////bitmap text
		//for (CBitmapText* t : zTexts)
		//{
		//	t->zUpdate();
		//	if (t->Visible)
		//	{
		//		if (t->TexFilter == TEX_FILTER::LINEAR)
		//			Core->zContext->PSSetSamplers(0, 1, &DrawManager->zLineSampler);
		//		else
		//			Core->zContext->PSSetSamplers(0, 1, &DrawManager->zPointSampler);
		//		t->zDraw();
		//	}
		//}
	}

	void RenderTarget::Destroy()
	{
		throw std::runtime_error("Not implemented RenderTarget::Destroy()");
	}
}