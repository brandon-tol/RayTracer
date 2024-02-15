#pragma once
#include <memory>
#include "structures.h"

namespace RayTracer
{
    class viewport {
    private:
        int _m_width;
        int _m_height;
        std::vector<double> _m_pixels;
        size_t _m_pixel_index = 0;

    public:
        viewport(int width, int height)
            : _m_width(width), _m_height(height) 
            {
                _m_pixels = std::vector<double>(3 * resolution());
            }

        viewport(int height, double aspect_ratio)
            : _m_width(static_cast<int>(height * aspect_ratio)), _m_height(height)
            {
                _m_pixels = std::vector<double>(3 * resolution());
            }

        ~viewport() = default;

        int width() const { return _m_width; }
        int height() const { return _m_height; }
        double aspect_ratio() const { return static_cast<double>(_m_width) / _m_height; }
        int resolution() const { return _m_width * _m_height; }
        void set_pixel(int x, int y, color3 pixel) 
        {
            _m_pixel_index = 3 * (y * _m_width + x);
            _m_pixels[_m_pixel_index++] = pixel.x();
            _m_pixels[_m_pixel_index++] = pixel.y();
            _m_pixels[_m_pixel_index++] = pixel.z();
        }

        void set_next_pixel(color3 pixel)
        {
            _m_pixels[_m_pixel_index++] = (pixel.x());
            _m_pixels[_m_pixel_index++] = (pixel.y());
            _m_pixels[_m_pixel_index++] = (pixel.z());
        }

        std::vector<double> pixel_array() const { return _m_pixels; }
    };    
} // namespace RayTracer