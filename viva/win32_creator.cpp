#ifdef _WIN32

#include <viva/proto.h>

namespace viva
{
    Polygon* Win32Creator::CreatePolygon(const vector<Point>& points)
    {
        //color = XMFLOAT4(0, 0, 0, 0);
        //vertexCount = (int)points.size();
        //span = 0;

        /*/method 1
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC;                // CPU writes, GPU reads
        bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // CPU writes
        Device->CreateBuffer(&bd, NULL, &vertexBuffer);

        VERTEX* vertices = new VERTEX[n];
        for (int i = 0; i < n; i++)
        vertices[i] = { points[i].x, points[i].y, 0.0f, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };

        D3D11_MAPPED_SUBRESOURCE ms;
        Context->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
        memcpy(ms.pData, vertices, sizeof(VERTEX)*n);
        Context->Unmap(vertexBuffer, NULL);
        delete[] vertices;//*/

        //method 2
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;				   // GPU writes and reads
        bd.ByteWidth = (UINT)(sizeof(Vertex) * points.size());
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
        bd.CPUAccessFlags = 0;		                   // CPU does nothing

        Vertex* temp = new Vertex[points.size()];
        for (int i = 0; i < points.size(); i++)
        {
            //float distFromOrigin = sqrtf(points[i].x*points[i].x + points[i].y*points[i].y);
            //if (distFromOrigin > span)
            //    span = distFromOrigin;
            //vertices.push_back(DirectX::XMVectorSet(points[i].x, points[i].y, 0, 0));
            temp[i] = { points[i].X, points[i].Y, 0, 1, 1, 1, 0, 0 };
        }
        //transformedVertices = vertices;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = temp;                   //Memory in CPU to copy in to GPU

        ID3D11Buffer* vertexBuffer;
        device->CreateBuffer(&bd, &sd, &vertexBuffer);
        delete[] temp;//*/

        return new Win32Polygon(vertexBuffer, (int)points.size());
    }
}

#endif