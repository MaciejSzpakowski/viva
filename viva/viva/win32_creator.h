#pragma once

namespace viva
{
    class Win32Creator : public Creator
    {
    private:
        ID3D11Device* device;
        ID3D11DeviceContext* context;
    public:
        Win32Creator(ID3D11Device* _device, ID3D11DeviceContext* _context)
        {
            device = _device;
            context = _context;
        }

        Polygon* CreatePolygon(const vector<Point>& points) override;
    };
}