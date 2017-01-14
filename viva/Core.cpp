#include "viva.h"

namespace viva
{
    // Main viva object. Viva starts and ends here.
    class Core
    {
    public:
        // Initialize viva.
        // title: window title
        // size: size of the viewport
        // path: the default path,
        Core(const wstring& title, const Size& size, const wstring& path)
        {
            engine = new Win32Engine(title, size, path);
            engine->_Init();
        }

        // Destructor.
        ~Core()
        {
            engine->_Destroy();
        }
    };
}
