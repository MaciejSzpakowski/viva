#include "viva.h"

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
        Sprite() : flipHorizontally(false), flipVertically(false), uv(0, 1, 1, 0)
        {
        }

        // Set filter type.
        Sprite* SetFilterType(TextureFilter _filter) 
        { 
            filter = _filter; 
            return this;
        }

        // Get filter type.
        TextureFilter GetFilterType() const 
        { 
            return filter; 
        }

        // Set scale to match pixel size.
        // _size: desired size in pixels
        Sprite* SetPixelScale(const viva::Size& _size)
        {
            Size frustum = camera->GetFrustumSize(transform.GetPosition().f.z);
            Size client = engine->GetClientSize();
            //Point unitsPerPixel = { frustum.Width / client.Width, frustum.Height / client.Height };
            //scale.x = unitsPerPixel.x * _size.width / 2;
            //scale.y = unitsPerPixel.y * _size.height / 2;

            transform.SetScale(frustum.Width / client.Width * _size.Width / 2,
                frustum.Height / client.Height * _size.Height / 2);

            return this;
        }

        // Set scale to match texture size.
        Sprite* SetScale2TextureSize()
        {
            SetPixelScale(GetTexture()->GetSize());
            return this;
        }

        // Is sprite flipped horizontally.
        bool IsFlippedHorizontally() const
        {
            return flipHorizontally;
        }

        // Set horizontal flip.
        // _flipHorizontally: flip or not
        Sprite* SetFlipHorizontally(bool _flipHorizontally)
        {
            flipHorizontally = _flipHorizontally;
            return this;
        }

        // Is sprite flipped vertically.
        bool IsFlippedVertically() const
        {
            return flipVertically;
        }

        // Set vertical flip.
        // _flipVertically: flip or not
        Sprite* SetFlipVertically(bool _flipVertically)
        {
            flipVertically = _flipVertically;
            return this;
        }

        // Get uv.
        const Rect& GetUV() const 
        { 
            return uv; 
        }

        // Get PS.
        virtual PixelShader* GetPixelShader() const = 0;

        //Set Ps.
        virtual Sprite* SetPixelShader(PixelShader* _ps) = 0;

        // Set uv.
        // _uv: new uv
        Sprite* SetUV(const Rect& _uv)
        { 
            uv = _uv;
            return this;
        }

        // Get texture associated with this sprite. Sprites can share a texture.
        virtual Texture* GetTexture() = 0;
    };
}
