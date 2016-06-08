#include <viva/proto.h>

namespace viva
{
    DrawManager::DrawManager()
    {
    }

    Polygon* DrawManager::AddPolygon(const vector<Point>& points)
    {
        p = creator->CreatePolygon(points);

        return p;
    }

	void DrawManager::Destroy()
	{
	}
}