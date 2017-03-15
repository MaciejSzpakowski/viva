#include "viva.h"

namespace viva{
Drawable::Drawable()
{
}
}

namespace viva{
Node::Node()
{
}
}

namespace viva{
Color::Color(): R(1), G(1), B(1), A(1)
{
}
}

namespace viva{
Color::Color(float _r, float _g, float _b, float _a): R(_r), G(_g), B(_b), A(_a)
{
}
}

namespace viva{
Color::Color(const Pixel& pixel): R(pixel.R / 255.0f),G(pixel.G / 255.0f),B(pixel.B / 255.0f),A(pixel.A / 255.0f)
{
}
}

namespace viva{
const Color& Colorable::GetColor() const
{
return color;
}
}

namespace viva{
Colorable* Colorable::SetColor(float r, float g, float b, float a)
{
color.A = a;
color.B = b;
color.G = g;
color.R = r;

return this;
}
}

namespace viva{
Colorable* Colorable::SetColor(const Color& c)
{
color = c;
return this;
}
}

namespace viva{
Colorable* Colorable::SetR(float r)
{
color.R = r;
return this;
}
}

namespace viva{
Colorable* Colorable::SetG(float g)
{
color.G = g;
return this;
}
}

namespace viva{
Colorable* Colorable::SetB(float b)
{
color.B = b;
return this;
}
}

namespace viva{
Colorable* Colorable::SetA(float a)
{
color.A = a;
return this;
}
}

namespace viva{
Vector::Vector():f{ 0,0,0,0 }
{
}
}

namespace viva{
Vector::Vector(float x, float y, float z, float w):f{ x,y,z,w }
{
}
}

namespace viva{
Vector Vector::Zero()
{
return Vector(0, 0, 0, 0);
}
}

namespace viva{
Vector Vector::One()
{
return Vector(1, 1, 1, 1);
}
}

namespace viva{
float Vector::GetX() const
{
return f.x;
}
}

namespace viva{
float Vector::GetY() const
{
return f.y;
}
}

namespace viva{
float Vector::GetZ() const
{
return f.z;
}
}

namespace viva{
float Vector::GetW() const
{
return f.w;
}
}

namespace viva{
Vector* Vector::SetX(float x)
{
f.x = x;
return this;
}
}

namespace viva{
Vector* Vector::SetY(float y)
{
f.y = y;
return this;
}
}

namespace viva{
Vector* Vector::SetZ(float z)
{
f.z = z;
return this;
}
}

namespace viva{
Vector* Vector::SetW(float w)
{
f.w = w;
return this;
}
}

namespace viva{
Vector* Vector::Add(const Vector& rhs)
{
f.x += rhs.f.x;
f.y += rhs.f.y;
f.z += rhs.f.z;
f.w += rhs.f.w;
return this;
}
}

namespace viva{
Vector Vector::operator+(const Vector& rhs)
{
return Vector(f.x + rhs.f.x, f.y + rhs.f.y, f.z + rhs.f.z, f.w + rhs.f.w);
}
}

namespace viva{
Point::Point():X(0), Y(0)
{
}
}

namespace viva{
Point::Point(float x, float y):X(x), Y(y)
{
}
}

namespace viva{
Transform::Transform(): position(), rotation(0), scale({ 1,1 }), size(1),parent(nullptr), mode(TransformMode::World), index(-1)
{
}
}

namespace viva{
Transform* Transform::SetCoordMode(TransformMode m)
{
mode = m;
return this;
}
}

namespace viva{
TransformMode Transform::GetMode() const
{
return mode;
}
}

namespace viva{
void Transform::GetWorld(Matrix* dst)
{
Matrix::Translation(Vector(-origin.f.x, -origin.f.y, 0, 0), dst);
Matrix sca, rot, loc;
Matrix::Scaling({ scale.X * size, scale.Y * size }, &sca);
Matrix::Rotation(rotation, &rot);
Matrix::Translation(position, &loc);

Matrix::Multiply(*dst, sca, dst);
Matrix::Multiply(*dst, rot, dst);
Matrix::Multiply(*dst, loc, dst);

/*if (parent != nullptr)
{
XMMATRIX parentRot = XMMatrixRotationRollPitchYawFromVector(parent->absoluteRotation);
XMMATRIX parentLoc = XMMatrixTranslationFromVector(parent->absolutePosition);
XMMATRIX parentRotLoc = parentRot * parentLoc;
absolutePosition = DirectX::XMVector3Transform(position, parentRotLoc);
absoluteRotation = rotation + parent->absoluteRotation;
world = world * parentRotLoc;
}
else
{
absolutePosition = position;
absoluteRotation = rotation;
}*/
}
}

namespace viva{
void Transform::GetWorldViewProj(Matrix* dst)
{
if (mode == TransformMode::World)
{
GetWorld(dst);
Matrix::Multiply(*dst, camera->GetViewProj(), dst);
}
else
{
GetWorldScreen(dst);
}
}
}

namespace viva{
void Transform::GetWorldScreen(Matrix* dst)
{
auto screenSize = engine->GetClientSize();
float w = scale.X * size / screenSize.Width;
float h = scale.Y * size / screenSize.Height;

float ox = origin.GetX() / screenSize.Width + w;
float oy = origin.GetY() / screenSize.Height - h;

float x = position.GetX() * 2 / screenSize.Width - 1;
float y = -position.GetY() * 2 / screenSize.Height + 1;

Matrix::Identity(dst);
Matrix sca, ori, rot, loc;

Matrix::Translation(Vector(ox, oy, 0, 0), &ori);
Matrix::Scaling({ w,h }, &sca);
Matrix::Rotation(rotation, &rot);
Matrix::Translation(Vector(x, y, position.GetZ(), 0), &loc);

Matrix::Multiply(*dst, sca, dst);
Matrix::Multiply(*dst, ori, dst);
//Matrix::Multiply(*dst, rot, dst);
Matrix::Multiply(*dst, loc, dst);
}
}

namespace viva{
Transform* Transform::SetOrigin(float x, float y)
{
origin.f.x = x; origin.f.y = y;
return this;
}
}

namespace viva{
Transform* Transform::SetOrigin(const Vector& v)
{
origin = v;
return this;
}
}

namespace viva{
const Vector& Transform::GetOrigin() const
{
return origin;
}
}

namespace viva{
Transform* Transform::SetPosition(float x, float y, float z)
{
position.SetX(x);
position.SetY(y);
position.SetZ(z);
return this;
}
}

namespace viva{
Transform* Transform::SetPosition(float x, float y)
{
position.SetX(x);
position.SetY(y);
return this;
}
}

namespace viva{
Transform* Transform::SetX(float x)
{
position.SetX(x);
return this;
}
}

namespace viva{
Transform* Transform::SetY(float y)
{
position.SetY(y);
return this;
}
}

namespace viva{
Transform* Transform::SetZ(float z)
{
position.SetZ(z);
return this;
}
}

namespace viva{
Transform* Transform::SetPosition(const Vector& v)
{
position = v;
return this;
}
}

namespace viva{
const Vector& Transform::GetPosition() const
{
return position;
}
}

namespace viva{
Transform* Transform::Translate(float x, float y, float z)
{
position.Add(Vector(x, y, z, 0));

return this;
}
}

namespace viva{
Transform* Transform::Translate(const Vector& v)
{
position.Add(v);
return this;
}
}

namespace viva{
Transform* Transform::SetRotation(float radians)
{
rotation = radians;
return this;
}
}

namespace viva{
float Transform::GetRotation() const
{
return rotation;
}
}

namespace viva{
Transform* Transform::Rotate(float angle)
{
rotation += angle;
return this;
}
}

namespace viva{
Transform* Transform::SetScale(float width, float height)
{
scale.X = width;
scale.Y = height;
return this;
}
}

namespace viva{
Transform* Transform::SetScale(const Point& s)
{
scale = s;
return this;
}
}

namespace viva{
Transform* Transform::SetScaleX(float x)
{
scale.X = x;
return this;
}
}

namespace viva{
Transform* Transform::SetScaleY(float y)
{
scale.Y = y;
return this;
}
}

namespace viva{
const Point& Transform::GetScale() const
{
return scale;
}
}

namespace viva{
Transform* Transform::Scale(const Point& s)
{
scale.X += s.X; scale.Y += s.Y;
return this;
}
}

namespace viva{
Transform* Transform::SetSize(float s)
{
size = s;
return this;
}
}

namespace viva{
float Transform::GetSize() const
{
return size;
}
}

namespace viva{
Transform* Transform::Grow(float factor)
{
size *= factor;
return this;
}
}

namespace viva{
Transform* Transform::Shrink(float factor)
{
size /= factor;
return this;
}
}

namespace viva{
Transform* Transform::SetParent(Transform* p)
{
if (index != -1)
throw Error(__FUNCTION__, "Object can have only one parent");

parent = p;
index = parent->children.size();
parent->children.push_back(this);

return this;
}
}

namespace viva{
Transform* Transform::GetParent()
{
return parent;
}
}

namespace viva{
Transform* Transform::RemoveChild(Transform* child)
{
if (child->index == -1)
throw Error(__FUNCTION__, "Object doesn't have a parent");

if(children.at(child->index) != child)
throw Error(__FUNCTION__, "Wrong index");

children.erase(children.begin() + child->index);
child->index = -1;
child->parent = nullptr;

return this;
}
}

namespace viva{
Text::Text(const wstring& str, Font* f): font(f), text(str), texFilter(drawManager->GetDefaultTextureFilter()),parent(nullptr), index(-1), visible(true)
{
sprite = creator->CreateSprite(font->GetTexture());
}
}

namespace viva{
Text::Text(const wstring& str): Text(str, drawManager->GetDefaultFont())
{
}
}

namespace viva{
Transform* Text::T() 
{
return &transform;
}
}

namespace viva{
Text* Text::SetText(const wstring& _text)
{
text = _text;

return this;
}
}

namespace viva{
const wstring& Text::GetText() const
{
return text;
}
}

namespace viva{
Transform* Text::GetTransform() 
{
return &transform;
}
}

namespace viva{
TextureFilter Text::GetTextureFilter() const
{
return texFilter;
}
}

namespace viva{
Text* Text::SetTextureFilter(TextureFilter filter)
{
texFilter = filter;

return this;
}
}

namespace viva{
void Text::Destroy() 
{
sprite->Destroy();

delete this;
}
}

