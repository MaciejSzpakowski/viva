#pragma once

namespace viva
{
	class Drawable : public Dynamic
	{
	public:
		virtual void Draw() = 0;
	};
}