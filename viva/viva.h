#pragma once
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "stb_image.h"
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>
#include <map>
#include <array>
#include "viva.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <d3dcompiler.h>
#include <Xinput.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")
#pragma comment(lib, "Xinput9_1_0.lib")
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"
#include "viva.h"

namespace viva {
class Drawable;}

namespace viva {
union Vector;}

namespace viva {
struct Point;}

namespace viva {
class Transform;}

namespace viva {
class Node;}

namespace viva {
struct Color;}

namespace viva {
class Colorable;}

namespace viva {
struct FontMetrics;}

namespace viva {
class Text;}

namespace viva {
class Core;}

namespace viva {
struct Size;}

namespace viva {
class Engine;}

namespace viva {
class Win32Engine;}

namespace viva {
union Matrix;}

namespace viva {
class Camera;}

namespace viva {
struct Pixel;}

namespace viva {
class Creator;}

namespace viva {
struct D3D11;}

namespace viva {
class DrawManager;}

namespace viva {
class Error;}

namespace viva {
struct Rect;}

namespace viva {
class Font;}

namespace viva::Input {
class Mouse;}

namespace viva {
class Resource;}

namespace viva {
class Texture;}

namespace viva::Input {
class Keyboard;}

namespace viva::Input {
class Gamepad;}

namespace viva {
class Polygon;}

namespace viva {
class Sprite;}

namespace viva {
class ResourceManager;}

namespace viva {
class Win32Creator;}

namespace viva {
struct IRoutine;}

namespace viva {
struct Routine;}

namespace viva {
class RoutineManager;}

namespace viva {
class Surface;}

namespace viva {
class Time;}

namespace viva {
class Window;}

namespace viva {
class Win32Window;}

namespace viva {
struct Vertex;}

namespace viva::Input {
class Win32Mouse;}

namespace viva {
class PixelShader;}

namespace viva {
struct Win32PixelShader;}

namespace viva::Input {
class Win32Keyboard;}

namespace viva {
class Win32Polygon;}

namespace viva {
class Win32Sprite;}

namespace viva {
class Win32Surface;}

namespace viva {
class Win32Time;}

namespace viva {
class Win32Texture;}

namespace viva{
    typedef unsigned char byte;}

namespace viva{
    using std::wstring;}

namespace viva{
    using std::wstring;}

namespace viva{
    using std::vector;}

namespace viva{
    typedef unsigned char byte;}

namespace viva{
    typedef unsigned int uint;}


namespace viva::Input
{
enum class MouseKey : int
{Left = 0x01,Right = 0x02,Middle = 0x04};
}

