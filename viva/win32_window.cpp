#ifdef _WIN32

#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    Input::Win32Mouse* win32mouse = nullptr;

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
            PostQuitMessage(0);
            break;
        }
        case WM_COMMAND:
            break;
        case WM_MOUSEWHEEL:
        {
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
                win32mouse->SetCursorDeltaRaw(xPosRelative, yPosRelative);
            }
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
	}

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
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, FALSE, 0);

		handle = CreateWindowEx(0, className, title.c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
			NULL, NULL, GetModuleHandle(0), NULL);

        USHORT HID_USAGE_PAGE_GENERIC = 1;
        USHORT HID_USAGE_GENERIC_MOUSE = 2;

        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
        Rid[0].dwFlags = RIDEV_INPUTSINK;
        Rid[0].hwndTarget = handle;
        RegisterRawInputDevices(Rid, 1, sizeof(RAWINPUTDEVICE));

		if (handle == NULL)
		{
			MessageBox(NULL, L"Window Creation Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}
	}

	void* Win32Window::GetHandle() const
	{
		return handle;
	}

    void Win32Window::SetWindowTitle(const wstring& title)
    {
        ::SetWindowText(handle, title.c_str());
    }

	void Win32Window::_Destroy()
	{
        DestroyWindow(handle);
        UnregisterClass(L"myWindowClass", GetModuleHandle(0));
		delete this;
	}

	void Win32Window::Run(const std::function<void()>& gameloop, const std::function<void()>& intloop)
	{
        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);

        win32mouse = (Input::Win32Mouse*)mouse;
        activity = gameloop;
        worker = intloop;

        while (true)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    ZeroMemory(&msg, sizeof(msg));
                    break;
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

#endif