#include "viva.h"

namespace viva
{
    class Win32Surface : public Surface
    {
    private:
        ID3D11Texture2D* tex;
        ID3D11RenderTargetView* rtv;
        ID3D11ShaderResourceView* srv;
        Win32PixelShader* ps;
    public:
        Win32Surface(ID3D11Texture2D* t, ID3D11RenderTargetView* r,
            ID3D11ShaderResourceView* s) 
            : tex(t), rtv(r), srv(s)
        {
        }

        PixelShader* GetPixelShader() const override
        {
            return ps;
        }

        void SetPixelShader(PixelShader* _ps)
        {
            ps = (Win32PixelShader*)_ps;
        }

        void _DrawAll() override
        {
            d3d.context->ClearDepthStencilView(d3d.depthStencil,
                D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            //if (Core->IsAlphaEnabled())
            //   Core->_GetContext()->OMSetBlendState(Core->_GetBlendState(), 0, 0xffffffff);

            d3d.context->OMSetRenderTargets(1, &rtv, d3d.depthStencil);
            float four0[4] = { 0, 0, 0, 0 };
            d3d.context->ClearRenderTargetView(rtv, four0);

            for (int i = 0; i < drawables.size(); i++)
                drawables[i]->_Draw();
        }

        void _DrawSurface() override
        {
            d3d.context->PSSetShader(ps->ps, 0, 0);
            //tex
            d3d.context->PSSetShaderResources(0, 1, &srv);
            //draw
            d3d.context->DrawIndexed(6, 0, 0);
        }

        void Destroy() override
        {
            tex->Release();
            rtv->Release();
            srv->Release();
        }

        /*void RenderTarget::MoveToTop()
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
        }*/
    };
}