namespace viva::Input
{
enum class KeyboardKey : int
{BackSpace = 0x08,Tab = 0x09,Enter = 0x0D,Shift = 0x10,Control = 0x11,Alt = 0x12,PauseBreak = 0x13,CapsLock = 0x14,Escape = 0x1B,Space = 0x20,PageUp = 0x21,PageDown = 0x22,End = 0x23,Home = 0x24,Left = 0x25,Up = 0x26,Right = 0x27,Down = 0x28,PrintScreen = 0x2C,Insert = 0x2D,Delete = 0x2E,Key0 = '0',Key1 = '1',Key2 = '2',Key3 = '3',Key4 = '4',Key5 = '5',Key6 = '6',Key7 = '7',Key8 = '8',Key9 = '9',KeyA = 'A',KeyB = 'B',KeyC = 'C',KeyD = 'D',KeyE = 'E',KeyF = 'F',KeyG = 'G',KeyH = 'H',KeyI = 'I',KeyJ = 'J',KeyK = 'K',KeyL = 'L',KeyM = 'M',KeyN = 'N',KeyO = 'O',KeyP = 'P',KeyQ = 'Q',KeyR = 'R',KeyS = 'S',KeyT = 'T',KeyU = 'U',KeyV = 'V',KeyW = 'W',KeyX = 'X',KeyY = 'Y',KeyZ = 'Z',WinLeft = 0x5B,WinRight = 0x5C,Menu = 0x5D,RightMenu = 0x5D,Num0 = 0x60,Num1 = 0x61,Num2 = 0x62,Num3 = 0x63,Num4 = 0x64,Num5 = 0x65,Num6 = 0x66,Num7 = 0x67,Num8 = 0x68,Num9 = 0x69,NumMultiply = 0x6A,NumPlus = 0x6B,NumMinus = 0x6D,NumDot = 0x6E,NumDivide = 0x6F,F1 = 0x70,F2 = 0x71,F3 = 0x72,F4 = 0x73,F5 = 0x74,F6 = 0x75,F7 = 0x76,F8 = 0x77,F9 = 0x78,F10 = 0x79,F11 = 0x7A,F12 = 0x7B,F13 = 0x7C,F14 = 0x7D,F15 = 0x7E,F16 = 0x7F,F17 = 0x80,F18 = 0x81,F19 = 0x82,F20 = 0x83,F21 = 0x84,F22 = 0x85,F23 = 0x86,F24 = 0x87,Numlock = 0x90,ScrollLock = 0x91,LeftShift = 0xA0,RightShift = 0xA1,LeftControl = 0xA2,RightControl = 0xA3,LeftAlt = 0xA4,RightAlt = 0xA5,Semicolon = 0xBA,Plus = 0xBB,Equals = 0xBB,Comma = 0xBC,Minus = 0xBD,Period = 0xBE,Slash = 0xBF,Tilde = 0xC0,LeftBracket = 0xDB,BackSlash = 0xDC,RightBracket = 0xDD,Apostrophe = 0xDE,};
}

namespace viva::Input
{
enum class GamepadKey : int
{Up = 1,Down = 2,Left = 4,Right = 8,Start = 16,Back = 32,LeftStick = 64,RightStick = 128,LB = 256,RB = 512,_1024 = 1024,_2048 = 2048,A = 4096,B = 8192,X = 16384,Y = 32768,};
}

namespace viva
{
enum class TransformMode
{World, Screen};
}

namespace viva
{
enum class ResourceType
{Texture};
}

namespace viva
{
enum class TextureFilter
{POINT, LINEAR};
}

namespace viva {
class Drawable
{
protected:
Surface* parent;
uint index;
public:
Drawable();

virtual void _Draw() = 0;
Surface* GetSurface() const;

void _SetSurface(Surface* surface);

void _SetIndex(uint i);

int _GetIndex() const;

virtual Node* GetNode() = 0;
};}

namespace viva {
union Vector
{
__m128 m;
struct {float x; float y; float z; float w; } f;
DirectX::XMVECTOR v;
Vector();

Vector(float x, float y, float z, float w);

static Vector Zero();

static Vector One();

float X() const;

float Y() const;

float Z() const;

float W() const;

void X(float x);

void Y(float y);

void Z(float z);

void W(float w);

void Add(const Vector& rhs);

Vector operator+(const Vector& rhs);

};}

namespace viva {
struct Point
{
float X, Y;
Point();

Point(float x, float y);

};}

namespace viva {
class Transform
{
private:
Transform* parent;
vector<Transform*> children;
TransformMode mode;
Vector origin;
Vector position;
float rotation;
Point scale;
float size;
Vector velocity;
float angularVelocity;
Point scaleVelocity;
float sizeVelocity;
Vector acceleration;
float angularAcceleration;
Point scaleAcceleration;
float sizeAcceleration;
public:
Transform();

Transform* SetCoordMode(TransformMode m);

TransformMode GetMode() const;

void GetWorld(Matrix* dst);

void GetWorldViewProj(Matrix* dst);

void GetWorldScreen(Matrix* dst);

Transform* SetOrigin(float x, float y);

Transform* SetOrigin(const Vector& v);

const Vector& GetOrigin() const;

Transform* SetPosition(float x, float y, float z);

Transform* SetPosition(float x, float y);

Transform* SetPositionX(float x);

Transform* SetPositionY(float y);

Transform* SetPositionZ(float z);

Transform* SetPosition(const Vector& v);

const Vector& GetPosition() const;

Transform* Translate(float x, float y, float z);

Transform* Translate(const Vector& v);

Transform* SetRotation(float radians);

float GetRotation() const;

Transform* Rotate(float angle);

Transform* SetScale(float width, float height);

Transform* SetScale(const Point& s);

Transform* SetScaleX(float x);

Transform* SetScaleY(float y);

const Point& GetScale() const;

Transform* Scale(const Point& s);

Transform* SetSize(float s);

float GetSize() const;

Transform* Grow(float factor);

Transform* Shrink(float factor);

};}

