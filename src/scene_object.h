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
    };

    class scene_object
    {    
    public:
        virtual ~scene_object() = default;
        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        
    };
} // namespace RayTracer
