#pragma once
#include "structures.h"
#include "eye.h"
#include "ray.h"
#include "scene_object.h"
#include <memory>

namespace RayTracer
{
    class scene : public scene_object
    {
    public:
        scene(eye eye): _m_eye(eye) {}
        ~scene() {}

        void add_object(std::shared_ptr<scene_object> object) { _m_objects.push_back(object); }

        const eye &get_eye() const { return _m_eye; }

        color3 trace(const ray& r) const;

        virtual bool on_hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    private:
        eye _m_eye;
        std::vector<std::shared_ptr<scene_object>> _m_objects;
    };
} // namespace RayTracer
