#include <viva/viva.h>

namespace viva
{
    void Sprite::SetPixelScale(const viva::Size& _size)
    {
        Size frustum = camera->GetFrustumSize(transform.GetPosition().f.z);
        Size client = engine->GetClientSize();
        //Point unitsPerPixel = { frustum.Width / client.Width, frustum.Height / client.Height };
        //scale.x = unitsPerPixel.x * _size.width / 2;
        //scale.y = unitsPerPixel.y * _size.height / 2;
        transform.SetScale(frustum.Width / client.Width * _size.Width / 2,
            frustum.Height / client.Height * _size.Height / 2);
    }
}