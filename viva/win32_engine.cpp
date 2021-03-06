#include "viva.h"

namespace viva
{
    void intloop()
    {
    }

    D3D11 d3d;

    struct D3D11
    {
        ID3D11BlendState* blendState;
        IDXGISwapChain* swapChain;
        ID3D11RenderTargetView* backBuffer;
        ID3D11Device* device;
        ID3D11DeviceContext* context;
        ID3D11InputLayout* layout; //vertex input layout: float[3] pos, float[3] col, float[2] uv
        ID3D11DepthStencilView* depthStencil;
        ID3D11Texture2D* depthStencilBuffer;
        ID3D11RasterizerState* rsSolid;
        ID3D11RasterizerState* rsWire;
        ID3D11VertexShader* defaultVS;
        Win32PixelShader* defaultPS;
        Win32PixelShader* defaultPost;
        ID3D11Buffer* constantBufferVS; // shared cb for worldViewProj matrix
        ID3D11Buffer* constantBufferPS; // shared cb for color
        ID3D11Buffer* constantBufferUV; // shared cb for uv
        ID3D11Buffer* constantBufferPSExtra; // shared cb for user varsiables for ps
        ID3D11Buffer* indexBuffer; // shared for sprites and surfaces
        ID3D11Buffer* vertexBuffer; // shared for sprites and surfaces
        ID3D11SamplerState* samplerPoint;
        ID3D11SamplerState* samplerLinear;
    };