namespace viva {
class Node
{
protected:
Transform transform;
public:
Node();

virtual void Destroy() = 0;
Transform* T();

Transform* GetTransform();

};}

namespace viva {
struct Color
{
float R, G, B, A;
Color();

Color(float _r, float _g, float _b, float _a);

Color(const Pixel& pixel);

};}

namespace viva {
class Colorable
{
protected:
Color color;
public:
const Color& GetColor() const;

void SetColor(float r, float g, float b, float a);

void SetColor(const Color& c);

void SetColorR(float r);

void SetColorG(float g);

void SetColorB(float b);

void SetColorA(float a);

};}

namespace viva {
struct FontMetrics
{
};}

namespace viva {
class Text : public Drawable, public Node, public Colorable
{
private:
FontMetrics metrics;
wstring text;
TextureFilter texFilter;
Sprite* sprite;
public:
Text(Font* font);

void Destroy() override;

void _Draw() override;

};}

namespace viva {
class Core
{
public:
Core(const wstring& title, const Size& size, const wstring& path);

~Core();

};}

namespace viva {
struct Size
{
float Width;
float Height;
Size();

Size(float _width, float _height);

};}

namespace viva {
class Engine
{
protected:
wstring defaultPath;
Color backgroundColor;
Size clientSize;
virtual void Activity() = 0;
public:
Engine(const std::wstring& path, const Size& size);

virtual void _Init() = 0;
virtual void _Destroy() = 0;
virtual void Run(const std::function<void()>& gameloop = []() {}) = 0;
const Color& GetBackgroundColor() const;

void SetBackgroundColor(const Color& color);

const std::wstring& GetDefaultPath() const;

const Size& GetClientSize() const;

void SetDefaultPath(const std::wstring& path);

virtual void Exit() = 0;
virtual void OpenConsole() = 0;
virtual void CloseConsole() = 0;
};}

namespace viva {
class Win32Engine : public Engine
{
private:
void Activity() override;

public:
Win32Engine(const wstring& title, const Size& size, const wstring& path);

void _Destroy() override;

void _Init() override;

void OpenConsole() override;

void CloseConsole() override;

void Exit() override;

void Run(const std::function<void()>& gameloop) override;

ID3D11Buffer* CreateConstantBuffer(UINT size);

};}

namespace viva {
union Matrix
{
struct {__m128 r0; __m128 r1; __m128 r2; __m128 r3; } f;
DirectX::XMMATRIX m;
Matrix();

Matrix(const DirectX::XMMATRIX& _m);

Matrix(DirectX::XMMATRIX&& _m);

static void LookAtLH(const Vector& position, const Vector& target, const Vector& up, Matrix* result);

static void  PerspectiveFovLH(float fovAngle, float aspectRatio, float nearPlane, float farPlane, Matrix* result);

static void Translation(const Vector& position, Matrix* result);

static void Scaling(const Point& scale, Matrix* result);

static void Multiply(const Matrix& m1, const Matrix& m2, Matrix* result);

static void Multiply(const Matrix& m, const Vector& v, Vector* result);

static void Identity(Matrix* result);

static void Rotation(float angle, Matrix* result);

void Transpose();

};}

