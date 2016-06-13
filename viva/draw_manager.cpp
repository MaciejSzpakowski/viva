#include <viva/viva.h>

namespace viva
{
    DrawManager::DrawManager()
    {
        defaultRenderTarget = creator->CreateSurface();
    }

    Polygon* DrawManager::AddPolygon(const vector<Point>& points)
    {
        Polygon* p = creator->CreatePolygon(points);
        defaultRenderTarget->Add(p);
        return p;
    }

    void DrawManager::_DrawNodes()
    {
        defaultRenderTarget->_DrawAll();
    }

    void DrawManager::_DrawSurfaces()
    {
        defaultRenderTarget->_Draw();
    }

	void DrawManager::_Destroy()
	{
        defaultRenderTarget->Destroy();
	}

    Sprite* DrawManager::AddSprite(Texture* t)
    {
        Sprite* s = creator->CreateSprite(t);
        defaultRenderTarget->Add(s);
        return s;
    }

    Sprite* DrawManager::AddSprite(const wstring& filepath)
    {
        Sprite* s = creator->CreateSprite(filepath);
        defaultRenderTarget->Add(s);
        return s;
    }
}