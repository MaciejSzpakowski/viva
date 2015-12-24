#pragma once

namespace viva
{
	class DrawManager
	{
	private:
		TextureFilter defaultFilter;
		Camera* camera;
		bool initialized;
		DrawManager() { initialized = false; }
		void ThrowUninitialized();
	public:
		// cannot construct singleton
		DrawManager(DrawManager const&) = delete;

		//cannot assign to singleton
		void operator=(DrawManager const&) = delete;

		// get instance of Core singleton
		static DrawManager& Get();

		// initializes DrawManager object
		void Initialize(RenderTarget* _defaultRenderTarget);

		RenderTarget* defaultRenderTarget;
		vector<RenderTarget*> renderTargets;
		//CBitmapFont* zDefaultFont;
		
		void DrawAll(const Core& core);

		DrawManager();
		void Destroy();
		Polygon* AddPoly(XMFLOAT2 points[], int n,
			RenderTarget* target = nullptr);
		/*Rectangle* AddRect(float sizex, float sizey,
			CRenderTarget* target = nullptr);
		Circle* AddCircle(float radius, unsigned char resolution,
			CRenderTarget* target = nullptr);
		void AddPoly(CPolygon* p,
			CRenderTarget* target = nullptr);
		void RemovePoly(CPolygon* p);*/

		//add sprite from file
		//supported file formats: BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, EMF
		/*CSprite* AddSprite(LPCWSTR file,
			CRenderTarget* target = nullptr);*/

		/*void AddSprite(CSprite* s,
			CRenderTarget* target = nullptr);
		void RemoveSprite(CSprite* s);
		CAnimation* AddAnimation(LPCWSTR file, int x, int y,
			CRenderTarget* target = nullptr);
		void AddAnimation(CAnimation* a,
			CRenderTarget* target = nullptr);
		void RemoveAnimation(CAnimation* a);
		CBitmapFont* AddBitmapFont(LPCWSTR file, vector<Rect> chars);
		void AddBitmapFont(CBitmapFont* font);
		CBitmapFont* AddBitmapFont(LPCWSTR file, int width, int height, int charsPerRow);
		CBitmapText* AddBitmapText(CBitmapFont* font,
			CRenderTarget* target = nullptr);
		void AddBitmapText(CBitmapText* text,
			CRenderTarget* target = nullptr);
		void RemoveBitmapFont(CBitmapFont* font);
		void RemoveBitmapText(CBitmapText* text);
		CBitmapFont* GetDefaultFont();
		CRenderTarget* AddRenderTarget();
		void DestroyRenderTarget(CRenderTarget* target);
		void InitDefaultFont();*/

		//create extra buffer for PS
		//size in bytes must be multiple of 16
		//void CreateExtraBuffer(UINT size);

		////destroys all but default render target
		//void ClearRenderTargets();

		//TEX_FILTER TexFilterCreationMode;
		//bool SupressDuplicateWarning;
	};
}
