#pragma once
#include "scene_light.h"
#include "area_light.h"

namespace btoleda
{
    class point_light : public scene_light
    {
    public:
        inline point_light(const Eigen::Vector3d &id, const Eigen::Vector3d &is, const point3 &center) : scene_light{id, is}, _m_center{center} {}
        inline point_light(const area_light &al) : scene_light{al.id(), al.is()}, _m_center{al.center()} {}
        inline point_light(const area_light &al, int i, int j) : scene_light{al.id() / al.n_squared(), al.is() / al.n_squared()}
        {
            vec3 u = al.u();
            vec3 v = al.v();
            _m_center = al.p0() + (i + 0.5) * u + (j + 0.5) * v;
        }
        inline const point3 &center() const { return _m_center; }

    private:
        point3 _m_center;
    };
} // namespace btoleda