namespace viva{
void Text::_Draw() 
{
int row = 0;
int col = 0;

for (int i = 0; i < text.length(); i++)
{
if (text.at(i) == '\n')
{
row++;
col = 0;
continue;
}

sprite->SetUV(font->GetChar(text.at(i)));
sprite->T()->SetPosition(col * 1.0f + transform.GetPosition().GetX(), 1.3f * row + transform.GetPosition().GetY(), transform.GetPosition().GetZ());
sprite->SetPixelScale(20, 38);
sprite->_Draw();

col++;
}
}
}

namespace viva{
Surface* Text::GetSurface() const 
{
return parent;
}
}

namespace viva{
bool Text::IsVisible() const 
{
return visible;
}
}

namespace viva{
Drawable* Text::SetVisible(bool val) 
{
visible = val;
return this;
}
}

namespace viva{
void Text::_SetSurface(Surface* surface) 
{
parent = surface;
}
}

namespace viva{
void Text::_SetIndex(uint i) 
{
index = i;
}
}

namespace viva{
int Text::_GetIndex() const 
{
return index;
}
}

namespace viva{
Node* Text::GetNode()
{
return this;
}
}

namespace viva{
Core::Core(const wstring& title, const Size& size, const wstring& path)
{
engine = new Win32Engine(title, size, path);
engine->_Init();
}
}

namespace viva{
Core::~Core()
{
engine->_Destroy();
}
}

namespace viva{
Size::Size():Width(0), Height(0)
{
}
}

namespace viva{
Size::Size(float _width, float _height):Width(_width), Height(_height)
{
}
}

namespace viva{
Engine::Engine(const std::wstring& path, const Size& size):backgroundColor(0, 0.25f, 0.5f, 1), defaultPath(path), clientSize(size)
{
}
}

namespace viva{
const Color& Engine::GetBackgroundColor() const
{
return backgroundColor;
}
}

namespace viva{
void Engine::SetBackgroundColor(const Color& color)
{
backgroundColor = color;
}
}

namespace viva{
const std::wstring& Engine::GetDefaultPath() const
{
return defaultPath;
}
}

namespace viva{
const Size& Engine::GetClientSize() const
{
return clientSize;
}
}

namespace viva{
void Engine::SetDefaultPath(const std::wstring& path)
{
defaultPath = path;
}
}

namespace viva{
void Win32Engine::Activity() 
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
}

namespace viva{
Win32Engine::Win32Engine(const wstring& title, const Size& size, const wstring& path): Engine(path, size)
{
window = new Win32Window(title.c_str(), size);
}
}

namespace viva{
void Win32Engine::_Destroy() 
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
}

namespace viva{
void Win32Engine::_Init() 
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
}

namespace viva{
void Win32Engine::OpenConsole() 
{
AllocConsole();
SetConsoleTitle(L"Console");
freopen("CONOUT$", "w", stdout);
freopen("CONIN$", "r", stdin);
}
}

namespace viva{
void Win32Engine::CloseConsole() 
{
FreeConsole();
}
}

namespace viva{
void Win32Engine::Exit() 
{
PostMessage((HWND)window->GetHandle(), WM_CLOSE, (int)CloseReason::EngineClose, 0);
}
}

namespace viva{
CloseReason Win32Engine::Run(const std::function<void()>& gameloop) 
{
return static_cast<Win32Window*>(window)->Run(gameloop, [&]() {Activity(); });
}
}

namespace viva{
ID3D11Buffer* Win32Engine::CreateConstantBuffer(UINT size)
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
}

namespace viva{
Matrix::Matrix()
{
}
}

namespace viva{
Matrix::Matrix(const DirectX::XMMATRIX& _m)
{
m = _m;
}
}

namespace viva{
Matrix::Matrix(DirectX::XMMATRIX&& _m)
{
m = _m;
}
}

namespace viva{
void Matrix::LookAtLH(const Vector& position, const Vector& target, const Vector& up, Matrix* result)
{
result->m = DirectX::XMMatrixLookAtLH(position.v, target.v, up.v);
}
}

namespace viva{
void  Matrix::PerspectiveFovLH(float fovAngle, float aspectRatio, float nearPlane, float farPlane, Matrix* result)
{
result->m = DirectX::XMMatrixPerspectiveFovLH(fovAngle, aspectRatio, nearPlane, farPlane);
}
}

namespace viva{
void Matrix::Translation(const Vector& position, Matrix* result)
{
result->m = DirectX::XMMatrixTranslationFromVector(position.v);
}
}

namespace viva{
void Matrix::Scaling(const Point& scale, Matrix* result)
{
result->m = DirectX::XMMatrixScaling(scale.X, scale.Y, 1);
}
}

namespace viva{
void Matrix::Multiply(const Matrix& m1, const Matrix& m2, Matrix* result)
{
result->m = DirectX::XMMatrixMultiply(m1.m, m2.m);
}
}

namespace viva{
void Matrix::Multiply(const Matrix& m, const Vector& v, Vector* result)
{
result->v = DirectX::XMVector3Transform(v.v, m.m);
}
}

namespace viva{
void Matrix::Identity(Matrix* result)
{
result->m = DirectX::XMMatrixIdentity();
}
}

namespace viva{
void Matrix::Rotation(float angle, Matrix* result)
{
result->m = DirectX::XMMatrixRotationZ(angle);
}
}

namespace viva{
void Matrix::Transpose()
{
m = DirectX::XMMatrixTranspose(m);
}
}

namespace viva{
Camera::Camera(const Size& size)
{
nearPlane = 0.1f;
farPlane = 50.0f;
fovAngle = 0.4f*3.14f; //72 deg
//Camera information
transform.SetPosition(0, 0, -20);  // by default camera is at -20
Vector target(0.0f, 0.0f, 0.0f, 0.0f);
up = Vector(0.0f, 1.0f, 0.0f, 0.0f);

//Set the View matrix
Matrix::LookAtLH(transform.GetPosition(), target, up, &view);

//Set the Projection matrix
aspectRatio = (float)size.Width / size.Height;
Matrix::PerspectiveFovLH(fovAngle, aspectRatio, nearPlane, farPlane, &proj);
}
}

namespace viva{
Size Camera::GetFrustumSize(float z)
{
Size s;
s.Width = (20 + z) * tan(fovAngle / 2) * aspectRatio * 2;
s.Height = (20 + z) * tan(fovAngle / 2) * 2;
return s;
}
}

namespace viva{
const Matrix& Camera::GetView() const
{
return view;
}
}

namespace viva{
const Matrix& Camera::GetProj() const
{
return proj;
}
}

namespace viva{
const Matrix& Camera::GetViewProj() const
{
return viewProj;
}
}

namespace viva{
void Camera::_CalcViewProj()
{
Matrix::Multiply(view, proj, &viewProj);
}
}

namespace viva{
Point Camera::WorldToScreen(const Vector& pos) const
{
Vector res;
Matrix::Multiply(viewProj, pos, &res);

return Point(res.GetX(), res.GetY());
}
}

namespace viva{
Vector Camera::ScreenToWorld(const Point& pos, float z) const
{
return Vector();
}
}

namespace viva{
void Camera::_Destroy()
{
delete this;
}
}

namespace viva{
Pixel::Pixel(): R(1), G(1), B(1), A(1)
{
}
}

namespace viva{
Pixel::Pixel(byte r, byte g, byte b, byte a): R(r), G(g), B(b), A(a)
{
}
}

namespace viva{
Pixel::Pixel(const Color& color): R((int)(color.R * 255)),G((int)(color.G * 255)),B((int)(color.B * 255)),A((int)(color.A * 255))
{
}
}

namespace viva{
Texture* Creator::CreateTexture(const wstring& filepath)
{
Pixel* pixels = nullptr;
Size size = util::ReadImageToPixels(filepath, &pixels);
Texture* tex = CreateTexture(pixels, size, filepath);

if (pixels != nullptr)
free(pixels);

return tex;
}
}

namespace viva{
Font* Creator::CreateFontV(const wstring& filename)
{
return new Font(filename);
}
}

namespace viva{
Font* Creator::CreateFontV(Texture* tex, const vector<Rect>& glyphs)
{
return new Font(tex, glyphs);
}
}

namespace viva{
Font* Creator::CreateFontV(Texture* tex)
{
return new Font(tex);
}
}

namespace viva{
Texture* Creator::CreateTexture(const Pixel* pixels, const Size& size)
{
return CreateTexture(pixels, size, L"");
}
}

namespace viva{
Text* Creator::CreateText(const wstring& text)
{
return new Text(text);
}
}

namespace viva{
Text* Creator::CreateText(const wstring& text, Font* font)
{
return new Text(text, font);
}
}

namespace viva{
Animation* Creator::CreateAnimation(Sprite* sprite)
{
return new Animation(sprite);
}
}

namespace viva{
Animation* Creator::CreateAnimation(const wstring& filename)
{
Sprite* sprite = CreateSprite(filename);
return CreateAnimation(sprite);
}
}

