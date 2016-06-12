#pragma once

namespace viva
{
    using std::vector;

    class Win32Polygon : public Polygon
    {
    private:
        ID3D11Buffer* vertexBuffer;
        Win32PixelShader* ps;
    public:
        Win32Polygon(ID3D11Buffer* vertexbuffer, int count);

        void Destroy() override;

        PixelShader* GetPixelShader() override
        {
            return ps;
        }

        void SetPixelShader(PixelShader* _ps) { ps = (Win32PixelShader*)_ps; }
        
        void _Draw() override;

        void _Transform() override;
    };
}