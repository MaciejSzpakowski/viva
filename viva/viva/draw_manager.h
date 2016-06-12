#pragma once

namespace viva
{
    // Wrapper for adding and removing drawables.
	class DrawManager
	{
	private:
		Surface* defaultRenderTarget;
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

        Polygon* AddPolygon(const vector<Point>& points);

        Sprite* AddSprite(Texture* t);
	};
}
