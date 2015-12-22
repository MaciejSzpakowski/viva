#pragma once

namespace viva
{
	class DrawManager
	{
	private:
		bool initialized;
		DrawManager() { initialized = false; }
		void ThrowUninitialized();

		RenderTarget* defaultRenderTarget;
		vector<RenderTarget*> renderTargets;
		//BitmapFont* defaultFont;
		TextureFilter defaultFilter;
		Matrix* renderTargetMatrix; // every render target has the same transform matrix
		Camera* camera;
	public:
		// cannot construct singleton
		DrawManager(DrawManager const&) = delete;

		//cannot assign to singleton
		void operator=(DrawManager const&) = delete;

		// get instance of Core singleton
		static DrawManager& Get();

		// initializes DrawManager object
		void Initialize(RenderTarget* _defaultRenderTarget);

		// completely destroys DrawManager object
		void Destroy();

		// DO I ACTUALLY NEED THIS ?
		void DrawAll(const Core& core);

		Camera* GetCamera() const { return camera; }

		void SetDefaultTextureFilter(TextureFilter filter) { defaultFilter = filter; }

		TextureFilter GetDefaultTextureFilter() const { return defaultFilter; }
	};
}
