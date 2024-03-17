#pragma once

#include "scene_object.h"
#include "triangle.h"

namespace btoleda
{
    class rectangle : public scene_object
    {
        public:
        rectangle(const point3& p0, const point3& p1, const point3& p2, const point3& p3, const material& mat) : scene_object{mat}, _m_t1{p0, p1, p2, mat}, _m_t2{p0, p2, p3, mat} 
        {
        }
        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        const vec3& normal() const { return _m_t1.normal(); }

        private:
        const triangle _m_t1;
        const triangle _m_t2;

    };
} // namespace btoleda