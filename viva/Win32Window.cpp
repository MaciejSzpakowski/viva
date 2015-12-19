#include "Win32.h"

namespace viva
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			break;
		case WM_MOUSEWHEEL:
			//Input->zMouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	Win32Window::Win32Window(LPCWSTR title, int width, int heigth)
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
			MessageBox(NULL, L"Window Registration Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}

		RECT rect = { 0, 0, width, heigth };
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, FALSE, 0);

		handle = CreateWindowEx(0, className, L"", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
			NULL, NULL, GetModuleHandle(0), NULL);

		if (handle == NULL)
		{
			MessageBox(NULL, L"Window Creation Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}
	}

	void* Win32Window::GetNativeHandle()
	{
		return handle;
	}

	void Win32Window::Destroy()
	{
		delete this;
	}

	void Win32Window::Run(std::function<void()>& gameloop, std::function<void()>& intloop)
	{
		ShowWindow(handle, SW_SHOW);
		UpdateWindow(handle);
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				intloop();
				gameloop();
			}
		}
		UnregisterClass(L"myWindowClass", GetModuleHandle(0));
		//return (int)msg.wParam;
	}
}