namespace viva {
class Camera
{
private:
Transform transform;
Matrix view;
Matrix proj;
Matrix viewProj;
Vector up;
float nearPlane;
float farPlane;
float fovAngle;
float aspectRatio;
public:
Camera(const Size& size);

Size GetFrustumSize(float z);

const Matrix& GetView() const;

const Matrix& GetProj() const;

const Matrix& GetViewProj() const;

void _CalcViewProj();

Point WorldToScreen(const Vector& pos) const;

Vector ScreenToWorld(const Point& pos, float z) const;

void _Destroy();

};}

namespace viva {
struct Pixel
{
byte R, G, B, A;
Pixel();

Pixel(byte r, byte g, byte b, byte a);

Pixel(const Color& color);

};}

namespace viva {
class Creator
{
public:
virtual PixelShader* CreatePixelShader(const wstring& filepath) = 0;
virtual PixelShader* CreatePixelShader(const std::string& str) = 0;
Texture* CreateTexture(const wstring& filepath);

virtual Texture* CreateTexture(const Pixel* pixels, const Size& size, const wstring& name) = 0;
Texture* CreateTexture(const Pixel* pixels, const Size& size);

virtual Sprite* CreateSprite(const wstring& filepath) = 0;
virtual Sprite* CreateSprite(Texture* texture) = 0;
virtual Polygon* CreatePolygon(const vector<Point>& points) = 0;
virtual Surface* CreateSurface() = 0;
virtual void _Destroy() = 0;
};}

namespace viva {
struct D3D11
{
ID3D11BlendState* blendState;
IDXGISwapChain* swapChain;
ID3D11RenderTargetView* backBuffer;
ID3D11Device* device;
ID3D11DeviceContext* context;
ID3D11InputLayout* layout;
ID3D11DepthStencilView* depthStencil;
ID3D11Texture2D* depthStencilBuffer;
ID3D11RasterizerState* rsSolid;
ID3D11RasterizerState* rsWire;
ID3D11VertexShader* defaultVS;
Win32PixelShader* defaultPS;
Win32PixelShader* defaultPost;
ID3D11Buffer* constantBufferVS;
ID3D11Buffer* constantBufferPS;
ID3D11Buffer* constantBufferUV;
ID3D11Buffer* constantBufferPSExtra;
ID3D11Buffer* indexBuffer;
ID3D11Buffer* vertexBuffer;
ID3D11SamplerState* samplerPoint;
ID3D11SamplerState* samplerLinear;
};}

namespace viva {
class DrawManager
{
private:
Sprite* defaultFont;
Surface* defaultSurface;
Texture* whitePixel;
public:
DrawManager();

void _Destroy();

void _DrawNodes();

void _DrawSurfaces();

Polygon* AddPolygon(const vector<Point>& points, Surface* surface);

Polygon* AddPolygon(const vector<Point>& points);

Sprite* AddSprite(Texture* t, Surface* surface);

Sprite* AddSprite(Texture* t);

Sprite* AddRectangle(Surface* surface);

Sprite* AddRectangle();

Sprite* AddSprite(const wstring& filepath, Surface* surface);

Sprite* AddSprite(const wstring& filepath);

void Remove(Drawable* drawable);

void Add(Drawable* drawable, Surface* surface);

void Add(Drawable* drawable);

Sprite* GetDefaultFont() const;

};}

namespace viva {
class Error : public std::runtime_error
{
public:
const char* function;
Error(const char* fun, const char* msg);

Error(const char* fun, wstring msg);

};}

namespace viva {
struct Rect
{
float left, top, right, bottom;
Rect();

Rect(float _left, float _top, float _right, float _bottom);

};}

namespace viva {
class Font
{
private:
Texture* texture;
vector<Rect> charsUv;
public:
Font::Font(Texture* tex, const Size& letterSize, int charsPerRow);

void Font::Destroy();

};}

