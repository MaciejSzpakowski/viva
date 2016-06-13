#ifdef _WIN32

#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    Win32Polygon::Win32Polygon(ID3D11Buffer* _vertexBuffer, int count):
        Polygon(count)
    {
        vertexBuffer = _vertexBuffer;
    }

    void Win32Polygon::_Draw()
    {
        // transform
        Matrix worldViewProj;
        T()->GetWorldViewProj(&worldViewProj);
        worldViewProj.Transpose();
        d3d.context->UpdateSubresource(d3d.constantBufferVS, 0, NULL, &worldViewProj, 0, 0);

        d3d.context->UpdateSubresource(d3d.constantBufferPS, 0, 0, &color, 0, 0);
        d3d.context->PSSetShader(ps->ps, 0, 0);
        d3d.context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
        d3d.context->RSSetState(d3d.rsWire);
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        d3d.context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        d3d.context->Draw(vertexCount, 0);
    }

    void Win32Polygon::Destroy()
    {
#pragma message("Polygon ps destroy")
        vertexBuffer->Release();
        delete this;
    }
}

#endif