namespace viva{
DrawManager::DrawManager()
{
defaultFilter = TextureFilter::Point;
defaultSurface = creator->CreateSurface();

// create default font
{
vector<int> data =
{
604,1,2,1,6,1,111,1,47,1,8,2,1,2,6,1,2,1,5,5,5,2,18,3,11,1,4,1,11,1,51,1,6,4,7,2,6,5,17,1,
8,2,1,2,5,1,2,1,5,1,4,1,4,1,2,1,17,3,10,1,6,1,10,1,9,1,40,1,6,1,4,1,4,2,1,1,5,1,5,1,
16,1,8,1,2,1,6,1,2,1,5,1,9,1,2,1,8,3,7,1,11,1,6,1,7,7,6,1,40,1,6,1,4,1,7,1,5,1,5,1,
16,1,8,1,2,1,4,8,3,1,10,2,8,1,10,1,10,1,8,1,9,1,9,1,39,1,7,1,4,1,7,1,11,1,16,1,18,1,2,1,
6,4,8,3,5,1,10,1,10,1,8,1,8,1,1,1,8,1,39,1,7,1,4,1,7,1,10,1,17,1,18,1,2,1,10,1,4,3,8,2,
20,1,8,1,7,1,3,1,4,7,13,7,15,1,8,1,4,1,7,1,8,2,18,1,16,8,8,1,7,2,5,1,1,1,2,1,17,1,8,1,
19,1,38,1,8,1,4,1,7,1,7,1,39,1,2,1,10,1,6,1,2,1,4,1,2,2,18,1,8,1,19,1,8,2,27,1,9,1,4,1,
7,1,6,1,20,3,17,1,2,1,5,1,4,1,6,1,2,1,4,1,3,1,18,1,8,1,19,1,8,1,19,2,7,1,9,1,4,1,7,1,
5,1,5,1,15,3,16,1,2,1,6,5,8,2,6,5,18,1,6,1,20,1,7,2,19,2,6,1,11,4,5,7,2,7,34,1,2,1,8,1,
41,1,6,1,28,1,28,1,82,1,42,1,4,1,29,1,1400,4,9,1,5,5,8,4,2,7,5,4,6,4,67,4,53,2,4,1,7,2,5,1,
11,1,6,1,5,1,4,1,4,1,4,1,4,1,29,2,12,2,10,4,6,1,4,1,4,3,5,6,6,4,1,1,2,6,4,7,9,1,6,1,
1,1,5,1,10,1,13,1,4,1,4,1,4,1,4,1,28,1,16,1,8,1,4,1,4,1,5,1,5,2,6,1,4,1,4,1,4,2,3,1,
4,1,4,1,4,1,9,1,5,1,2,1,5,1,9,1,13,1,5,1,4,1,4,1,4,1,5,2,9,2,8,2,5,8,5,2,6,1,4,1,
4,1,3,3,4,1,2,1,5,1,4,1,3,1,6,1,3,1,5,1,3,1,4,1,6,3,6,1,2,1,5,5,5,1,1,4,8,1,6,4,
5,1,3,2,5,2,9,2,7,1,22,1,10,1,4,1,2,1,2,1,4,1,2,1,5,1,4,1,3,1,10,1,5,1,3,1,2,1,10,1,
5,1,3,1,10,1,4,2,4,1,6,1,6,1,4,1,5,3,1,1,23,2,24,2,7,1,5,1,2,1,2,1,4,1,2,1,5,5,4,1,
10,1,5,1,3,4,11,1,4,6,9,1,4,1,5,1,6,1,6,1,4,1,9,1,25,1,7,8,7,1,8,1,6,1,2,1,2,1,3,6,
4,1,4,1,3,1,10,1,5,1,3,1,2,1,11,1,8,1,10,1,4,1,5,1,6,1,6,1,4,1,8,1,17,2,8,2,18,2,16,1,
3,3,3,1,4,1,4,1,4,1,3,1,10,1,5,1,3,1,4,1,3,1,5,1,8,1,4,1,5,1,4,1,5,1,5,1,7,1,4,1,
7,1,7,2,9,1,11,1,16,1,10,2,6,1,8,1,6,1,3,1,4,1,4,1,5,1,3,1,4,1,4,1,4,1,4,5,7,4,4,5,
6,5,6,1,8,4,5,3,8,2,8,2,12,2,12,2,11,2,7,1,3,1,2,3,4,3,1,6,6,5,3,6,4,7,85,1,50,3,1764,7,
5,4,1,1,2,3,2,3,2,7,5,6,2,3,1,4,2,5,4,3,3,3,1,3,3,3,4,4,5,6,5,4,4,6,6,3,1,1,3,7,
3,3,2,3,1,3,4,7,1,4,1,3,3,3,3,1,4,1,4,1,4,2,3,1,4,1,6,1,11,1,5,1,3,1,6,1,7,2,3,2,
3,2,4,1,4,1,4,1,5,1,4,1,3,1,4,1,4,1,4,1,4,1,3,2,3,1,2,1,2,1,4,1,4,1,3,1,6,1,2,1,
5,1,3,1,5,1,4,1,4,1,3,1,10,1,4,1,6,1,11,1,5,1,2,1,7,1,7,1,1,1,1,1,1,1,3,1,1,1,3,1,
3,1,6,1,4,1,4,1,2,1,6,1,3,1,4,1,4,1,4,1,3,1,2,1,2,1,4,1,4,1,4,1,4,1,3,1,2,1,2,1,
4,1,3,1,5,1,2,1,5,1,10,1,4,1,6,1,11,1,5,1,1,1,8,1,7,1,1,1,1,1,1,1,3,1,1,1,3,1,3,1,
6,1,4,1,4,1,2,1,6,1,3,1,4,1,4,1,8,1,2,1,2,1,4,1,4,1,4,1,4,1,3,1,2,1,2,1,5,1,1,1,
6,4,5,1,10,6,6,1,11,1,5,4,7,1,7,1,1,1,1,1,1,1,3,1,2,1,2,1,3,1,6,1,4,1,4,1,2,1,6,1,
3,5,6,4,7,1,7,1,4,1,5,1,2,1,4,1,1,1,1,1,1,1,6,1,7,1,2,1,5,1,3,5,2,1,4,1,6,1,6,1,
4,1,5,1,3,1,6,1,4,1,2,1,2,1,2,1,3,1,3,1,1,1,3,1,6,1,4,5,3,1,6,1,3,1,2,1,11,1,6,1,
7,1,4,1,5,1,2,1,4,1,1,1,1,1,1,1,5,1,1,1,6,1,8,1,6,1,3,1,4,1,6,1,6,1,4,1,5,1,3,1,
6,1,4,1,2,1,5,1,3,1,3,1,1,1,3,1,6,1,4,1,7,1,6,1,3,1,3,1,5,1,4,1,6,1,7,1,4,1,5,1,
2,1,4,1,1,1,1,1,1,1,4,1,3,1,5,1,9,1,5,1,3,1,4,1,6,1,6,1,4,1,5,1,4,1,5,1,4,1,2,1,
5,1,3,1,4,2,4,1,4,1,5,1,8,1,4,1,4,1,4,1,4,2,3,1,6,1,7,1,4,1,6,2,5,1,1,1,1,1,1,1,
3,1,5,1,3,5,7,5,3,3,2,3,2,7,4,4,5,3,3,2,2,8,1,3,3,3,1,3,3,2,5,4,5,5,6,4,4,3,3,2,
3,1,1,3,5,5,6,4,7,2,6,1,3,1,3,3,3,3,115,5,1432,1,22,1,109,1,10,1,38,3,4,1,10,3,9,1,18,1,17,2,
23,2,16,5,12,2,11,1,10,1,5,2,7,3,3,3,3,6,6,1,7,1,11,1,8,1,1,1,18,1,17,1,24,1,15,1,18,1,29,1,
8,1,5,1,4,1,4,1,6,1,7,1,11,1,7,1,3,1,18,1,16,1,24,1,15,1,18,1,29,1,9,1,3,1,9,1,7,1,8,1,
10,1,6,1,5,1,25,4,5,1,1,3,6,4,1,1,4,3,1,1,5,3,5,7,5,3,1,2,3,1,1,3,5,3,7,5,5,1,2,3,
5,1,1,1,9,1,8,1,8,1,10,1,37,1,4,1,4,2,3,1,4,1,4,2,3,1,3,2,4,1,3,1,6,1,8,1,3,2,4,2,
3,1,6,1,11,1,5,1,2,1,8,1,10,1,8,1,8,1,10,1,42,1,4,1,5,1,2,1,9,1,5,1,3,1,5,1,5,1,7,1,
5,1,4,1,4,1,6,1,11,1,5,1,1,1,9,1,9,1,9,1,9,1,9,1,37,6,4,1,5,1,2,1,9,1,5,1,3,7,5,1,
7,1,5,1,4,1,4,1,6,1,11,1,5,3,9,1,8,1,3,1,6,1,9,1,9,1,36,1,5,1,4,1,5,1,2,1,9,1,5,1,
3,1,11,1,7,1,5,1,4,1,4,1,6,1,11,1,5,1,2,1,8,1,7,1,4,1,6,1,10,1,8,1,36,1,4,2,4,2,3,1,
4,1,5,1,3,1,3,2,4,1,4,1,5,1,8,1,3,2,4,1,4,1,6,1,11,1,5,1,3,1,5,5,5,6,6,1,10,1,8,1,
37,4,1,2,2,2,1,3,6,5,5,3,1,2,4,4,5,5,6,3,1,1,3,3,2,3,2,7,8,1,4,2,2,4,25,1,11,1,7,1,
102,1,28,1,37,3,15,3,102,1,28,1,155,5,24,5,74,10,1072,3,159,1,29,1,77,1,72,1,8,1,9,1,19,1,77,1,71,1,9,1,
10,1,18,1,5,2,1,1,2,1,4,2,1,3,6,3,5,2,1,3,6,3,1,2,3,2,2,3,3,4,1,1,2,7,4,2,3,2,3,3,
2,3,1,3,5,2,1,3,2,3,1,3,3,3,2,7,6,1,9,1,10,1,18,1,6,2,1,2,1,1,4,2,3,1,4,1,3,1,5,2,
3,1,4,1,3,2,5,3,5,1,4,2,4,1,9,1,4,1,4,1,4,1,3,1,3,1,3,1,2,1,4,1,3,1,5,1,3,1,4,1,
7,1,9,1,10,1,6,2,10,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,5,1,7,1,10,1,9,1,
4,1,5,1,2,1,4,1,3,1,3,1,3,1,2,1,5,1,3,1,8,1,8,1,9,1,10,1,5,1,2,1,2,1,6,1,6,1,2,1,
2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,5,1,8,5,5,1,9,1,4,1,5,1,2,1,5,1,1,1,1,1,1,1,
5,2,6,1,3,1,7,1,8,1,10,1,11,1,8,2,7,1,6,1,2,1,2,1,4,1,4,1,3,1,5,1,4,1,5,1,2,1,5,1,
5,1,13,1,4,1,9,1,4,1,5,1,2,1,5,1,1,1,1,1,1,1,4,1,2,1,6,1,1,1,7,1,10,1,9,1,10,1,18,1,
6,1,2,1,2,1,4,1,4,1,4,1,3,1,5,2,3,1,4,1,3,2,5,1,7,1,5,1,4,1,4,1,4,1,3,2,6,2,6,1,
1,1,1,1,1,1,3,1,4,1,5,1,1,1,6,1,4,1,6,1,9,1,10,1,15,7,2,3,1,2,1,2,2,3,2,3,4,3,6,1,
1,3,6,3,1,1,4,5,4,6,6,4,6,3,1,2,5,2,7,1,3,1,3,3,2,3,5,1,6,7,6,1,9,1,10,1,56,1,14,1,
76,1,19,1,9,1,10,1,56,1,14,1,75,1,21,1,8,1,9,1,56,3,12,3,71,5,435
};

// here's how above encoding works, each number represents how many consecutive pixels in a row are transparent or white
// they simply alternate between white or transparent
// e.g. 4,7,2 means 4 pixels transparent then 7 pixels white then 2 pixels transparent
vector<Pixel> data2;
Pixel current = Pixel(0,0,0,0);

for (auto i : data)
{
for (int j = 0; j < i; j++)
data2.push_back(current);

current = current.R == 0 ? Pixel(255, 255, 255, 255) : Pixel(0, 0, 0, 0);
}

Texture* t = creator->CreateTexture(data2.data(), Size(190, 95), L"?vivaDefaultFontTexture");
resourceManager->Remove(L"?vivaDefaultFontTexture");
defaultFont = creator->CreateFontV(t);
defaultFont->CalcGlyphs({ 10,19 }, 19);
}

Pixel p[] = { Pixel(255,255,255,255) };
whitePixel = creator->CreateTexture(p, Size(1, 1), L"?whitePixel");
resourceManager->Remove(L"?whitePixel");

vector<Point> square({Point(-1,-1),Point(-1,1) ,Point(1,1) ,Point(1,-1) ,Point(-1,-1) });
rectVertexBuffer = creator->CreateVertexBuffer(square);

vector<Point> circle;
for (int i = 0; i < 21; i++)
circle.push_back(Point(sinf(2 * Math::Pi / 20.0f * i), cosf(2 * Math::Pi / 20.0f * i)));
circleVertexBuffer = creator->CreateVertexBuffer(circle);
}
}

