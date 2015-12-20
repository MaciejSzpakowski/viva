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

	class Animation : public Sprite
	{
	protected:
	public:
	};
}