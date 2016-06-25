#ifdef _WIN32

#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    void Win32Sprite::_Draw()
    {
        // transform
        Matrix worldViewProj;
        T()->GetWorldViewProj(&worldViewProj);
        worldViewProj.Transpose();
        d3d.context->UpdateSubresource(d3d.constantBufferVS, 0, NULL, &worldViewProj, 0, 0);

        // uv
        Rect finaluv;
        finaluv.left = flipHorizontally ? uv.right : uv.left;
        finaluv.right = flipHorizontally ? uv.left : uv.right;
        finaluv.top = flipVertically ? uv.bottom : uv.top;
        finaluv.bottom = flipVertically ? uv.top : uv.bottom;
        d3d.context->UpdateSubresource(d3d.constantBufferUV, 0, 0, &finaluv, 0, 0);
        // rs
        d3d.context->RSSetState(d3d.rsSolid);
        // sampler and color
        d3d.context->PSSetSamplers(0, 1, &d3d.samplerPoint);
        d3d.context->UpdateSubresource(d3d.constantBufferPS, 0, 0, &color, 0, 0);
        // vb
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        d3d.context->IASetVertexBuffers(0, 1, &d3d.vertexBuffer, &stride, &offset);
        d3d.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        // texture
        d3d.context->PSSetShaderResources(0, 1, &texture->shaderResource);
        d3d.context->DrawIndexed(6, 0, 0);
    }

    void Win32Sprite::Destroy()
    {
        texture->Destroy();
        delete this;
    }
}

#endif