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
        Transform transform;

        Surface* parent;
        uint index;
        bool visible;
    public:
        // Ctor.
        Sprite() : flipHorizontally(false), flipVertically(false), 
            uv(0, 0, 1, 1), filter(drawManager->GetDefaultTextureFilter()),
            parent(nullptr), index(-1), visible(true)
        {
        }

        // Get transform of the object.
        Transform* T() override
        {
            return &transform;
        }

        // Get transform of the object.
        Transform* GetTransform() override
        {
            return &transform;
        }

        // Set filter type.
        Sprite* SetTextureFilter(TextureFilter _filter) 
        { 
            filter = _filter; 
            return this;
        }

        // Get filter type.
        TextureFilter GetTextureFilter() const 
        { 
            return filter; 
        }

        // Set scale to match pixel size.
        // _size: desired size in pixels
        Sprite* SetPixelScale(const viva::Size& size)
        {
            Size frustum = camera->GetFrustumSize(transform.GetPosition().f.z);
            Size client = engine->GetClientSize();
            //Point unitsPerPixel = { frustum.Width / client.Width, frustum.Height / client.Height };
            //scale.x = unitsPerPixel.x * _size.width / 2;
            //scale.y = unitsPerPixel.y * _size.height / 2;

            transform.SetScale(frustum.Width / client.Width * size.Width / 2,
                frustum.Height / client.Height * size.Height / 2);

            return this;
        }

        // Set scale to match pixel size.
        // width: width in pixels
        // height: height in pixels
        Sprite* SetPixelScale(uint width, uint height)
        {
            return SetPixelScale(Size(width, height));
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

        Node* GetNode() override
        {
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
        //         0          
        //    +---------+     
        //    |         |     
        // 0  |         | 1    
        //    |         |      
        //    +---------+      
        //         1          
        Sprite* SetUV(const Rect& _uv)
        { 
            uv = _uv;
            return this;
        }

        // Set uv.
        Sprite* SetUV(float left, float top, float right, float bottom)
        {
            return SetUV(Rect(left, top, right, bottom));
        }

        // Get texture associated with this sprite. Sprites can share a texture.
        virtual Texture* GetTexture() = 0;

        Surface* GetSurface() const override
        {
            return parent;
        }

        bool IsVisible() const override
        {
            return visible;
        }

        Drawable* SetVisible(bool val) override
        {
            visible = val;
            return this;
        }

        void _SetSurface(Surface* surface) override
        {
            parent = surface;
        }

        void _SetIndex(uint i) override
        {
            index = i;
        }
         
        int _GetIndex() const override
        {
            return index;
        }
    };
}
