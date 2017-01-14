#include "viva.h"

namespace viva 
{
    namespace Input
    {
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
            Win32Mouse() 
                : lastCursorPos({ 0,0 }),
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

            // maps MouseKey to ARR const value
            int GetMappedKey(MouseKey key) const
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

            void SetMouseWheel(int wheel)
            {
                mouseWheel = wheel;
            }

            void SetCursorDeltaRaw(int x, int y)
            {
                cursorDeltaRaw.X = (float)x;
                cursorDeltaRaw.Y = (float)y;
            }

            int GetWheelDelta() const override
            {
                return mouseWheel;
            }

            Point GetCursorDelta() const override
            {
                return useRaw ? cursorDeltaRaw : cursorDelta;
            }

            Point GetCursorClientPos() const override
            {
                throw Error("Win32Mouse::GetCursorClientPos()", "Not implemented");
                return lastCursorPos;
            }

            Point GetCursorPos() const override
            {
                return lastCursorPos;
            }

            void ShowCursor(bool visible)
            {
                ::ShowCursor(visible);
            }

            bool IsButtonDown(MouseKey key) const override
            {
                int mappedKey = GetMappedKey(key);

                return curState.at(mappedKey);
            }

            bool IsButtonPressed(MouseKey key) const
            {
                int mappedKey = GetMappedKey(key);

                return curState.at(mappedKey) && !prevState.at(mappedKey);
            }

            bool IsButtonReleased(MouseKey key) const
            {
                int mappedKey = GetMappedKey(key);

                return !curState.at(mappedKey) && prevState.at(mappedKey);
            }

            void Activity()
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

            void ResetKey(MouseKey key) override
            {
                int mappedKey = GetMappedKey(key);
                curState[mappedKey] = false;
                prevState[mappedKey] = false;
            }

            void Destroy() override
            {
                delete this;
            }
        };

        class Win32Keyboard : public Input::Keyboard
        {
        private:
            int keyNumber;
            vector<bool> curState;
            vector<bool> prevState;
            bool capslockActive;
        public:
            Win32Keyboard() 
                : keyNumber(256),
                curState(keyNumber),
                prevState(keyNumber),
                capslockActive(false)
            {
            }

            void Activity()
            {
                capslockActive = GetKeyState((int)KeyboardKey::CapsLock) & 1;

                //swap states
                curState.swap(prevState);

                // get button states
                for (int i = 0; i<keyNumber; i++)
                    curState[i] = (GetAsyncKeyState(i) & 0x8000) && true;
            }

            bool IsKeyDown(KeyboardKey key) const override
            {
                return curState.at((int)key);
            }

            bool IsKeyPressed(KeyboardKey key) const override
            {
                return curState.at((int)key) && !prevState.at((int)key);
            }

            bool IsKeyReleased(KeyboardKey key) const override
            {
                return curState.at((int)key) && !prevState.at((int)key);
            }

            char GetChar(bool enableShift, bool enableCapslock) const override
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

            bool IsCapslockActive() const override
            {
                return capslockActive;
            }

            /*char Win32Keyboard::GetKey(int offset) const override
            {
            }*/

            void ResetKey(KeyboardKey key) override
            {
                curState[(int)key] = false;
                prevState[(int)key] = false;
            }

            void Destroy() override
            {
                delete this;
            }
        };
    }
}