namespace viva::Input {
class Mouse
{
protected:
bool cursorVisibility;
bool rawCursor;
public:
virtual int GetWheelDelta() const = 0;
virtual Point GetCursorDelta() const = 0;
virtual Point GetCursorClientPos() const = 0;
virtual Point GetCursorPos() const = 0;
void UseRawInput(bool val);

virtual void ShowCursor(bool visible) = 0;
bool IsCursorVisible() const;

virtual bool IsButtonDown(MouseKey key) const = 0;
virtual bool IsButtonPressed(MouseKey key) const = 0;
virtual bool IsButtonReleased(MouseKey key) const = 0;
virtual void ResetKey(MouseKey key) = 0;
virtual void _Destroy() = 0;
virtual void _Activity() = 0;
};}

namespace viva {
class Resource
{
protected:
wstring name;
bool cached;
ResourceType type;
public:
Resource(const wstring& _name, ResourceType t);

bool IsCached() const;

ResourceType GetType() const;

void _SetCached(bool _cached);

const wstring& GetName() const;

virtual void Destroy() = 0;
};}

namespace viva {
class Texture : public Resource
{
protected:
Size size;
public:
Texture(const wstring& _name);

Size GetSize() const;

};}

namespace viva::Input {
class Keyboard
{
public:
virtual bool IsKeyDown(KeyboardKey key) const = 0;
virtual bool IsKeyPressed(KeyboardKey key) const = 0;
virtual bool IsKeyReleased(KeyboardKey key) const = 0;
virtual char GetChar(bool enableShift = true, bool enableCapslock = true) const = 0;
virtual bool IsCapslockActive() const = 0;
virtual void ResetKey(KeyboardKey key) = 0;
virtual void _Destroy() = 0;
virtual void _Activity() = 0;
};}

namespace viva::Input {
class Gamepad
{
};}

namespace viva {
class Polygon : public Node, public Drawable, public Colorable
{
protected:
float span;
uint vertexCount;
public:
Polygon(int count);

Node* GetNode() override;

virtual PixelShader* GetPixelShader() const = 0;
virtual void SetPixelShader(PixelShader* ps) = 0;
int GetVertexCount() const;

};}

namespace viva {
class Sprite : public Node, public Drawable, public Colorable
{
protected:
TextureFilter filter;
Rect uv;
bool flipHorizontally;
bool flipVertically;
public:
Sprite();

Sprite* SetFilterType(TextureFilter _filter);

TextureFilter GetFilterType() const;

Sprite* SetPixelScale(const viva::Size& _size);

Sprite* SetScale2TextureSize();

bool IsFlippedHorizontally() const;

Sprite* SetFlipHorizontally(bool _flipHorizontally);

bool IsFlippedVertically() const;

Sprite* SetFlipVertically(bool _flipVertically);

Node* GetNode() override;

const Rect& GetUV() const;

virtual PixelShader* GetPixelShader() const = 0;
virtual Sprite* SetPixelShader(PixelShader* _ps) = 0;
Sprite* SetUV(const Rect& _uv);

virtual Texture* GetTexture() = 0;
};}

namespace viva {
class ResourceManager
{
private:
std::map<wstring, Resource*> resources;
public:
ResourceManager();

void AddResource(Resource* res);

Resource* GetResource(const wstring& name) const;

Texture* GetTexture(const wstring& name) const;

void RemoveResource(const wstring& name);

void RemoveAll();

void _Destroy();

};}

namespace viva {
class Win32Creator : public Creator
{
public:
Polygon* CreatePolygon(const vector<Point>& points);

Surface* CreateSurface() override;

PixelShader* CreatePixelShader(const wstring& filepath) override;

PixelShader* CreatePixelShader(const std::string& str) override;

ID3D11ShaderResourceView* SrvFromPixels(const Pixel* pixels, const Size& _size);

Sprite* CreateSprite(Texture* texture);

Sprite* CreateSprite(const wstring& filepath);

Texture* CreateTexture(const Pixel* pixels, const Size& size, const wstring& name) override;

void _Destroy() override;

};}

