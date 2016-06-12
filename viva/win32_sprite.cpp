#ifdef _WIN32

#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    void Win32Sprite::_Draw()
    {
        _Transform();

        d3d.context->RSSetState(d3d.rsSolid);
        d3d.context->PSSetSamplers(0, 1, &d3d.samplerPoint);
        d3d.context->UpdateSubresource(d3d.constantBufferPS, 0, 0, &color, 0, 0);
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        d3d.context->IASetVertexBuffers(0, 1, &d3d.vertexBuffer, &stride, &offset);
        d3d.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        d3d.context->PSSetShaderResources(0, 1, &texture->shaderResource);
        d3d.context->DrawIndexed(6, 0, 0);
    }

    void Win32Sprite::_Transform()
    {
        Matrix t;
        Matrix::Translation(transform.GetPosition(), &t);
        Matrix::Multiply(t, camera->GetView(), &t);
        Matrix::Multiply(t, camera->GetProj(), &t);
        t.Transpose();

        d3d.context->UpdateSubresource(d3d.constantBufferVS, 0, NULL, &t, 0, 0);
    }

    void Win32Sprite::Destroy()
    {
        texture->Destroy();
        delete this;
    }
}

#endif