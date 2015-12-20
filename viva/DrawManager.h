#pragma once

namespace viva
{
	enum class TextFilterCreationMode
	{
		Point, Linear
	};

	class DrawManager
	{
	private:
		bool initialized;
		DrawManager() { initialized = false; }
		void ThrowUninitialized();

		Polygon* spriteMesh;  // polygon used by all sprites
		RenderTarget* defaultRenderTarget;
		vector<RenderTarget*> renderTargets;
		//BitmapFont* defaultFont;
		TextureSampler* pointSampler;
		TextureSampler* lineSampler;
		RasterizerState* wireframe;
		RasterizerState* solid;
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
		void Initialize();

		// completely destroys DrawManager object
		void Destroy();

		void DrawAll(const Core& core);

		Camera* GetCamera() const { return camera; }
	};
}
