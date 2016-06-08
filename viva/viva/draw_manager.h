#pragma once

namespace viva
{
	class DrawManager
	{
	private:
		//RenderTarget* defaultRenderTarget;
		//vector<RenderTarget*> renderTargets;
		//BitmapFont* defaultFont;
		//TextureFilter defaultFilter;
		//Matrix* renderTargetMatrix; // every render target has the same transform matrix
        Polygon* p;
	public:
        DrawManager();

		// completely destroys DrawManager object
		void Destroy();

		//void SetDefaultTextureFilter(TextureFilter filter) { defaultFilter = filter; }

		//TextureFilter GetDefaultTextureFilter() const { return defaultFilter; }

        Polygon* AddPolygon(const vector<Point>& points);

        Polygon* GetPolygon() const { return p; }
	};
}
