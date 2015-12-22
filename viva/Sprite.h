#pragma once

namespace viva
{
	template <class Vector, class Matrix>
	class Sprite : public Drawable
	{
	protected:
		Texture* texture;
		TextureFilter filter;
	public:
		Sprite():Drawable( {}

		void SetFilterType(TextureFilter _filter) { filter = _filter; }

		TextureFilter GetFilterType() const { return filter; }

		Texture* GetTexture() const { return texture; }
	};

	template <class Vector, class Matrix>
	class Animation : public Sprite
	{
	protected:
	public:
	};
}