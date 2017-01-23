#include "viva.h"

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

    class Win32Window : public Window
    {
    private:
        RAWINPUTDEVICE Rid; //RAWINPUTDEVICE Rid[1]; // you can have more than one
        HWND handle;
        MSG msg;
        std::function<void()> worker;   // lib side worker
        std::function<void()> activity; // client size activity
    public:
        Win32Window(const std::wstring& title, const Size& size)
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

        void* GetHandle() const override
        {
            return handle;
        }

        void _Destroy() override
        {
            DestroyWindow(handle);
            UnregisterClass(L"myWindowClass", GetModuleHandle(0));
            delete this;
        }

        void SetWindowTitle(const wstring& title) override
        {
            ::SetWindowText(handle, title.c_str());
        }

        // start win32 message pump
        // gameloop: user's function that runs every frame
        // intloop: engine function that runs every frame
        void Run(const std::function<void()>& gameloop, const std::function<void()>& intloop)
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
    };
}
