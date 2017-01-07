#pragma once

namespace viva
{
    // Wrapper for adding and removing drawables.
	class DrawManager
	{
	private:
        Sprite* defaultFont;
		Surface* defaultSurface;
		//vector<RenderTarget*> renderTargets;
		//BitmapFont* defaultFont;
		//TextureFilter defaultFilter;
		//Matrix* renderTargetMatrix; // every render target has the same transform matrix
	public:
        DrawManager();

		// Destroys DrawManager and all drawables.
		void _Destroy();

		//void SetDefaultTextureFilter(TextureFilter filter) { defaultFilter = filter; }

		//TextureFilter GetDefaultTextureFilter() const { return defaultFilter; }
        
        // Draw all objects on their surfaces.
        void _DrawNodes();

        // Draw surfaces.
        void _DrawSurfaces();

        // Create and add polygon to be drawn.
        // points: list of points
        Polygon* AddPolygon(const vector<Point>& points, Surface* surface = nullptr);

        // Create and add sprite to be drawn.
        // t: texture to be used by the sprite
        Sprite* AddSprite(Texture* t, Surface* surface = nullptr);

        // Create and add sprite to be drawn. Also, create texture if it doesnt exist.
        // filepath: file path of the image to be used by the texture
        Sprite* AddSprite(const wstring& filepath, Surface* surface = nullptr);

        void Remove(Drawable* drawable);

        void Add(Drawable* drawable, Surface* surface = nullptr);

        Sprite* GetDefaultFont() const
        {
            return defaultFont;
        }

        // Remove and destroy all surfaces and drawables except for default surface.
        void Clear();
	};
}
