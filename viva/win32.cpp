#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <d3dcompiler.h>
#include <Xinput.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")
//#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")