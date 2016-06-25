#pragma once

namespace viva
{
    // Main viva object. Viva starts and ends here.
	class Core
	{
	public:
        // Initialize viva.
        // title: window title
        // size: size of the viewport
        // path: the default path, engine will look for default shaders there
        Core(const wstring& title, const Size& size, const wstring& path = L"");
        
        // Destructor.
        ~Core();
	};
}