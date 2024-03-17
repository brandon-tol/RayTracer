#pragma once

#include "core.h"

namespace btoleda
{
    class ray
    {
    public:
        inline ray() {}
        inline ray(const point3 &origin, const vec3 &direction)
            : _m_origin{origin}, _m_direction{direction}
        {
        }

        inline const point3 &origin() const { return _m_origin; }
        inline const vec3 &direction() const { return _m_direction; }

        inline const point3 at(const double t) const
        {
            return _m_origin + t * _m_direction;
        }

    private:
        point3 _m_origin;
        vec3 _m_direction;
    };
} // namespace btoleda