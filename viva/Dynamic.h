#pragma once

namespace viva
{
	class Dynamic
	{
	protected:
		int index; // index in the parent container
	public:
		Dynamic():index(-1) {}

		virtual void Transform() = 0;
		
		virtual void Destroy() = 0;
	};
}