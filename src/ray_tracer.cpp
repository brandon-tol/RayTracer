#include "ray_tracer.h"
#include <simpleppm.h>
#include <iostream>

namespace RayTracer
{
    void ray_tracer::generate_viewport()
    {
        auto cam = _m_scene.get_eye();
        double delta_x = cam.retina_width() / _m_viewport.width();
        double delta_y = cam.retina_height() / _m_viewport.height();
        int ns = 100;

        point3 p0 = cam.point0();
        for (int j = 0; j < _m_viewport.height(); j++)
        {
            for (int i = 0; i < _m_viewport.width(); i++)
            {
                color3 partial_color(0, 0, 0);
                for (int s = 0; s < ns; s++)
                {
                    double x = i + drand48();
                    double y = j + drand48();
                    ray r(cam.pupil(), cam.pupil() - (p0 + x * delta_x * cam.retina_u() + y * delta_y * cam.retina_v()));
                    partial_color += _m_scene.trace(r);
                }
                _m_viewport.set_next_pixel(partial_color / double(ns));
                
            }
        }
    }

    void ray_tracer::print_viewport(const std::string target_filename) const
    {
        save_ppm(target_filename, _m_viewport.pixel_array(), _m_viewport.width(), _m_viewport.height());
    }
} // namespace RayTracer
