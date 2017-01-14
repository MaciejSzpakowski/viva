#include "viva.h"

namespace viva
{
    // 1000 MHP
    class Engine
    {
    protected:
        wstring defaultPath;
        Color backgroundColor;
        Size clientSize;

        // Internal gameloop.
        virtual void Activity() = 0;
    public:
        // Ctor.
        // path: used to load some resources
        // size: viewport size
        Engine(const std::wstring& path, const Size& size) 
            :backgroundColor(0, 0.25f, 0.5f, 1), defaultPath(path), clientSize(size) 
        {
        }

        // Post constructor.
        virtual void _Init() = 0;

        // Completely destroys engine.
        virtual void _Destroy() = 0;

        // Start engine (game loop).
        // gameloop: user's function called every frame
        virtual void Run(const std::function<void()>& gameloop = []() {}) = 0;

        // Get background color. Background color is the color being drawn if there's nothing there.
        const Color& GetBackgroundColor() const 
        { 
            return backgroundColor; 
        }

        // Set background color. Background color is the color being drawn if there's nothing there.
        // color: the color
        void SetBackgroundColor(const Color& color) 
        { 
            backgroundColor = color; 
        }

        // Get default path.
        const std::wstring& GetDefaultPath() const
        {
            return defaultPath;
        }

        // Get viewport/client size. Client is the drawing area in window.
        const Size& GetClientSize() const
        {
            return clientSize;
        }

        // Set default path.
        // path: the path
        void SetDefaultPath(const std::wstring& path)
        {
            defaultPath = path;
        }

        // Stop engine. Makes Run method return.
        virtual void Exit() = 0;

        // Open console in win32.
        virtual void OpenConsole() = 0;

        // Close console in win32.
        virtual void CloseConsole() = 0;
    };
}