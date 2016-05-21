#pragma once

namespace viva
{
	class RenderTarget
	{
	protected:
		vector<RenderTarget*>* parentContainer;
		PixelShader* pixelShader;
		vector<Polygon*> polygons;
		vector<Sprite*> sprites;
		//vector<BitmapText*> texts;

	public:
		RenderTarget() { parentContainer = nullptr; }

		// draw all objects that belong to the render target
		virtual void Draw() = 0;

		// move to the top of the stack
		void MoveToTop();

		// move to the bottom of the stack
		void MoveToBottom();

		// move one place up i.e. swap with one above
		void MoveUp();

		// move one place down i.e. swap with one below
		void MoveDown();

		// used by draw manager to insert
		void Insert(vector<RenderTarget*>* _parentContainer);

		// unsed by draw manager to remove
		void Remove();

		// dstroy the render target and all objects on it
		virtual void Destroy() = 0;
	};
}