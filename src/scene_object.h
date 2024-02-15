#pragma once
#include "structures.h"
#include "ray.h"

namespace RayTracer
{
    struct hit_record 
    {
        double t;
        vec3 hit_pos;
        vec3 normal;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            front_face = r.direction().dot(outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };

    class scene_object
    {    
    public:
        virtual ~scene_object() = default;
        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        
    };
} // namespace RayTracer
