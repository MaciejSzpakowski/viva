#pragma once

namespace viva
{
    // Drawable picture.
	class Sprite : public Node, public IDrawable, public IColorable
	{
	protected:
		TextureFilter filter;
	public:
        // Ctor.
		Sprite() {}

        // Set filter type.
		void SetFilterType(TextureFilter _filter) { filter = _filter; }

        // Get filter type.
		TextureFilter GetFilterType() const { return filter; }

        // Get texture associated with this sprite. Sprites can share a texture.
        virtual Texture* GetTexture() = 0;
	};
}