namespace viva {
struct IRoutine
{
virtual void Destroy() = 0;
virtual void Pause() = 0;
virtual void Resume() = 0;
virtual const wstring& GetName() = 0;
};}

namespace viva {
struct Routine : public IRoutine
{
double tick;
double lifeTime;
double delay;
double startTime;
std::function<int()> Activity;
wstring Name;
double lastPulse;
bool remove;
bool pause;
Routine(std::function<int()> activity, wstring name);

void Destroy() override;

void Pause() override;

void Resume() override;

const wstring& GetName() override;

};}

namespace viva {
class RoutineManager
{
private:
vector<Routine*> routines;
std::map<wstring, vector<std::function<void()>>> handlers;
public:
void _Activity();

IRoutine* AddRoutine(std::function<int()> func, const wstring& name, double delay, double lifeTime, double tick);

IRoutine* FindRoutine(wstring name);

void Trigger(wstring _event);

void AddHandler(wstring _event, std::function<void()> handler);

void ClearHandlers(wstring _event);

void ClearHandlers();

void ClearRoutines();

void _Destroy();

};}

namespace viva {
class Surface
{
protected:
vector<Drawable*> drawables;
public:
Surface();

virtual void _DrawAll() = 0;
virtual void _DrawSurface() = 0;
virtual PixelShader* GetPixelShader() const = 0;
virtual void SetPixelShader(PixelShader* ps) = 0;
void Add(Drawable* d);

void RemoveAll();

void Remove(Drawable* d);

void Clear();

virtual void Destroy() = 0;
};}

namespace viva {
class Time
{
protected:
double gameTime;
double frameTime;
public:
Time();

double GetGameTime();

double GetFrameTime() const;

virtual void _Activity() = 0;
double GetFps() const;

virtual void _Destroy() = 0;
};}

namespace viva {
class Window
{
public:
Window();

virtual void _Destroy() = 0;
virtual void SetWindowTitle(const wstring& title) = 0;
virtual void* GetHandle() const = 0;
};}

namespace viva {
class Win32Window : public Window
{
private:
RAWINPUTDEVICE Rid;
HWND handle;
MSG msg;
std::function<void()> worker;
std::function<void()> activity;
public:
Win32Window(const std::wstring& title, const Size& size);

void* GetHandle() const override;

void _Destroy() override;

void SetWindowTitle(const wstring& title) override;

void Run(const std::function<void()>& gameloop, const std::function<void()>& intloop);

};}

namespace viva {
struct Vertex
{
float X, Y, Z;
float R, G, B;
float U, V;
Vertex();

Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v);

};}

namespace viva::Input {
class Win32Mouse : public Mouse
{
private:
const int ARR_LBUTTON = 0;
const int ARR_RBUTTON = 1;
const int ARR_MBUTTON = 2;
Point lastCursorPos;
vector<bool> curState;
vector<bool> prevState;
int mouseWheel;
Point cursorDelta;
Point cursorDeltaRaw;
bool useRaw;
public:
Win32Mouse();

int GetMappedKey(MouseKey key) const;

void SetMouseWheel(int wheel);

void SetCursorDeltaRaw(int x, int y);

int GetWheelDelta() const override;

Point GetCursorDelta() const override;

Point GetCursorClientPos() const override;

Point GetCursorPos() const override;

void ShowCursor(bool visible);

bool IsButtonDown(MouseKey key) const override;

bool IsButtonPressed(MouseKey key) const;

bool IsButtonReleased(MouseKey key) const;

void _Activity() override;

void ResetKey(MouseKey key) override;

void _Destroy() override;

};}

namespace viva {
class PixelShader
{
public:
virtual void Destroy() = 0;
};}

