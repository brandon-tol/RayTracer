#pragma once

#include "scene_object.h"

namespace RayTracer
{
    class sphere : public scene_object
    {
    public:
        sphere(point3 center, double radius)
            : _m_center(center), _m_radius(radius)
        {}

        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

        static vec3 random_in_unit_sphere();
    private:
        point3 _m_center;
        double _m_radius;
    };
} // namespace RayTracer

/*
double hit_sphere(const point3& center, double radius, const ray& r)
    {
        vec3 oc = r.origin() - center;
        auto a = r.direction().squaredNorm();
        auto b = 2.0 * oc.dot(r.direction());
        auto c = oc.squaredNorm() - radius * radius;
        auto discriminant = b * b - 4.0 * a * c;
        return discriminant <= 0 ? -1.0 : (-b - sqrt(discriminant)) / (2.0 * a);
    }

*/