#pragma once

#include "i_hittable.h"
#include "material.h"
#include "ray.h"

namespace btoleda
{


    class scene_object : public i_hittable
    {
        protected:
        scene_object(const material& mat) : _m_material{mat} {};
        const material _m_material;
        
        public:
        virtual ~scene_object() = default;
        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    };
} // namespace btoleda