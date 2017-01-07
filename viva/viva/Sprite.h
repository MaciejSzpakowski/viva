#pragma once

namespace viva
{
    // Drawable picture.
	class Sprite : public Node, public Drawable, public Colorable
	{
	protected:
		TextureFilter filter;
        Rect uv;
        bool flipHorizontally;
        bool flipVertically;
	public:
        // Ctor.
		Sprite():
            flipHorizontally(false), 
            flipVertically(false),
            uv(0, 1, 1, 0)
        {}

        // Set filter type.
		void SetFilterType(TextureFilter _filter) { filter = _filter; }

        // Get filter type.
		TextureFilter GetFilterType() const { return filter; }

        // Set scale to match pixel size.
        // _size: desired size in pixels
        void SetPixelScale(const viva::Size& _size);

        // Set scale to match texture size.
        void SetScale2TextureSize()
        {
            SetPixelScale(GetTexture()->GetSize());
        }

        // Is sprite flipped horizontally.
        bool IsFlippedHorizontally() const
        {
            return flipHorizontally;
        }

        // Set horizontal flip.
        // _flipHorizontally: flip or not
        void SetFlipHorizontally(bool _flipHorizontally)
        { 
            flipHorizontally = _flipHorizontally;
        }

        // Is sprite flipped vertically.
        bool IsFlippedVertically() const
        { 
            return flipVertically;
        }

        // Set vertical flip.
        // _flipVertically: flip or not
        void SetFlipVertically(bool _flipVertically)
        {
            flipVertically = _flipVertically;
        }

        // Get uv.
        const Rect& GetUV() const { return uv; }

        // Set uv.
        // _uv: new uv
        void SetUV(const Rect& _uv) { uv = _uv; }

        // Get texture associated with this sprite. Sprites can share a texture.
        virtual Texture* GetTexture() = 0;
	};
}