namespace viva{
void DrawManager::_Destroy()
{
defaultSurface->Destroy();
defaultFont->Destroy();
whitePixel->Destroy();
rectVertexBuffer->Destroy();
circleVertexBuffer->Destroy();
delete this;
}
}

namespace viva{
void DrawManager::_DrawNodes()
{
defaultSurface->_DrawAll();
}
}

namespace viva{
void DrawManager::_DrawSurfaces()
{
defaultSurface->_DrawSurface();
}
}

namespace viva{
Polygon* DrawManager::AddPolygon(const vector<Point>& points, Surface* surface)
{
Polygon* p = creator->CreatePolygon(points);
Add(p, surface);
return p;
}
}

namespace viva{
Polygon* DrawManager::AddPolygon(VertexBuffer* vb, Surface* surface)
{
Polygon* p = creator->CreatePolygon(vb);
Add(p, surface);
return p;
}
}

namespace viva{
Polygon* DrawManager::AddRectangle()
{
return AddRectangle(defaultSurface);
}
}

namespace viva{
Polygon* DrawManager::AddRectangle(Surface* surface)
{
Polygon* p = creator->CreatePolygon(rectVertexBuffer);
Add(p, surface);
return p;
}
}

namespace viva{
Polygon* DrawManager::AddCircle()
{
return AddCircle(defaultSurface);
}
}

namespace viva{
Polygon* DrawManager::AddCircle(Surface* surface)
{
Polygon* p = creator->CreatePolygon(circleVertexBuffer);
Add(p, surface);
return p;
}
}

namespace viva{
Polygon* DrawManager::AddCircle(uint vertices)
{
return AddCircle(vertices, defaultSurface);
}
}

namespace viva{
Polygon* DrawManager::AddCircle(uint vertices, Surface* surface)
{
vector<Point> circle;
for (int i = 0; i < vertices + 1; i++)
circle.push_back(Point(sinf(2.0f * Math::Pi / vertices * i), cosf(2.0f * Math::Pi / vertices * i)));

Polygon* p = creator->CreatePolygon(circle);
Add(p, surface);
return p;
}
}

namespace viva{
Polygon* DrawManager::AddPolygon(const vector<Point>& points)
{
return AddPolygon(points, defaultSurface);
}
}

namespace viva{
Polygon* DrawManager::AddPolygon(VertexBuffer* vb)
{
return AddPolygon(vb, defaultSurface);
}
}

namespace viva{
Sprite* DrawManager::AddSprite(Texture* t, Surface* surface)
{
Sprite* s = creator->CreateSprite(t);
Add(s, surface);
return s;
}
}

namespace viva{
Sprite* DrawManager::AddSprite(Texture* t)
{
return AddSprite(t, defaultSurface);
}
}

namespace viva{
Sprite* DrawManager::AddFillRectangle(Surface* surface)
{
Sprite* s = AddSprite(whitePixel, surface);
return s;
}
}

namespace viva{
Sprite* DrawManager::AddFillRectangle()
{
return AddFillRectangle(defaultSurface);
}
}

namespace viva{
Sprite* DrawManager::AddSprite(const wstring& filepath, Surface* surface)
{
Sprite* s = creator->CreateSprite(filepath);
Add(s, surface);
return s;
}
}

namespace viva{
Sprite* DrawManager::AddSprite(const wstring& filepath)
{
return AddSprite(filepath, defaultSurface);
}
}

namespace viva{
Text* DrawManager::AddText(const wstring& text)
{
return AddText(text, defaultSurface);
}
}

namespace viva{
Text* DrawManager::AddText(const wstring& text, Font* font)
{
return AddText(text, font, defaultSurface);
}
}

namespace viva{
Text* DrawManager::AddText(const wstring& text, Surface* surface)
{
Text* t = creator->CreateText(text);
Add(t, surface);

return t;
}
}

namespace viva{
Text* DrawManager::AddText(const wstring& text, Font* font, Surface* surface)
{
Text* t = creator->CreateText(text, font);
Add(t, surface);

return t;
}
}

namespace viva{
Animation* DrawManager::AddAnimation(const wstring& filename, Surface* surface)
{
Animation* ani = creator->CreateAnimation(filename);
Add(ani, surface);
return ani;
}
}

namespace viva{
Animation* DrawManager::AddAnimation(const wstring& filename)
{
Animation* ani = creator->CreateAnimation(filename);
Add(ani, defaultSurface);
return ani;
}
}

namespace viva{
Animation* DrawManager::AddAnimation(Sprite* sprite, Surface* surface)
{
Animation* ani = creator->CreateAnimation(sprite);
Add(ani, surface);
return ani;
}
}

namespace viva{
Animation* DrawManager::AddAnimation(Sprite* sprite)
{
Animation* ani = creator->CreateAnimation(sprite);
Add(ani, defaultSurface);
return ani;
}
}

namespace viva{
void DrawManager::Remove(Drawable* drawable)
{
drawable->GetSurface()->Remove(drawable);
}
}

namespace viva{
void DrawManager::Add(Drawable* drawable, Surface* surface)
{
surface->Add(drawable);
}
}

namespace viva{
void DrawManager::Add(Drawable* drawable)
{
defaultSurface->Add(drawable);
}
}

namespace viva{
TextureFilter DrawManager::GetDefaultTextureFilter() const
{
return defaultFilter;
}
}

namespace viva{
void DrawManager::SetDefaultTextureFilter(TextureFilter filter)
{
defaultFilter = filter;
}
}

namespace viva{
Texture* DrawManager::GetPixel()
{
return whitePixel;
}
}

namespace viva{
Font* DrawManager::GetDefaultFont() const
{
return defaultFont;
}
}

namespace viva{
void DrawManager::Clear()
{
/*for (auto& s : surfaces)
s->Destroy();

surfaces.clear();*/

defaultSurface->Clear();
}
}

namespace viva{
Error::Error(const char* fun, const char* msg): runtime_error(msg), function(fun)
{
}
}

namespace viva{
Error::Error(const char* fun, wstring msg): runtime_error(std::string(msg.begin(),msg.end()).c_str()), function(fun)
{
}
}

namespace viva{
Rect::Rect():left(0), top(0), right(0), bottom(0)
{
}
}

namespace viva{
Rect::Rect(float _left, float _top, float _right, float _bottom): left(_left), top(_top), right(_right), bottom(_bottom)
{
}
}

namespace viva{
Font::Font(Texture* tex, const vector<Rect>& glyphs): texture(tex), charsUv(glyphs)
{
}
}

namespace viva{
Font::Font(Texture* tex):texture(tex)
{
}
}

namespace viva{
Font::Font(const wstring& filename)
{
Texture* t = resourceManager->GetTexture(filename);

if (t == nullptr)
t = creator->CreateTexture(filename);

texture = t;
}
}

namespace viva{
Font* Font::SetGlyphs(const vector<Rect>& glyphs)
{
charsUv = glyphs;
return this;
}
}

namespace viva{
Font* Font::CalcGlyphs(const Size& letterSize, uint charsPerRow)
{
charsUv.clear();

for (int i = 0; i < 32; i++)
charsUv.push_back(Rect(0, 0, 0, 0));

for (int i = 0, k = 32; k < 127; i++)
{
for (int j = 0; j < charsPerRow && k < 127; j++, k++)
{
charsUv.push_back(Rect(j*letterSize.Width / texture->GetSize().Width,
i*letterSize.Height / texture->GetSize().Height,
(j + 1)*letterSize.Width / texture->GetSize().Width,
(i + 1)*letterSize.Height / texture->GetSize().Height));
}
}

return this;
}
}

namespace viva{
const Rect& Font::GetChar(uint code) const
{
return charsUv.at(code);
}
}

namespace viva{
Texture* Font::GetTexture() const
{
return texture;
}
}

namespace viva{
void Font::Destroy()
{
if (!texture->IsCached())
texture->Destroy();

delete this;
}
}

namespace viva::Input{
void Mouse::UseRawInput(bool val)
{
rawCursor = val;
}
}

namespace viva::Input{
bool Mouse::IsCursorVisible() const
{
return cursorVisibility;
}
}

namespace viva{
Resource::Resource(const wstring& _name, ResourceType t)
{
name = _name;
type = t;
}
}

namespace viva{
bool Resource::IsCached() const
{
return cached;
}
}

namespace viva{
ResourceType Resource::GetType() const
{
return type;
}
}

namespace viva{
void Resource::_SetCached(bool _cached)
{
cached = _cached;
}
}

namespace viva{
const wstring& Resource::GetName() const
{
return name;
}
}

namespace viva{
Texture::Texture(const wstring& _name): Resource(_name, ResourceType::Texture)
{
}
}

namespace viva{
Size Texture::GetSize() const
{
return size;
}
}

namespace viva::Input{
void Keyboard::OnKeyPressed(const std::function<void(KeyboardKey)>& handler)
{
onKeyPressedHandlers.push_back(handler);
}
}