    void Checkhr(HRESULT hr, const char* function)
    {
        if (hr == 0)
            return;

        char str[128];
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr,
            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), str, 128, 0);
        std::stringstream message;
        message << function << "\n" << str;

        throw viva::Error(function, message.str().c_str());
    }

    class Win32Engine : public Engine
    {
    private:
        void Activity() override
        {
            // viewProj
            camera->_CalcViewProj();

            // time
            time->_Activity();

            // events
            routineManager->_Activity();

            // input
            mouse->_Activity();
            keyboard->_Activity();

            // render
            drawManager->_DrawNodes();

            // this snippet is here because drawmanager is front end/generic non win32 specific
            // also this is common for all render targets, I need to set this up only once
            float col[4] = { backgroundColor.R,backgroundColor.G,backgroundColor.B,backgroundColor.A };
            d3d.context->ClearRenderTargetView(d3d.backBuffer, col);
            d3d.context->ClearDepthStencilView(d3d.depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            d3d.context->OMSetRenderTargets(1, &d3d.backBuffer, d3d.depthStencil);
            d3d.context->RSSetState(d3d.rsSolid);
            d3d.context->PSSetSamplers(0, 1, &d3d.samplerPoint);
            UINT stride = sizeof(Vertex);
            UINT offset = 0;
            d3d.context->IASetVertexBuffers(0, 1, &d3d.vertexBuffer, &stride, &offset);
            d3d.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            Matrix t;
            Matrix::Identity(&t);
            Rect surfaceuv(0, 0, 1, 1);
            d3d.context->UpdateSubresource(d3d.constantBufferUV, 0, 0, &surfaceuv, 0, 0);
            d3d.context->UpdateSubresource(d3d.constantBufferVS, 0, NULL, &t, 0, 0);

            drawManager->_DrawSurfaces();

            d3d.swapChain->Present(0, 0);
        }
    public:
        Win32Engine(const wstring& title, const Size& size, const wstring& path)
            : Engine(path, size)
        {
            window = new Win32Window(title.c_str(), size);
        }

        void _Destroy() override
        {
            if(routineManager != nullptr)
                routineManager->_Destroy();
            if (time != nullptr)
                time->_Destroy();
            if (mouse != nullptr)
                mouse->_Destroy();
            if (keyboard != nullptr)
                keyboard->_Destroy();
            if (camera != nullptr)
                camera->_Destroy();
            if (drawManager != nullptr)
                drawManager->_Destroy();
            // destroy resource manager after drawmanager
            if (resourceManager != nullptr)
                resourceManager->_Destroy();
            if (creator != nullptr)
                creator->_Destroy();

            keyboard = nullptr;
            mouse = nullptr;
            engine = nullptr;
            camera = nullptr;
            creator = nullptr;
            drawManager = nullptr;
            resourceManager = nullptr;
            routineManager = nullptr;
            time = nullptr;

            // destroy objects
            d3d.defaultPS->Destroy();
            d3d.defaultPost->Destroy();

            // release interfaces
            d3d.constantBufferPS->Release();
            d3d.constantBufferPSExtra->Release();
            d3d.constantBufferUV->Release();
            d3d.constantBufferVS->Release();
            d3d.vertexBuffer->Release();
            d3d.samplerLinear->Release();
            d3d.samplerPoint->Release();
            d3d.indexBuffer->Release();
            d3d.blendState->Release();
            d3d.rsSolid->Release();
            d3d.rsWire->Release();
            d3d.layout->Release();
            d3d.defaultVS->Release();
            d3d.depthStencilBuffer->Release();
            d3d.depthStencil->Release();
            d3d.backBuffer->Release();
            d3d.swapChain->Release();
            d3d.context->Release();
            d3d.device->Release();

            // destroy window last
            window->_Destroy();
            window = nullptr;

            delete this;
        }

        void _Init() override
        {
            HRESULT hr = 0;

            std::string strPixelShader = "cbuffer cbBufferPS{float4 color;};Texture2D ObjTexture;"
                "SamplerState ObjSamplerState;struct VS_OUTPUT"
                "{float4 Pos:SV_POSITION;float3 Col:COLOR;float2 TexCoord:TEXCOORD;};"
                "float4 main(VS_OUTPUT input):SV_TARGET"
                "{if(input.Col.r==0){float4 result=ObjTexture.Sample(ObjSamplerState,input.TexCoord);"
                "clip(result.a-0.001f);return result*color;}else{return color;}}";

            std::string strVertexShader = "cbuffer cbBufferVS{float4x4 transformation;};cbuffer cbBufferUV"
                "{float4 uv;};struct VS_OUTPUT"
                "{float4 Pos:SV_POSITION;float3 Col:COLOR;float2 TexCoord:TEXCOORD;};"
                "VS_OUTPUT main(float4 inPos:POSITION,float3 inCol:COLOR,float2 inTexCoord:TEXCOORD)"
                "{VS_OUTPUT output;output.Pos=mul(inPos,transformation);output.Col=inCol;"
                "output.TexCoord=inTexCoord;if(inTexCoord[0]==0&&inTexCoord[1]==0)"
                "output.TexCoord=float2(uv[0],1-uv[1]);if(inTexCoord[0]==1&&inTexCoord[1]==0)"
                "output.TexCoord=float2(uv[2],1-uv[1]);if(inTexCoord[0]==0&&inTexCoord[1]==1)"
                "output.TexCoord=float2(uv[0],1-uv[3]);if(inTexCoord[0]==1&&inTexCoord[1]==1)"
                "output.TexCoord=float2(uv[2],1-uv[3]);return output;}";

            std::string strPostShader = "cbuffer cbBufferPS{};Texture2D ObjTexture;SamplerState ObjSamplerState;"
                "struct VS_OUTPUT{float4 Pos:SV_POSITION;float3 Col:COLOR;"
                "float2 TexCoord:TEXCOORD;};float4 main(VS_OUTPUT input):SV_TARGET"
                "{float4 result=ObjTexture.Sample(ObjSamplerState,input.TexCoord);"
                "clip(result.a-0.001f);return result;}";

            //    DEVICE, DEVICE CONTEXT AND SWAP CHAIN    ////
            DXGI_SWAP_CHAIN_DESC scd;
            ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
            scd.BufferCount = 1;                                    // one back buffer
            scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
            scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
            scd.OutputWindow = (HWND)window->GetHandle();     // the window to be used
            scd.SampleDesc.Quality = 0;
            scd.SampleDesc.Count = 1;                               // no anti aliasing
            scd.Windowed = TRUE;                                    // windowed/full-screen mode
                                                                    //scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // alternative fullscreen mode

            hr = D3D11CreateDeviceAndSwapChain(NULL,
                D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
                D3D11_SDK_VERSION, &scd, &d3d.swapChain, &d3d.device, NULL,
                &d3d.context);
            Checkhr(hr, "D3D11CreateDeviceAndSwapChain()");

            ////    BACK BUFFER AS RENDER TARGET, DEPTH STENCIL   ////
            ID3D11Texture2D* buf;
            d3d.swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&buf);
            // use the back buffer address to create the render target
            hr = d3d.device->CreateRenderTargetView(buf, NULL, &d3d.backBuffer);
            Checkhr(hr, "CreateRenderTargetView()");
            buf->Release();

            D3D11_TEXTURE2D_DESC depthStencilDesc;
            depthStencilDesc.Width = (UINT)clientSize.Width;
            depthStencilDesc.Height = (UINT)clientSize.Height;
            depthStencilDesc.MipLevels = 1;
            depthStencilDesc.ArraySize = 1;
            depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
            depthStencilDesc.SampleDesc.Count = 1;
            depthStencilDesc.SampleDesc.Quality = 0;
            depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
            depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            depthStencilDesc.CPUAccessFlags = 0;
            depthStencilDesc.MiscFlags = 0;

            hr = d3d.device->CreateTexture2D(&depthStencilDesc, NULL, &d3d.depthStencilBuffer);
            Checkhr(hr, "CreateTexture2D() for depthStencilDesc");
            hr = d3d.device->CreateDepthStencilView(d3d.depthStencilBuffer, NULL, &d3d.depthStencil);
            Checkhr(hr, "CreateDepthStencilView()");

            ////   VIEWPORT    ////
            // Set the viewport
            D3D11_VIEWPORT viewport;
            ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;
            viewport.Width = (float)clientSize.Width;
            viewport.Height = (float)clientSize.Height;
            viewport.MinDepth = 0.0f;
            viewport.MaxDepth = 1.0f;
            d3d.context->RSSetViewports(1, &viewport);

            ////    VS   ////
            ID3D10Blob *vs; //release vs after CreateInputLayout()
                            //alternative to loading shader from cso file
            hr = D3DCompile(strVertexShader.c_str(), strVertexShader.length(), 0, 0, 0, "main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vs, 0);
            Checkhr(hr, "D3DCompile() vs");
            hr = d3d.device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), 0,
                &d3d.defaultVS);
            Checkhr(hr, "CreateVertexShader()");
            d3d.context->VSSetShader(d3d.defaultVS, 0, 0);
            Checkhr(hr, "CreateVertexShader()");

            //    INPUT LAYOUT    ////
            D3D11_INPUT_ELEMENT_DESC ied[] =
            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
                0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT,
                0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
                0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                //if you need to pass something on your own to PS or VS per vertex
                //{ "SOME_MORE_DATA", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };
            hr = d3d.device->CreateInputLayout(ied, 3, vs->GetBufferPointer(), vs->GetBufferSize(),
                &d3d.layout);
            Checkhr(hr, "CreateInputLayout()");
            vs->Release();
            d3d.context->IASetInputLayout(d3d.layout);

            ///    BLEND STATE    ////
            D3D11_BLEND_DESC blendDesc;
            ZeroMemory(&blendDesc, sizeof(blendDesc));
            D3D11_RENDER_TARGET_BLEND_DESC rtbd;
            ZeroMemory(&rtbd, sizeof(rtbd));
            rtbd.BlendEnable = true;
            rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
            rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            rtbd.BlendOp = D3D11_BLEND_OP_ADD;
            rtbd.SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;// D3D11_BLEND_ONE;
            rtbd.DestBlendAlpha = D3D11_BLEND_ONE;//D3D11_BLEND_ZERO;
            rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
            rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;
            blendDesc.AlphaToCoverageEnable = false;
            blendDesc.RenderTarget[0] = rtbd;
            hr = d3d.device->CreateBlendState(&blendDesc, &d3d.blendState);
            Checkhr(hr, "CreateBlendState()");

            ////    RASTERIZERS     ////
            D3D11_RASTERIZER_DESC rd;
            ZeroMemory(&rd, sizeof(rd));
            rd.FillMode = D3D11_FILL_WIREFRAME;
            rd.CullMode = D3D11_CULL_NONE;
            hr = d3d.device->CreateRasterizerState(&rd, &d3d.rsWire);
            Checkhr(hr, "CreateRasterizerState()");
            rd.FillMode = D3D11_FILL_SOLID;
            rd.CullMode = D3D11_CULL_FRONT;
            hr = d3d.device->CreateRasterizerState(&rd, &d3d.rsSolid);
            Checkhr(hr, "CreateRasterizerState()");

            ////    SAMPLERS    //////
            D3D11_SAMPLER_DESC sampDesc;
            ZeroMemory(&sampDesc, sizeof(sampDesc));
            sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
            sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
            sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
            sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
            sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
            sampDesc.MinLOD = 0;
            sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
            d3d.device->CreateSamplerState(&sampDesc, &d3d.samplerPoint);
            sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            d3d.device->CreateSamplerState(&sampDesc, &d3d.samplerLinear);

            //// SO FAR ONLY INDEX BUFFER ////
            vector<int> indices({ 0, 1, 2, 0, 2, 3, });

            D3D11_BUFFER_DESC indexBufferDesc;
            ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.ByteWidth = sizeof(int) * (UINT)indices.size();
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            indexBufferDesc.CPUAccessFlags = 0;
            indexBufferDesc.MiscFlags = 0;

            D3D11_SUBRESOURCE_DATA srd;
            srd.pSysMem = indices.data();
            d3d.device->CreateBuffer(&indexBufferDesc, &srd, &d3d.indexBuffer);
            d3d.context->IASetIndexBuffer(d3d.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

            //// GLOBALS ////
            viva::creator = new Win32Creator();

            //////   PS    ///////
            d3d.defaultPS = static_cast<Win32PixelShader*>(creator->CreatePixelShader(strPixelShader));
            d3d.defaultPost = static_cast<Win32PixelShader*>(creator->CreatePixelShader(strPostShader));

            viva::resourceManager = new ResourceManager();
            viva::camera = new Camera(clientSize);
            viva::drawManager = new DrawManager();
            viva::keyboard = new Input::Win32Keyboard();
            viva::mouse = new Input::Win32Mouse();
            viva::time = new Win32Time();
            viva::routineManager = new RoutineManager();

            /////// CONSTANT BUFFERS ///////
            d3d.constantBufferVS = CreateConstantBuffer(sizeof(Matrix));
            d3d.context->VSSetConstantBuffers(0, 1, &d3d.constantBufferVS);

            d3d.constantBufferUV = CreateConstantBuffer(sizeof(Rect));
            d3d.context->VSSetConstantBuffers(1, 1, &d3d.constantBufferUV);

            d3d.constantBufferPS = CreateConstantBuffer(sizeof(Color));
            d3d.context->PSSetConstantBuffers(0, 1, &d3d.constantBufferPS);

            d3d.constantBufferPSExtra = CreateConstantBuffer(16);
            d3d.context->PSSetConstantBuffers(1, 1, &d3d.constantBufferPSExtra);

            /////// SQUARE VERTEX BUFFER //////
            vector<Vertex> v({
                Vertex(-1.0f, -1.0f, 0, 0, 0, 0, 0, 1),
                Vertex(1.0f, -1.0f, 0, 0, 0, 0, 1, 1),
                Vertex(1.0f, 1.0f, 0, 0, 0, 0, 1, 0),
                Vertex(-1.0f, 1.0f, 0, 0, 0, 0, 0, 0) });

            D3D11_BUFFER_DESC vertexBufferDesc;
            ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            vertexBufferDesc.CPUAccessFlags = 0;
            vertexBufferDesc.MiscFlags = 0;

            D3D11_SUBRESOURCE_DATA vertexBufferData;
            ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
            vertexBufferData.pSysMem = v.data();
            d3d.device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &d3d.vertexBuffer);
        }        

        void OpenConsole() override
        {
            AllocConsole();
            SetConsoleTitle(L"Console");
            freopen("CONOUT$", "w", stdout);
            freopen("CONIN$", "r", stdin);
        }

        void CloseConsole() override
        {
            FreeConsole();
        }

        void Exit() override
        {
            PostMessage((HWND)window->GetHandle(), WM_CLOSE, (int)CloseReason::EngineClose, 0);
        }

        CloseReason Run(const std::function<void()>& gameloop) override
        {
            return static_cast<Win32Window*>(window)->Run(gameloop, [&]() {Activity(); });
        }

        ID3D11Buffer* CreateConstantBuffer(UINT size)
        {
            ID3D11Buffer* cb;

            D3D11_BUFFER_DESC cbbd;
            ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
            cbbd.Usage = D3D11_USAGE_DEFAULT;
            cbbd.ByteWidth = size;
            cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            cbbd.CPUAccessFlags = 0;
            cbbd.MiscFlags = 0;
            d3d.device->CreateBuffer(&cbbd, NULL, &cb);

            return cb;
        }
    };
}
