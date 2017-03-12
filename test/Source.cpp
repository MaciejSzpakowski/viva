#define STB_IMAGE_IMPLEMENTATION
#include "viva.h"
#pragma comment(lib,"viva.lib")

#include <vector>
#include <functional>
#include <cmath>
#include <string>

#define IMG_LEAF  L"./images/leaf.png"
#define IMG_BRICK L"./images/brick.jpg"
#define IMG_ANI   L"./images/ani.png"

int level = 1;
std::vector<std::function<void()>>* tests = nullptr;

void gameloop()
{
    viva::Animation* a = new viva::Animation();

    /*int levelold = level;

    if (viva::keyboard->IsKeyPressed(viva::Input::KeyboardKey::LeftBracket))
        level--;
    else if (viva::keyboard->IsKeyPressed(viva::Input::KeyboardKey::RightBracket))
        level++;

    if (levelold != level)
        viva::engine->Exit();*/
}

void testNotSharedVertexBuffer()
{
    viva::routineManager->AddRoutine([]()
    {
        std::vector<viva::Point> points({viva::Point(-1,-1), viva::Point(-1,1), 
            viva::Point(1,1), viva::Point(1,-1), viva::Point(-1,-1) });

        viva::Polygon* p = viva::drawManager->AddPolygon(points);
        p->T()->SetPosition(viva::util::RandomDouble() * 20 - 10, viva::util::RandomDouble() * 20 - 10);
        p->SetColor(0, 0, 0, 1);

        viva::routineManager->AddRoutine([=]()
        {
            p->Destroy();

            return 0;
        }, L"", 1, 0, 0);

        return 1;
    }, L"", 0, 0,0);
}

void testSpritesAndTextures()
{
    /*wstring msg = L"Test3: texture and sprites\n"
        "On the left, brick 200x200 in pixels (take a screenshot and check)\n"
        "On the right, red-green checkerboard 200x200\n"
        "In the middle, leaf in pink square (should be proportional)\n"
        "Press 1 to hide everything";
    text1->SetText(msg);*/

    viva::Sprite* s1 = viva::drawManager->AddSprite(IMG_BRICK);
    s1->SetPixelScale(200, 200)->T()->SetX(-10);

    std::vector<viva::Pixel> pixels;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            pixels.push_back(viva::Pixel(255 - 255 * ((i + j) % 2), 255 * ((i + j) % 2), 0, 255));
    viva::Texture* t1 = viva::creator->CreateTexture(pixels.data(), viva::Size(8, 8), L"checkerboard");

    viva::Sprite* s2 = viva::creator->CreateSprite(t1);
    viva::drawManager->Add(s2);
    s2->SetPixelScale(200, 200)->T()->SetX(10);

    viva::Sprite* s3 = viva::drawManager->AddSprite(IMG_LEAF);
    s3->SetScale2TextureSize()->T()->SetSize(0.5f);

    viva::Polygon* p1 = viva::drawManager->AddRectangle();
    p1->T()->SetSize(s3->T()->GetScale().X * 0.5f)->SetZ(-0.001f);
    p1->SetColor(viva::Color(1, 0, 1, 1));

    viva::routineManager->AddRoutine([=]
    {
        if (viva::keyboard->IsKeyDown(viva::Input::KeyboardKey::Key1))
        {
            //text1->SetVisible(false);
            s1->SetVisible(false);
            s2->SetVisible(false);
            s3->SetVisible(false);
            p1->SetVisible(false);
        }
        else
        {
            //text1->SetVisible(true);
            s1->SetVisible(true);
            s2->SetVisible(true);
            s3->SetVisible(true);
            p1->SetVisible(true);
        }
        return 1;
    }, L"", 0, 0, 0);
}

void testPolygonsAndColors()
{
    /*wstring msg = L"Test2: polygons and colors\n"
        "Red star on the left, blue rectangle in the middle, \nrainbow circle on the right";
    text1->SetText(msg);
    text1->SetVisible(true);*/

    std::vector<viva::Point> v;
    for (int i = 0; i < 10; i += 2)
    {
        v.push_back(viva::Point(sinf(0.31415f*i * 2), cosf(0.31415f*i * 2)));
        v.push_back(viva::Point(sinf(0.31415f*(i + 1) * 2) * 2, cosf(0.31415f*(i + 1) * 2) * 2));
    }
    v.push_back(*v.begin());
    viva::Polygon* p1 = viva::drawManager->AddPolygon(v);
    p1->T()->SetX(-10);
    p1->SetColor(viva::Color(1, 0, 0, 1));

    viva::Polygon* r1 = viva::drawManager->AddRectangle();
    r1->T()->SetScale(10, 3);
    r1->SetColor(viva::Color(0, 0, 1, 1));

    viva::Polygon* c1 = viva::drawManager->AddCircle();
    c1->T()->SetSize(2)->SetX(10);

    viva::routineManager->AddRoutine([c1]()
    {
        c1->SetColor(viva::Color(sinf(viva::time->GetGameTime()), cosf(viva::time->GetGameTime()*0.6), sinf(viva::time->GetGameTime() *0.5), 1));
        return 1;
    }, L"", 0, 0, 0);
}

void testInit()
{
    // coordinates

    viva::routineManager->AddRoutine([]()
    {
        viva::window->SetWindowTitle(std::to_wstring(viva::keyboard->IsKeyDown(viva::Input::KeyboardKey::RightBracket)));

        return 1;
    }, L"", 0, 0, 0);
}

int wrapper()
{
    while (true)
    {
        {
            viva::Core core(L"", { 800,600 }, L"");
            viva::engine->OpenConsole();
            viva::engine->SetBackgroundColor(viva::Color(1, 1, 1, 1));

            // add handlers
            viva::keyboard->OnKeyPressed([](viva::Input::KeyboardKey key)
            {
                int levelold = level;

                if (key == viva::Input::KeyboardKey::LeftBracket)
                {
                    level--;

                    if (level < 1)
                        level = 1;
                }
                else if (key == viva::Input::KeyboardKey::RightBracket)
                {
                    level++;

                    if (level > tests->size() - 1)
                        level = tests->size() - 1;
                }

                if (levelold != level)
                    viva::engine->Exit();
            });

            tests->at(level)();
            auto code = viva::engine->Run(gameloop);

            // if user clicked close then break
            if (code == viva::CloseReason::WindowClose)
                break;

        } // force viva destroy on exit

        /*printf("Exit ?\n");
        int c = getchar();
        if (c == 'y' || c == 'Y')
            break;*/
    }

    return 0;
}

int main(int argc, char** argv)
{
    try
    {
        std::vector<std::function<void()>> _tests;
        tests = &_tests;
        tests->push_back([]() {});
        tests->push_back(testInit);
        tests->push_back(testPolygonsAndColors);
        tests->push_back(testSpritesAndTextures);
        tests->push_back(testNotSharedVertexBuffer);

        wrapper();
    }
    catch (viva::Error& err)
    {
        printf("%s\n%s\n", err.function, err.what());
    }
    // these exceptions are hard to nail so dont catch, visual studio willshow me call stack
    /*catch (std::exception& err)
    {
        printf("%s\n", err.what());
    }*/

    return 0;
}