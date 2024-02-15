#pragma once
#include "structures.h"
#include "eye.h"
#include "ray.h"
#include "scene_object.h"

namespace RayTracer
{
    class scene : public scene_object
    {
    public:
        scene(eye eye, const scene_object** objects, size_t list_count): _m_eye(eye), _m_objects(objects), _m_list_count(list_count) {}
        ~scene() {}

        const eye &get_eye() const { return _m_eye; }

        color3 trace(const ray& r) const;

        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    private:
        eye _m_eye;
        const scene_object **_m_objects;
        size_t _m_list_count;
    };
} // namespace RayTracer
