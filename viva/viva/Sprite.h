#pragma once

namespace viva
{
	class Sprite : public Node, public IDrawable
	{
	protected:
		Texture* texture;
		TextureFilter filter;
	public:
		Sprite() {}

		void SetFilterType(TextureFilter _filter) { filter = _filter; }

		TextureFilter GetFilterType() const { return filter; }

		Texture* GetTexture() const { return texture; }
	};
}