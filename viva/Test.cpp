#include "Viva.h"

#define CORE viva::Core::Get()
#define DRAW_MANAGER viva::DrawManager::Get()

void Activity()
{
}

int main()
{
	try
	{
		viva::Initialize(viva::EngineType::DirectX11, L"Hello", 800, 600);
		CORE.SetBackgroundColor(viva::Color(1.0f, 0, 0, 1));
		viva::Run(Activity);
		viva::Destroy();
	}
	catch (std::runtime_error e)
	{
		printf("%s\n", e.what());
	}
}