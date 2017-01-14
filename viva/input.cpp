#include "viva.h"

namespace viva 
{
    namespace Input 
    {
        class Mouse
        {
        protected:
            bool cursorVisibility;
            bool rawCursor;
        public:
            // Get difference between mouse wheel positions from frame to frame.
            virtual int GetWheelDelta() const = 0;

            // Get difference between cursor positions from frame to frame.
            virtual Point GetCursorDelta() const = 0;

            // Get cursor position in client coordinates (in pixels from top left corner).
            virtual Point GetCursorClientPos() const = 0;

            // Get cursor position in screen coordinates (in pixels from top left corner of the screen).
            virtual Point GetCursorPos() const = 0;

            // Should cursor delta be read from os or from harware directly.
            // val: yes or no ?
            void UseRawInput(bool val)
            {
                rawCursor = val;
            }

            // Show/hide cursor.
            // visible: show or hide
            virtual void ShowCursor(bool visible) = 0;

            // Is cursor visible (returns state set by ShowCursor()).
            bool IsCursorVisible() const
            {
                return cursorVisibility;
            }

            // Is key down in this frame.
            // key: key to check
            virtual bool IsButtonDown(MouseKey key) const = 0;

            // Is key down in this frame but was up in previous.
            // key: key to check
            virtual bool IsButtonPressed(MouseKey key) const = 0;

            // Is key up in this frame but was down in previous.
            // key: key to check
            virtual bool IsButtonReleased(MouseKey key) const = 0;

            // Sets key state to up.
            virtual void ResetKey(MouseKey key) = 0;

            virtual void Destroy() = 0;
        };

        class Keyboard
        {
        protected:
        public:
            // Is key down in this frame.
            // key: key to check
            virtual bool IsKeyDown(KeyboardKey key) const = 0;

            // Is key down in this frame but was up in previous.
            // key: key to check
            virtual bool IsKeyPressed(KeyboardKey key) const = 0;

            // Is key up in this frame but was down in previous.
            // key: key to check
            virtual bool IsKeyReleased(KeyboardKey key) const = 0;

            // Returns key typed including all ASCII chars between 32 and 127 and \n \t \b
            // If not applicable char was typed, the function returns 0.
            // enableShift: should I include shift for capitalization
            // enableCapslock: should I enable capslock for capitalization
            virtual char GetChar(bool enableShift = true, bool enableCapslock = true) const = 0;

            //Is capslock active.
            virtual bool IsCapslockActive() const = 0;

            // 
            //virtual char GetKey(int offset) const = 0;

            // Sets key state to up.
            virtual void ResetKey(KeyboardKey key) = 0;

            // Destroys keyboard object.
            virtual void Destroy() = 0;
        };

        class Gamepad
        {
            //how many gamepads listen to
            //keeps this at minimum for efficiency
            //max count is XUSER_MAX_COUNT (currently 4)
            //virtual void SetGamepadsCount(UINT count) { acceptGamepads = count; }
            //virtual UINT GetGamepadsCount() const { return acceptGamepads; }
            //virtual bool IsAnyButtonDown(UINT gamepad) const;
            //virtual bool IsButtonDown(UINT gamepad, Buttons button) const;
            //virtual bool IsButtonPressed(UINT gamepad, Buttons button) const;
            //virtual bool IsButtonReleased(UINT gamepad, Buttons button) const;
            //virtual BYTE GetLeftTrigger(UINT gamepad) const;
            //virtual BYTE GetRightTrigger(UINT gamepad) const;
            //virtual SHORT GetLeftStickX(UINT gamepad) const;
            //virtual SHORT GetLeftStickY(UINT gamepad) const;
            //virtual SHORT GetRightStickX(UINT gamepad) const;
            //virtual SHORT GetRightStickY(UINT gamepad) const;
            //virtual BYTE GetLeftTriggerDelta(UINT gamepad) const;
            //virtual BYTE GetRightTriggerDelta(UINT gamepad) const;
            //virtual SHORT GetLeftStickXDelta(UINT gamepad) const;
            //virtual SHORT GetLeftStickYDelta(UINT gamepad) const;
            //virtual SHORT GetRightStickXDelta(UINT gamepad) const;
            //virtual SHORT GetRightStickYDelta(UINT gamepad) const;
            //virtual void SetMotorSpeed(UINT gamepad, USHORT speedLeft, USHORT speedRight);

            ////technically: was gamepad connected during last read
            ////generally: is that gamepad connected
            //virtual bool IsGamepadActive(UINT gamepad) const;

            ////was a new gamepad detected between last and current read
            //virtual bool GamepadConnected() const;

            ////was a gamepad lost between last and current read
            //virtual bool GamepadDisconnected() const;
            //virtual void Destroy();
        };
    }
}