namespace viva::Input{
void Keyboard::OnKeyReleased(const std::function<void(KeyboardKey)>& handler)
{
onKeyReleasedHandlers.push_back(handler);
}
}

namespace viva::Input{
void Keyboard::ClearOnKeyPressed()
{
onKeyPressedHandlers.clear();
}
}

namespace viva::Input{
void Keyboard::ClearOnKeyReleased()
{
onKeyReleasedHandlers.clear();
}
}

namespace viva{
Polygon::Polygon(): parent(nullptr), index(-1), visible(true)
{
}
}

namespace viva{
Transform* Polygon::T() 
{
return &transform;
}
}

namespace viva{
Transform* Polygon::GetTransform() 
{
return &transform;
}
}

namespace viva{
Node* Polygon::GetNode() 
{
return this;
}
}

namespace viva{
uint Polygon::GetVertexCount() const
{
return vertexCount;
}
}

namespace viva{
Surface* Polygon::GetSurface() const 
{
return parent;
}
}

namespace viva{
bool Polygon::IsVisible() const 
{
return visible;
}
}

namespace viva{
Drawable* Polygon::SetVisible(bool val) 
{
visible = val;
return this;
}
}

namespace viva{
void Polygon::_SetSurface(Surface* surface) 
{
parent = surface;
}
}

namespace viva{
void Polygon::_SetIndex(uint i) 
{
index = i;
}
}

namespace viva{
int Polygon::_GetIndex() const 
{
return index;
}
}

namespace viva{
Sprite::Sprite(): flipHorizontally(false), flipVertically(false),uv(0, 0, 1, 1), filter(drawManager->GetDefaultTextureFilter()),parent(nullptr), index(-1), visible(true)
{
}
}

namespace viva{
Transform* Sprite::T() 
{
return &transform;
}
}

namespace viva{
Transform* Sprite::GetTransform() 
{
return &transform;
}
}

namespace viva{
Sprite* Sprite::SetTextureFilter(TextureFilter _filter)
{
filter = _filter;
return this;
}
}

namespace viva{
TextureFilter Sprite::GetTextureFilter() const
{
return filter;
}
}

namespace viva{
Sprite* Sprite::SetPixelScale(const viva::Size& size)
{
Size frustum = camera->GetFrustumSize(transform.GetPosition().f.z);
Size client = engine->GetClientSize();
//Point unitsPerPixel = { frustum.Width / client.Width, frustum.Height / client.Height };
//scale.x = unitsPerPixel.x * _size.width / 2;
//scale.y = unitsPerPixel.y * _size.height / 2;

transform.SetScale(frustum.Width / client.Width * size.Width / 2,
frustum.Height / client.Height * size.Height / 2);

return this;
}
}

namespace viva{
Sprite* Sprite::SetPixelScale(uint width, uint height)
{
return SetPixelScale(Size(width, height));
}
}

namespace viva{
Sprite* Sprite::SetScale2TextureSize()
{
SetPixelScale(GetTexture()->GetSize());
return this;
}
}

namespace viva{
bool Sprite::IsFlippedHorizontally() const
{
return flipHorizontally;
}
}

namespace viva{
Sprite* Sprite::SetFlipHorizontally(bool _flipHorizontally)
{
flipHorizontally = _flipHorizontally;
return this;
}
}

namespace viva{
bool Sprite::IsFlippedVertically() const
{
return flipVertically;
}
}

namespace viva{
Sprite* Sprite::SetFlipVertically(bool _flipVertically)
{
flipVertically = _flipVertically;
return this;
}
}

namespace viva{
Node* Sprite::GetNode() 
{
return this;
}
}

namespace viva{
const Rect& Sprite::GetUV() const
{
return uv;
}
}

namespace viva{
Sprite* Sprite::SetUV(const Rect& _uv)
{
uv = Rect(_uv.left, 1 - _uv.bottom, _uv.right, 1 - _uv.top);
return this;
}
}

namespace viva{
Sprite* Sprite::SetUV(float left, float top, float right, float bottom)
{
return SetUV(Rect(left, top, right, bottom));
}
}

namespace viva{
Surface* Sprite::GetSurface() const 
{
return parent;
}
}

namespace viva{
bool Sprite::IsVisible() const 
{
return visible;
}
}

namespace viva{
Drawable* Sprite::SetVisible(bool val) 
{
visible = val;
return this;
}
}

namespace viva{
void Sprite::_SetSurface(Surface* surface) 
{
parent = surface;
}
}

namespace viva{
void Sprite::_SetIndex(uint i) 
{
index = i;
}
}

namespace viva{
int Sprite::_GetIndex() const 
{
return index;
}
}

namespace viva{
ResourceManager::ResourceManager()
{
}
}

namespace viva{
void ResourceManager::AddResource(Resource* res)
{
auto it = resources.find(res->GetName());

if (it != resources.end())
throw Error(__FUNCTION__, "Resource of that name already exists");

res->_SetCached(true);
resources[res->GetName()] = res;
}
}

namespace viva{
Resource* ResourceManager::GetResource(const wstring& name) const
{
auto it = resources.find(name);

if (it == resources.end())
return nullptr;        // DONT CHANGE THAT to error

return it->second;
}
}

namespace viva{
Texture* ResourceManager::GetTexture(const wstring& name) const
{
auto it = resources.find(name);

if (it == resources.end() || it->second->GetType() != ResourceType::Texture)
return nullptr;             // DONT CHANGE THAT to error

return (Texture*)it->second;
}
}

namespace viva{
void ResourceManager::Remove(const wstring& name)
{
auto it = resources.find(name);

if (it == resources.end())
throw Error(__FUNCTION__, "Resource not found");

it->second->_SetCached(false);
resources.erase(it);
}
}

namespace viva{
void ResourceManager::RemoveAll()
{
for (auto& r : resources)
r.second->_SetCached(false);

resources.clear();
}
}

namespace viva{
void ResourceManager::_Destroy()
{
for (auto& r : resources)
r.second->Destroy();

delete this;
}
}

namespace viva{
Polygon* Win32Creator::CreatePolygon(const vector<Point>& points)
{
VertexBuffer* vb = CreateVertexBuffer(points);
return new Win32Polygon(vb);
}
}

namespace viva{
Polygon* Win32Creator::CreatePolygon(VertexBuffer* vb)
{
vb->_MakeShared();
return new Win32Polygon(vb);
}
}

namespace viva{
VertexBuffer* Win32Creator::CreateVertexBuffer(const vector<Point>& points) 
{
uint count = (uint)points.size();

D3D11_BUFFER_DESC bd;
ZeroMemory(&bd, sizeof(bd));
bd.Usage = D3D11_USAGE_DEFAULT;				   // GPU writes and reads
bd.ByteWidth = (UINT)(sizeof(Vertex) * count);
bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
bd.CPUAccessFlags = 0;		                   // CPU does nothing

vector<Vertex> temp;
for (int i = 0; i < points.size(); i++)
{
//float distFromOrigin = sqrtf(points[i].x*points[i].x + points[i].y*points[i].y);
//if (distFromOrigin > span)
//    span = distFromOrigin;
//vertices.push_back(DirectX::XMVectorSet(points[i].x, points[i].y, 0, 0));
temp.push_back({ points.at(i).X, points.at(i).Y, 0, 1, 1, 1, 0, 0 }); // IMPORTANT, red must be non 0, 0 is reserved for sprites
}
//transformedVertices = vertices;

D3D11_SUBRESOURCE_DATA sd;
ZeroMemory(&sd, sizeof(sd));
sd.pSysMem = temp.data();                   //Memory in CPU to copy in to GPU

ID3D11Buffer* vertexBuffer;
d3d.device->CreateBuffer(&bd, &sd, &vertexBuffer);

return new Win32VertexBuffer(vertexBuffer, count);
}
}

namespace viva{
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
HRESULT hr = d3d.device->CreateTexture2D(&textureDesc, NULL, &tex);
Checkhr(hr, "CreateTexture2D()");

D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
renderTargetViewDesc.Format = textureDesc.Format;
renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
renderTargetViewDesc.Texture2D.MipSlice = 0;
hr = d3d.device->CreateRenderTargetView(tex,
&renderTargetViewDesc, &rtv);
Checkhr(hr, "CreateRenderTargetView()");

D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
shaderResourceViewDesc.Format = textureDesc.Format;
shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
shaderResourceViewDesc.Texture2D.MipLevels = 1;
hr = d3d.device->CreateShaderResourceView(tex,
&shaderResourceViewDesc, &srv);
Checkhr(hr, "CreateShaderResourceView()");

Win32Surface* surf = new Win32Surface(tex, rtv, srv);
surf->SetPixelShader(d3d.defaultPost);
return surf;
}
}

namespace viva{
PixelShader* Win32Creator::CreatePixelShader(const wstring& filepath) 
{
std::string ps = util::ReadFileToStringA(filepath);
return CreatePixelShader(ps);
}
}

namespace viva{
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
}

