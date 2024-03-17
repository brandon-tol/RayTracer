#pragma once

#include "scene_light.h"

namespace btoleda
{
    class area_light : public scene_light
    {
    private:
        point3 _m_p0;
        point3 _m_p1;
        point3 _m_p2;
        point3 _m_p3;
        unsigned int _m_num_samples_per_side;

    public:
        area_light(const point3 &p0, const point3 &p1, const point3 &p2, const point3 &p3, const color3 &id, const color3 &is, const unsigned int num_samples_per_side)
            : scene_light(id, is), _m_p0{p0}, _m_p1{p1}, _m_p2{p2}, _m_p3{p3}, _m_num_samples_per_side{num_samples_per_side} {}
        inline const point3 center() const
        {
            return (_m_p0 + _m_p1 + _m_p2 + _m_p3) / 4;
        }

        inline const unsigned int n() const
        {
            return _m_num_samples_per_side;
        }

        inline const unsigned int n_squared() const
        {
            return _m_num_samples_per_side * _m_num_samples_per_side;
        }

        inline const vec3 u() const
        {
            return (_m_p1 - _m_p0) / _m_num_samples_per_side;
        }

        inline const vec3 v() const
        {
            return (_m_p2 - _m_p1) / _m_num_samples_per_side;
        }

        inline const point3 p0() const
        {
            return _m_p0;
        }
    };
} // namespace btoleda
