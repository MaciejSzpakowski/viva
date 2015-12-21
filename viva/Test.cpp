#include "Viva.h"
#include <string>

#define CORE viva::Core::Get()
#define DRAW_MANAGER viva::DrawManager::Get()
#define CONSOLE viva::Core::Get().GetConsole()

void Activity()
{
}

int main()
{
	try
	{
		viva::Initialize(viva::EngineType::DirectX11, L"Hello", 800, 600);
		CONSOLE->Open();
		CONSOLE->Write(std::wstring(L"Hello"));
		CORE.SetBackgroundColor(viva::Color(1.0f, 0, 0, 1));
		viva::Run(Activity);
		viva::Destroy();
	}
	catch (std::runtime_error e)
	{
		printf("%s\n", e.what());
	}
}