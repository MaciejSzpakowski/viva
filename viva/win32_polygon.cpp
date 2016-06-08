#ifdef _WIN32

#include <viva/proto.h>

namespace viva
{
    Win32Polygon::Win32Polygon(ID3D11Buffer* _vertexBuffer, int count):
        Polygon(count)
    {
        vertexBuffer = _vertexBuffer;
    }

    /*void Win32Polygon::Draw(ID3D11DeviceContext* context)
    {
        Core->_GetContext()->UpdateSubresource(DrawManager->_GetConstantBufferPS(), 0, NULL, &color, 0, 0);
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        Core->_GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        Core->_GetContext()->Draw(vertexCount, 0);
    }*/

    void Win32Polygon::_Draw()
    {
    }

    void Win32Polygon::_Transform()
    {
    }

    void Win32Polygon::Destroy()
    {
        vertexBuffer->Release();
        delete this;
    }
}

#endif