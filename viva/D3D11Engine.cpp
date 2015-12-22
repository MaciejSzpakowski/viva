#include "Win32.h"
#include "D3D11ShadersRC.h"

namespace viva
{
	void Checkhr(HRESULT hr, const char* function)
	{
		if (hr == 0)
			return;

		char str[128];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), str, 128, 0);
		std::stringstream message;
		message << function << "\n" << str;

		throw std::runtime_error(message.str().c_str());
	}

	D3D11Engine::D3D11Engine(const wstring& title, int clientWidth, int clientHeigth)
		: Engine(EngineType::DirectX11, Size((float)clientWidth, (float)clientHeigth))
	{
		HRESULT hr;

		window = new Win32Window(title.c_str(), clientWidth, clientHeigth);

		console = new Win32Console();

		//// *********** PIPELINE SETUP STARTS HERE *********** ////
		// create a struct to hold information about the swap chain
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferCount = 1;                                    // one back buffer
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		scd.OutputWindow = (HWND)window->GetNativeHandle();     // the window to be used
		scd.SampleDesc.Quality = 0;
		scd.SampleDesc.Count = 1;                               // no anti aliasing
		scd.Windowed = TRUE;                                    // windowed/full-screen mode
		//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // alternative fullscreen mode

		////    DEVICE, DEVICE CONTEXT AND SWAP CHAIN    ////
		hr = D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &scd, &swapChain, &device, NULL,
			&context);
		Checkhr(hr, "D3D11CreateDeviceAndSwapChain()");

		////    BACK BUFFER AS RENDER TARGET, DEPTH STENCIL   ////
		// get the address of the back buffer
		ID3D11Texture2D* buf;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&buf);
		// use the back buffer address to create the render target
		hr = device->CreateRenderTargetView(buf, NULL, &backBuffer);
		Checkhr(hr, "CreateRenderTargetView()");
		buf->Release();

		//Describe our Depth/Stencil Buffer
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = clientWidth;
		depthStencilDesc.Height = clientHeigth;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		//Create the Depth/Stencil View
		hr = device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
		Checkhr(hr, "CreateTexture2D() for depthStencilDesc");
		hr = device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
		Checkhr(hr, "CreateDepthStencilView()");

		////   VIEWPORT    ////
		// Set the viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (float)clientWidth;
		viewport.Height = (float)clientHeigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		context->RSSetViewports(1, &viewport);

		////    VS and PS    ////
		//default shaders
		ID3D11VertexShader* vs;
		ID3D10Blob *blob; //release vs after CreateInputLayout()
						//alternative to loading shader from cso file
						//hr = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &vs, 0); CHECKHR();
		hr = D3DCompile(rc_VertexShader, strlen(rc_VertexShader),
			0, 0, 0, "main", "vs_5_0", 0, 0, &blob, 0);
		Checkhr(hr, "D3DCompile()");
		hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), 0,
			&vs);
		defaultVertexShader = new D3D11VertexShader(vs);
		Checkhr(hr, "CreateVertexShader()");
		context->VSSetShader(((D3D11VertexShader*)defaultVertexShader)->vs, 0, 0);
		const char* args[] = { "main", "ps_5_0" };
		defaultPixelShader = CreatePixelShaderFromString(rc_PixelShader, args);
		const char* args2[] = { "main", "ps_5_0" };
		defaultPostProcessing = CreatePixelShaderFromString(rc_PostProcessing, args2);

		////    INPUT LAYOUT    ////
		//defaul input layout
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
		hr = device->CreateInputLayout(ied, 3, blob->GetBufferPointer(), blob->GetBufferSize(),
			&layout);
		Checkhr(hr, "CreateInputLayout()");
		blob->Release();
		context->IASetInputLayout(layout);

		///    BLEND STATE    ////
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		D3D11_RENDER_TARGET_BLEND_DESC rtbd;
		ZeroMemory(&rtbd, sizeof(rtbd));
		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.RenderTarget[0] = rtbd;
		hr = device->CreateBlendState(&blendDesc, &blendState);
		Checkhr(hr, "CreateBlendState()");

		////    RASTERIZERS     ////

		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_NONE;
		hr = device->CreateRasterizerState(&rd, &rsWire);
		Checkhr(hr, "CreateRasterizerState()");
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_FRONT;
		hr = device->CreateRasterizerState(&rd, &rsSolid);
		Checkhr(hr, "CreateRasterizerState()");

		//// *********** PIPELINE SETUP ENDS HERE *********** ////
		
		//timer
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			throw std::runtime_error("QueryPerformanceFrequency() failed");

		frequency = double(li.QuadPart);
		QueryPerformanceCounter(&li);
		startTime = li.QuadPart;
		prevFrameTime = startTime;
		gameTime = 0;
		frameTime = 0;
	}

	void D3D11Engine::Destroy()
	{
		window->Destroy();
		delete console;
	}

	void D3D11Engine::Run(std::function<void()>& gameloop, std::function<void()>& intloop)
	{ 
		static_cast<Win32Window*>(window)->Run(gameloop, intloop);
	}

	PixelShader* D3D11Engine::CreatePixelShaderFromFile(const wstring& filepath, void* args)
	{
		auto file = Utils::ReadFileToString(filepath);
		return CreatePixelShaderFromString(std::string(file.begin(), file.end()).c_str(), args);
	}

	PixelShader* D3D11Engine::CreatePixelShaderFromString(const char* str, void* args)
	{
		ID3D11PixelShader* ps;
		ID3D10Blob *blob;
		HRESULT hr;

		hr = D3DCompile(str, strlen(str), 0, 0, 0, ((const char**)args)[0], ((const char**)args)[1], 0, 0, &blob, 0);
		Checkhr(hr, "D3DCompile() in D3D11Engine::CreatePixelShaderFromString()");
		hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), 0, &ps);
		Checkhr(hr, "CreatePixelShader() in D3D11Engine::CreatePixelShaderFromString()");
		ps->Release();

		return new D3D11PixelShader(ps);
	}

	RenderTarget* D3D11Engine::CreateRenderTarget()
	{
		HRESULT hr;
		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

		ID3D11Texture2D* tex;
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = (UINT)size.width;
		textureDesc.Height = (UINT)size.height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&textureDesc, NULL, &tex);
		Checkhr(hr, "CreatePixelShader() in D3D11Engine::CreateRenderTarget()");

		ID3D11RenderTargetView* rtv;
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
		hr = device->CreateRenderTargetView(tex, &renderTargetViewDesc, &rtv);
		Checkhr(hr, "CreatePixelShader() in D3D11Engine::CreateRenderTarget()");

		ID3D11ShaderResourceView* srv;
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		hr = device->CreateShaderResourceView(tex, &shaderResourceViewDesc, &srv);
		Checkhr(hr, "CreateShaderResourceView() in D3D11Engine::CreateRenderTarget()");

		return new D3D11RenderTarget(tex, rtv, srv);
	}

	Sprite* D3D11Engine::CreateSprite(const wstring& filepath)
	{
		return new D3D11Sprite();
	}

	Sprite* D3D11Engine::CreateSprite(Texture* texture)
	{
		return new D3D11Sprite();
	}

	Texture* D3D11Engine::CreateTexture(const wstring& filepath, bool cached)
	{
		return new D3D11Texture(filepath,nullptr);
	}

	Texture* D3D11Engine::CreateTexture(const Pixel data[], const Size& size, wstring& name)
	{
		return new D3D11Texture(name, nullptr);
	}

	void D3D11Engine::Draw(const vector<RenderTarget*>& targets, const Camera* camera)
	{
		float col[4] = { backgroundColor.r, backgroundColor.g, 
			backgroundColor.b, backgroundColor.a};

		for (auto t : targets)
			t->Draw();

		context->ClearRenderTargetView(backBuffer, col);
		context->ClearDepthStencilView(depthStencilView,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		context->OMSetRenderTargets(1, &backBuffer, depthStencilView);

		for (auto t : targets)
		{
			/*zRenderTargetTransform(i);
			Core->zContext->PSSetShader(zRenderTargets[i]->PixelShader, 0, 0);
			zRenderTargets[i]->zSprite->zDraw();*/
		}

		//debug text
		//context->PSSetShader(Core->zDefaultPS, 0, 0);
		//DebugManager->Flush();
		//if (DebugManager->zDebugText->Text != L"")
		//	DebugManager->zDebugText->zDraw();

		swapChain->Present(0, 0);
	}

	Polygon* D3D11Engine::CreatePolygon(const vector<Point>& points)
	{
		return new D3D11Polygon(device, points);
	}
}