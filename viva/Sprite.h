#pragma once

namespace viva
{
	class Sprite : public Drawable
	{
	protected:
		Texture* texture;
	public:
		Sprite() {}
	};
}