#pragma once
#include "core.h"
#include "ray.h"
#include "material.h"

namespace btoleda
{
    struct hit_record
    {
        double t;
        point3 hit_pos;
        vec3 normal;
        const material *mat;
    };

    class i_hittable
    {
    protected:
        i_hittable() = default;

    public:
        virtual ~i_hittable() = default;
        virtual bool on_hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
    };
} // namespace RayTracer