namespace viva {
struct Win32PixelShader : public PixelShader
{
ID3D11PixelShader* ps;
Win32PixelShader();

Win32PixelShader(ID3D11PixelShader* _ps);

void Destroy() override;

};}

namespace viva::Input {
class Win32Keyboard : public Input::Keyboard
{
private:
int keyNumber;
vector<bool> curState;
vector<bool> prevState;
bool capslockActive;
public:
Win32Keyboard();

void _Activity() override;

bool IsKeyDown(KeyboardKey key) const override;

bool IsKeyPressed(KeyboardKey key) const override;

bool IsKeyReleased(KeyboardKey key) const override;

char GetChar(bool enableShift, bool enableCapslock) const override;

bool IsCapslockActive() const override;

void ResetKey(KeyboardKey key) override;

void _Destroy() override;

};}

namespace viva {
class Win32Polygon : public Polygon
{
private:
ID3D11Buffer* vertexBuffer;
Win32PixelShader* ps;
public:
Win32Polygon(ID3D11Buffer* _vertexBuffer, int count);

void Destroy() override;

PixelShader* GetPixelShader() const override;

void SetPixelShader(PixelShader* _ps);

void _Draw() override;

};}

namespace viva {
class Win32Sprite : public Sprite
{
private:
Win32Texture* texture;
Win32PixelShader* ps;
public:
Win32Sprite(Win32Texture* tex, Win32PixelShader* _ps);

void _Draw() override;

void Destroy() override;

Texture* GetTexture() override;

PixelShader* GetPixelShader() const override;

Sprite* SetPixelShader(PixelShader* _ps) override;

};}

namespace viva {
class Win32Surface : public Surface
{
private:
ID3D11Texture2D* tex;
ID3D11RenderTargetView* rtv;
ID3D11ShaderResourceView* srv;
Win32PixelShader* ps;
public:
Win32Surface(ID3D11Texture2D* t, ID3D11RenderTargetView* r,ID3D11ShaderResourceView* s);

PixelShader* GetPixelShader() const override;

void SetPixelShader(PixelShader* _ps);

void _DrawAll() override;

void _DrawSurface() override;

void Destroy() override;

};}

namespace viva {
class Win32Time : public Time
{
private:
double frequency;
long long startTime;
long long prevFrameTime;
public:
Win32Time();

void _Destroy() override;

void _Activity() override;

};}

namespace viva {
class Win32Texture : public Texture
{
public:
ID3D11ShaderResourceView* shaderResource;
Win32Texture(const wstring& _name, ID3D11ShaderResourceView* srv, const Size& _size);

void Destroy() override;

};}

namespace viva::Math {
float Deg2Rad(float deg);}

namespace viva::Math {
float Rad2Deg(float rad);}

namespace viva::util {
std::string ReadFileToStringA(const std::wstring& filepath);}

namespace viva::util {
void ReadFileToBytes(const std::wstring& filepath, vector<byte>& dst);}

namespace viva::util {
Size ReadImageToPixels(const std::wstring& filepath, Pixel** dst);}

namespace viva::util {
bool EndsWith(const wstring& s, const wstring& end);}

namespace viva {
void intloop();}

namespace viva {
void Checkhr(HRESULT hr, const char* function);}

namespace viva {
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);}

namespace viva::Math {
    extern const float Pi ;}

namespace viva {
    extern Engine* engine ;}

namespace viva {
    extern Camera* camera ;}

namespace viva {
    extern Creator* creator ;}

namespace viva {
    extern DrawManager* drawManager ;}

namespace viva {
    extern Window* window ;}

namespace viva {
    extern ResourceManager* resourceManager ;}

namespace viva {
    extern Input::Mouse* mouse ;}

namespace viva {
    extern Input::Keyboard* keyboard ;}

namespace viva {
    extern RoutineManager* routineManager ;}

namespace viva {
    extern Time* time ;}

namespace viva {
    extern D3D11 d3d;}

namespace viva {
    extern Input::Win32Mouse* win32mouse ;}

