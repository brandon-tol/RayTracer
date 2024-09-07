#pragma once
#include "eye.h"
#include "ray.h"
#include "scene_object.h"
#include "scene_light.h"
#include <memory>

namespace btoleda
{

    class scene : public i_hittable
    {
    public:
        inline scene(const eye &e, const color3 &background_color) : _m_eye{e}, _m_background{background_color}, _m_objects{}, _m_lights{} {}
        inline scene() : _m_background{0.0, 0.0, 0.0} {}
        inline ~scene() = default;

        inline void add_object(std::shared_ptr<scene_object> object) { _m_objects.push_back(object); }
        inline void add_light(std::shared_ptr<scene_light> light) { _m_lights.push_back(light); }

        inline void set_eye(const eye &e) { _m_eye = e; }
        inline const eye &get_eye() const { return _m_eye; }

        inline void set_background(const color3 &c) { _m_background = c; }
        inline const color3 &get_background() const { return _m_background; }

        inline void set_ambient_intensity(const color3 &c) { _m_ambient_intensity = c; }
        inline const color3 &get_ambient_intensity() const { return _m_ambient_intensity; }

        const color3 trace(const ray &r, ray_tracer_parameters params) const;

        virtual bool on_hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    private:
        eye _m_eye;
        color3 _m_background;
        std::vector<std::shared_ptr<scene_object>> _m_objects;
        std::vector<std::shared_ptr<scene_light>> _m_lights;
        color3 _m_ambient_intensity;

        const color3 _get_color(const ray &r, color_type ct, bool twosiderender, bool usecenter) const;
        const color3 _path_trace(const ray &r, const int max_bounces_left, const double prob_terminate, bool twosiderender) const;
    };
} // namespace btoleda
