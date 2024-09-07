#include "ray_tracer.h"
#include <simpleppm.h>

namespace btoleda
{
    void ray_tracer::generate_viewport()
    {
        auto cam = _m_scene.get_eye();
        double delta_x = cam.retina_width() / _m_viewport.width();
        double delta_y = cam.retina_height() / _m_viewport.height();

        point3 p0 = cam.point0();
        int x = _m_params.raysperpixel[0];
        double x_ = 1.0 / x;
        int y = _m_params.raysperpixel[1];
        double y_ = 1.0 / y;
        int n = _m_params.raysperpixel[2];
        double n_ = 1.0 / n;

        for (int j = 0; j < _m_viewport.height(); j++)
        {
            for (int i = 0; i < _m_viewport.width(); i++)
            {
                // Per pixel
                color3 pixel_color{0.0, 0.0, 0.0};
                for (int k = 0; k < x; k++)
                {
                    for (int l = 0; l < y; l++)
                    {
                        for (int m = 0; m < n; m++)
                        {
                            double x_offset = n > 1 ? random_double() : 0.5;
                            double y_offset = n > 1 ? random_double() : 0.5;
                            ray r{cam.pupil(), (cam.pupil() - (p0 + (double(i) + (double(k) + x_offset) * x_) * delta_x * cam.retina_u() + (double(j) + (double(l) + y_offset) * y_) * delta_y * cam.retina_v())).normalized()};
                            pixel_color += _m_scene.trace(r, _m_params);
                        }
                    }
                }
                pixel_color *= n_ * y_ * x_;
                if (_m_params.globalillum)
                    pixel_color = pixel_color.array().pow(0.4); // Gamma correction
                _m_viewport.set_next_pixel(pixel_color);
            }
        }
    }

    void ray_tracer::print_viewport(const std::string &target_filename) const
    {
        save_ppm(target_filename, _m_viewport.pixel_array(), _m_viewport.width(), _m_viewport.height());
    }
} // namespace btoleda
