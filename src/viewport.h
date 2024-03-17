#pragma once
#include <memory>
#include "core.h"

namespace btoleda
{
    class viewport 
    {
    private:
        int _m_width;
        int _m_height;
        std::vector<double> _m_pixels;
        size_t _m_pixel_index = 0;

    public:
        inline viewport(int width, int height)
            : _m_width(width), _m_height(height) 
            {
                _m_pixels = std::vector<double>(3 * resolution());
            }

        inline viewport(int height, double aspect_ratio)
            : _m_width(static_cast<int>(height * aspect_ratio)), _m_height(height)
            {
                _m_pixels = std::vector<double>(3 * resolution());
            }

        inline ~viewport() = default;

        inline int width() const { return _m_width; }
        inline int height() const { return _m_height; }
        inline double aspect_ratio() const { return static_cast<double>(_m_width) / _m_height; }
        inline int resolution() const { return _m_width * _m_height; }
        inline void set_pixel(int x, int y, color3 pixel) 
        {
            _m_pixel_index = 3 * (y * _m_width + x);
            _m_pixels[_m_pixel_index++] = pixel.x();
            _m_pixels[_m_pixel_index++] = pixel.y();
            _m_pixels[_m_pixel_index++] = pixel.z();
        }

        inline void set_next_pixel(color3 pixel)
        {
            _m_pixels[_m_pixel_index++] = (pixel.x());
            _m_pixels[_m_pixel_index++] = (pixel.y());
            _m_pixels[_m_pixel_index++] = (pixel.z());
        }

        inline const std::vector<double>& pixel_array() const { return _m_pixels; }
    };    
} // namespace RayTracer