namespace viva{
ID3D11ShaderResourceView* Win32Creator::SrvFromPixels(const Pixel* pixels, const Size& _size)
{
ID3D11Texture2D *tex;
ID3D11ShaderResourceView* srv;

D3D11_SUBRESOURCE_DATA sub;
sub.pSysMem = pixels;
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
}

namespace viva{
Sprite* Win32Creator::CreateSprite(Texture* texture)
{
Win32Texture* tex = static_cast<Win32Texture*>(texture);
Win32PixelShader* ps = d3d.defaultPS;
return new Win32Sprite(tex, ps);
}
}

namespace viva{
Sprite* Win32Creator::CreateSprite(const wstring& filepath)
{
Texture* tex = resourceManager->GetTexture(filepath);

if (tex == nullptr)
tex = Creator::CreateTexture(filepath);

return CreateSprite(tex);
}
}

namespace viva{
Texture* Win32Creator::CreateTexture(const Pixel* pixels, const Size& size, const wstring& name) 
{
Texture* t = new Win32Texture(name, SrvFromPixels(pixels, size), size);

if(name.size() != 0)
resourceManager->AddResource(t);

return t;
}
}

namespace viva{
void Win32Creator::_Destroy() 
{
delete this;
}
}

namespace viva{
Routine::Routine(const std::function<int()>& activity, wstring name): Activity(activity), Name(name)
{
}
}

namespace viva{
void Routine::Destroy() 
{
remove = true;
}
}

namespace viva{
void Routine::Pause() 
{
pause = true;
}
}

namespace viva{
void Routine::Resume() 
{
pause = false;
}
}

namespace viva{
const wstring& Routine::GetName() 
{
return Name;
}
}

namespace viva{
void RoutineManager::_Activity()
{
double gameTime = time->GetGameTime();

if (routines.size() == 0)
return;

//might be removed so backwards iteration
for (int i = (int)routines.size() - 1; i >= 0; i--)
{
// destroy if remove flag is up
if (routines.at(i) != nullptr && routines.at(i)->remove)
{
delete routines.at(i);
routines.at(i) = nullptr;
}

//pop if last routine is empty
if (routines.at(i) == nullptr && i == routines.size() - 1)
{
routines.pop_back();
continue;
}
//if its empty but not last
else if (routines.at(i) == nullptr)
{
routines.at(i) = routines.back();
routines.pop_back();
continue;
}

int ret = 1;

//if delay time has passed...
if (gameTime - routines.at(i)->startTime > routines.at(i)->delay && !routines.at(i)->pause)
//...and it's time for next pulse then run
if (routines.at(i)->tick == 0 ||
(gameTime - routines.at(i)->lastPulse > routines.at(i)->tick))
{
ret = routines.at(i)->Activity();
routines.at(i)->lastPulse = gameTime;
}
//if returned 0 or expired then remove
if (ret == 0 || (routines.at(i)->lifeTime > 0 &&
gameTime - routines.at(i)->startTime > routines.at(i)->lifeTime))
{
delete routines.at(i);
routines.at(i) = routines.back();
routines.pop_back();
}
}
}
}

namespace viva{
IRoutine* RoutineManager::AddRoutine(const std::function<int()>& func, const wstring& name, double delay, double lifeTime, double tick)
{
Routine* newRoutine = new Routine(func, name);
newRoutine->tick = tick;
newRoutine->lifeTime = lifeTime;
newRoutine->delay = delay;
newRoutine->startTime = time->GetGameTime();
newRoutine->Activity = func;
newRoutine->Name = name;
newRoutine->lastPulse = 0;
newRoutine->remove = false;
newRoutine->pause = false;

routines.push_back(newRoutine);
return newRoutine;
}
}

namespace viva{
IRoutine* RoutineManager::FindRoutine(wstring name)
{
for (int i = 0; i<routines.size(); i++)
if (routines.at(i) && routines.at(i)->Name == name)
return routines.at(i);

throw Error(__FUNCTION__, "Routine not found");
}
}

namespace viva{
void RoutineManager::Trigger(int _event, int data)
{
auto it = handlers.find(_event);

if (it == handlers.end())
return;

for (auto& handler : it->second)
handler(data);
}
}

namespace viva{
void RoutineManager::AddHandler(int _event, const std::function<void(int)>& handler)
{
handlers[_event].push_back(handler);
}
}

namespace viva{
void RoutineManager::ClearHandlers(int _event)
{
auto it = handlers.find(_event);

if (it == handlers.end())
return;

it->second.clear();
}
}

namespace viva{
void RoutineManager::ClearHandlers()
{
handlers.clear();
}
}

namespace viva{
void RoutineManager::ClearRoutines()
{
for (uint i = 0; i < routines.size(); i++)
delete routines.at(i);

routines.clear();
}
}

namespace viva{
void RoutineManager::_Destroy()
{
ClearRoutines();
ClearHandlers();

delete this;
}
}

namespace viva{
int VertexBuffer::GetVertexCount() const
{
return vertexCount;
}
}

namespace viva{
VertexBuffer::VertexBuffer(uint vertexCount): shared(false), vertexCount(vertexCount)
{
}
}

namespace viva{
bool VertexBuffer::IsShared() const
{
return shared;
}
}

namespace viva{
void VertexBuffer::_MakeShared()
{
shared = true;
}
}

namespace viva{
Win32VertexBuffer::Win32VertexBuffer(ID3D11Buffer* vb, uint vertexCount): VertexBuffer(vertexCount), vertexBuffer(vb)
{
}
}

namespace viva{
void Win32VertexBuffer::Destroy() 
{
vertexBuffer->Release();
delete this;
}
}

namespace viva{
Surface::Surface()
{
}
}

namespace viva{
void Surface::Add(Drawable* d)
{
d->_SetIndex(drawables.size());
d->_SetSurface(this);
drawables.push_back(d);
}
}

namespace viva{
void Surface::RemoveAll()
{
for (uint i = 0; i < drawables.size(); i++)
{
drawables.at(i)->_SetIndex(-1);
drawables.at(i)->_SetSurface(nullptr);
}

drawables.clear();
}
}

namespace viva{
void Surface::Remove(Drawable* d)
{
int indexOfd = d->_GetIndex();

if (indexOfd == -1)
return;

// if d is not at the end
if (indexOfd != drawables.size() - 1)
{
// move back to where d is and update its index
drawables.back()->_SetIndex(indexOfd);
drawables.at(indexOfd) = drawables.back();
}

drawables.pop_back();
d->_SetIndex(-1);
d->_SetSurface(nullptr);
}
}

namespace viva{
void Surface::Clear()
{
for (uint i = 0; i < drawables.size(); i++)
drawables.at(i)->GetNode()->Destroy();

drawables.clear();
}
}

namespace viva{
Time::Time(): gameTime(0), frameTime(0)
{
}
}

namespace viva{
double Time::GetGameTime()
{
return gameTime;
}
}

namespace viva{
double Time::GetFrameTime() const
{
return frameTime;
}
}

namespace viva{
double Time::GetFps() const
{
return 1 / frameTime;
}
}

namespace viva{
Window::Window()
{
}
}

namespace viva{
Win32Window::Win32Window(const std::wstring& title, const Size& size)
{
const wchar_t className[] = L"myWindowClass";
WNDCLASSEX wc;
ZeroMemory(&msg, sizeof(msg));
ZeroMemory(&wc, sizeof(wc));
wc.cbSize = sizeof(WNDCLASSEX);
wc.lpfnWndProc = WndProc;
wc.hInstance = GetModuleHandle(0);
wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
wc.lpszClassName = className;
wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

if (!RegisterClassEx(&wc))
{
throw viva::Error("Win32Window()", "Window Class failed to register");
}

RECT rect = { 0, 0, (int)size.Width, (int)size.Height };

// this is to enforce the correct size of window client
AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, FALSE, 0);

handle = CreateWindowEx(0, className, title.c_str(), WS_OVERLAPPEDWINDOW,
CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
NULL, NULL, GetModuleHandle(0), NULL);

USHORT HID_USAGE_PAGE_GENERIC = 1;
USHORT HID_USAGE_GENERIC_MOUSE = 2;

Rid.usUsagePage = HID_USAGE_PAGE_GENERIC;
Rid.usUsage = HID_USAGE_GENERIC_MOUSE;
Rid.dwFlags = RIDEV_INPUTSINK;
Rid.hwndTarget = handle;
RegisterRawInputDevices(&Rid, 1, sizeof(RAWINPUTDEVICE));

if (handle == NULL)
{
MessageBox(NULL, L"Window Creation Failed!", L"Error!",
MB_ICONEXCLAMATION | MB_OK);
exit(0);
}
}
}

namespace viva{
void* Win32Window::GetHandle() const 
{
return handle;
}
}

namespace viva{
void Win32Window::_Destroy() 
{
DestroyWindow(handle);
UnregisterClass(L"myWindowClass", GetModuleHandle(0));
delete this;
}
}

namespace viva{
void Win32Window::SetWindowTitle(const wstring& title) 
{
::SetWindowText(handle, title.c_str());
}
}

namespace viva{
CloseReason Win32Window::Run(const std::function<void()>& gameloop, const std::function<void()>& intloop)
{
ShowWindow(handle, SW_SHOW);
UpdateWindow(handle);

win32mouse = static_cast<Input::Win32Mouse*>(mouse);
activity = gameloop;
worker = intloop;

while (true)
{
if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
{
if (msg.message == WM_QUIT)
{
CloseReason code = (CloseReason)msg.wParam;
ZeroMemory(&msg, sizeof(msg));
return code;
}
TranslateMessage(&msg);
DispatchMessage(&msg);
}
else
{
worker();
activity();
}
}
}
}

namespace viva{
Vertex::Vertex()
{
}
}

namespace viva{
Vertex::Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v): X(_x), Y(_y), Z(_z), R(_r), G(_g), B(_b), U(_u), V(_v)
{
}
}

namespace viva::Input{
Win32Mouse::Win32Mouse(): lastCursorPos({ 0,0 }),mouseWheel(0),cursorDelta({ 0,0 }),cursorDeltaRaw({ 0,0 }),useRaw(false),curState(3),prevState(3)
{
window->GetHandle();
POINT p;
::GetCursorPos(&p);
lastCursorPos.X = (float)p.x;
lastCursorPos.Y = (float)p.y;
}
}

namespace viva::Input{
int Win32Mouse::GetMappedKey(MouseKey key) const
{
switch (key)
{
case MouseKey::Left:
return ARR_LBUTTON;
case MouseKey::Right:
return ARR_RBUTTON;
case MouseKey::Middle:
return ARR_MBUTTON;
default:
throw Error("Win32Mouse::IsButtonDown()", "unknown default statement");
}
}
}

namespace viva::Input{
void Win32Mouse::SetMouseWheel(int wheel)
{
mouseWheel = wheel;
}
}

namespace viva::Input{
void Win32Mouse::SetCursorDeltaRaw(int x, int y)
{
cursorDeltaRaw.X = (float)x;
cursorDeltaRaw.Y = (float)y;
}
}

namespace viva::Input{
int Win32Mouse::GetWheelDelta() const 
{
return mouseWheel;
}
}

namespace viva::Input{
Point Win32Mouse::GetCursorDelta() const 
{
return useRaw ? cursorDeltaRaw : cursorDelta;
}
}

namespace viva::Input{
Point Win32Mouse::GetCursorClientPos() const 
{
throw Error("Win32Mouse::GetCursorClientPos()", "Not implemented");
return lastCursorPos;
}
}

namespace viva::Input{
Point Win32Mouse::GetCursorPos() const 
{
return lastCursorPos;
}
}

namespace viva::Input{
void Win32Mouse::ShowCursor(bool visible)
{
::ShowCursor(visible);
}
}

namespace viva::Input{
bool Win32Mouse::IsButtonDown(MouseKey key) const 
{
int mappedKey = GetMappedKey(key);

return curState.at(mappedKey);
}
}

