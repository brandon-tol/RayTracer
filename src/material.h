#pragma once

#include "core.h"
#include "ray.h"

namespace btoleda
{
    class material
    {
    public:
        inline material(const vec3 &ac, const vec3 &dc, const vec3 &sc, double ka, double kd, double ks, double pc, double reflectance = 0.0)
            : _m_ambient_color{ac}, _m_diffuse_color{dc}, _m_specular_color{sc}, _m_k_ambient{ka}, _m_k_diffuse{kd}, _m_k_specular{ks}, _m_pc{pc}, _m_reflectance{reflectance} {}

        inline const vec3 &ambient_color() const { return _m_ambient_color; }
        inline const vec3 &diffuse_color() const { return _m_diffuse_color; }
        inline const vec3 &specular_color() const { return _m_specular_color; }
        inline const double k_ambient() const { return _m_k_ambient; }
        inline const double k_diffuse() const { return _m_k_diffuse; }
        inline const double k_specular() const { return _m_k_specular; }
        inline const double pc() const { return _m_pc; }
        virtual const ray scatter(const point3 &impact, const vec3 &incident, const vec3 &normal) const;

    private:
        color3 _m_ambient_color;
        color3 _m_diffuse_color;
        color3 _m_specular_color;

        double _m_k_ambient;
        double _m_k_diffuse;
        double _m_k_specular;

        double _m_pc;
        double _m_reflectance;
    };
} // namespace btoleda
