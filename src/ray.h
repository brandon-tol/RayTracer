#pragma once

#include "structures.h"

namespace RayTracer {
    class ray 
    {
    public:
        ray() {}
        ray(const point3 origin, const vec3 direction)
            : _m_origin(origin), _m_direction(direction)
        {}

        point3 origin() const { return _m_origin; }
        vec3 direction() const { return _m_direction; }

        point3 at(double t) const {
            return _m_origin + t * _m_direction;
        }

    public:
        point3 _m_origin;
        vec3 _m_direction;
    };
} // namespace RayTracer