namespace viva::Input{
bool Win32Mouse::IsButtonPressed(MouseKey key) const
{
int mappedKey = GetMappedKey(key);

return curState.at(mappedKey) && !prevState.at(mappedKey);
}
}

namespace viva::Input{
bool Win32Mouse::IsButtonReleased(MouseKey key) const
{
int mappedKey = GetMappedKey(key);

return !curState.at(mappedKey) && prevState.at(mappedKey);
}
}

namespace viva::Input{
void Win32Mouse::_Activity() 
{
// get cursor pos and delta from os
window->GetHandle();
POINT p;
::GetCursorPos(&p);
cursorDelta.X = p.x - lastCursorPos.X;
cursorDelta.Y = p.y - lastCursorPos.Y;
lastCursorPos.X = (float)p.x;
lastCursorPos.Y = (float)p.y;

//swap states
curState.swap(prevState);

// get button states
curState.at(ARR_LBUTTON) = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) && true;
curState.at(ARR_RBUTTON) = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) && true;
curState.at(ARR_MBUTTON) = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) && true;
}
}

namespace viva::Input{
void Win32Mouse::ResetKey(MouseKey key) 
{
int mappedKey = GetMappedKey(key);
curState.at(mappedKey) = false;
prevState.at(mappedKey) = false;
}
}

namespace viva::Input{
void Win32Mouse::_Destroy() 
{
delete this;
}
}

namespace viva::Input{
Win32Keyboard::Win32Keyboard(): keyNumber(256),curState(keyNumber),prevState(keyNumber),capslockActive(false)
{
}
}

namespace viva::Input{
void Win32Keyboard::_Activity() 
{
capslockActive = GetKeyState((int)KeyboardKey::CapsLock) & 1;

//swap states
curState.swap(prevState);

// get button states
for (int i = 0; i < keyNumber; i++)
{
curState.at(i) = (GetAsyncKeyState(i) & 0x8000) && true;

// fire events
if (IsKeyPressed((KeyboardKey)i))
for (auto& h : onKeyPressedHandlers)
h((KeyboardKey)i);
else if (IsKeyReleased((KeyboardKey)i))
for (auto& h : onKeyReleasedHandlers)
h((KeyboardKey)i);
}
}
}

namespace viva::Input{
bool Win32Keyboard::IsKeyDown(KeyboardKey key) const 
{
return curState.at((int)key);
}
}

namespace viva::Input{
bool Win32Keyboard::IsKeyPressed(KeyboardKey key) const 
{
return curState.at((int)key) && !prevState.at((int)key);
}
}

namespace viva::Input{
bool Win32Keyboard::IsKeyReleased(KeyboardKey key) const 
{
return !curState.at((int)key) && prevState.at((int)key);
}
}

namespace viva::Input{
char Win32Keyboard::GetChar(bool enableShift, bool enableCapslock) const 
{
byte input[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'Q', 'W', 'E', 'R', 'T',
'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0xc0, 0xbd, 0xbb, 0xdc, 0xdb,
0xdd, 0xba, 0xde, 0xbc, 0xbe, 0xbf,
' ', 0x0d, '\t', '\b' };
byte output[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'q', 'w', 'e', 'r', 't',
'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
'z', 'x', 'c', 'v', 'b', 'n', 'm', '`', '-', '=', '\\', '[', ']', ';', '\'', ',', '.', '/',
' ', '\n', '\t', '\b' };
byte output2[] = { ')', '!', '@', '#', '$', '%', '^', '&', '*', '(', 'Q', 'W', 'E', 'R', 'T',
'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', '~', '_', '+', '|', '{', '}', ':', '\"', '<', '>', '?',
' ', '\n', '\t', '\b' };
// from combination of capslock and shit, figure out what is the case
char mod = (enableShift && IsKeyDown(KeyboardKey::Shift)) + (enableCapslock && capslockActive);

for (uint i = 0; i < sizeof(input); i++)
{
if (IsKeyPressed((KeyboardKey)input[i]))
{
if (mod == 1)
return output2[i];
else
return output[i];
}
}
return 0;
}
}

namespace viva::Input{
bool Win32Keyboard::IsCapslockActive() const 
{
return capslockActive;
}
}

namespace viva::Input{
void Win32Keyboard::ResetKey(KeyboardKey key) 
{
curState.at((int)key) = false;
prevState.at((int)key) = false;
}
}

namespace viva::Input{
void Win32Keyboard::_Destroy() 
{
delete this;
}
}

namespace viva{
Win32Polygon::Win32Polygon(VertexBuffer* vb): vertexBuffer((Win32VertexBuffer*)vb)
{
vertexCount = vb->GetVertexCount();
ps = d3d.defaultPS;
}
}

namespace viva{
void Win32Polygon::Destroy() 
{
if(!vertexBuffer->IsShared())
vertexBuffer->Destroy();

if (index != -1)
parent->Remove(this);

delete this;
}
}

namespace viva{
PixelShader* Win32Polygon::GetPixelShader() const 
{
return ps;
}
}

namespace viva{
void Win32Polygon::SetPixelShader(PixelShader* _ps)
{
ps = (Win32PixelShader*)_ps;
}
}

namespace viva{
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
d3d.context->IASetVertexBuffers(0, 1, &(vertexBuffer->vertexBuffer), &stride, &offset);

if(visible)
d3d.context->Draw(vertexCount, 0);
}
}

namespace viva{
Action::Action(const vector<Rect>& _uvTable, const wstring& _name, double _speed): name(_name), uvTable(_uvTable), speed(_speed)
{
}
}

namespace viva{
Animation::Animation(Sprite* _sprite): indicator(0), currentFrame(0), currentAction(nullptr), sprite(_sprite)
{
}
}

namespace viva{
Transform* Animation::T() 
{
return sprite->T();
}
}

namespace viva{
Transform* Animation::GetTransform() 
{
return sprite->T();
}
}

namespace viva{
void Animation::_Play()
{
if (currentAction != nullptr && currentAction->speed != 0)
{
indicator += currentAction->speed * time->GetFrameTime();
if (indicator >= 1)
{
indicator = 0;
NextFrame();
}
else if (indicator < 0)
{
indicator = 1;
PreviousFrame();
}
}

if(currentAction != nullptr)
sprite->SetUV(currentAction->uvTable.at(currentFrame));
}
}

namespace viva{
int Animation::GetFrameCount() const
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

return currentAction->uvTable.size();
}
}

namespace viva{
void Animation::NextFrame()
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

currentFrame++;

for (int i = 0; i < onFrameChangedhandlers.size(); i++)
onFrameChangedhandlers.at(i)(currentFrame);

if (currentFrame >= currentAction->uvTable.size())
{
currentFrame = 0;

for (int i = 0; i < onActionLoopedHandlers.size(); i++)
onActionLoopedHandlers.at(i)(currentFrame);
}
}
}

namespace viva{
void Animation::PreviousFrame()
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

currentFrame--;

for (int i = 0; i < onFrameChangedhandlers.size(); i++)
onFrameChangedhandlers.at(i)(currentFrame);

if (currentFrame < 0)
{
currentFrame = currentAction->uvTable.size() - 1;

for (int i = 0; i < onActionLoopedHandlers.size(); i++)
onActionLoopedHandlers.at(i)(currentFrame);
}
}
}

namespace viva{
Sprite* Animation::GetSprite() const
{
return sprite;
}
}

namespace viva{
double Animation::GetSpeed() const
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

return currentAction->speed;
}
}

namespace viva{
void Animation::SetSpeed(double speed)
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

currentAction->speed = speed;
}
}

namespace viva{
void Animation::SetSpeed(double speed, const wstring& action)
{
for(auto& a : actions)
if (a.name == action)
{
a.speed = speed;
return;
}

throw new Error(__FUNCTION__, "Name not found");
}
}

namespace viva{
int Animation::GetFrame() const
{
return currentFrame;
}
}

namespace viva{
void Animation::SetFrame(int _currentFrame)
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

currentFrame = _currentFrame;

if (currentFrame < 0)
currentFrame = 0;
else if (currentFrame >= currentAction->uvTable.size())
currentFrame = currentAction->uvTable.size() - 1;
}
}

namespace viva{
void Animation::SetAction(const wstring& name)
{
auto it = std::find_if(actions.begin(), actions.end(), [&](Action& e) { return e.name == name; });

if (it == actions.end())
throw Error(__FUNCTION__, "Name not found");

currentAction = it._Ptr;
}
}

namespace viva{
const wstring& Animation::GetAction() const
{
if (currentAction == nullptr)
throw Error(__FUNCTION__, "Action not set");

return currentAction->name;
}
}

namespace viva{
void Animation::AddAction(const wstring& name, double speed, int columns, int rows, int first, int last)
{
auto it = std::find_if(actions.begin(), actions.end(), [&](Action& e) { return e.name == name; });

if (it != actions.end())
throw Error(__FUNCTION__, L"Action " + name + L" is already on the list");

vector<Rect> uvTable;

float width = 1.0f / columns;
float height = 1.0f / rows;

for (int i = 0; i < rows; i++)
for (int j = 0; j < columns; j++)
{
if (columns * i + j >= first)
uvTable.push_back(Rect(width*j, height*i, width*(j + 1), height*(i + 1)));
if (columns * i + j >= last)
{
// break;
i = rows;
j = columns;
}
}

actions.push_back(Action(uvTable, name, speed));
}
}

namespace viva{
void Animation::AddAction(const wstring& name, double speed, const vector<Rect>& uvTable)
{
auto it = std::find_if(actions.begin(), actions.end(), [&](Action& e) { return e.name == name; });

if (it != actions.end())
throw Error(__FUNCTION__, L"Action " + name + L" is already on the list");

actions.push_back(Action(uvTable, name, speed));
}
}

namespace viva{
void Animation::AddOnFrameChangeHandler(const std::function<void(int)>& fun)
{
onFrameChangedhandlers.push_back(fun);
}
}

namespace viva{
void Animation::AddOnActionLoopedHandler(const std::function<void(int)>& fun)
{
onActionLoopedHandlers.push_back(fun);
}
}

namespace viva{
void Animation::ClearOnFrameChangeHandlers()
{
onFrameChangedhandlers.clear();
}
}

namespace viva{
void Animation::ClearAddOnActionLoopedHandlers()
{
onActionLoopedHandlers.clear();
}
}

