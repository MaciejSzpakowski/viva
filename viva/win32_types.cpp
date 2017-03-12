#include "viva.h"

namespace viva
{
    class Win32PixelShader : public PixelShader
    {
    public:
        ID3D11PixelShader* ps;

        Win32PixelShader(ID3D11PixelShader* _ps) :ps(_ps) 
        { 
        }

        void Destroy() override
        {
            ps->Release();
            delete this;
        }
    };

    class Win32VertexBuffer : public VertexBuffer
    {
    public:
        ID3D11Buffer* vertexBuffer;

        Win32VertexBuffer(ID3D11Buffer* vb, uint vertexCount)
            : VertexBuffer(vertexCount), vertexBuffer(vb)
        {
        }

        void Destroy() override
        {
            vertexBuffer->Release();
            delete this;
        }
    };

    class Win32Texture : public Texture
    {
    private:
    public:
        ID3D11ShaderResourceView* shaderResource;

        Win32Texture(const wstring& _name, ID3D11ShaderResourceView* srv, const Size& _size)
            :Texture(_name), shaderResource(srv)
        {
            size = _size;
        }

        void Destroy() override
        {
            shaderResource->Release();
            delete this;
        }
    };
}