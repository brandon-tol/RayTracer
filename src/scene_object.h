#pragma once
#include "structures.h"

namespace RayTracer
{
    struct hit_record 
    {
        double t;
        vec3 p;
        vec3 normal;
    };

    class scene_object
    {    
    public:
        virtual ~scene_object() = default;
        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        
    };
} // namespace RayTracer
