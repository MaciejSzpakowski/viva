#include <viva/viva.h>
#pragma comment(lib,"viva.lib")

#define IMG_LEAF  L"C:/Users/Szpak/Documents/Visual Studio 2015/Projects/viva/viva/viva/images/leaf.png"
#define IMG_BRICK L"C:/Users/Szpak/Documents/Visual Studio 2015/Projects/viva/viva/viva/images/brick.jpg"
#define IMG_ANI   L"C:/Users/Szpak/Documents/Visual Studio 2015/Projects/viva/viva/viva/images/ani.png"
#define IMG_HEX   L"C:/bajery/bLeNdEr/tekstury/hex.tga"

void f()
{
}

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

            viva::routineManager->AddRoutine([=]()
            {
                p1->SetColor(1, 1, p1->GetColor().B ? 0 : 1, 1);

                return 1;
            }, L"", 0, 0, 1);

            int a = 0;
            viva::IRoutine* r = viva::routineManager->AddRoutine([&]()
            {
                a++;

                if (a > 1000)
                {
                    printf("remove\n");
                    r->Destroy();
                }

                return 1;
            });

            viva::Size t1size(256, 256);
            viva::Array<viva::Pixel> pixels((int)t1size.Width * (int)t1size.Height);
            for (int i = 0; i < t1size.Height ; i++)
                for (int j = 0; j < t1size.Width ; j++)
                    pixels[i * (int)t1size.Width + j] = { viva::byte(i), viva::byte(j), 0, 255 };
            auto t1 = viva::creator->CreateTexture(pixels, t1size, viva::wstring(L""));
            auto s1 = viva::drawManager->AddSprite(t1);
            s1->T()->SetRotation(viva::Math::Deg2Rad(45));
            s1->T()->SetSize(3);

            /*auto s2 = viva::drawManager->AddSprite(IMG_BRICK);
            s2->T()->SetPosition(-5, 4);
            s2->SetPixelScale({ 537,800 });*/

            auto s3 = viva::drawManager->AddSprite(IMG_HEX);
            s3->T()->SetPosition(5, -5);
            s3->SetPixelScale({ 512, 512 });
                        
            viva::engine->Run(f);
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