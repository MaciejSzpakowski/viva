#pragma once

namespace viva {
    namespace Input
    {
        class Win32Mouse : public Mouse
        {
        private:
            const int ARR_LBUTTON = 0;
            const int ARR_RBUTTON = 1;
            const int ARR_MBUTTON = 2;
            Point lastCursorPos;
            Array<bool> curState;
            Array<bool> prevState;
            int mouseWheel;
            Point cursorDelta;
            Point cursorDeltaRaw;
            bool useRaw;
        public:
            Win32Mouse();

            // maps MouseKey to ARR const value
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

            void Activity();

            void ResetKey(MouseKey key) override;

            void Destroy() override;
        };

        class Win32Keyboard : public Input::Keyboard
        {
        private:
            int keyNumber;
            Array<bool> curState;
            Array<bool> prevState;
            bool capslockActive;
        public:
            Win32Keyboard();

            void Activity();

            bool IsKeyDown(KeyboardKey key) const override;

            bool IsKeyPressed(KeyboardKey key) const override;

            bool IsKeyReleased(KeyboardKey key) const override;

            char GetChar(bool enableShift, bool enableCapslock) const override;

            bool IsCapslockActive() const override;

            //char GetKey(int offset) const override;

            void ResetKey(KeyboardKey key) override;

            void Destroy() override;
        };
    }
}