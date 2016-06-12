#pragma once

namespace viva
{
    using std::vector;

    // Factory for all objects.
	class Creator
	{
	public:
		// Create pixel shader from file.
        // filepath: path to file containing pixel shader.
		virtual PixelShader* CreatePixelShader(const wstring& filepath) = 0;

		// Create pixel shader from string. This actually has to be ascii so wstring is not accepted.
        // str: pixel shader code itself
		virtual PixelShader* CreatePixelShader(const std::string& str) = 0;
        
		// Create texture from file.
		virtual Texture* CreateTexture(const wstring& filepath, bool cached) = 0;

		// Create texture from pixels.
        // pixels: pixels for the texture starting from left top
        // size: size of the image in pixels
        // name: some name, used by resource manager for caching
		virtual Texture* CreateTexture(const vector<Pixel>& pixels, const Size& size, const wstring& name = wstring(L"")) = 0;

		// create sprite from file
		//virtual Sprite* CreateSprite(const wstring& filepath) = 0;

		// Create sprite from texture.
        // texture: existing texture object
		virtual Sprite* CreateSprite(Texture* texture) = 0;

        // Create polygon from points.
        // points: vector of points where each point is x,y in world coordinates
        virtual Polygon* CreatePolygon(const vector<Point>& points) = 0;

        // Create surface to render objects on.
        virtual Surface* CreateSurface() = 0;
	};    
}