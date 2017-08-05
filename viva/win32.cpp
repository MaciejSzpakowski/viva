#define WIN32_LEAN_AND_MEAN
//WinSock2.h include must be before windows.h
#include <Ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <d3dcompiler.h>
#include <Xinput.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")
//#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")