namespace viva{
void Animation::_Draw() 
{
_Play();

if(currentAction != nullptr)
sprite->_Draw();
}
}

namespace viva{
Surface* Animation::GetSurface() const 
{
return sprite->GetSurface();
}
}

namespace viva{
bool Animation::IsVisible() const 
{
return sprite->IsVisible();
}
}

namespace viva{
Drawable* Animation::SetVisible(bool val) 
{
sprite->SetVisible(val);
return this;
}
}

namespace viva{
void Animation::_SetSurface(Surface* surface) 
{
sprite->_SetSurface(surface);
}
}

namespace viva{
void Animation::_SetIndex(uint i) 
{
sprite->_SetIndex(i);
}
}

namespace viva{
int Animation::_GetIndex() const 
{
return sprite->_GetIndex();
}
}

namespace viva{
void Animation::Destroy() 
{
sprite->Destroy();
delete this;
}
}

namespace viva{
Node* Animation::GetNode() 
{
return this;
}
}

namespace viva{
Animation* Animation::SetPixelScale(uint width, uint height)
{
sprite->SetPixelScale(width, height);
return this;
}
}

namespace viva{
Animation* Animation::SetScale2TextureSize()
{
sprite->SetScale2TextureSize();
return this;
}
}

namespace viva{
bool Animation::IsFlippedHorizontally() const
{
return sprite->IsFlippedHorizontally();
}
}

namespace viva{
Animation* Animation::SetFlipHorizontally(bool _flipHorizontally)
{
sprite->SetFlipHorizontally(_flipHorizontally);
return this;
}
}

namespace viva{
bool Animation::IsFlippedVertically() const
{
return sprite->IsFlippedVertically();
}
}

namespace viva{
Animation* Animation::SetFlipVertically(bool _flipVertically)
{
sprite->SetFlipVertically(_flipVertically);
return this;
}
}

namespace viva{
Animation* Animation::SetTextureFilter(TextureFilter _filter)
{
sprite->SetTextureFilter(_filter);
return this;
}
}

namespace viva{
TextureFilter Animation::GetTextureFilter() const
{
return sprite->GetTextureFilter();
}
}

namespace viva{
Win32Sprite::Win32Sprite(Win32Texture* tex, Win32PixelShader* _ps): texture(tex), ps(_ps)
{
}
}

namespace viva{
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
// ps
d3d.context->PSSetShader(ps->ps, 0, 0);
// vb
UINT stride = sizeof(Vertex);
UINT offset = 0;
d3d.context->IASetVertexBuffers(0, 1, &d3d.vertexBuffer, &stride, &offset);
d3d.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
// texture
d3d.context->PSSetShaderResources(0, 1, &texture->shaderResource);

if(visible)
d3d.context->DrawIndexed(6, 0, 0);
}
}

namespace viva{
void Win32Sprite::Destroy() 
{
if(!texture->IsCached())
texture->Destroy();

if (index != -1)
drawManager->Remove(this);

delete this;
}
}

namespace viva{
Texture* Win32Sprite::GetTexture() 
{
return texture;
}
}

namespace viva{
PixelShader* Win32Sprite::GetPixelShader() const 
{
return ps;
}
}

namespace viva{
Sprite* Win32Sprite::SetPixelShader(PixelShader* _ps) 
{
ps = static_cast<Win32PixelShader*>(_ps);
return this;
}
}

namespace viva{
Win32Surface::Win32Surface(ID3D11Texture2D* t, ID3D11RenderTargetView* r,ID3D11ShaderResourceView* s): tex(t), rtv(r), srv(s)
{
}
}

namespace viva{
PixelShader* Win32Surface::GetPixelShader() const 
{
return ps;
}
}

namespace viva{
void Win32Surface::SetPixelShader(PixelShader* _ps)
{
ps = (Win32PixelShader*)_ps;
}
}

namespace viva{
void Win32Surface::_DrawAll() 
{
d3d.context->ClearDepthStencilView(d3d.depthStencil,
D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//if (Core->IsAlphaEnabled())
//   Core->_GetContext()->OMSetBlendState(Core->_GetBlendState(), 0, 0xffffffff);

d3d.context->OMSetRenderTargets(1, &rtv, d3d.depthStencil);
float four0[4] = { 0, 0, 0, 0 };
d3d.context->ClearRenderTargetView(rtv, four0);

for (int i = 0; i < drawables.size(); i++)
drawables.at(i)->_Draw();
}
}

namespace viva{
void Win32Surface::_DrawSurface() 
{
d3d.context->PSSetShader(ps->ps, 0, 0);
//tex
d3d.context->PSSetShaderResources(0, 1, &srv);
//draw
d3d.context->DrawIndexed(6, 0, 0);
}
}

namespace viva{
void Win32Surface::Destroy() 
{
Clear();

tex->Release();
rtv->Release();
srv->Release();
}
}

namespace viva{
Win32Time::Win32Time()
{
LARGE_INTEGER li;
if (!QueryPerformanceFrequency(&li))
throw Error("QueryPerformanceFrequency()", "QueryPerformanceFrequency() failed");
frequency = double(li.QuadPart);
QueryPerformanceCounter(&li);
startTime = li.QuadPart;
prevFrameTime = startTime;
}
}

namespace viva{
void Win32Time::_Destroy() 
{
delete this;
}
}

namespace viva{
void Win32Time::_Activity() 
{
LARGE_INTEGER currentTime;
long long frameTickCount;
QueryPerformanceCounter(&currentTime);
frameTickCount = currentTime.QuadPart - prevFrameTime;
frameTime = double(frameTickCount) / frequency;
prevFrameTime = currentTime.QuadPart;
gameTime = double(currentTime.QuadPart - startTime) / frequency;
}
}

namespace viva{
Win32PixelShader::Win32PixelShader(ID3D11PixelShader* _ps):ps(_ps)
{
}
}

namespace viva{
void Win32PixelShader::Destroy() 
{
ps->Release();
delete this;
}
}

namespace viva{
Win32Texture::Win32Texture(const wstring& _name, ID3D11ShaderResourceView* srv, const Size& _size):Texture(_name), shaderResource(srv)
{
size = _size;
}
}

namespace viva{
void Win32Texture::Destroy() 
{
shaderResource->Release();
delete this;
}
}

namespace viva::Math {
float Deg2Rad(float deg)
{
return deg * 2 * Pi / 360;
}
}

namespace viva::Math {
float Rad2Deg(float rad)
{
return rad * 360 / 2 / Pi;
}
}

namespace viva::util {
std::string ReadFileToStringA(const std::wstring& filepath)
{
std::ifstream file(filepath);

if (!file)
throw viva::Error("ReadFileToString()", "could not open the file");

return std::string((std::istreambuf_iterator<char>(file)),
std::istreambuf_iterator<char>());
}
}

namespace viva::util {
void ReadFileToBytes(const std::wstring& filepath, vector<byte>& dst)
{
std::ifstream file(filepath, std::ios::binary);

if (!file)
throw viva::Error("ReadFileToString()", "could not open the file");

byte c;
while (!file.eof())
{
c = file.get();
dst.push_back(c);
}
dst.pop_back();
}
}

namespace viva::util {
Size ReadImageToPixels(const std::wstring& filepath, Pixel** dst)
{
std::string str(filepath.begin(), filepath.end());
int x, y, n;
const int components = 4; // components means how many elements from 'RGBA'
// you want to return, I want 4 (RGBA) even in not all 4 are present
byte* data = stbi_load(str.c_str(), &x, &y, &n, components);

if (data == nullptr)
{
std::string msg = "could not open: " + std::string(filepath.begin(), filepath.end()) + " reason: ";
msg += stbi_failure_reason();
throw Error(__FUNCTION__, msg.c_str());
}

*dst = (Pixel*)data;

return{ (float)x,(float)y };
}
}

namespace viva::util {
bool EndsWith(const wstring& s, const wstring& end)
{
if (s.length() < end.length())
return false;

return s.rfind(end) == (s.length() - end.length());
}
}

namespace viva::util {
double RandomDouble()
{
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0, 1);
return dis(gen);
}
}

namespace viva::util {
int RandomInt(int min, int max)
{
static std::random_device rd;
static std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(min, max);
return dis(gen);
}
}

namespace viva {
void intloop()
{
}
}

namespace viva {
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
}

namespace viva {
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
switch (msg)
{
case WM_SYSKEYDOWN:
{
if (wParam == VK_MENU)//ignore left alt stop
{
}
else
return DefWindowProc(hwnd, msg, wParam, lParam); // this makes ALT+F4 work
break;
}
case WM_CLOSE:
{
ShowWindow(hwnd, false);

if(wParam == 0)
PostQuitMessage((int)CloseReason::WindowClose);
else if(wParam == (int)CloseReason::EngineClose)
PostQuitMessage((int)CloseReason::EngineClose);

break;
}
case WM_COMMAND:
break;
case WM_MOUSEWHEEL:
{
if(win32mouse != nullptr)
win32mouse->SetMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));

break;
}
case WM_INPUT:
{
UINT dwSize = 48; // 48 for 64bit build
static BYTE lpb[48];

GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
lpb, &dwSize, sizeof(RAWINPUTHEADER)); // this gets relative coords

RAWINPUT* raw = (RAWINPUT*)lpb;

if (raw->header.dwType == RIM_TYPEMOUSE)
{
int xPosRelative = raw->data.mouse.lLastX;
int yPosRelative = raw->data.mouse.lLastY;

if(win32mouse != nullptr)
win32mouse->SetCursorDeltaRaw(xPosRelative, yPosRelative);
}
break;
}
default:
return DefWindowProc(hwnd, msg, wParam, lParam);
}
return 0;
}
}

namespace viva::Math {
const float Pi = 3.1415926f;}

namespace viva {
Engine* engine = nullptr;}

namespace viva {
Camera* camera = nullptr;}

namespace viva {
Creator* creator = nullptr;}

namespace viva {
DrawManager* drawManager = nullptr;}

namespace viva {
Window* window = nullptr;}

namespace viva {
ResourceManager* resourceManager = nullptr;}

namespace viva {
Input::Mouse* mouse = nullptr;}

namespace viva {
Input::Keyboard* keyboard = nullptr;}

namespace viva {
RoutineManager* routineManager = nullptr;}

namespace viva {
Time* time = nullptr;}

namespace viva {
D3D11 d3d;}

namespace viva {
Input::Win32Mouse* win32mouse = nullptr;}

