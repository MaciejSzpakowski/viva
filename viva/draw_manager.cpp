#include <viva/viva.h>

namespace viva
{
    DrawManager::DrawManager()
    {
        defaultSurface = creator->CreateSurface();
    }

    Polygon* DrawManager::AddPolygon(const vector<Point>& points, Surface* surface)
    {
        Polygon* p = creator->CreatePolygon(points);
        Add(p, surface);
        return p;
    }

    void DrawManager::Remove(IDrawable* drawable)
    {
        drawable->GetParent()->Remove(drawable);
    }

    void DrawManager::Add(IDrawable* drawable, Surface* surface)
    {
        if (surface == nullptr)
            surface = defaultSurface;

        surface->Add(drawable);
    }

    void DrawManager::_DrawNodes()
    {
        defaultSurface->_Draw();
    }

    void DrawManager::_DrawSurfaces()
    {
        defaultSurface->_DrawSurface();
    }

	void DrawManager::_Destroy()
	{
        Clear();
        defaultSurface->Destroy();
        delete this;
	}

    void DrawManager::Clear()
    {
        //defaultSurface->Clear();
    }

    Sprite* DrawManager::AddSprite(Texture* t, Surface* surface)
    {
        Sprite* s = creator->CreateSprite(t);
        Add(s, surface);
        return s;
    }

    Sprite* DrawManager::AddSprite(const wstring& filepath, Surface* surface)
    {
        Sprite* s = creator->CreateSprite(filepath);
        Add(s, surface);
        return s;
    }
}