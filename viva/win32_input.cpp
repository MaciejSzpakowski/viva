#ifdef _WIN32

#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    namespace Input
    {
#pragma region MOUSE

        Win32Mouse::Win32Mouse():
            lastCursorPos({ 0,0 }),
            mouseWheel(0),
            cursorDelta({ 0,0 }),
            cursorDeltaRaw({ 0,0 }),
            useRaw(false),
            curState(3),
            prevState(3)
        {
            window->GetHandle();
            POINT p;
            ::GetCursorPos(&p);
            lastCursorPos.X = (float)p.x;
            lastCursorPos.Y = (float)p.y;
        }

        void Win32Mouse::Activity()
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
            curState[ARR_LBUTTON] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) && true;
            curState[ARR_RBUTTON] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) && true;
            curState[ARR_MBUTTON] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) && true;
        }

        void Win32Mouse::SetMouseWheel(int wheel)
        {
            mouseWheel = wheel;
        }

        void Win32Mouse::SetCursorDeltaRaw(int x, int y)
        {
            cursorDeltaRaw.X = (float)x;
            cursorDeltaRaw.Y = (float)y;
        }

        int Win32Mouse::GetWheelDelta() const
        {
            return mouseWheel;
        }

        Point Win32Mouse::GetCursorDelta() const
        {
            return useRaw ? cursorDeltaRaw : cursorDelta;
        }

        Point Win32Mouse::GetCursorClientPos() const
        {
            throw Error("Win32Mouse::GetCursorClientPos()", "Not implemented");
            return lastCursorPos;
        }

        Point Win32Mouse::GetCursorPos() const
        {
            return lastCursorPos;
        }

        void Win32Mouse::ShowCursor(bool visible)
        {
            ::ShowCursor(visible);
        }

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

        bool Win32Mouse::IsButtonDown(MouseKey key) const
        {
            int mappedKey = GetMappedKey(key);
            
            return curState.at(mappedKey);
        }

        bool Win32Mouse::IsButtonPressed(MouseKey key) const
        {
            int mappedKey = GetMappedKey(key);

            return curState.at(mappedKey) && !prevState.at(mappedKey);
        }

        bool Win32Mouse::IsButtonReleased(MouseKey key) const
        {
            int mappedKey = GetMappedKey(key);

            return !curState.at(mappedKey) && prevState.at(mappedKey);
        }

        void Win32Mouse::ResetKey(MouseKey key)
        {
            int mappedKey = GetMappedKey(key);
            curState[mappedKey] = false;
            prevState[mappedKey] = false;
        }

        void Win32Mouse::Destroy()
        {
            delete this;
        }

#pragma endregion

#pragma region KEYBOARD

        Win32Keyboard::Win32Keyboard():
            keyNumber(256),
            curState(keyNumber),
            prevState(keyNumber),
            capslockActive(false)
        {
        }

        void Win32Keyboard::Activity()
        {
            capslockActive = GetKeyState((int)KeyboardKey::CapsLock) & 1;

            //swap states
            curState.swap(prevState);

            // get button states
            for(int i=0;i<keyNumber;i++)
                curState[i] = (GetAsyncKeyState(i) & 0x8000) && true;
        }

        bool Win32Keyboard::IsKeyDown(KeyboardKey key) const
        {
            return curState.at((int)key);
        }

        bool Win32Keyboard::IsKeyPressed(KeyboardKey key) const
        {
            return curState.at((int)key) && !prevState.at((int)key);
        }

        bool Win32Keyboard::IsKeyReleased(KeyboardKey key) const
        {
            return curState.at((int)key) && !prevState.at((int)key);
        }

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

            for (int i = 0; i < sizeof(input); i++)
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

        bool Win32Keyboard::IsCapslockActive() const
        {
            return capslockActive;
        }

        /*char Win32Keyboard::GetKey(int offset) const
        {
        }*/

        void Win32Keyboard::ResetKey(KeyboardKey key)
        {
            curState[(int)key] = false;
            prevState[(int)key] = false;
        }

        void Win32Keyboard::Destroy()
        {
            delete this;
        }

#pragma endregion
    }
}

#endif