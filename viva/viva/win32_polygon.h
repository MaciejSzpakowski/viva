#pragma once

namespace viva
{
    using std::vector;

    class Win32Polygon : public Polygon
    {
    private:
        ID3D11Buffer* vertexBuffer;
    public:
        Win32Polygon(ID3D11Buffer* vertexbuffer, int count);

        void Destroy() override;

        ID3D11Buffer** _GetVertexBufferAddr() { return &vertexBuffer; }
        
        void _Draw() override;

        void _Transform() override;
    };
}