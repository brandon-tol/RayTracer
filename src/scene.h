#pragma once
#include "structures.h"

namespace RayTracer
{
    class scene
    {
    public:
        scene() {}

        static bool hits_sphere(const ray& r, const point3& center, double radius)
        {
            vec3 oc = r.origin() - center;
            auto a = r.direction().squaredNorm();
            auto half_b = oc.dot(r.direction());
            auto c = oc.squaredNorm() - radius * radius;
            auto discriminant = half_b * half_b - a * c;
            return discriminant > 0;
        }

        static color3 trace(const ray& r)
        {
            if (hits_sphere(r, point3(-10, 0, 5), 1.0))
            {
                return color3(1, 0, 0);
            }
            auto a = (r.direction().normalized().y() + 1.0) * 0.5;
            return (a * color3(0.5, 0.7, 1.0)) + ((1.0 - a) * color3(1.0, 1.0, 1.0));
        }
    };
} // namespace RayTracer
