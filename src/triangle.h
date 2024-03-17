#pragma once

#include "scene_object.h"

namespace btoleda
{
    class triangle : public scene_object
    {
        public:
        inline triangle(point3 p0, point3 p1, point3 p2, material mat) : scene_object(mat), _m_p0(p0), _m_p1(p1), _m_p2(p2), _m_normal((p1 - p0).cross(p2 - p0).normalized()) 
        {
        }
        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        const vec3& normal() const { return _m_normal; }

        private:
        point3 _m_p0;
        point3 _m_p1;
        point3 _m_p2;
        vec3 _m_normal;
    };
} // namespace btoleda