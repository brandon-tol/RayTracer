#include "ray_tracer.h"
#include <simpleppm.h>
#include <iostream>

namespace RayTracer
{
    void ray_tracer::generate_viewport()
    {
        double delta_x = _m_eye.retina_width() / _m_viewport.width();
        double delta_y = _m_eye.retina_height() / _m_viewport.height();

        point3 p0 = _m_eye.point0();
        for (int j = 0; j < _m_viewport.height(); j++)
        {
            for (int i = 0; i < _m_viewport.width(); i++)
            {
                ray r(_m_eye.pupil(), _m_eye.pupil() - (p0 + i * delta_x * _m_eye.retina_u() + j * delta_y * _m_eye.retina_v()));
                _m_viewport.set_next_pixel(_m_scene.trace(r));
            }
        }
    }

    void ray_tracer::print_viewport() const
    {
        // int ctr = 3;
        // for(double x : _m_viewport.pixel_array())
        // {
        //     if(ctr-- <= 0)
        //     {
        //         std::cout << std::endl;
        //         ctr = 3;
        //     }
        //     std::cout << x << ' ' << std::endl;
        // }
        save_ppm("test.ppm", _m_viewport.pixel_array(), _m_viewport.width(), _m_viewport.height());
    }
} // namespace RayTracer
