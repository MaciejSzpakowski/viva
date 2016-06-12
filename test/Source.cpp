#include <viva/viva.h>
#pragma comment(lib,"viva.lib")

int wrapper()
{
    while (true)
    {
        {
            viva::Core core(L"Hello", { 800,600 }, L"C:/Users/Szpak/Documents/Visual Studio 2015/Projects/viva/viva/viva/resources/");
            viva::engine->OpenConsole();
            
            std::vector<viva::Point> v;
            v.push_back({ 0,0 });
            v.push_back({ 1,0 });
            v.push_back({ 0,1 });
            v.push_back({ 0,0 });
            auto p1 = viva::drawManager->AddPolygon(v);
            p1->SetColor(1, 0, 0, 1);
            auto p2 = viva::drawManager->AddPolygon(v);
            p2->SetColor(0, 1, 0, 1);
            auto p3 = viva::drawManager->AddPolygon(v);
            p3->SetColor(0, 0, 1, 1);
            p1->T()->SetPosition(5.0f, 5.0f);
            p2->T()->SetPosition(5.0f, 7.0f);
            p3->T()->SetPosition(5.0f, 9.0f);

            std::vector<viva::Pixel> pixels;
            for (int i = 0; i < 100; i++)
                for (int j = 0; j < 100; j++)
                    pixels.push_back(viva::Pixel(100 + i, 100 + j, 255, 255));
            auto t1 = viva::creator->CreateTexture(pixels, viva::Size(100, 100), viva::wstring(L""));
            auto s1 = viva::drawManager->AddSprite(t1);
            
            viva::engine->Run();
        }

        printf("Exit ?\n");
        int c = getchar();
        if (c == 'y' || c == 'Y')
            break;
    }

    return 0;
}

int main(int argc, char** argv)
{
    try
    {
        wrapper();
    }
    catch (viva::Error& err)
    {
        printf("%s\n%s\n", err.function, err.what());
    }

    return 0;
}