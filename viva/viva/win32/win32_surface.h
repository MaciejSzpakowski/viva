#pragma once

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
            ID3D11ShaderResourceView* s):
            tex(t),rtv(r),srv(s)
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

        void _DrawAll() override;

        void _Draw() override;

        void Destroy() override;
    };
}