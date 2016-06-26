#pragma once

namespace viva
{
    // Special drawable where all of its objects are drawn on it.
	class Surface
	{
	protected:
		//PixelShader* pixelShader;
		vector<IDrawable*> drawables;
		//vector<Sprite*> sprites;
		//vector<BitmapText*> texts;

	public:
        // Ctor.
        Surface() {  }

        // Insert drawable onto this surface.
        // d: drawable to add
        void Add(IDrawable* d);

        void Remove(IDrawable* d);

        // Draw all objects this surface contains.
        virtual void _DrawAll() = 0;

		// Draw surface itself.
		virtual void _Draw() = 0;

        // Get pixel shader.
        virtual PixelShader* GetPixelShader() const = 0;

        // Set pixel shader.
        // ps: ps
        virtual void SetPixelShader(PixelShader* ps) = 0;

		//// move to the top of the stack
		//void MoveToTop();

		//// move to the bottom of the stack
		//void MoveToBottom();

		//// move one place up i.e. swap with one above
		//void MoveUp();

		//// move one place down i.e. swap with one below
		//void MoveDown();

		//// used by draw manager to insert
		//void Insert(vector<RenderTarget*>* _parentContainer);

		// unsed by draw manager to remove
		////void Remove();

		// Destroy the surface and all drawables it contains.
		virtual void Destroy() = 0;
	};
}