#ifdef _WIN32

#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    Size util::ReadImageToPixels(const std::wstring& filepath, Array<Pixel>& dst)
    {
        UINT w, h;
        ULONG_PTR m_gdiplusToken;
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

        {
            Gdiplus::Bitmap gdibitmap(filepath.c_str());

            if (gdibitmap.GetLastStatus() != 0)
            {
                std::stringstream msg;
                msg << "Could not open " << std::string(filepath.begin(), filepath.end());
                Gdiplus::GdiplusShutdown(m_gdiplusToken);
                throw Error("ReadImageToPixels()", msg.str().c_str());
            }

            h = gdibitmap.GetHeight();
            w = gdibitmap.GetWidth();

            HBITMAP hbitmap;
            Gdiplus::Color c(0, 0, 0);
            gdibitmap.GetHBITMAP(c, &hbitmap);

            int status = gdibitmap.GetLastStatus();

            BITMAP bitmap;
            GetObject(hbitmap, sizeof(bitmap), (LPVOID)&bitmap);
            BYTE* data = (BYTE*)bitmap.bmBits;

            dst = Array<Pixel>(h * w);

            // funny order, it's probably endianess mismatch
            for (int i = 0; i < (int)(h*w * 4); i += 4)
                dst[i >> 2] = { data[i + 2],data[i + 1],data[i + 0],data[i + 3] };

            DeleteObject(hbitmap);
        }

        Gdiplus::GdiplusShutdown(m_gdiplusToken);

        return Size((float)w, (float)h);
    }

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
            temp[i] = { points[i].X, points[i].Y, 0, 1, 1, 1, 0, 0 }; // IMPORTANT, red must be non 0, 0 is reserved for sprites
        }
        //transformedVertices = vertices;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = temp;                   //Memory in CPU to copy in to GPU

        ID3D11Buffer* vertexBuffer;
        d3d.device->CreateBuffer(&bd, &sd, &vertexBuffer);
        delete[] temp;//*/

        Win32Polygon* poly = new Win32Polygon(vertexBuffer, (int)points.size());
        poly->SetPixelShader(d3d.defaultPS);
        return poly;
    }

    Surface* Win32Creator::CreateSurface()
    {
        ID3D11Texture2D* tex;
        ID3D11ShaderResourceView* srv;
        ID3D11RenderTargetView* rtv;

        D3D11_TEXTURE2D_DESC textureDesc;
        ZeroMemory(&textureDesc, sizeof(textureDesc));
        textureDesc.Width = (UINT)engine->GetClientSize().Width;
        textureDesc.Height = (UINT)engine->GetClientSize().Height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        HRESULT hr = d3d.device->CreateTexture2D(&textureDesc, NULL, &tex); Checkhr(hr, "CreateTexture2D()");

        D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        renderTargetViewDesc.Format = textureDesc.Format;
        renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        renderTargetViewDesc.Texture2D.MipSlice = 0;
        hr = d3d.device->CreateRenderTargetView(tex,
            &renderTargetViewDesc, &rtv); Checkhr(hr, "CreateRenderTargetView()");

        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
        shaderResourceViewDesc.Format = textureDesc.Format;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        hr = d3d.device->CreateShaderResourceView(tex,
            &shaderResourceViewDesc, &srv); Checkhr(hr, "CreateShaderResourceView()");

        Win32Surface* surf = new Win32Surface(tex, rtv, srv);
        surf->SetPixelShader(d3d.defaultPost);
        return surf;
    }

    PixelShader* Win32Creator::CreatePixelShader(const wstring& filepath)
    {
        std::string ps = util::ReadFileToString(filepath);
        return CreatePixelShader(ps);
    }

    PixelShader* Win32Creator::CreatePixelShader(const std::string& str)
    {
        ID3D11PixelShader* result;

        ID3D10Blob *ps;
        HRESULT hr = D3DCompile(str.c_str(), str.length(), 0, 0, 0, "main", "ps_5_0", 0, 0, &ps, 0);
        Checkhr(hr, "CreatePixelShader()");

        hr = d3d.device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), 0, &result);
        Checkhr(hr, "CreatePixelShader()");
        ps->Release();

        return new Win32PixelShader(result);
    }

    ID3D11ShaderResourceView* Win32Creator::SrvFromPixels(const Array<Pixel>& pixels, const Size& _size)
    {
        ID3D11Texture2D *tex;
        ID3D11ShaderResourceView* srv;

        D3D11_SUBRESOURCE_DATA sub;
        sub.pSysMem = pixels.data();
        sub.SysMemPitch = (UINT)_size.Width * 4;
        sub.SysMemSlicePitch = (UINT)_size.Height*(UINT)_size.Width * 4;

        D3D11_TEXTURE2D_DESC desc;
        desc.Width = (UINT)_size.Width;
        desc.Height = (UINT)_size.Height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        HRESULT hr = d3d.device->CreateTexture2D(&desc, &sub, &tex);
        Checkhr(hr, "CreateTexture2D()");

        D3D11_TEXTURE2D_DESC desc2;
        tex->GetDesc(&desc2);
        hr = d3d.device->CreateShaderResourceView(tex, 0, &srv);
        Checkhr(hr, "CreateShaderResourceView()");
        tex->Release();

        return srv;
    }

    Sprite* Win32Creator::CreateSprite(Texture* texture)
    {
        Win32Texture* tex = static_cast<Win32Texture*>(texture);
        return new Win32Sprite(tex);
    }

    Sprite* Win32Creator::CreateSprite(const wstring& filepath)
    {
        Win32Texture* tex = static_cast<Win32Texture*>(resourceManager->GetTexture(filepath));

        if (tex == nullptr)
            tex = CreateTextureWin32(filepath, true);

        return new Win32Sprite(tex);
    }
}

#endif