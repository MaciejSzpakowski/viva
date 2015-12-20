#pragma once

namespace viva
{
	class Drawable : public Dynamic
	{
	private:
		//RenderTarget* renderTarget;
	public:
		virtual void Draw() = 0;
	};
}